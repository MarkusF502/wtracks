#include "../include/TimePitchFile.h"
#include "../include/ffi_bridge.h"
#include "../include/AudioEngine.h"
#include "../include/WaveformExtractor.h"
#include <cstring>
#include <memory>
#include <mutex>
#include <vector>

// The per-deck functions live in ffi_deck_api.inc, compiled once per deck.
#define WT_CAT_(a, b) a##b
#define WT_CAT(a, b) WT_CAT_(a, b)

#if defined(__ANDROID__)
#include <jni.h>
#include <juce_core/juce_core.h>
#include <juce_core/native/juce_JNIHelpers_android.h>

extern "C" JNIEXPORT void JNICALL
Java_com_example_flutter_1app_MainActivity_initJuceContext(JNIEnv *env, jobject thiz, jobject context) {
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    juce::JNIClassBase::initialiseAllClasses(env, context);
    juce::Thread::initialiseJUCE(env, context);
}
#endif

// Two decks: [0] is the song that plays (the device calls it), [1] holds the next song during a transition. The hand-off swaps them,
// so the Dart side keeps talking to deck 0 (`wtracks_*`) for the song that plays and to deck 1 (`wtracks_n_*`) for the preloaded one.
static std::unique_ptr<wtracks::AudioEngine> decks[2];
// An isolated click decoder must finish before its owning engine is destroyed.
static std::mutex engineLifetimeMutex;

extern "C" {

bool wtracks_initialise(int sampleRate, int bufferSize)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    decks[1].reset();
    decks[0] = std::make_unique<wtracks::AudioEngine>();
    return decks[0]->initialise(sampleRate, bufferSize);
}

void wtracks_shutdown()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (decks[0]) decks[0]->cancelTransition();
    if (decks[1]) decks[1]->shutdown();   // the second deck only lets go of its song
    decks[1].reset();
    if (decks[0])
        decks[0]->shutdown();
    decks[0].reset();
}

// ---- Second deck and song transitions ----
bool wtracks_prepare_next_deck()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!decks[0]) return false;
    if (!decks[1]) decks[1] = std::make_unique<wtracks::AudioEngine>(decks[0]->sharedIo());
    return true;
}

void wtracks_release_next_deck()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (decks[0]) decks[0]->cancelTransition();
    decks[1].reset();
}

bool wtracks_schedule_transition(int kind, double startSeconds, double durationSeconds)
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!decks[0] || !decks[1]) return false;
    return decks[0]->scheduleTransition(decks[1].get(), kind == 1 ? wtracks::TransitionKind::Crossfade : wtracks::TransitionKind::Overlap,
                                        startSeconds, durationSeconds);
}

void wtracks_cancel_transition()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (decks[0]) decks[0]->cancelTransition();
}

double wtracks_get_transition_progress() { return decks[0] ? decks[0]->getTransitionProgress() : -1.0; }
bool wtracks_is_transition_scheduled() { return decks[0] && decks[0]->isTransitionScheduled(); }

// The incoming song takes the device over and becomes deck 0; the old one is released, stopped and kept as deck 1 (unload it).
bool wtracks_handoff()
{
    const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
    if (!decks[0] || !decks[1] || !decks[1]->isPlaying()) return false;
    decks[1]->activate();
    decks[0]->finishTransitionAsOutgoing();
    decks[0]->stop();
    std::swap(decks[0], decks[1]);
    return true;
}

bool wtracks_process_time_pitch(const char* inputPath, const char* outputPath, double timeFactor, double pitchFactor, bool complexAlgorithm, int64_t token)
{
    if (!inputPath || !outputPath) return false;
    wtracks::TimePitchResult result;
    try {
        result = wtracks::processTimePitchFile(juce::File(juce::String::fromUTF8(inputPath)), juce::File(juce::String::fromUTF8(outputPath)),
                                               {timeFactor, pitchFactor, complexAlgorithm}, token);
    } catch (...) { result.error = "Time/pitch processing failed"; }
    if (!result.ok) {
        const std::lock_guard<std::mutex> lock(engineLifetimeMutex);
        if (decks[0]) decks[0]->setLastError(wtracks::EngineErrorCode::Unknown, result.error);
    }
    return result.ok;
}

void wtracks_cancel_time_pitch(int64_t token) { wtracks::cancelTimePitch(token); }
void wtracks_set_time_pitch_memory_budget(uint64_t bytes) { wtracks::setTimePitchMemoryBudget(bytes); }

int wtracks_midi_list_outputs(char* buffer, int capacity)
{
    const auto text = wtracks::AudioEngine::listMidiOutputs().joinIntoString("\n") + "\n";
    const auto utf8 = text.toStdString();
    const int needed = static_cast<int>(utf8.size()) + 1;
    if (buffer && capacity >= needed) std::memcpy(buffer, utf8.c_str(), static_cast<size_t>(needed));
    return needed;
}

int wtracks_midi_list_inputs(char* buffer, int capacity)
{
    const auto text = wtracks::AudioEngine::listMidiInputs().joinIntoString("\n") + "\n";
    const auto utf8 = text.toStdString();
    const int needed = static_cast<int>(utf8.size()) + 1;
    if (buffer && capacity >= needed) std::memcpy(buffer, utf8.c_str(), static_cast<size_t>(needed));
    return needed;
}

bool wtracks_generate_waveform_peaks(const char** channelPaths, int channelCount, int numBuckets, float* outPeaks)
{
    try {
        std::vector<juce::File> files;
        for (int i = 0; i < channelCount; ++i) {
            const char* p = channelPaths[i];
            juce::String s = p != nullptr ? juce::String(juce::CharPointer_UTF8(p)) : juce::String();
            files.emplace_back(s);
        }
        return wtracks::extractWaveformPeaks(files, numBuckets, outPeaks);
    } catch (...) {
        return false;
    }
}

#define WT_DECK 0
#define WT(name) WT_CAT(wtracks_, name)
#define ENGINE decks[WT_DECK]
#include "ffi_deck_api.inc"
#undef WT
#undef ENGINE
#undef WT_DECK

#define WT_DECK 1
#define WT(name) WT_CAT(wtracks_n_, name)
#define ENGINE decks[WT_DECK]
#include "ffi_deck_api.inc"
#undef WT
#undef ENGINE
#undef WT_DECK

} // extern "C"
