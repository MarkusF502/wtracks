#include "AudioEngine.h"
#include <thread>
using namespace wtracks;
class ReadAheadTests : public juce::UnitTest {
public:
    ReadAheadTests() : juce::UnitTest("Read ahead transport", "Audio") {}
    void runTest() override {
        auto directory=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_read_ahead","",false);
        directory.createDirectory();
        auto write=[&](const juce::String& name, double rate, double duration, int channels) {
            auto file=directory.getChildFile(name); juce::WavAudioFormat format;
            auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
            auto writer=std::unique_ptr<juce::AudioFormatWriter>(format.createWriterFor(stream.get(),rate,channels,24,{},0)); stream.release();
            juce::AudioBuffer<float> data(channels,static_cast<int>(duration*rate));
            for(int ch=0;ch<channels;++ch) juce::FloatVectorOperations::fill(data.getWritePointer(ch),0.2f*(ch+1),data.getNumSamples());
            writer->writeFromAudioSampleBuffer(data,0,data.getNumSamples()); writer.reset(); return file;
        };
        beginTest("Oversized host blocks are chunked; EOF and click clamp exactly inside block");
        auto shortTrack=write("short.wav",44100,0.1,2);
        AudioEngine engine; engine.prepareToPlay(64,48000); expect(engine.loadTrack("short",{shortTrack}));
        engine.setClickEnabled(true); engine.setClickOffsetSeconds(0.1); engine.play();
        juce::AudioBuffer<float> output(2,5010); juce::FloatVectorOperations::fill(output.getWritePointer(0),0.8f,5010);
        juce::AudioSourceChannelInfo host(&output,5,5000); expect(engine.waitForReadAhead(64,1000)); engine.getNextAudioBlock(host);
        expectEquals(engine.getUnderrunCount(),uint64_t(0)); expect(!engine.isPlaying());
        expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),0.1,1.0/48000);
        expectWithinAbsoluteError(output.getSample(0,0),0.8f,0.00001f);
        expectWithinAbsoluteError(output.getSample(0,5005),0.8f,0.00001f);
        expect(output.getRMSLevel(0,105,4600)>0.15f); expect(output.getRMSLevel(1,105,4600)>0.3f);
        expectEquals(output.getMagnitude(0,4805,200),0.0f); expectEquals(output.getMagnitude(1,4805,200),0.0f);
        beginTest("Seek prefill and pause/resume keep source and master positions aligned");
        auto longTrack=write("long.wav",44100,8,1); expect(engine.loadTrack("long",{longTrack})); engine.setClickEnabled(false);
        engine.seekToSeconds(5.25); expect(engine.waitForReadAhead(64,1000)); engine.play();
        juce::AudioBuffer<float> block(2,64); juce::AudioSourceChannelInfo info(&block,0,64); engine.getNextAudioBlock(info);
        expect(block.getRMSLevel(0,0,64)>0.05f); expectEquals(block.getSample(0,32),block.getSample(1,32));
        const double previous=engine.getCurrentPositionSeconds(); engine.pause(); engine.getNextAudioBlock(info);
        expectEquals(block.getMagnitude(0,64),0.0f); expectEquals(engine.getCurrentPositionSeconds(),previous);
        engine.play(); engine.getNextAudioBlock(info); expect(engine.getCurrentPositionSeconds()>previous);
        beginTest("Source/device rate migration and backwards seek remain ready");
        engine.prepareToPlay(256,44100); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),previous+64.0/48000,1.0/44100);
        engine.seekToSeconds(0.25); expect(engine.waitForReadAhead(256,1000)); engine.getNextAudioBlock(info);
        expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),0.25+64.0/44100,1.0/44100);
        beginTest("Concurrent rendering and prepared seeks complete without deadlock");
        std::atomic<bool> finished {false};
        std::thread renderer([&] { juce::AudioBuffer<float> data(2,64); juce::AudioSourceChannelInfo audio(&data,0,64);
            while(!finished.load()) engine.getNextAudioBlock(audio); });
        for(int i=0;i<8;++i) { engine.seekToSeconds(i*0.125); engine.play(); engine.setChannelVolume(0,0.5f); engine.setChannelMuted(0,false); }
        engine.pause(); finished=true; renderer.join();
        expect(std::isfinite(engine.getCurrentPositionSeconds())); expect(engine.getCurrentPositionSeconds()<=8);
        expect(engine.waitForReadAhead(64,1000));
        logMessage("Underrun count under render/seek contention: "+juce::String(engine.getUnderrunCount()));
        engine.unloadCurrentTrack(); directory.deleteRecursively();
    }
};
static ReadAheadTests readAheadTests;
