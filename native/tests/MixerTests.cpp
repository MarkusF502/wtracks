#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Mixer reconstruction: ramped gain, mute, output base and mono/stereo routing (see MixerStage.h).
class MixerTests : public juce::UnitTest {
public:
    MixerTests() : juce::UnitTest("Mixer stage and channel routing", "Audio") {}

    static juce::File dc(const juce::File& dir, const juce::String& name, float left, float right, int frames) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0)); stream.release();
        juce::AudioBuffer<float> data(2,frames);
        for (int i=0;i<frames;++i) { data.setSample(0,i,left); data.setSample(1,i,right); }
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }
    static void render(AudioEngine& engine,int total,int block,std::vector<float>& l,std::vector<float>& r) {
        l.assign(static_cast<size_t>(total),0.f); r=l; juce::AudioBuffer<float> out(2,block); int offset=0;
        while (offset<total) {
            const int count=juce::jmin(block,total-offset); juce::AudioSourceChannelInfo info(&out,0,count); engine.getNextAudioBlock(info);
            for (int i=0;i<count;++i) { l[static_cast<size_t>(offset+i)]=out.getSample(0,i); r[static_cast<size_t>(offset+i)]=out.getSample(1,i); }
            offset+=count;
        }
    }

    void runTest() override {
        beginTest("GainRamp is linear, per sample and adopts the first target");
        {
            GainRamp ramp; ramp.set(0.7f); expectEquals(ramp.value,0.7f);
            ramp.set(0); const float step=GainRamp::stepFor(48000); expectWithinAbsoluteError(step,1.0f/480,1e-9f);
            for (int i=0;i<480;++i) ramp.next(step); expect(ramp.value<1e-6f); ramp.next(step); expect(ramp.silent());
        }
        beginTest("mixStem: stereo, mono and invalid routes");
        {
            const float left[4]={0.5f,0.5f,0.5f,0.5f}, right[4]={0.25f,0.25f,0.25f,0.25f};
            auto run=[&](ChannelRoute route,int outputs,float gain,float& o0,float& o1,float& o2) {
                float a[4]={},b[4]={},c[4]={}; float* out[3]={a,b,c}; GainRamp ramp; ramp.set(gain);
                mixStem(left,right,out,outputs,0,4,route,ramp,0.01f); o0=a[3]; o1=b[3]; o2=c[3];
            };
            float o0,o1,o2;
            run({0,false},2,1,o0,o1,o2); expectEquals(o0,0.5f); expectEquals(o1,0.25f); expectEquals(o2,0.f);
            run({0,true},2,1,o0,o1,o2); expectEquals(o0,0.375f); expectEquals(o1,0.f);
            run({1,true},2,0.5f,o0,o1,o2); expectEquals(o0,0.f); expectEquals(o1,0.1875f);
            run({1,false},2,1,o0,o1,o2); expectEquals(o0+o1+o2,0.f); // base+1 beyond the device
            run({1,false},3,1,o0,o1,o2); expectEquals(o0,0.f); expectEquals(o1,0.5f); expectEquals(o2,0.25f);
            run({2,true},2,1,o0,o1,o2); expectEquals(o0+o1+o2,0.f);
            run({-1,true},2,1,o0,o1,o2); expectEquals(o0+o1+o2,0.f);
        }

        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_mixer","",false); dir.createDirectory();
        auto a=dc(dir,"a.wav",0.5f,0.25f,96000), b=dc(dir,"b.wav",0.5f,0.5f,96000);
        auto fresh=[&](AudioEngine& engine,int block,std::initializer_list<juce::File> files) {
            engine.prepareToPlay(block,48000); expect(engine.loadTrack("mix",std::vector<juce::File>(files)));
        };

        beginTest("Engine stereo default, mono left/right and invalid route");
        {
            AudioEngine engine; fresh(engine,256,{a}); engine.play(); std::vector<float> l,r;
            render(engine,512,256,l,r); expectWithinAbsoluteError(l[300],0.5f,1e-5f); expectWithinAbsoluteError(r[300],0.25f,1e-5f);
            expect(engine.setChannelRoute(0,0,true)); render(engine,1024,256,l,r);
            expectWithinAbsoluteError(l[1000],0.375f,1e-5f); expectEquals(r[1000],0.f);
            expect(engine.setChannelRoute(0,1,true)); render(engine,1024,256,l,r);
            expectEquals(l[1000],0.f); expectWithinAbsoluteError(r[1000],0.375f,1e-5f);
            expect(engine.setChannelRoute(0,1,false)); render(engine,1024,256,l,r);
            expectEquals(l[1000],0.f); expectEquals(r[1000],0.f);
            expect(!engine.setChannelRoute(0,-1,false)); expect(!engine.setChannelRoute(5,0,false)); expect(!engine.setChannelRoute(0,64,false));
        }

        beginTest("Mute and volume ramp linearly over 10 ms independent of host block size");
        for (int block : {64,100,480,1024}) {
            AudioEngine engine; fresh(engine,block,{a}); engine.play(); std::vector<float> l,r;
            render(engine,2000,block,l,r); expectWithinAbsoluteError(l[1999],0.5f,1e-5f);
            engine.setChannelMuted(0,true); render(engine,1200,block,l,r);
            for (int i=0;i<1200;++i) expectWithinAbsoluteError(l[static_cast<size_t>(i)],0.5f*juce::jmax(0.f,1.f-(i+1)/480.f),2e-5f);
            engine.setChannelMuted(0,false); engine.setChannelVolume(0,0.5f); render(engine,1200,block,l,r);
            for (int i=0;i<1200;++i) expectWithinAbsoluteError(l[static_cast<size_t>(i)],0.5f*juce::jmin(0.5f,(i+1)/480.f),2e-5f);
            expectEquals(engine.getUnderrunCount(),uint64_t(0));
        }

        beginTest("Channels sum without clipping and master volume scales everything");
        {
            AudioEngine engine; fresh(engine,256,{a,b}); engine.play(); std::vector<float> l,r;
            render(engine,512,256,l,r); expectWithinAbsoluteError(l[400],1.0f,1e-5f); expectWithinAbsoluteError(r[400],0.75f,1e-5f);
            engine.setChannelVolume(0,1.f); engine.setMasterVolume(2.f); render(engine,1024,256,l,r);
            expectWithinAbsoluteError(l[1000],2.0f,1e-5f); expectWithinAbsoluteError(r[1000],1.5f,1e-5f); // above full scale: not clipped
            engine.setMasterVolume(0.5f); render(engine,1024,256,l,r);
            expectWithinAbsoluteError(l[1000],0.5f,1e-5f); expectWithinAbsoluteError(r[1000],0.375f,1e-5f);
            engine.setMasterVolume(std::numeric_limits<float>::quiet_NaN()); render(engine,64,64,l,r);
            expectWithinAbsoluteError(l[63],0.5f,1e-5f);
        }
        dir.deleteRecursively();
    }
};
static MixerTests mixerTests;
