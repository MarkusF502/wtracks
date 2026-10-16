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

        beginTest("Explicit click times (MultiTracks): exact samples and voices for any block size, seek, and no grid clicks");
        for (int block : {1,64,1000}) {
            ClickTimeline fixed; impulse(fixed); fixed.soundRates.fill(48000); fixed.gains.fill(1);  // the grid alone would click at 0
            fixed.events={{100,0},{1000,1},{1500,2},{1600,3},{1600,1}};
            std::vector<std::pair<int64_t,float>> heard;
            juce::AudioBuffer<float> o(1,block);
            for (int64_t position=0;position<2000;position+=block) {
                o.clear(); fixed.render(o,0,block,position,48000,true);
                for (int i=0;i<block;++i) if (o.getSample(0,i)!=0) heard.push_back({position+i,o.getSample(0,i)});
            }
            expectEquals<int>(static_cast<int>(heard.size()),4,"block "+juce::String(block));
            if (heard.size()==4) {
                expectEquals<int64_t>(heard[0].first,100); expectWithinAbsoluteError(heard[0].second,1.0f,1e-5f);
                expectEquals<int64_t>(heard[1].first,1000); expectWithinAbsoluteError(heard[1].second,2.0f,1e-5f);
                expectEquals<int64_t>(heard[2].first,1500); expectWithinAbsoluteError(heard[2].second,3.0f,1e-5f);
                expectEquals<int64_t>(heard[3].first,1600); expectWithinAbsoluteError(heard[3].second,4.0f+2.0f,1e-5f);  // two voices at once
            }
            for (int64_t delta : {-1,0,1}) {  // seek before, on and after an event
                juce::AudioBuffer<float> one(1,4); one.clear(); fixed.render(one,0,4,1000+delta,48000,true);
                if (delta<=0) expectWithinAbsoluteError(one.getSample(0,static_cast<int>(-delta)),2.0f,1e-5f);
                else expectEquals(one.getMagnitude(0,4),0.0f);
            }
        }

        beginTest("Engine: explicit click times follow the time scale and the device rate, are validated, and a new song drops them");
        {
            auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_click_times","",false);
            dir.createDirectory();
            auto wav=[&](const juce::String& name, float first, int length) {
                auto file=dir.getChildFile(name); juce::WavAudioFormat format;
                auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
                auto writer=std::unique_ptr<juce::AudioFormatWriter>(format.createWriterFor(stream.get(),48000,1,24,{},0));
                stream.release(); juce::AudioBuffer<float> data(1,length); data.clear(); data.setSample(0,0,first);
                writer->writeFromAudioSampleBuffer(data,0,length); writer.reset(); return file;
            };
            AudioEngine e; e.prepareToPlay(64,48000);
            auto silence=wav("silence.wav",0,4*48000);
            std::array<juce::String,4> voices;
            for (int v=0;v<4;++v) voices[v]=wav("v"+juce::String(v)+".wav",0.1f*(v+1),1).getFullPathName();
            expect(e.loadTrack("t",{silence})); expect(e.loadClickBank(voices)); expect(e.configureClick(120,4,4,4,0,1,1,1,1));
            e.setClickEnabled(true);
            const double times[3]={0.25,1.0,1.0}; const uint8_t kinds[3]={2,0,1};
            expect(e.setClickTimes(times,kinds,3));
            juce::AudioBuffer<float> o(2,64);
            // Samples rendered after seeking to `seconds` (song time) until the first click, and its value.
            const auto firstClickAfter=[&](double seconds, int64_t limit) -> std::pair<int64_t,float> {
                e.seekToSeconds(seconds); e.play();
                const int64_t start=0;
                for (int64_t done=0;done<limit;done+=64) {
                    o.clear(); juce::AudioSourceChannelInfo info(&o,0,64); e.getNextAudioBlock(info);
                    for (int i=0;i<64;++i) if (std::fabs(o.getSample(0,i))>1e-6f) { e.pause(); return {start+done+i,o.getSample(0,i)}; }
                }
                e.pause(); return {-1,0.f};
            };
            auto hit=firstClickAfter(0,48000);
            expectEquals<int64_t>(hit.first,12000); expectWithinAbsoluteError(hit.second,0.3f,1e-5f);  // eighth voice; no grid click at 0
            hit=firstClickAfter(0.5,48000);
            expectEquals<int64_t>(hit.first,24000); expectWithinAbsoluteError(hit.second,0.1f+0.2f,1e-5f);  // accent and quarter together

            expect(e.setTimeScale(2.0));  // processed audio twice as long: 0.1 s of song time is 0.2 s of processed timeline
            hit=firstClickAfter(0.9,96000);
            expectEquals<int64_t>(hit.first,9600);
            expect(e.setTimeScale(1.0));

            e.prepareToPlay(64,44100);  // device rate changes: same song seconds
            hit=firstClickAfter(0.5,44100);
            expectEquals<int64_t>(hit.first,22050);
            e.prepareToPlay(64,48000);

            const double bad[2]={1.0,0.5}; const uint8_t badKinds[2]={0,0}; const uint8_t badVoice[1]={4};
            const double nan[1]={std::numeric_limits<double>::quiet_NaN()};
            expect(!e.setClickTimes(bad,badKinds,2)); expect(!e.setClickTimes(times,badVoice,1)); expect(!e.setClickTimes(nan,badKinds,1));
            expect(!e.setClickTimes(nullptr,nullptr,1));
            hit=firstClickAfter(0,48000);
            expectEquals<int64_t>(hit.first,12000,"a refused list keeps the previous one");

            expect(e.loadTrack("t2",{silence})); expect(e.configureClick(120,4,4,4,0,1,1,1,1));
            hit=firstClickAfter(0,4800);
            expectEquals<int64_t>(hit.first,0,"a new song is back on the tempo grid");
            expect(e.setClickTimes(times,kinds,3)); expect(e.setClickTimes(nullptr,nullptr,0));
            hit=firstClickAfter(0,4800);
            expectEquals<int64_t>(hit.first,0,"count 0 returns to the grid");
            e.unloadCurrentTrack();
            dir.deleteRecursively();
        }
    }
};
static ClickTimelineTests clickTimelineTests;
