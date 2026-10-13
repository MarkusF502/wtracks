#include "AudioEngine.h"
#include <limits>
using namespace wtracks;
class LoopTests : public juce::UnitTest {
public:
    LoopTests() : juce::UnitTest("Prepared section loops", "Audio") {}
    void runTest() override {
        constexpr double rate=48000;
        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_loops","",false);dir.createDirectory();
        auto write=[&](const juce::String& name, bool silent, bool click=false) {
            auto file=dir.getChildFile(name);juce::WavAudioFormat format;
            auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
            auto writer=std::unique_ptr<juce::AudioFormatWriter>(format.createWriterFor(stream.get(),rate,2,24,{},0));stream.release();
            const int count=click ? 1 : 48000;juce::AudioBuffer<float> data(2,count);data.clear();
            if(!silent) for(int i=0;i<count;++i) {data.setSample(0,i,click ? 0.8f : (i%13==0 ? 0.5f:0));data.setSample(1,i,click ? 0.8f : (i%17==0 ? 0.3f:0));}
            writer->writeFromAudioSampleBuffer(data,0,count);writer.reset();return file;
        };
        auto impulses=write("impulses.wav",false);
        beginTest("Exact impulse loop boundaries independent of prepared and host block size");
        for(int block : {64,256,1024}) {
            AudioEngine engine;engine.prepareToPlay(block,rate);expect(engine.loadTrack("impulses",{impulses}));
            expect(engine.setLoop(100/rate,237/rate,true));engine.play();juce::AudioBuffer<float> output(2,block);
            int offset=0;const int total=137*5+17;
            while(offset<total) {
                const int count=juce::jmin(block,total-offset);juce::AudioSourceChannelInfo info(&output,0,count);engine.getNextAudioBlock(info);
                for(int sample=0;sample<count;++sample) {
                    const int frame=100+(offset+sample)%137;
                    expectWithinAbsoluteError(output.getSample(0,sample),frame%13==0 ? 0.5f:0.0f,0.000001f);
                    expectWithinAbsoluteError(output.getSample(1,sample),frame%17==0 ? 0.3f:0.0f,0.000001f);
                }offset+=count;
            }
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),117/rate,1.0/rate);
            expectEquals(engine.getUnderrunCount(),uint64_t(0));expect(engine.isPlaying());
        }
        beginTest("Queued promotion at exact boundary preserves leftover host frames and atomic snapshot");
        AudioEngine engine;engine.prepareToPlay(64,rate);expect(engine.loadTrack("impulses",{impulses}));
        expect(engine.setLoop(100/rate,237/rate,true));expect(engine.enqueueLoop(1000/rate,1129/rate));engine.play();
        juce::AudioBuffer<float> output(2,283);juce::AudioSourceChannelInfo info(&output,0,283);engine.getNextAudioBlock(info);
        for(int i=0;i<283;++i) {const int frame=i<137 ? 100+i : 1000+(i-137)%129;
            expectWithinAbsoluteError(output.getSample(0,i),frame%13==0 ? 0.5f:0.0f,0.000001f);}
        expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1017/rate,1.0/rate);
        double state[6];engine.getLoopState(state);expectEquals(state[0],1.0);expectEquals(state[1],1000/rate);expectEquals(state[3],0.0);
        beginTest("Invalid active/queued requests preserve state; seek and clear remain explicit");
        expect(engine.enqueueLoop(2000/rate,2129/rate));
        expect(!engine.setLoop(std::numeric_limits<double>::quiet_NaN(),0.1,true));expect(!engine.setLoop(0,2,true));
        expect(!engine.enqueueLoop(-1,0.1));expect(!engine.enqueueLoop(0.5,0.5));
        expectEquals(engine.getLoopStart(),1000/rate);expectEquals(engine.getQueuedLoopStart(),2000/rate);
        engine.clearQueuedLoop();expect(!engine.getQueuedLoopEnabled());engine.seekToSeconds(0.9);
        expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1000/rate,1.0/rate);
        engine.seekToSeconds(1050/rate);expect(engine.setLoop(1000/rate,1100/rate,true));
        expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1050/rate,1.0/rate);
        beginTest("Source cache survives rate migration; disable and stop restore streaming contract");
        engine.prepareToPlay(256,44100);expect(engine.getLoopEnabled());expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1050/rate,1.0/44100);
        expect(engine.setLoop(0,0,false));expect(!engine.getLoopEnabled());expect(engine.waitForReadAhead(64,1000));
        engine.stop();expectEquals(engine.getCurrentPositionSeconds(),0.0);expect(!engine.getLoopEnabled());
        expect(engine.setLoop(0.1,0.2,true));expect(engine.loadTrack("replacement",{impulses}));expect(!engine.getLoopEnabled());
        beginTest("Click schedules restart at loop song-position and never fire at exclusive loop end");
        auto silence=write("silence.wav",true);auto pulse=write("click.wav",false,true);
        engine.prepareToPlay(64,rate);expect(engine.loadTrack("click-loop",{silence}));expect(engine.configureClick(120,4,4,4,0,1,1,0,0));
        expect(engine.loadClickSound(0,pulse.getFullPathName()));engine.setClickEnabled(true);expect(engine.setLoop(0,0.5,true));engine.play();
        output.setSize(2,24064);juce::AudioSourceChannelInfo clickInfo(&output,0,24064);engine.getNextAudioBlock(clickInfo);
        expectWithinAbsoluteError(output.getSample(0,0),0.8f,0.000001f);expectWithinAbsoluteError(output.getSample(0,24000),0.8f,0.000001f);
        expectEquals(output.getMagnitude(0,1,23999),0.0f);expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),64/rate,1.0/rate);
        engine.unloadCurrentTrack();expect(!engine.getLoopEnabled());expect(!engine.getQueuedLoopEnabled());
        beginTest("Oversized sparse-file loop is rejected before allocation and leaves active loop intact");
        auto huge=dir.getChildFile("sparse.wav");auto stream=std::unique_ptr<juce::FileOutputStream>(huge.createOutputStream());
        const int dataBytes=192000*90*4;stream->write("RIFF",4);stream->writeInt(dataBytes+36);stream->write("WAVEfmt ",8);
        stream->writeInt(16);stream->writeShort(1);stream->writeShort(2);stream->writeInt(192000);stream->writeInt(192000*4);
        stream->writeShort(4);stream->writeShort(16);stream->write("data",4);stream->writeInt(dataBytes);
        stream->setPosition(dataBytes+43);stream->writeByte(0);stream.reset();
        expect(engine.loadTrack("huge",{huge}));expect(engine.setLoop(0,0.01,true));
        expect(!engine.setLoop(0,90,true));expect(!engine.enqueueLoop(0,90));expect(engine.getLoopEnabled());expectEquals(engine.getLoopEnd(),0.01);
        huge.deleteFile();expect(!engine.setLoop(0.01,0.02,true));expectEquals(engine.getLoopEnd(),0.01);
        engine.unloadCurrentTrack();dir.deleteRecursively();
    }
};static LoopTests loopTests;
