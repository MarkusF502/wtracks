#include "AudioEngine.h"
#include <limits>
#include <vector>
using namespace wtracks;

// Integration of GuideTimeline with AudioEngine: real WAV decode, scheduling across host block
// sizes, loop/seek/EOF/mute, track replacement and failure preservation.
class GuideEngineTests : public juce::UnitTest {
public:
    GuideEngineTests() : juce::UnitTest("Guide schedule in AudioEngine", "Audio") {}

    struct Schedule {
        std::vector<double> times; std::vector<juce::String> paths; std::vector<float> gains;
        bool apply(AudioEngine& engine) {
            std::vector<const char*> raw; std::vector<std::string> store(paths.size());
            for (size_t i=0;i<paths.size();++i) { store[i]=paths[i].toStdString(); raw.push_back(store[i].c_str()); }
            return engine.configureGuides(times.data(),raw.data(),gains.data(),static_cast<int>(times.size()));
        }
    };

    static juce::File writeWav(const juce::File& dir, const juce::String& name, double rate, int channels, int bits,
                               int frames, const std::vector<std::vector<float>>& pcm) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),rate,static_cast<unsigned>(channels),bits,{},0));
        stream.release();
        juce::AudioBuffer<float> data(channels,frames); data.clear();
        for (size_t ch=0;ch<pcm.size() && ch<static_cast<size_t>(channels);++ch)
            for (size_t i=0;i<pcm[ch].size() && i<static_cast<size_t>(frames);++i) data.setSample(static_cast<int>(ch),static_cast<int>(i),pcm[ch][i]);
        writer->writeFromAudioSampleBuffer(data,0,frames); writer.reset(); return file;
    }

    // Plays `total` frames with `block`-sized host callbacks; returns channel 0 and 1.
    static void render(AudioEngine& engine, int total, int block, std::vector<float>& left, std::vector<float>& right) {
        left.assign(static_cast<size_t>(total),0.f); right = left;
        juce::AudioBuffer<float> out(2,block); int offset=0;
        while (offset<total) {
            const int count=juce::jmin(block,total-offset); juce::AudioSourceChannelInfo info(&out,0,count);
            engine.getNextAudioBlock(info);
            for (int i=0;i<count;++i) { left[static_cast<size_t>(offset+i)]=out.getSample(0,i); right[static_cast<size_t>(offset+i)]=out.getSample(1,i); }
            offset+=count;
        }
    }

    void runTest() override {
        constexpr double rate=48000;
        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_guides","",false); dir.createDirectory();
        const int trackFrames=96000;
        auto silence=writeWav(dir,"silence.wav",rate,2,24,trackFrames,{{},{}});
        // Stereo L=0.6 R=0.2 -> mono mean 0.4, one frame (24-bit keeps the value within 1e-6).
        auto pulse=writeWav(dir,"pulse.wav",rate,2,24,1,{{0.6f},{0.2f}});
        // 100-frame constant 0.1 mono tail for voice stealing / mute / EOF.
        auto tail=writeWav(dir,"tail.wav",rate,1,24,100,{std::vector<float>(100,0.1f)});
        auto start=[&](AudioEngine& engine,int block){ engine.prepareToPlay(block,rate); expect(engine.loadTrack("guides",{silence})); };

        beginTest("Real WAV cues land on exact sample positions for any host block size");
        for (int block : {64,256,1024}) {
            AudioEngine engine; start(engine,block);
            Schedule s{{4800/rate,12000/rate},{pulse.getFullPathName(),pulse.getFullPathName()},{1.f,0.5f}};
            expect(s.apply(engine)); engine.setGuidesEnabled(true); engine.play();
            std::vector<float> l,r; render(engine,16000,block,l,r);
            for (int i=0;i<16000;++i) {
                const float want=i==4800 ? 0.4f : i==12000 ? 0.2f : 0.f;
                expectWithinAbsoluteError(l[static_cast<size_t>(i)],want,1e-5f); expectWithinAbsoluteError(r[static_cast<size_t>(i)],want,1e-5f);
            }
            expectEquals(engine.getUnderrunCount(),uint64_t(0));
        }

        beginTest("Disabled guides are silent but the schedule keeps advancing; no cue fires late");
        {
            AudioEngine engine; start(engine,256);
            Schedule s{{0.0,200/rate,5000/rate},{tail.getFullPathName(),tail.getFullPathName(),pulse.getFullPathName()},{1.f,1.f,1.f}};
            expect(s.apply(engine)); engine.play(); std::vector<float> l,r;
            render(engine,512,256,l,r); expectEquals(juce::FloatVectorOperations::findMaximum(l.data(),512),0.f);
            engine.setGuidesEnabled(true); render(engine,5000,256,l,r);
            expectEquals(juce::FloatVectorOperations::findMaximum(l.data(),4488),0.f); // the 5000 cue is at global 5000
            expectWithinAbsoluteError(l[4488],0.4f,1e-5f);
        }

        beginTest("Four-voice overlap steals the oldest at the same sample");
        {
            AudioEngine engine; start(engine,64);
            Schedule s; for (int i=0;i<5;++i) { s.times.push_back(0); s.paths.push_back(tail.getFullPathName()); s.gains.push_back(0.2f*static_cast<float>(i+1)); }
            expect(s.apply(engine)); engine.setGuidesEnabled(true); engine.play(); std::vector<float> l,r; render(engine,64,64,l,r);
            expectWithinAbsoluteError(l[0],0.1f*(0.4f+0.6f+0.8f+1.0f),1e-5f); expectWithinAbsoluteError(l[63],0.1f*(0.4f+0.6f+0.8f+1.0f),1e-5f);
        }

        beginTest("Loop replays cues each pass, never at the exclusive end, and seek skips past cues");
        {
            AudioEngine engine; start(engine,64);
            Schedule s{{0.1,0.5},{pulse.getFullPathName(),pulse.getFullPathName()},{1.f,1.f}};
            expect(s.apply(engine)); engine.setGuidesEnabled(true);
            expect(engine.setLoop(0,0.5,true)); engine.play(); std::vector<float> l,r; render(engine,48000,64,l,r);
            for (int i=0;i<48000;++i) expectWithinAbsoluteError(l[static_cast<size_t>(i)],(i==4800||i==28800) ? 0.4f : 0.f,1e-5f);
            engine.stop(); expect(engine.setLoop(0,0,false));
            engine.seekToSeconds(0.2); engine.play(); render(engine,100,64,l,r);
            expectEquals(juce::FloatVectorOperations::findMaximum(l.data(),100),0.f);
            engine.seekToSeconds(0.1-1.0/rate); engine.play(); render(engine,4,64,l,r);
            expectWithinAbsoluteError(l[1],0.4f,1e-5f);
        }

        beginTest("End of file cuts tails, stops playback and keeps the position at the end");
        {
            AudioEngine engine; start(engine,64);
            Schedule s{{(trackFrames-50)/rate},{tail.getFullPathName()},{1.f}};
            expect(s.apply(engine)); engine.setGuidesEnabled(true); engine.seekToSeconds((trackFrames-100)/rate); engine.play();
            std::vector<float> l,r; render(engine,200,64,l,r);
            expect(!engine.isPlaying()); expectWithinAbsoluteError(l[49],0.f,1e-6f); expectWithinAbsoluteError(l[50],0.1f,1e-5f);
            expectWithinAbsoluteError(l[99],0.1f,1e-5f); expectWithinAbsoluteError(l[100],0.f,1e-6f);
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),trackFrames/rate,1.0/rate);
        }

        beginTest("Replacing or unloading the track discards the previous schedule");
        {
            AudioEngine engine; start(engine,64);
            Schedule s{{0.0},{pulse.getFullPathName()},{1.f}};
            expect(s.apply(engine)); engine.setGuidesEnabled(true);
            expect(engine.loadTrack("other",{silence})); engine.play(); std::vector<float> l,r; render(engine,64,64,l,r);
            expectEquals(juce::FloatVectorOperations::findMaximum(l.data(),64),0.f);
            engine.unloadCurrentTrack(); expect(!s.apply(engine)); Schedule empty; expect(empty.apply(engine));
        }

        beginTest("Invalid or failing replacements preserve the active schedule; empty clears it");
        {
            AudioEngine engine; start(engine,64);
            Schedule good{{0.0},{pulse.getFullPathName()},{1.f}}; expect(good.apply(engine)); engine.setGuidesEnabled(true);
            const double nan=std::numeric_limits<double>::quiet_NaN();
            auto path=pulse.getFullPathName();
            Schedule bad[]={
                {{0.0},{dir.getChildFile("missing.wav").getFullPathName()},{1.f}},
                {{nan},{path},{1.f}}, {{-1.0},{path},{1.f}}, {{2.0,1.0},{path,path},{1.f,1.f}},
                {{trackFrames/rate+0.1},{path},{1.f}}, {{0.0},{path},{3.f}}, {{0.0},{path},{-1.f}},
                {{0.0},{juce::String()},{1.f}},
                {{0.0},{dir.getFullPathName()},{1.f}},
            };
            for (auto& entry : bad) expect(!entry.apply(engine));
            expect(!engine.configureGuides(nullptr,nullptr,nullptr,1)); expect(!engine.configureGuides(nullptr,nullptr,nullptr,4097));
            expect(!engine.configureGuides(nullptr,nullptr,nullptr,-1));
            // Mixed: first cue decodes, the second fails; nothing is published.
            Schedule mixed{{0.0,0.1},{tail.getFullPathName(),dir.getChildFile("nope.wav").getFullPathName()},{1.f,1.f}}; expect(!mixed.apply(engine));
            engine.play(); std::vector<float> l,r; render(engine,64,64,l,r);
            expectWithinAbsoluteError(l[0],0.4f,1e-5f); expectWithinAbsoluteError(l[1],0.f,1e-6f);
            engine.stop(); Schedule empty; expect(empty.apply(engine)); engine.play(); render(engine,64,64,l,r);
            expectEquals(juce::FloatVectorOperations::findMaximum(l.data(),64),0.f);
        }

        beginTest("Per-file 60 s limit and shared 64 MiB PCM limit with path deduplication");
        {
            AudioEngine engine; start(engine,64);
            auto tooLong=writeWav(dir,"too_long.wav",8000,1,8,8000*61,{});
            Schedule longSchedule{{0.0},{tooLong.getFullPathName()},{1.f}}; expect(!longSchedule.apply(engine));
            auto big1=writeWav(dir,"big1.wav",192000,1,8,192000*40,{});
            auto big2=dir.getChildFile("big2.wav"); big1.copyFileTo(big2); auto big3=dir.getChildFile("big3.wav"); big1.copyFileTo(big3);
            const auto p1=big1.getFullPathName(), p2=big2.getFullPathName(), p3=big3.getFullPathName();
            Schedule shared{{0,0,0},{p1,p1,p1},{1.f,1.f,1.f}}; expect(shared.apply(engine));
            Schedule two{{0,0},{p1,p2},{1.f,1.f}}; expect(two.apply(engine));
            Schedule three{{0,0,0},{p1,p2,p3},{1.f,1.f,1.f}}; expect(!three.apply(engine));
        }

        dir.deleteRecursively();
    }
};
static GuideEngineTests guideEngineTests;
