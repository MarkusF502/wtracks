#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Custom song start and end (Playback SongArrangement.storedStartTime / storedEndTime).
class PlayRangeTests : public juce::UnitTest {
public:
    PlayRangeTests() : juce::UnitTest("Custom song start and end", "Audio") {}

    static juce::File writeRamp(const juce::File& dir, const juce::String& name, int frames) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(2,frames);  // the sample value encodes the time: frame / 8 s * 0.5 (4 s file)
        for (int ch=0;ch<2;++ch) for (int i=0;i<frames;++i) data.setSample(ch,i,static_cast<float>(i)/static_cast<float>(frames)*0.9f);
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
        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_range","",false); dir.createDirectory();
        auto file=writeRamp(dir,"ramp.wav",4*48000);   // 4 s
        auto load=[&](AudioEngine& engine,int block){ engine.prepareToPlay(block,48000); expect(engine.loadTrack("range",{file})); };

        beginTest("Validation: negative or inverted ranges change nothing; 0/0 is the whole file");
        {
            AudioEngine engine; load(engine,64);
            expect(engine.setPlayRange(1.0,3.0)); expect(!engine.setPlayRange(-1,3)); expect(!engine.setPlayRange(2,2)); expect(!engine.setPlayRange(3,1));
            double r[2]; engine.getPlayRange(r); expectEquals(r[0],1.0); expectEquals(r[1],3.0);
            expect(engine.setPlayRange(0,0)); engine.getPlayRange(r); expectEquals(r[0],0.0); expectEquals(r[1],0.0);
            expect(engine.setPlayRange(2.0,0.0));   // start only
        }

        beginTest("A waiting song follows its start; play from zero begins at the start, stop returns there");
        for (int block : {64,1000}) {
            AudioEngine engine; load(engine,block);
            expect(engine.setPlayRange(1.0,0)); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1.0,1e-6);
            engine.play(); auto l=render(engine,480,block);
            expectWithinAbsoluteError(l[0],0.9f*(48000.0f/192000.0f),1e-4f);   // the sample at 1 s
            engine.pause(); engine.seekToSeconds(0.0); engine.play(); l=render(engine,10,block);
            expectWithinAbsoluteError(l[0],0.9f*(48000.0f/192000.0f),1e-4f);   // a playhead at 0 means "the beginning": it starts at the custom start
        }
        {
            AudioEngine engine; load(engine,64);
            expect(engine.setPlayRange(1.0,0)); engine.play(); render(engine,4800,64); engine.stop();
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1.0,1e-6); expect(!engine.isPlaying());
            expect(engine.setPlayRange(0.5,0)); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),0.5,1e-6);  // still parked at the old start
            engine.seekToSeconds(2.0); expect(engine.setPlayRange(0.25,0)); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),2.0,1e-6);
        }

        beginTest("The custom end stops the song exactly there with EndReached; the end fade counts back from it");
        for (int block : {64,1000}) {
            AudioEngine engine; load(engine,block);
            expect(engine.setPlayRange(0,2.0)); engine.seekToSeconds(1.5); engine.play();
            auto l=render(engine,48000,block);
            expect(!engine.isPlaying()); expect(engine.pollTransportEvents()==uint32_t(AudioEngine::EndReached));
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),2.0,1e-6);
            expectWithinAbsoluteError(l[23999],0.9f*(95999.0f/192000.0f),1e-4f);   // last sample before 2 s
            expectEquals(l[24000],0.0f);
            expect(engine.setEndFade(1.0)); engine.stop(); engine.seekToSeconds(0.0); engine.play();
            render(engine,48000,block);   // 1 s: the fade (starting at 1 s of 2) has not begun
            expect(!engine.isFadeDown()); render(engine,10,block); expect(engine.isFadeDown());
        }

        beginTest("Time scale: the range is in song time");
        {
            AudioEngine engine; load(engine,64);
            expect(engine.setTimeScale(2.0));   // the file now renders 2 s of song per 4 s... song length = file / 2
            expect(engine.setPlayRange(0.5,1.5)); engine.stop();
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),0.5,1e-6);
            engine.play(); render(engine,96000,64);
            expect(!engine.isPlaying()); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1.5,1e-6);
        }
        dir.deleteRecursively();
    }
} playRangeTests;
