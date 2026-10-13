#include "AudioEngine.h"
#include <limits>
using namespace wtracks;
class ClickTimelineTests : public juce::UnitTest {
public:
    ClickTimelineTests() : juce::UnitTest("Click timeline", "Audio") {}
    void impulse(ClickTimeline& click) {
        for (int voice=0;voice<4;++voice) {
            click.sounds[voice].setSize(1,1); click.sounds[voice].setSample(0,0,float(voice+1));
        }
    }
    void runTest() override {
        beginTest("Absolute fractional events independent of block size and sample rate");
        for (double rate : {44100.0,48000.0}) for (int block : {64,256,1024}) {
            ClickTimeline click; impulse(click); click.bpm=137.25; click.offset=0.12345;
            click.soundRates.fill(rate); click.numerator=7; click.denominator=8; click.bpmUnit=4;
            click.gains.fill(1); juce::AudioBuffer<float> out(2,block);
            const long double tick=60.0L/click.bpm*rate*click.bpmUnit/click.denominator/4;
            const long double origin=click.offset*static_cast<long double>(rate);
            int event=0;
            for (int64_t position=0;position<rate*10;position+=block) {
                out.clear(); click.render(out,0,block,position,rate,true);
                for (int i=0;i<block;++i) if (out.getSample(0,i)!=0) {
                    expectEquals(position+i, static_cast<int64_t>(std::llround(origin+event*tick)));
                    const int sub=event%4;
                    const int voice=sub==0 ? ((event/4)%7==0 ? 0:1) : (sub==2?2:3);
                    expectWithinAbsoluteError(out.getSample(0,i),float(voice+1),0.0001f);
                    expectEquals(out.getSample(1,i),out.getSample(0,i)); ++event;
                }
            }
            expect(event>100);
            // One-hour positions: rounded integer-period implementations drift thousands of samples.
            click.reset(); const int64_t distantIndex=static_cast<int64_t>(rate*3600/tick);
            const int64_t target=std::llround(origin+distantIndex*tick);
            out.clear(); click.render(out,0,block,target-1,rate,true);
            expectEquals(out.getSample(0,0),0.0f); expect(out.getSample(0,1)>0);
        }
        beginTest("Mute preserves phase and seek before/on/after an event");
        ClickTimeline click; impulse(click); click.soundRates.fill(48000); click.gains.fill(1);
        juce::AudioBuffer<float> out(1,64);
        out.clear(); click.render(out,0,64,0,48000,false); expectEquals(out.getMagnitude(0,64),0.0f);
        out.clear(); click.render(out,0,64,24000,48000,true); expectEquals(out.getSample(0,0),2.0f);
        for (int delta : {-1,0,1}) {
            click.reset(); out.clear(); click.render(out,0,64,24000+delta,48000,true);
            if (delta<=0) expectEquals(out.getSample(0,-delta),2.0f);
            else expectEquals(out.getMagnitude(0,64),0.0f);
        }
        beginTest("Invalid parameters leave configuration unchanged and sampled loading errors are reported");
        AudioEngine engine;
        expect(engine.configureClick(137.25,7,8,4,0.2,1,1,0.5,0.25));
        expect(!engine.configureClick(std::numeric_limits<double>::quiet_NaN(),4,4,4,0,1,1,0,0));
        expect(!engine.configureClick(120,4,3,4,0,1,1,0,0));
        expect(!engine.configureClick(120,0,4,4,0,1,1,0,0));
        expect(!engine.configureClick(120,4,4,4,-1,1,1,0,0));
        expect(!engine.configureClick(120,4,4,4,0,1,1,3,0));
        expect(!engine.loadClickSound(4,"")); expect(!engine.loadClickSound(0,"/tmp/missing-click.wav"));
        expect(engine.loadClickSound(0,""));
        beginTest("Decoded WAV voice is rendered through AudioEngine and clearing restores synthesis");
        auto directory=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_click", "", false);
        directory.createDirectory();
        auto writeWav=[&](const juce::String& name, float firstSample, int length) {
            auto file=directory.getChildFile(name); juce::WavAudioFormat format;
            auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
            auto writer=std::unique_ptr<juce::AudioFormatWriter>(format.createWriterFor(stream.get(),48000,1,24,{},0));
            stream.release(); juce::AudioBuffer<float> data(1,length); data.clear(); data.setSample(0,0,firstSample);
            writer->writeFromAudioSampleBuffer(data,0,length); writer.reset(); return file;
        };
        auto track=writeWav("silence.wav",0,48000); auto pulse=writeWav("pulse.wav",0.75f,16);
        engine.prepareToPlay(64,48000); expect(engine.loadTrack("sample-test",{track}));
        expect(engine.configureClick(120,4,4,4,0,1,1,0,0));
        expect(engine.loadClickSound(0,pulse.getFullPathName())); engine.setClickEnabled(true); engine.play();
        out.clear(); juce::AudioSourceChannelInfo audio(&out,0,64); engine.getNextAudioBlock(audio);
        expectWithinAbsoluteError(out.getSample(0,0),0.75f,0.00001f);
        engine.stop(); expect(engine.loadClickSound(0,"")); engine.play(); out.clear(); engine.getNextAudioBlock(audio);
        expectEquals(out.getSample(0,0),0.0f); expect(out.getSample(0,1)>0);
        beginTest("Atomic four-voice bank retains every previous voice if one decode fails");
        std::array<juce::String,4> bank;
        for (int voice=0;voice<4;++voice) bank[voice]=writeWav("voice"+juce::String(voice)+".wav",0.1f*(voice+1),16).getFullPathName();
        expect(engine.loadClickBank(bank)); expect(engine.configureClick(120,4,4,4,0,1,1,1,1));
        const std::array<double,4> times {{0,0.5,0.25,0.125}};
        auto assertBank=[&]() {
            for (int voice=0;voice<4;++voice) {
                engine.seekToSeconds(times[voice]); engine.play(); out.clear(); engine.getNextAudioBlock(audio);
                expectWithinAbsoluteError(out.getSample(0,0),0.1f*(voice+1),0.00001f);
            }
        };
        assertBank(); auto broken=bank; broken[0]=pulse.getFullPathName(); broken[3]="/tmp/missing-bank-voice.wav";
        expect(!engine.loadClickBank(broken)); assertBank();
        beginTest("Device sample-rate migration preserves timeline seconds and click phase");
        engine.pause(); engine.prepareToPlay(64,44100); engine.seekToSeconds(0.5);
        engine.prepareToPlay(64,48000); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),0.5,1.0/48000);
        engine.play(); out.clear(); engine.getNextAudioBlock(audio);
        expectWithinAbsoluteError(out.getSample(0,0),0.2f,0.00001f);
        expect(engine.loadClickBank({{"","","",""}}));
        engine.stop(); engine.play(); out.clear(); engine.getNextAudioBlock(audio);
        expectEquals(out.getSample(0,0),0.0f); expect(out.getSample(0,1)>0);
        engine.unloadCurrentTrack(); out.clear(); engine.getNextAudioBlock(audio); expectEquals(out.getMagnitude(0,64),0.0f);
        directory.deleteRecursively();
        beginTest("Sampled voices resample and gain without per-block preparation");
        ClickTimeline sampled; sampled.sounds[0].setSize(1,2); sampled.sounds[0].setSample(0,0,1); sampled.sounds[0].setSample(0,1,0);
        sampled.soundRates[0]=24000; sampled.gains[0]=0.5; sampled.masterGain=0.5f;
        out.clear(); sampled.render(out,0,64,0,48000,true);
        expectWithinAbsoluteError(out.getSample(0,0),0.25f,0.00001f);
        expectWithinAbsoluteError(out.getSample(0,1),0.125f,0.00001f);
        sampled.reset(); out.clear(); sampled.render(out,0,64,1,48000,true);
        expectEquals(out.getMagnitude(0,64),0.0f);
    }
};
static ClickTimelineTests clickTimelineTests;
