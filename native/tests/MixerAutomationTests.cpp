#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Mixer automation: own design (see MixerAutomation.h); these tests pin the contract.
class MixerAutomationTests : public juce::UnitTest {
public:
    MixerAutomationTests() : juce::UnitTest("Mixer automation", "Audio") {}

    using P = MixerAutomation::Point;
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
    static bool apply(AudioEngine& engine, const std::vector<P>& points) {
        std::vector<double> s, e; std::vector<int> p; std::vector<float> v;
        for (const auto& x : points) { s.push_back(x.start); e.push_back(x.end); p.push_back(x.param); v.push_back(x.value); }
        return engine.configureMixerAutomation(s.data(),e.data(),p.data(),v.data(),static_cast<int>(points.size()));
    }

    void runTest() override {
        constexpr double rate=48000;
        beginTest("Timeline: linear ramps toward the point, base before it, instant mutes, cut ramps chain");
        {
            MixerAutomation a; a.setBase(0,1.0f); a.setBase(MixerAutomation::kMaster,1.0f);
            expect(a.configure({{1,2,0,0.0f},{3,3,MixerAutomation::mute(0),1.0f}}));
            expectEquals(a.value(0,24000,rate),1.0f); expectEquals(a.value(0,48000,rate),1.0f);
            expectWithinAbsoluteError(a.value(0,72000,rate),0.5f,1e-6f); expectEquals(a.value(0,96000,rate),0.0f);
            expectEquals(a.value(MixerAutomation::mute(0),143999,rate),0.0f); expectEquals(a.value(MixerAutomation::mute(0),144000,rate),1.0f);
            a.setBase(0,0.5f); expectWithinAbsoluteError(a.value(0,72000,rate),0.25f,1e-6f);
            expect(a.configure({{1,3,0,0.0f},{2,4,0,1.0f}}));  // the second ramp cuts the first at 2 s (value 0.25 from base 0.5)
            expectWithinAbsoluteError(a.value(0,96000,rate),0.25f,1e-6f);
            expectWithinAbsoluteError(a.value(0,144000,rate),0.625f,1e-6f);
            expectEquals(a.value(0,192000,rate),1.0f);
            a.setTimeScale(2); expectWithinAbsoluteError(a.value(0,96000*2,rate),0.25f,1e-6f); a.setTimeScale(1);
            const auto before=a.size();
            for (const auto& bad : std::vector<std::vector<P>>{
                     {{2,2,0,0.5f},{1,3,0,0.5f}}, {{1,3,0,0.5f},{2,2.5,0,0.5f},{1.5,4,0,0.5f}}, {{1,2,MixerAutomation::mute(1),1.0f}},
                     {{1,1,MixerAutomation::mute(1),0.5f}}, {{1,1,0,1.5f}}, {{1,1,MixerAutomation::kMaster,2.5f}}, {{-1,1,0,0.5f}},
                     {{2,1,0,0.5f}}, {{1,1,MixerAutomation::kParams,0.5f}}, {{1,std::nan(""),0,0.5f}}})
                expect(!a.configure(bad) && a.size()==before);
            expect(a.configure({{1,1,MixerAutomation::kMaster,2.0f}}));
        }

        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_automation","",false); dir.createDirectory();
        auto dc=writeDc(dir,"dc.wav",4*48000,0.5f);
        auto start=[&](AudioEngine& engine,int block,int stems=1){
            engine.prepareToPlay(block,rate); std::vector<juce::File> files(static_cast<size_t>(stems),dc); expect(engine.loadTrack("auto",files)); };

        beginTest("Engine: volume ramp follows the automation sample by sample for any block size");
        for (int block : {64,512,1024}) {
            AudioEngine engine; start(engine,block);
            expect(apply(engine,{{1,2,0,0.0f}})); engine.play();
            auto l=render(engine,3*48000,block);
            expectWithinAbsoluteError(l[24000],0.5f,1e-5f); expectWithinAbsoluteError(l[48000],0.5f,1e-5f);
            expectWithinAbsoluteError(l[72000],0.25f,1e-5f); expectWithinAbsoluteError(l[84000],0.125f,1e-5f);
            expectWithinAbsoluteError(l[96000],0.0f,1e-5f); expectWithinAbsoluteError(l[140000],0.0f,1e-6f);
        }

        beginTest("Engine: instant mute with de-click, solo independent of automation, manual values when disabled");
        {
            AudioEngine engine; start(engine,256,2);
            engine.setChannelMuted(1,true);
            expect(apply(engine,{{1,1,MixerAutomation::mute(0),1.0f},{1,1,MixerAutomation::mute(1),0.0f}})); engine.play();
            auto l=render(engine,2*48000,256);
            expectWithinAbsoluteError(l[47999],0.5f,1e-5f);       // ch1 manually muted before its first point
            expectWithinAbsoluteError(l[48000+240],0.5f,1e-5f);   // crossfaded by the 20 ms ramps
            expectWithinAbsoluteError(l[48000+500],0.5f,1e-5f);
            engine.setChannelSoloMuted(1,true); l=render(engine,1000,256);
            expectWithinAbsoluteError(l[999],0.0f,1e-6f);
            engine.setChannelSoloMuted(1,false); engine.setAutomationEnabled(false); l=render(engine,2000,256);
            expectWithinAbsoluteError(l[1999],0.5f,1e-5f);        // manual: ch0 open, ch1 muted
            float volumes[2]={}; uint8_t mutes[2]={}; float master=0;
            expectEquals(engine.getMixState(volumes,mutes,2,&master),2);
            expect(mutes[0]==0 && mutes[1]==1 && master==1.0f);
            engine.setAutomationEnabled(true); expect(engine.getAutomationEnabled());
            expectEquals(engine.getMixState(volumes,mutes,2,&master),2);
            expect(mutes[0]==1 && mutes[1]==0);
        }

        beginTest("Engine: master automation, seek into a ramp and loop wraps land on the automated value");
        {
            AudioEngine engine; start(engine,64);
            expect(apply(engine,{{1,1,MixerAutomation::kMaster,2.0f},{2,3,0,0.0f}}));
            engine.seekToSeconds(1.5); engine.play(); auto l=render(engine,1000,64);
            expectWithinAbsoluteError(l[999],1.0f,1e-5f);  // 0.5 stem x master 2
            engine.pause(); engine.seekToSeconds(2.5); engine.play(); l=render(engine,1000,64);
            expectWithinAbsoluteError(l[999],0.5f*(0.5f-999/48000.0f)*2.0f,1e-4f);
            float volume=0; uint8_t mute=0; float master=0; engine.getMixState(&volume,&mute,1,&master);
            expectWithinAbsoluteError(volume,0.5f-1000/48000.0f,1e-4f); expectEquals(master,2.0f);
            engine.stop(); expect(engine.setLoop(2,3,true)); engine.seekToSeconds(2); engine.play();
            l=render(engine,48000+24000,64);
            expectWithinAbsoluteError(l[24000],0.5f,1e-5f); expectWithinAbsoluteError(l[48000+24000-1],0.5f,1e-4f);
        }

        beginTest("Engine: manual fader changes move the start of the first ramp; new songs drop the automation");
        {
            AudioEngine engine; start(engine,64);
            expect(apply(engine,{{1,2,0,0.0f}})); engine.setChannelVolume(0,0.5f);
            engine.seekToSeconds(1.5); float volume=0; engine.getMixState(&volume,nullptr,1,nullptr);
            expectWithinAbsoluteError(volume,0.25f,1e-6f);
            expect(engine.loadTrack("other",{dc})); engine.seekToSeconds(1.5); engine.getMixState(&volume,nullptr,1,nullptr);
            expectEquals(volume,1.0f);
            const double s=1, e=0; const int p=0; const float v=0.5f;
            expect(!engine.configureMixerAutomation(&s,&e,&p,&v,1));
            expect(engine.configureMixerAutomation(nullptr,nullptr,nullptr,nullptr,0));
        }
        dir.deleteRecursively();
    }
} mixerAutomationTests;
