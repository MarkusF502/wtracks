#include "AudioEngine.h"
#include "RenderStats.h"
#include <thread>
#include <vector>
using namespace wtracks;

// Medição do callback (WT-06): contagem, máximo, percentis e estouros, sem contar o deck embutido de uma transição em dobro.
class RenderStatsTests : public juce::UnitTest {
public:
    RenderStatsTests() : juce::UnitTest("Render timing statistics", "Audio") {}

    static juce::File writeDc(const juce::File& dir, const juce::String& name, int frames, float value) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(2,frames);
        for (int ch=0;ch<2;++ch) juce::FloatVectorOperations::fill(data.getWritePointer(ch),value,frames);
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }

    void runTest() override {
        beginTest("Percentiles, maximum and overruns come from the recorded load");
        {
            RenderStats stats;
            const int64_t deadline=10'000'000;  // 10 ms
            expectEquals<uint64_t>(stats.snapshot().callbacks,0);
            for (int i=0;i<98;++i) stats.record(1'000'000,deadline);  // 10 % load
            stats.record(6'000'000,deadline);                          // 60 %
            stats.record(12'000'000,deadline);                         // 120 %: an overrun
            const auto s=stats.snapshot();
            expectEquals<uint64_t>(s.callbacks,100); expectEquals<uint64_t>(s.overruns,1);
            expectWithinAbsoluteError(s.maxMs,12.0,1e-9); expectWithinAbsoluteError(s.maxLoad,1.2,1e-6);
            expectWithinAbsoluteError(s.lastDeadlineMs,10.0,1e-9);
            expect(s.p50Load >= 0.10 && s.p50Load <= 0.10+1.0/RenderStats::kBuckets+1e-9);
            expect(s.p95Load <= 0.15);                                 // the 5 slow ones are above the 95th percentile
            expect(s.p99Load >= 0.60 && s.p99Load <= 0.60+1.0/RenderStats::kBuckets+1e-9);
            stats.reset(); expectEquals<uint64_t>(stats.snapshot().callbacks,0); expectEquals(stats.snapshot().maxMs,0.0);
            stats.record(1,0); expectEquals<uint64_t>(stats.snapshot().callbacks,0);  // no deadline, no sample
        }

        beginTest("The engine times each device callback once, including a transition's incoming deck");
        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_renderstats","",false); dir.createDirectory();
        auto songA=writeDc(dir,"a.wav",2*48000,0.5f), songB=writeDc(dir,"b.wav",2*48000,0.25f);
        AudioEngine a; AudioEngine b(a.sharedIo());
        a.prepareToPlay(480,48000); b.prepareToPlay(480,48000); a.activate();
        expect(a.loadTrack("a",{songA})); expect(b.loadTrack("b",{songB}));
        expect(a.scheduleTransition(&b,TransitionKind::Crossfade,0.5,0.5));
        a.resetRenderStats(); b.resetRenderStats();
        a.play();
        juce::AudioBuffer<float> out(2,480);
        for (int i=0;i<150;++i) { juce::AudioSourceChannelInfo info(&out,0,480); a.sharedIo()->deckSwitch.getNextAudioBlock(info); }
        const auto s=a.getRenderStats();
        expectEquals<uint64_t>(s.callbacks,150);
        expectEquals<uint64_t>(b.getRenderStats().callbacks,0);     // the incoming deck is part of the outgoing deck's callback
        expectWithinAbsoluteError(s.lastDeadlineMs,10.0,1e-6);
        expect(s.maxMs > 0.0);

        beginTest("Contention (WT-06): reloading songs while the callback runs keeps every callback inside its deadline in this scenario");
        {
            // 8 stems of 20 s so that releasing a song is real work; one thread plays the callback, another reloads in a loop.
            std::vector<juce::File> stems;
            for (int i=0;i<8;++i) stems.push_back(writeDc(dir,"stem"+juce::String(i)+".wav",20*48000,0.01f*static_cast<float>(i+1)));
            AudioEngine engine; engine.prepareToPlay(480,48000); engine.activate();
            expect(engine.loadTrack("s",stems)); engine.play();
            engine.resetRenderStats();
            std::atomic<bool> stop { false };
            std::thread audio([&] {
                juce::AudioBuffer<float> out(2,480);
                while (!stop.load()) {
                    juce::AudioSourceChannelInfo info(&out,0,480); engine.sharedIo()->deckSwitch.getNextAudioBlock(info);
                    juce::Thread::sleep(1);
                }
            });
            for (int i=0;i<12;++i) { expect(engine.loadTrack("s"+juce::String(i),stems)); engine.play(); }
            stop=true; audio.join();
            const auto s=engine.getRenderStats();
            logMessage("callbacks="+juce::String(static_cast<juce::int64>(s.callbacks))+" max="+juce::String(s.maxMs,3)+" ms p99load="+juce::String(s.p99Load,3)
                       +" overruns="+juce::String(static_cast<juce::int64>(s.overruns))+" deadline="+juce::String(s.lastDeadlineMs,2)+" ms");
            expect(s.callbacks > 0);
            expectEquals<uint64_t>(s.overruns,0);
        }
        dir.deleteRecursively();
    }
};

static RenderStatsTests renderStatsTests;
