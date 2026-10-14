#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Transport fade as an on/off switch (Playback: the fade button does not pause; see FadeRamp in MixerStage.h).
class FadeOutTests : public juce::UnitTest {
public:
    FadeOutTests() : juce::UnitTest("Transport fade (on/off)", "Audio") {}

    static juce::File writeDc(const juce::File& dir, const juce::String& name, int frames, float value) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(2,frames);
        for (int ch=0;ch<2;++ch) juce::FloatVectorOperations::fill(data.getWritePointer(ch),value,frames);
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }
    static std::vector<float> render(AudioEngine& engine, int total, int block) {
        std::vector<float> left(static_cast<size_t>(total),0.f);
        juce::AudioBuffer<float> out(2,block); int offset=0;
        while (offset<total) {
            const int count=juce::jmin(block,total-offset); juce::AudioSourceChannelInfo info(&out,0,count);
            engine.getNextAudioBlock(info);
            for (int i=0;i<count;++i) left[static_cast<size_t>(offset+i)]=out.getSample(0,i);
            offset+=count;
        }
        return left;
    }

    void runTest() override {
        beginTest("FadeRamp: linear down, back up from the current level, jump, reset");
        {
            FadeRamp f; expect(f.idle()); expectEquals(f.next(),1.0f);
            f.ramp(true,4); expect(f.down()); expect(f.active());
            expectEquals(f.next(),1.0f); expectEquals(f.next(),0.75f); expectEquals(f.next(),0.5f); expectEquals(f.next(),0.25f);
            expectEquals(f.gain,0.0f); expect(!f.active()); expect(f.down()); expect(!f.idle());
            f.ramp(false,4); expectEquals(f.next(),0.0f); expectEquals(f.next(),0.25f);
            f.ramp(true,2);  // reversed halfway: from 0.5 to 0 over 2 samples
            expectEquals(f.next(),0.5f); expectEquals(f.next(),0.25f); expectEquals(f.gain,0.0f);
            f.jump(false); expect(f.idle()); f.jump(true); expectEquals(f.gain,0.0f); f.reset(); expect(f.idle());
        }

        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_fade","",false); dir.createDirectory();
        auto dc=writeDc(dir,"dc.wav",4*48000,0.5f);
        auto start=[&](AudioEngine& engine,int block,int stems=1){
            engine.prepareToPlay(block,48000); std::vector<juce::File> files(static_cast<size_t>(stems),dc); expect(engine.loadTrack("fade",files)); };

        beginTest("Fade on/off: linear over real samples, the song keeps playing and no event is raised, any block size");
        for (int block : {64,500,1024}) {
            AudioEngine engine; start(engine,block);
            expect(!engine.setFade(true,0.0)); expect(!engine.setFade(true,61));
            engine.play(); render(engine,4800,block);
            expect(engine.setFade(true,0.5)); expect(engine.isFadeDown());
            auto l=render(engine,36000,block);
            expectWithinAbsoluteError(l[0],0.5f,1e-5f); expectWithinAbsoluteError(l[12000],0.25f,1e-5f);
            expectWithinAbsoluteError(l[23999],0.5f/24000,1e-5f); expectEquals(l[24000],0.0f); expectEquals(l[35999],0.0f);
            expect(engine.isPlaying()); expect(engine.pollTransportEvents()==uint32_t(0));
            expectWithinAbsoluteError(engine.getFadeGain(),0.0,1e-9); expect(engine.isFadeDown());
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),(4800+36000)/48000.0,1e-9);
            expect(engine.setFade(false,0.5)); expect(!engine.isFadeDown());
            l=render(engine,24000,block);
            expectEquals(l[0],0.0f); expectWithinAbsoluteError(l[12000],0.25f,1e-5f); expectWithinAbsoluteError(l[23999],0.5f-0.5f/24000,1e-5f);
            l=render(engine,100,block); expectWithinAbsoluteError(l[0],0.5f,1e-5f); expectWithinAbsoluteError(engine.getFadeGain(),1.0,1e-9);
        }

        beginTest("Reversing in the middle starts from the current level; pause and seek keep the level; stop restores it");
        {
            AudioEngine engine; start(engine,64);
            engine.play(); expect(engine.setFade(true,1.0)); render(engine,24000,64);          // half way down
            expectWithinAbsoluteError(engine.getFadeGain(),0.5,1e-4);
            expect(engine.setFade(false,1.0)); auto l=render(engine,12000,64);
            expectWithinAbsoluteError(l[0],0.25f,1e-4f); expectWithinAbsoluteError(l[11999],0.5f*(0.5f+0.5f*11999/48000.0f),1e-4f);
            expect(engine.setFade(true,1.0)); render(engine,48000,64); expectWithinAbsoluteError(engine.getFadeGain(),0.0,1e-9);
            engine.pause(); expect(engine.isFadeDown()); engine.seekToSeconds(1.0); expect(engine.isFadeDown());
            engine.play(); l=render(engine,100,64); expectEquals(l[99],0.0f);
            engine.stop(); expectWithinAbsoluteError(engine.getFadeGain(),1.0,1e-9); expect(!engine.isFadeDown());
            engine.play(); l=render(engine,2000,64); expectWithinAbsoluteError(l[1999],0.5f,1e-5f);   // after the 20 ms channel ramp
        }

        beginTest("Stopped: the fade applies at once; a new song starts at full level");
        {
            AudioEngine engine; start(engine,64);
            expect(engine.setFade(true,5.0)); expect(engine.isFadeDown()); expectWithinAbsoluteError(engine.getFadeGain(),0.0,1e-9);
            engine.play(); auto l=render(engine,100,64); expectEquals(l[99],0.0f);
            expect(engine.setFade(false,0.05)); l=render(engine,4000,64); expectWithinAbsoluteError(l[3999],0.5f,1e-5f);
            expect(engine.setFade(true,5.0)); expect(engine.loadTrack("again",{dc}));
            expectWithinAbsoluteError(engine.getFadeGain(),1.0,1e-9); expect(!engine.isFadeDown());
        }

        beginTest("Excluded channels fade not; click and guides never fade");
        {
            AudioEngine engine; start(engine,64,2);
            engine.setChannelExcludedFromFade(1,true); engine.play();
            expect(engine.setFade(true,1.0)); auto l=render(engine,24000,64);
            expectWithinAbsoluteError(l[23999],0.5f+0.5f*(1-23999/48000.0f),1e-4f);
            engine.setClickEnabled(true); engine.setClickBpm(120); engine.setClickGain(1.0f);
            expect(engine.setFade(true,0.05)); render(engine,48000,64);   // everything else is silent now
            double peak=0; auto tail=render(engine,24000,64); (void) tail;
            engine.setChannelExcludedFromFade(1,false); tail=render(engine,24000,64);
            for (float v : tail) peak=juce::jmax(peak,static_cast<double>(std::abs(v)));
            expect(peak > 0.01);   // the click rings through the faded mix
        }

        beginTest("End fade starts the fade 'fadeSeconds' before the end, keeps playing and ends with EndReached");
        for (int block : {64,1000}) {
            AudioEngine engine; start(engine,block);
            expect(engine.setEndFade(1.0)); expect(!engine.setEndFade(-1)); expect(!engine.setEndFade(61));
            engine.seekToSeconds(2.5); engine.play(); auto l=render(engine,96000,block);
            expectWithinAbsoluteError(l[0],0.5f,1e-5f); expectWithinAbsoluteError(l[23999],0.5f,1e-5f);
            expectWithinAbsoluteError(l[48000],0.25f,1e-4f); expectEquals(l[72000],0.0f);   // the song ended at 4 s (sample 72000)
            expect(!engine.isPlaying());
            expect(engine.pollTransportEvents()==uint32_t(AudioEngine::EndReached));
            expect(engine.isFadeDown());                       // the button stays on until return to zero / stop
            engine.resetTransportState(); expect(!engine.isFadeDown()); expectWithinAbsoluteError(engine.getFadeGain(),1.0,1e-9);
            // Inside the last second the fade starts at once; a fade already on is left alone; a new song has none.
            engine.seekToSeconds(3.5); engine.play(); render(engine,10,block);
            expect(engine.isFadeDown());
            expect(engine.loadTrack("again",{dc})); engine.seekToSeconds(3.5); engine.play(); l=render(engine,1000,64);
            expectWithinAbsoluteError(l[999],0.5f,1e-5f);
        }

        beginTest("Fade during a pre-roll count-in applies at once and keeps the transport running");
        {
            AudioEngine engine; start(engine,64);
            const double at=0.0; const char* none[1]={nullptr};
            expect(engine.configurePreroll(true,&at,1,none,0)); engine.play(); expect(engine.isPrerolling());
            expect(engine.setFade(true,5.0)); expect(engine.isPlaying()); expect(engine.isPrerolling());
            expectWithinAbsoluteError(engine.getFadeGain(),0.0,1e-9);
            expect(engine.pollTransportEvents()==uint32_t(0));
        }

        beginTest("Return to zero: drops live and queued loops and the fade, but not the transport state");
        {
            AudioEngine engine; start(engine,64);
            expect(engine.setLoop(1.0,2.0,true)); expect(engine.enqueueLoop(2.0,3.0));
            engine.play(); expect(engine.setFade(true,5.0)); render(engine,4800,64);
            engine.resetTransportState();
            expect(!engine.getLoopEnabled()); expect(!engine.getQueuedLoopEnabled()); expect(engine.isPlaying());
            expect(!engine.isFadeDown()); expectWithinAbsoluteError(engine.getFadeGain(),1.0,1e-9);
        }
        dir.deleteRecursively();
    }
} fadeOutTests;
