#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Buses: track -> bus -> output (BusChannelAU contract), automation, solo gate, stereo split.
class BusTests : public juce::UnitTest {
public:
    BusTests() : juce::UnitTest("Song buses and routing", "Audio") {}

    static juce::File writeDc(const juce::File& dir, const juce::String& name, int frames, float left, float right) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(2,frames);
        juce::FloatVectorOperations::fill(data.getWritePointer(0),left,frames);
        juce::FloatVectorOperations::fill(data.getWritePointer(1),right,frames);
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }
    static void render(AudioEngine& engine, int total, int block, std::vector<float>& l, std::vector<float>& r, int outputs=2,
                       std::vector<float>* third=nullptr) {
        l.assign(static_cast<size_t>(total),0.f); r=l; if (third) *third=l;
        juce::AudioBuffer<float> out(outputs,block); int offset=0;
        while (offset<total) {
            const int count=juce::jmin(block,total-offset); juce::AudioSourceChannelInfo info(&out,0,count);
            engine.getNextAudioBlock(info);
            for (int i=0;i<count;++i) {
                l[static_cast<size_t>(offset+i)]=out.getSample(0,i); r[static_cast<size_t>(offset+i)]=out.getSample(1,i);
                if (third) (*third)[static_cast<size_t>(offset+i)]=out.getSample(2,i);
            }
            offset+=count;
        }
    }

    void runTest() override {
        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_buses","",false); dir.createDirectory();
        auto a=writeDc(dir,"a.wav",48000,0.5f,0.25f), b=writeDc(dir,"b.wav",48000,0.1f,0.1f);
        auto start=[&](AudioEngine& engine,int block){ engine.prepareToPlay(block,48000); expect(engine.loadTrack("bus",{a,b})); };

        beginTest("Tracks sum into their bus; the bus gain, mute and output route apply after the track fader");
        for (int block : {64,1000}) {
            AudioEngine engine; start(engine,block);
            expect(engine.configureBuses(2)); expect(engine.setChannelBus(0,1)); expect(engine.setBus(1,0.5f,false,0,false));
            engine.setChannelVolume(0,0.5f); engine.play(); std::vector<float> l,r;
            render(engine,2000,block,l,r);
            expectWithinAbsoluteError(l[1999],0.5f*0.5f*0.5f+0.1f,1e-5f); expectWithinAbsoluteError(r[1999],0.25f*0.25f+0.1f,1e-5f);
            expect(engine.setBus(1,0.5f,false,1,true)); render(engine,2000,block,l,r, 3);   // bus to output 2, mono
            expectWithinAbsoluteError(l[1999],0.1f,1e-5f); expectWithinAbsoluteError(r[1999],0.1f+0.25f*(0.5f+0.25f)*0.5f,1e-5f);
            expect(engine.setBus(1,0.5f,true,1,true)); render(engine,2000,block,l,r);
            expectWithinAbsoluteError(r[1999],0.1f,1e-5f);
            float vols[2]={}, peaks[2]={-1,-1}; uint8_t mutes[2]={};
            expectEquals(engine.getBusState(vols,mutes,2),2); expect(vols[1]==0.5f && mutes[1]==1 && mutes[0]==0);
            expectEquals(engine.takeBusMeters(peaks,2),2); expectEquals(peaks[0],0.0f);
        }

        beginTest("Bus solo gate, invalid indices, removing buses and new songs");
        {
            AudioEngine engine; start(engine,64);
            expect(!engine.configureBuses(17)); expect(!engine.setChannelBus(0,0)); expect(engine.configureBuses(1));
            expect(!engine.setChannelBus(0,1)); expect(!engine.setChannelBus(2,0)); expect(!engine.setBus(0,1.5f,false,0,false));
            expect(!engine.setBus(1,1,false,0,false)); expect(engine.setChannelBus(1,0));
            engine.setBusSoloMuted(0,true); engine.play(); std::vector<float> l,r; render(engine,2000,64,l,r);
            expectWithinAbsoluteError(l[1999],0.5f,1e-5f);
            float peak=0; engine.takeBusMeters(&peak,1); expectEquals(peak,0.0f);
            engine.setBusSoloMuted(0,false); render(engine,2000,64,l,r); expectWithinAbsoluteError(l[1999],0.6f,1e-5f);
            engine.takeBusMeters(&peak,1); expectWithinAbsoluteError(peak,0.1f,1e-5f);
            expect(engine.configureBuses(0)); render(engine,64,64,l,r); expectWithinAbsoluteError(l[63],0.6f,1e-5f);  // back to direct
            expect(engine.configureBuses(1)); expect(engine.setChannelBus(1,0)); expect(engine.loadTrack("other",{a,b}));
            expectEquals(engine.getBusState(nullptr,nullptr,0),0); expect(!engine.setChannelBus(1,0));
        }

        beginTest("Bus automation moves the bus fader; split sends click/guides left and tracks mono right");
        {
            AudioEngine engine; start(engine,64);
            expect(engine.configureBuses(1)); expect(engine.setChannelBus(0,0)); expect(engine.setChannelBus(1,0));
            const double s=0.5,e=0.5; const int p=MixerAutomation::busVolume(0); const float v=0.0f;
            expect(engine.configureMixerAutomation(&s,&e,&p,&v,1));
            engine.play(); std::vector<float> l,r; render(engine,48000,64,l,r);
            expectWithinAbsoluteError(l[20000],0.6f,1e-5f); expectWithinAbsoluteError(l[47999],0.0f,1e-6f);
            float vol=1; engine.getBusState(&vol,nullptr,1); expectEquals(vol,0.0f);
            engine.setAutomationEnabled(false); engine.setStereoSplit(true); engine.seekToSeconds(0.1); engine.play();  // no click before 0.5 s
            expect(engine.configureClick(120,4,4,4,0,1,1,0,0)); engine.setClickEnabled(true);
            render(engine,2000,64,l,r);
            expectWithinAbsoluteError(r[1999],(0.5f+0.25f)*0.5f+(0.1f+0.1f)*0.5f,1e-5f);  // tracks mono right
            expectEquals(l[1999],0.0f);                                                    // no track left
            engine.seekToSeconds(0.49); engine.play(); render(engine,2000,64,l,r);  // the 0.5 s click lands at frame 480
            float leftPeak=0, rightSpread=0;
            for (int i=0;i<2000;++i) { leftPeak=juce::jmax(leftPeak,std::abs(l[static_cast<size_t>(i)]));
                                       rightSpread=juce::jmax(rightSpread,std::abs(r[static_cast<size_t>(i)]-0.475f)); }
            expect(leftPeak > 0.1f); expectWithinAbsoluteError(rightSpread,0.0f,1e-5f);
        }
        dir.deleteRecursively();
    }
} busTests;
