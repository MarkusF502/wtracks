#pragma once
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>
#include "TimePitch.h"

namespace wtracks {
struct TimePitchResult {
    bool ok = false;
    bool cancelled = false;
    juce::String error;
};

// Renders `input` to a 32-bit float WAV at the same rate and channel count (stereo-or-less stems, 8 channels at most).
// The output appears atomically (temporary file + rename). Safe to call from several threads; it does not touch the engine.
// `token` identifies the call for cancelTimePitch(), which may arrive before or while the call runs.
TimePitchResult processTimePitchFile(const juce::File& input, const juce::File& output, const timepitch::Options& options, int64_t token);
void cancelTimePitch(int64_t token);

// Pico de memória estimado (bytes) de um trabalho. O processamento é por blocos (`timepitch::processStream`): por canal, o estado do
// vocoder, a região de overlap-add aberta e as janelas de entrada/intermediária de um bloco, mais o núcleo sinc. Não cresce com a
// duração (`frames` só limita o resultado). Limite superior grosso, usado só para o orçamento abaixo.
uint64_t estimateTimePitchBytes(int64_t frames, int channels, const timepitch::Options& options, double sampleRate = 192000);
// Orçamento global (bytes) somado entre os trabalhos simultâneos. Um trabalho que sozinho passa do orçamento roda quando for o
// único; os demais esperam (a espera respeita o cancelamento). Padrão 1 GiB; 0 restaura o padrão.
void setTimePitchMemoryBudget(uint64_t bytes);
// Para diagnóstico e testes: bytes reservados agora e o maior valor simultâneo já visto desde o último reset.
uint64_t timePitchReservedBytes();
uint64_t timePitchPeakReservedBytes(bool reset);
}
