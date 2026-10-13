#include "AudioEngine.h"
#include <vector>
using namespace wtracks;

// Dynamic guides (replacement while the loop wraps) and Song Section Pre-roll. Both rules are our own design; see
// GuideTimeline.h and Preroll.h.
class DynamicGuideTests : public juce::UnitTest {
public:
    DynamicGuideTests() : juce::UnitTest("Dynamic guides and section pre-roll", "Audio") {}

    static std::shared_ptr<const GuideTimeline::Sound> pcm(std::vector<float> mono) {
        auto s=std::make_shared<GuideTimeline::Sound>(); s->mono=std::move(mono); s->sourceRate=48000; return s;
    }
    static juce::File writeWav(const juce::File& dir, const juce::String& name, int channels, int frames, float value) {
        auto file=dir.getChildFile(name); juce::WavAudioFormat format;
        auto stream=std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
        std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,static_cast<unsigned>(channels),24,{},0));
        stream.release();
        juce::AudioBuffer<float> data(channels,frames); data.clear();
        for (int ch=0;ch<channels;++ch) for (int i=0;i<frames;++i) data.setSample(ch,i,value);
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
    struct Guides {
        std::vector<double> times, targets; std::vector<juce::String> paths, replacements; std::vector<float> gains;
        void add(double t, const juce::String& p, const juce::String& r, double target) { times.push_back(t); paths.push_back(p); replacements.push_back(r); targets.push_back(target); gains.push_back(1); }
        bool apply(AudioEngine& engine) {
            std::vector<std::string> a(paths.size()), b(paths.size()); std::vector<const char*> pa, pb;
            for (size_t i=0;i<paths.size();++i) { a[i]=paths[i].toStdString(); b[i]=replacements[i].toStdString(); pa.push_back(a[i].c_str()); pb.push_back(b[i].c_str()); }
            return engine.configureGuides(times.data(),pa.data(),pb.data(),targets.data(),gains.data(),static_cast<int>(times.size()));
        }
    };
    static bool preroll(AudioEngine& engine, bool enabled, std::vector<double> starts, const std::vector<juce::String>& counts) {
        std::vector<std::string> store(counts.size()); std::vector<const char*> raw;
        for (size_t i=0;i<counts.size();++i) { store[i]=counts[i].toStdString(); raw.push_back(store[i].c_str()); }
        return engine.configurePreroll(enabled,starts.data(),static_cast<int>(starts.size()),raw.data(),static_cast<int>(raw.size()));
    }

    void runTest() override {
        beginTest("Timeline: replacement plays only when the loop wraps before the announced section");
        {
            GuideTimeline g; auto normal=pcm({1}), swap=pcm({0.25f});
            GuideTimeline::Cue named{0.5,1,normal,swap,1.0}, countOnly{0.75,1,nullptr,swap,1.0}, plain{0.8,1,normal,nullptr,-1};
            expect(g.configure({named,countOnly,plain}));
            auto at=[&](int64_t sample,int64_t wrap){ float v=0; g.reset(); g.render(&v,1,sample,48000,true,wrap); return v; };
            expectEquals(at(24000,-1),1.0f); expectEquals(at(24000,48000),0.25f);
            expectEquals(at(36000,-1),0.0f); expectEquals(at(36000,48000),0.25f);
            expectEquals(at(38400,48000),1.0f);  // no target: never replaced
            expectEquals(at(24000,96000),1.0f);  // the loop wraps past the announced section: it will be reached
            expectEquals(at(24000,48040),0.25f); // within 1 ms of the wrap point counts as unreachable
            GuideTimeline::Cue empty{0,1,nullptr,nullptr,-1}, badTarget{0,1,normal,nullptr,-2};
            expect(!g.configure({empty}) && g.size()==3); expect(!g.configure({badTarget}) && g.size()==3);
        }

        beginTest("Pre-roll counter: beats on exact samples, voices mixed, tails continue after the count-in");
        {
            ClickTimeline click; click.gains={{1.0,0.5,0,0}};
            for (int v=0;v<4;++v) { click.sounds[v].setSize(1,1); click.sounds[v].setSample(0,0,1.0f); click.soundRates[v]=48000; }
            Preroll p; p.counts[0]=pcm({0.1f}); p.counts[1]=pcm({0.2f}); p.counts[2]=pcm(std::vector<float>(300,0.3f));
            expect(!Preroll::valid(0,4) && !Preroll::valid(100,0) && !Preroll::valid(100,65));
            expect(p.start(100.4L,3)); expectEquals(p.remaining(),int64_t(301));
            std::vector<float> l(600,0), r(600,0); float* out[2]={l.data(),r.data()};
            for (int done=0;done<600;) { const int n=static_cast<int>(juce::jmin<int64_t>(p.active()?p.remaining():64,juce::jmin(64,600-done))); p.render(out,2,done,n,click,48000,true,true); done+=n; }
            expectWithinAbsoluteError(l[0],1.1f,1e-6f); expectWithinAbsoluteError(l[100],0.7f,1e-6f);
            expectWithinAbsoluteError(l[201],0.8f,1e-6f);   // llround(200.8)=201: beat 3 = quarter + "3"
            expectWithinAbsoluteError(l[202],0.3f,1e-6f); expectWithinAbsoluteError(l[500],0.3f,1e-6f);  // tail after the end (301)
            expectEquals(l[501],0.0f); expectEquals(l[1],0.0f); expect(r==l); expect(!p.active());
            expect(p.start(100,2)); p.cancel(); expect(!p.active());
        }

        auto dir=juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_dynguides","",false); dir.createDirectory();
        auto silence=writeWav(dir,"silence.wav",2,4*48000,0.0f);
        auto name=writeWav(dir,"name.wav",1,1,0.5f), one=writeWav(dir,"one.wav",1,1,0.125f);
        auto start=[&](AudioEngine& engine){ engine.prepareToPlay(64,48000); expect(engine.loadTrack("dyn",{silence})); engine.setGuidesEnabled(true); };

        beginTest("Engine: a cue announcing the next section is replaced while an infinite loop wraps, original once released");
        {
            AudioEngine engine; start(engine);
            Guides g; g.add(0.9,name.getFullPathName(),one.getFullPathName(),1.0); g.add(0.95,"",one.getFullPathName(),1.0); expect(g.apply(engine));
            expect(engine.setLoop(0,1,true)); engine.play();
            auto l=render(engine,96000,64);
            expectWithinAbsoluteError(l[43200],0.125f,1e-6f); expectWithinAbsoluteError(l[45600],0.125f,1e-6f);
            expectWithinAbsoluteError(l[48000+43200],0.125f,1e-6f);
            expect(engine.setLoop(0,0,false)); engine.seekToSeconds(0.5); engine.play();
            l=render(engine,24000,64);
            expectWithinAbsoluteError(l[19200],0.5f,1e-6f); expectEquals(l[21600],0.0f);  // count-only cue is silent without wrap
        }

        beginTest("Engine: counted loop replaces on every pass but the last; a queued loop at the loop end keeps the original");
        {
            AudioEngine engine; start(engine);
            Guides g; g.add(0.9,name.getFullPathName(),one.getFullPathName(),1.0); expect(g.apply(engine));
            expect(engine.setLoop(0,1,true,2)); engine.play();
            auto l=render(engine,96000,64);
            expectWithinAbsoluteError(l[43200],0.125f,1e-6f); expectWithinAbsoluteError(l[48000+43200],0.5f,1e-6f);
            engine.stop(); expect(engine.setLoop(0,1,true)); expect(engine.enqueueLoop(1,2)); engine.play();
            l=render(engine,48000,64); expectWithinAbsoluteError(l[43200],0.5f,1e-6f);
        }

        beginTest("Engine pre-roll: one bar of click and count at the section start while the stems wait");
        {
            AudioEngine engine; start(engine);
            auto click=writeWav(dir,"click.wav",1,1,1.0f);
            std::vector<juce::String> counts; for (int k=1;k<=4;++k) counts.push_back(writeWav(dir,"count"+juce::String(k)+".wav",1,1,0.01f*k).getFullPathName());
            expect(engine.loadClickBank({click.getFullPathName(),click.getFullPathName(),click.getFullPathName(),click.getFullPathName()}));
            expect(engine.configureClick(120,4,4,4,0,1.0,0.5,0,0)); engine.setClickEnabled(true);
            expect(preroll(engine,true,{1.0},counts));
            engine.seekToSeconds(1.0); engine.play(); expect(engine.isPrerolling());
            auto l=render(engine,4*24000+64,64);
            expectWithinAbsoluteError(l[0],1.01f,1e-6f);
            for (int b=1;b<4;++b) expectWithinAbsoluteError(l[static_cast<size_t>(b*24000)],0.5f+0.01f*(b+1),1e-6f);
            expectEquals(l[1],0.0f); expectEquals(l[23999],0.0f);
            expectWithinAbsoluteError(l[96000],0.5f,1e-6f);  // the song resumes on its own grid: 1.0 s is beat 3 of bar 1 (quarter)
            expect(!engine.isPrerolling());
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),1.0+64/48000.0,1e-9);
        }

        beginTest("Engine pre-roll: only from a stopped playhead on a configured start; pause, seek and new songs cancel it");
        {
            AudioEngine engine; start(engine);
            auto count=writeWav(dir,"c1.wav",1,1,0.25f);
            expect(engine.configureClick(60,3,4,4,0,1,1,0,0));
            expect(preroll(engine,true,{0.0,2.0},{count.getFullPathName()}));
            engine.seekToSeconds(0.5); engine.play(); expect(!engine.isPrerolling()); engine.pause();
            engine.seekToSeconds(2.0); engine.play(); expect(engine.isPrerolling());
            render(engine,1000,64); expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),2.0,1e-9);
            engine.pause(); expect(!engine.isPrerolling()); engine.play(); expect(engine.isPrerolling());
            auto l=render(engine,3*48000,64);
            expectWithinAbsoluteError(l[0],0.25f,1e-6f);
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),2.0,1e-9);  // 3 beats of 1 s at 60 BPM: exactly done
            engine.play(); expect(!engine.isPrerolling());  // already playing: no count-in
            engine.pause(); engine.seekToSeconds(0.0); engine.play(); expect(engine.isPrerolling()); engine.seekToSeconds(0.0); expect(!engine.isPrerolling());
            engine.stop(); expect(preroll(engine,false,{0.0},{})); engine.play(); expect(!engine.isPrerolling()); engine.stop();
            expect(preroll(engine,true,{0.0},{})); expect(engine.loadTrack("other",{silence})); engine.play(); expect(!engine.isPrerolling());
            expect(!preroll(engine,true,{-1.0},{})); expect(!preroll(engine,true,{0.0},{dir.getChildFile("missing.wav").getFullPathName()}));
        }

        beginTest("Engine pre-roll: the spoken tail keeps sounding into the song");
        {
            AudioEngine engine; start(engine);
            auto longCount=writeWav(dir,"long.wav",1,48000,0.2f);
            expect(engine.configureClick(240,1,4,4,0,0,0,0,0));
            expect(preroll(engine,true,{0.0},{longCount.getFullPathName()}));
            engine.play(); auto l=render(engine,30000,64);
            expectWithinAbsoluteError(l[0],0.2f,1e-6f); expectWithinAbsoluteError(l[12000],0.2f,1e-6f); expectWithinAbsoluteError(l[29999],0.2f,1e-6f);
            expectWithinAbsoluteError(engine.getCurrentPositionSeconds(),18000/48000.0,1e-9);
        }
        dir.deleteRecursively();
    }
} dynamicGuideTests;
