#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Fade out and transport events. The curve and the pause afterwards are our own design (see FadeOut in MixerStage.h).
class FadeOutTests : public juce::UnitTest {
public:
    FadeOutTests() : juce::UnitTest("Fade out and transport events", "Audio") {}

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
        beginTest("FadeOut gains: linear manual fade, playhead-based end fade");
        {
            FadeOut f; expectEquals(f.gain(0),1.0f); f.start(4);
            expectEquals(f.gain(0),1.0f); expectEquals(f.gain(3),0.25f);
            expectEquals(FadeOut::endGain(0,100,0),1.0f); expectEquals(FadeOut::endGain(50,100,50),1.0f);
            expectEquals(FadeOut::endGain(75,100,50),0.5f); expectEquals(FadeOut::endGain(100,100,50),0.0f);
        }

        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_fade","",false); dir.createDirectory();
        auto dc=writeDc(dir,"dc.wav",4*48000,0.5f);
        auto start=[&](AudioEngine& engine,int block,int stems=1){
            engine.prepareToPlay(block,48000); std::vector<juce::File> files(static_cast<size_t>(stems),dc); expect(engine.loadTrack("fade",files)); };

        beginTest("Manual fade: linear over real samples, ends in a pause with a FadeFinished event, any block size");
        for (int block : {64,500,1024}) {
            AudioEngine engine; start(engine,block);
            expect(!engine.startFadeOut(1.0));  // not playing
            engine.play(); render(engine,4800,block);
            expect(engine.startFadeOut(0.5)); expectWithinAbsoluteError(engine.getFadeGain(),1.0,1e-9);
            auto l=render(engine,30000,block);
            expectWithinAbsoluteError(l[0],0.5f,1e-5f); expectWithinAbsoluteError(l[12000],0.25f,1e-5f);
            expectWithinAbsoluteError(l[23999],0.5f/24000,1e-5f); expectEquals(l[24000],0.0f); expectEquals(l[29999],0.0f);
            expect(!engine.isPlaying()); expect(engine.pollTransportEvents()==uint32_t(AudioEngine::FadeFinished));
            expect(engine.pollTransportEvents()==uint32_t(0)); expectWithinAbsoluteError(engine.getFadeGain(),-1.0,1e-9);
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),(4800+24000)/48000.0,1e-9);
            engine.play(); l=render(engine,1000,block); expectWithinAbsoluteError(l[999],0.5f,1e-5f);  // next play is at full level
        }

        beginTest("Excluded channels, click and guides; seek and pause cancel the fade");
        {
            AudioEngine engine; start(engine,64,2);
            engine.setChannelExcludedFromFade(1,true); engine.play();
            expect(engine.startFadeOut(1.0)); auto l=render(engine,24000,64);
            expectWithinAbsoluteError(l[23999],0.5f+0.5f*(24001/48000.0f),1e-4f);
            engine.seekToSeconds(1.0); expectWithinAbsoluteError(engine.getFadeGain(),-1.0,1e-9);
            l=render(engine,1000,64); expectWithinAbsoluteError(l[999],1.0f,1e-5f);
            expect(engine.startFadeOut(1.0)); engine.pause(); engine.play(); l=render(engine,1000,64);
            expectWithinAbsoluteError(l[999],1.0f,1e-5f);
        }

        beginTest("End fade follows the playhead over the last seconds; end of song raises EndReached");
        {
            AudioEngine engine; start(engine,64);
            expect(engine.setEndFade(1.0)); expect(!engine.setEndFade(-1)); expect(!engine.setEndFade(61));
            engine.seekToSeconds(2.5); engine.play(); auto l=render(engine,96000,64);
            expectWithinAbsoluteError(l[0],0.5f,1e-5f); expectWithinAbsoluteError(l[24000],0.5f,1e-5f);
            expectWithinAbsoluteError(l[48000],0.25f,1e-4f); expectEquals(l[72000],0.0f);
            expect(!engine.isPlaying()); expect(engine.pollTransportEvents()==uint32_t(AudioEngine::EndReached));
            expect(engine.loadTrack("again",{dc})); engine.seekToSeconds(3.5); engine.play(); l=render(engine,1000,64);
            expectWithinAbsoluteError(l[999],0.5f,1e-5f);  // a new song starts without end fade
        }

        beginTest("Fade during a pre-roll count-in pauses at once");
        {
            AudioEngine engine; start(engine,64);
            const double at=0.0; const char* none[1]={nullptr};
            expect(engine.configurePreroll(true,&at,1,none,0)); engine.play(); expect(engine.isPrerolling());
            expect(engine.startFadeOut(5.0)); expect(!engine.isPlaying()); expect(!engine.isPrerolling());
            expect(engine.pollTransportEvents()==uint32_t(AudioEngine::FadeFinished));
        }
        dir.deleteRecursively();
    }
} fadeOutTests;
