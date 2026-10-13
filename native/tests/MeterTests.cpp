#include "AudioEngine.h"
#include <thread>
#include <vector>
using namespace wtracks;

// Peak meters: post-fader channel peaks and post-master output peaks, read-and-reset, lock-free.
class MeterTests : public juce::UnitTest {
public:
    MeterTests() : juce::UnitTest("Peak meters", "Audio") {}

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
    static void render(AudioEngine& engine, int total, int block) {
        juce::AudioBuffer<float> out(2,block); int offset=0;
        while (offset<total) {
            const int count=juce::jmin(block,total-offset); juce::AudioSourceChannelInfo info(&out,0,count);
            engine.getNextAudioBlock(info); offset+=count;
        }
    }

    void runTest() override {
        beginTest("PeakMeter keeps the maximum until taken, also under concurrent writers");
        {
            PeakMeter m; m.raise(0.2f); m.raise(0.1f); expectEquals(m.take(),0.2f); expectEquals(m.take(),0.0f);
            std::vector<std::thread> writers;
            for (int t=0;t<4;++t) writers.emplace_back([&m,t]{ for (int i=0;i<10000;++i) m.raise(static_cast<float>(t*10000+i)/40000.0f); });
            for (auto& w : writers) w.join();
            expectEquals(m.take(),39999/40000.0f);
            float a=0,b=0; expectEquals(mixStem(&a,&b,nullptr,0,0,1,{0,false},*std::make_unique<GainRamp>()),0.0f);  // invalid route
        }

        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_meters","",false); dir.createDirectory();
        auto loud=writeDc(dir,"loud.wav",48000,0.5f,-0.25f), quiet=writeDc(dir,"quiet.wav",48000,0.1f,0.1f);

        beginTest("Channel peaks are post-fader and post-mute; output peaks follow the master and the routes");
        {
            AudioEngine engine; engine.prepareToPlay(256,48000); expect(engine.loadTrack("meters",{loud,quiet}));
            float channels[4]={-1,-1,-1,-1}, outputs[2]={-1,-1};
            expectEquals(engine.takeMeters(channels,4,outputs,2),2);
            expect(channels[0]==0 && channels[1]==0 && outputs[0]==0);
            engine.setChannelVolume(0,0.5f); engine.setMasterVolume(2.0f); engine.play(); render(engine,4800,256);
            engine.takeMeters(channels,4,outputs,2);
            expectWithinAbsoluteError(channels[0],0.25f,1e-5f); expectWithinAbsoluteError(channels[1],0.1f,1e-5f);
            expectWithinAbsoluteError(outputs[0],(0.25f+0.1f)*2,1e-4f); expectWithinAbsoluteError(outputs[1],(0.125f-0.1f)*2,1e-4f);
            expectEquals(channels[2],0.0f);  // beyond the song's channels: silent
            engine.setChannelMuted(1,true); render(engine,1024,256); engine.takeMeters(channels,4,outputs,2);  // 20 ms de-zipper
            render(engine,4800,256); engine.takeMeters(channels,4,outputs,2);
            expectEquals(channels[1],0.0f);
            expect(engine.setChannelRoute(0,0,true)); render(engine,4800,256); engine.takeMeters(channels,4,outputs,2);
            expectWithinAbsoluteError(channels[0],0.0625f,1e-5f); expectEquals(outputs[1],0.0f);
            engine.pause(); render(engine,256,256); engine.takeMeters(channels,4,outputs,2);
            expect(channels[0]==0 && outputs[0]==0);  // nothing played since the last read
        }
        dir.deleteRecursively();
    }
} meterTests;
