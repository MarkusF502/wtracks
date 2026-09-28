#pragma once

#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>
#include <vector>

namespace wtracks
{

// Lê os arquivos em channelFiles, mixa (soma simples, depois normaliza pelo
// pico global) e preenche outPeaks (já alocado pelo chamador, com
// numBuckets elementos) com valores 0.0..1.0. Retorna false se algum
// arquivo não puder ser lido (formato inválido/corrompido) -- nesse caso
// outPeaks não deve ser considerado válido pelo chamador.
//
// Função livre e sem estado compartilhado com o AudioEngine: usa seu
// próprio juce::AudioFormatManager local, então pode rodar concorrentemente
// enquanto o AudioEngine singleton está tocando outra música.
bool extractWaveformPeaks(const std::vector<juce::File>& channelFiles,
                           int numBuckets,
                           float* outPeaks);

} // namespace wtracks
