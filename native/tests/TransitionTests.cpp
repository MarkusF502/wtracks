#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Overlap / Crossfade between two decks that share the device (Playback transitions 2 and 3, pseudocode/second-pass).
class TransitionTests : public juce::UnitTest {
public:
    TransitionTests() : juce::UnitTest("Song transitions (second deck)", "Audio") {}

    static juce::File writeDc(const juce::File& dir, const juce::String& name, int frames, float value) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(2,frames);
        for (int ch=0;ch<2;++ch) juce::FloatVectorOperations::fill(data.getWritePointer(ch),value,frames);
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }
    // A file whose value at time t is t / 10 (0.1 per second), to see where a song starts.
    static juce::File writeRamp(const juce::File& dir, const juce::String& name, int frames) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(2,frames);
        for (int ch=0;ch<2;++ch) for (int i=0;i<frames;++i) data.setSample(ch,i,static_cast<float>(i)/480000.0f);
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }
    // Renders through the device switch, as the audio device would.
    static std::vector<float> render(AudioEngine& engine, int total, int block) {
        std::vector<float> left(static_cast<size_t>(total),0.f);
        juce::AudioBuffer<float> out(2,block); int offset=0;
        while (offset<total) {
            const int count=juce::jmin(block,total-offset); juce::AudioSourceChannelInfo info(&out,0,count);
            engine.sharedIo()->deckSwitch.getNextAudioBlock(info);
            for (int i=0;i<count;++i) left[static_cast<size_t>(offset+i)]=out.getSample(0,i);
            offset+=count;
        }
        return left;
    }

    void runTest() override {
        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_transition","",false); dir.createDirectory();
        auto songA=writeDc(dir,"a.wav",4*48000,0.5f), songB=writeDc(dir,"b.wav",4*48000,0.25f);
        auto setup=[&](AudioEngine& a, AudioEngine& b, int block, const juce::File& fileB) {
            a.prepareToPlay(block,48000); b.prepareToPlay(block,48000);
            a.activate();
            expect(a.loadTrack("a",{songA})); expect(b.loadTrack("b",{fileB}));
        };

        beginTest("Crossfade: (1-t)^2 for the outgoing song, t^2 for the incoming one, sample-exact, any block size");
        for (int block : {64,500,1024}) {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,block,songB);
            expect(a.scheduleTransition(&b,TransitionKind::Crossfade,2.0,1.0)); expect(a.isTransitionScheduled());
            expectWithinAbsoluteError(a.getTransitionProgress(),-1.0,1e-9);
            a.play(); auto l=render(a,5*48000,block);
            expectWithinAbsoluteError(l[0],0.5f,1e-5f); expectWithinAbsoluteError(l[95999],0.5f,1e-5f);
            for (int k : {0,12000,24000,36000,47999}) {
                const double x=k/48000.0; const float expected=static_cast<float>(0.5*(1-x)*(1-x)+0.25*x*x);
                expectWithinAbsoluteError(l[static_cast<size_t>(96000+k)],expected,1e-4f);
            }
            expectWithinAbsoluteError(l[144000],0.25f,1e-5f);   // incoming alone at full level
            expectWithinAbsoluteError(l[191999],0.25f,1e-5f);
            expectWithinAbsoluteError(l[200000],0.25f,1e-5f);   // the old song has ended; the new one carries on
            expectWithinAbsoluteError(a.getTransitionProgress(),1.0,1e-9);
            const auto events=a.pollTransportEvents();
            expect((events & AudioEngine::TransitionStarted) != 0); expect((events & AudioEngine::TransitionFinished) != 0);
            expect((events & AudioEngine::EndReached) != 0);
            expectWithinAbsoluteError(b.getCurrentPositionSeconds(),5.0-2.0,1e-3);
        }

        beginTest("Overlap: both songs at full level, the outgoing one simply ends underneath; the window never passes the end");
        for (int block : {64,1000}) {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,block,songB);
            expect(a.scheduleTransition(&b,TransitionKind::Overlap,3.5,2.0));   // only 0.5 s are left
            a.play(); auto l=render(a,5*48000,block);
            expectWithinAbsoluteError(l[3*48000+24000-1],0.5f,1e-5f);
            expectWithinAbsoluteError(l[3*48000+24000],0.75f,1e-5f);
            expectWithinAbsoluteError(l[4*48000-1],0.75f,1e-5f);
            expectWithinAbsoluteError(l[4*48000+10],0.25f,1e-5f);
            expect((a.pollTransportEvents() & AudioEngine::TransitionFinished) != 0);
        }

        beginTest("Start right now; the outgoing click and guides are cut when the transition starts");
        {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,64,songB);
            a.setClickEnabled(true); a.setClickBpm(240); a.setClickGain(1.0f);
            a.play(); auto before=render(a,24000,64);
            float peak=0; for (float v : before) peak=juce::jmax(peak,std::abs(v)); expect(peak > 0.55f);   // the click rings over the DC
            expect(a.scheduleTransition(&b,TransitionKind::Overlap,-1.0,1.0));
            auto l=render(a,48000,64);
            for (size_t i=64;i<l.size();++i) if (std::abs(l[i]-0.75f) > 1e-4f) { expectWithinAbsoluteError(l[i],0.75f,1e-4f); break; }
        }

        beginTest("An active loop holds the transition; it starts once the loop is released, with the window shortened to the end");
        {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,64,songB);
            expect(a.setLoop(1.0,2.0,true)); expect(a.scheduleTransition(&b,TransitionKind::Overlap,1.5,1.0));
            a.play(); auto l=render(a,3*48000,64);
            expect((a.pollTransportEvents() & AudioEngine::TransitionStarted) == 0);
            expectWithinAbsoluteError(l[3*48000-1],0.5f,1e-5f);
            expect(a.setLoop(0,0,false)); l=render(a,48000,64);
            expect((a.pollTransportEvents() & AudioEngine::TransitionStarted) != 0);
        }

        beginTest("Cancel: armed does nothing, running stops the incoming song and restores the outgoing level");
        {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,64,songB);
            expect(a.scheduleTransition(&b,TransitionKind::Crossfade,2.0,1.0)); a.cancelTransition(); expect(!a.isTransitionScheduled());
            a.play(); auto l=render(a,3*48000,64); expectWithinAbsoluteError(l[3*48000-1],0.5f,1e-5f);
            expect(!b.isPlaying());
        }
        {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,64,songB);
            expect(a.scheduleTransition(&b,TransitionKind::Crossfade,0.5,2.0)); a.play(); render(a,48000,64);
            expect(b.isPlaying()); a.cancelTransition(); expect(!b.isPlaying());
            auto l=render(a,1000,64); expectWithinAbsoluteError(l[999],0.5f,1e-5f);
        }

        beginTest("Pause stops both songs and play resumes both; stop cancels the transition");
        {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,64,songB);
            expect(a.scheduleTransition(&b,TransitionKind::Overlap,0.5,2.0)); a.play(); render(a,48000,64);
            const double posB=b.getCurrentPositionSeconds(); a.pause(); expect(!b.isPlaying());
            auto silent=render(a,1000,64); expectEquals(silent[999],0.0f);
            expectWithinAbsoluteError(b.getCurrentPositionSeconds(),posB,1e-9);
            a.play(); expect(b.isPlaying()); auto l=render(a,1000,64); expectWithinAbsoluteError(l[999],0.75f,1e-5f);
            a.stop(); expect(!b.isPlaying()); expect(!a.isTransitionScheduled());
        }

        beginTest("The incoming song starts from its own start point");
        {
            auto ramp=writeRamp(dir,"ramp.wav",4*48000);
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,64,ramp);
            expect(b.setPlayRange(2.0,0)); expect(a.scheduleTransition(&b,TransitionKind::Overlap,1.0,1.0));
            a.play(); auto l=render(a,3*48000,64);
            expectWithinAbsoluteError(l[48000+10],0.5f+(2.0f+10/48000.0f)/10.0f,1e-4f);
        }

        beginTest("Hand-off: the incoming deck takes the device over without a gap and the old one is released");
        for (int block : {64,1000}) {
            AudioEngine a; AudioEngine b(a.sharedIo()); setup(a,b,block,songB);
            expect(a.scheduleTransition(&b,TransitionKind::Crossfade,2.0,1.0)); a.play();
            render(a,3*48000+100,block);
            expect((a.pollTransportEvents() & AudioEngine::TransitionFinished) != 0);
            const double posB=b.getCurrentPositionSeconds();
            b.activate(); a.finishTransitionAsOutgoing(); a.stop();
            expect(b.isActive()); expect(!a.isActive());
            auto l=render(b,48000,block);
            expectWithinAbsoluteError(l[0],0.25f,1e-5f); expectWithinAbsoluteError(l[47999],0.25f,1e-5f);
            expectWithinAbsoluteError(b.getCurrentPositionSeconds(),posB+1.0,1e-3);
            expect(b.isPlaying()); expect(!a.isPlaying());
        }

        beginTest("Validation");
        {
            AudioEngine a; AudioEngine b(a.sharedIo()); AudioEngine other;
            a.prepareToPlay(64,48000); b.prepareToPlay(64,48000);
            expect(a.loadTrack("a",{songA}));
            expect(!a.scheduleTransition(&b,TransitionKind::Overlap,1.0,1.0));      // b has no song
            expect(b.loadTrack("b",{songB}));
            expect(!a.scheduleTransition(nullptr,TransitionKind::Overlap,1.0,1.0));
            expect(!a.scheduleTransition(&a,TransitionKind::Overlap,1.0,1.0));
            expect(!a.scheduleTransition(&other,TransitionKind::Overlap,1.0,1.0));  // another device
            expect(!a.scheduleTransition(&b,TransitionKind::Overlap,1.0,0.0));
            expect(!a.scheduleTransition(&b,TransitionKind::Overlap,1.0,61.0));
            expect(a.scheduleTransition(&b,TransitionKind::Crossfade,1.0,5.0));
        }
        dir.deleteRecursively();
    }
} transitionTests;
