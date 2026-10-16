package com.example.flutter_app

import android.media.AudioFormat
import android.media.MediaCodec
import android.media.MediaExtractor
import android.media.MediaFormat
import java.io.File
import java.io.RandomAccessFile
import java.nio.ByteBuffer
import java.nio.ByteOrder

internal object MultiTracksAudioDecoder {
    private const val dequeueTimeoutUs = 10_000L
    private const val maximumWaveDataBytes = 1_500_000_000L

    fun decodeM4aToWav(input: File, output: File) {
        require(input.isFile && input.length() > 0L) { "M4A de entrada inválido" }
        output.parentFile?.mkdirs()
        val partial = File("${output.absolutePath}.part")
        if (partial.exists()) partial.delete()

        val extractor = MediaExtractor()
        var codec: MediaCodec? = null
        try {
            extractor.setDataSource(input.absolutePath)
            val trackIndex = (0 until extractor.trackCount).firstOrNull { index ->
                extractor.getTrackFormat(index).getString(MediaFormat.KEY_MIME)?.startsWith("audio/") == true
            } ?: throw IllegalArgumentException("M4A sem faixa de áudio")
            extractor.selectTrack(trackIndex)
            val sourceFormat = extractor.getTrackFormat(trackIndex)
            val mime = sourceFormat.getString(MediaFormat.KEY_MIME)
                ?: throw IllegalArgumentException("Codec AAC ausente")
            sourceFormat.setInteger(MediaFormat.KEY_PCM_ENCODING, AudioFormat.ENCODING_PCM_16BIT)
            codec = MediaCodec.createDecoderByType(mime).apply {
                configure(sourceFormat, null, null, 0)
                start()
            }

            RandomAccessFile(partial, "rw").use { wave ->
                wave.setLength(0)
                wave.write(ByteArray(44))
                var sampleRate = sourceFormat.getInteger(MediaFormat.KEY_SAMPLE_RATE)
                var channelCount = sourceFormat.getInteger(MediaFormat.KEY_CHANNEL_COUNT)
                var pcmEncoding = AudioFormat.ENCODING_PCM_16BIT
                var inputEnded = false
                var outputEnded = false
                var dataBytes = 0L
                val bufferInfo = MediaCodec.BufferInfo()

                while (!outputEnded) {
                    if (!inputEnded) {
                        val inputIndex = codec.dequeueInputBuffer(dequeueTimeoutUs)
                        if (inputIndex >= 0) {
                            val inputBuffer = codec.getInputBuffer(inputIndex)
                                ?: throw IllegalStateException("Buffer AAC indisponível")
                            val sampleSize = extractor.readSampleData(inputBuffer, 0)
                            if (sampleSize < 0) {
                                codec.queueInputBuffer(
                                    inputIndex,
                                    0,
                                    0,
                                    0,
                                    MediaCodec.BUFFER_FLAG_END_OF_STREAM,
                                )
                                inputEnded = true
                            } else {
                                codec.queueInputBuffer(
                                    inputIndex,
                                    0,
                                    sampleSize,
                                    extractor.sampleTime.coerceAtLeast(0L),
                                    0,
                                )
                                extractor.advance()
                            }
                        }
                    }

                    when (val outputIndex = codec.dequeueOutputBuffer(bufferInfo, dequeueTimeoutUs)) {
                        MediaCodec.INFO_OUTPUT_FORMAT_CHANGED -> {
                            val decodedFormat = codec.outputFormat
                            sampleRate = decodedFormat.getInteger(MediaFormat.KEY_SAMPLE_RATE)
                            channelCount = decodedFormat.getInteger(MediaFormat.KEY_CHANNEL_COUNT)
                            pcmEncoding = if (decodedFormat.containsKey(MediaFormat.KEY_PCM_ENCODING)) {
                                decodedFormat.getInteger(MediaFormat.KEY_PCM_ENCODING)
                            } else {
                                AudioFormat.ENCODING_PCM_16BIT
                            }
                        }
                        MediaCodec.INFO_TRY_AGAIN_LATER -> Unit
                        else -> if (outputIndex >= 0) {
                            val outputBuffer = codec.getOutputBuffer(outputIndex)
                                ?: throw IllegalStateException("PCM decodificado indisponível")
                            if (bufferInfo.size > 0) {
                                outputBuffer.position(bufferInfo.offset)
                                outputBuffer.limit(bufferInfo.offset + bufferInfo.size)
                                val pcm16 = asPcm16(outputBuffer.slice(), pcmEncoding)
                                dataBytes += pcm16.size
                                if (dataBytes > maximumWaveDataBytes) {
                                    throw IllegalArgumentException("Áudio decodificado excede o limite")
                                }
                                wave.write(pcm16)
                            }
                            outputEnded = bufferInfo.flags and MediaCodec.BUFFER_FLAG_END_OF_STREAM != 0
                            codec.releaseOutputBuffer(outputIndex, false)
                        }
                    }
                }
                require(sampleRate in 8_000..192_000) { "Sample rate inválido" }
                require(channelCount in 1..8) { "Número de canais inválido" }
                require(dataBytes > 0L) { "Decoder AAC não produziu áudio" }
                writeWaveHeader(wave, sampleRate, channelCount, dataBytes)
                wave.fd.sync()
            }
            if (output.exists() && !output.delete()) {
                throw IllegalStateException("Não foi possível substituir WAV anterior")
            }
            if (!partial.renameTo(output)) {
                throw IllegalStateException("Não foi possível publicar WAV")
            }
        } finally {
            try {
                codec?.stop()
            } catch (_: Exception) {
            }
            codec?.release()
            extractor.release()
            if (partial.exists()) partial.delete()
        }
    }

    private fun asPcm16(buffer: ByteBuffer, encoding: Int): ByteArray = when (encoding) {
        AudioFormat.ENCODING_PCM_16BIT -> ByteArray(buffer.remaining()).also(buffer::get)
        AudioFormat.ENCODING_PCM_FLOAT -> {
            buffer.order(ByteOrder.nativeOrder())
            val output = ByteBuffer.allocate((buffer.remaining() / 4) * 2).order(ByteOrder.LITTLE_ENDIAN)
            while (buffer.remaining() >= 4) {
                val sample = buffer.float.coerceIn(-1f, 1f)
                output.putShort((sample * 32767f).toInt().toShort())
            }
            output.array()
        }
        AudioFormat.ENCODING_PCM_8BIT -> {
            val output = ByteBuffer.allocate(buffer.remaining() * 2).order(ByteOrder.LITTLE_ENDIAN)
            while (buffer.hasRemaining()) {
                output.putShort(((buffer.get().toInt() and 0xff) - 128 shl 8).toShort())
            }
            output.array()
        }
        else -> throw IllegalArgumentException("Formato PCM Android não suportado: $encoding")
    }

    private fun writeWaveHeader(
        file: RandomAccessFile,
        sampleRate: Int,
        channels: Int,
        dataBytes: Long,
    ) {
        require(dataBytes <= Int.MAX_VALUE - 36L) { "WAV excede o limite RIFF" }
        val byteRate = sampleRate * channels * 2
        val header = ByteBuffer.allocate(44).order(ByteOrder.LITTLE_ENDIAN).apply {
            put("RIFF".toByteArray(Charsets.US_ASCII))
            putInt((36L + dataBytes).toInt())
            put("WAVE".toByteArray(Charsets.US_ASCII))
            put("fmt ".toByteArray(Charsets.US_ASCII))
            putInt(16)
            putShort(1)
            putShort(channels.toShort())
            putInt(sampleRate)
            putInt(byteRate)
            putShort((channels * 2).toShort())
            putShort(16)
            put("data".toByteArray(Charsets.US_ASCII))
            putInt(dataBytes.toInt())
        }
        file.seek(0)
        file.write(header.array())
    }
}
