#include "GuideTimeline.h"
#include <stdexcept>
#include <string>
#ifndef WTRACKS_GUIDE_STANDALONE
#include <juce_core/juce_core.h>
#endif
namespace {
void check(bool valid,const char* label) {if(!valid)throw std::runtime_error(label);}
bool near(float a,float b){return std::abs(a-b)<1e-5f;}
std::shared_ptr<const wtracks::GuideTimeline::Sound> sound(std::vector<float> pcm,double rate=44100) {
    auto s=std::make_shared<wtracks::GuideTimeline::Sound>();s->mono=std::move(pcm);s->sourceRate=rate;return s;
}
void runGuideTests() {
    using G=wtracks::GuideTimeline;
    for(double rate:{44100.,48000.}) for(int block:{64,256,1024}) {
        G g;auto impulse=sound({1},rate);check(g.configure({{.123,1,impulse},{.456,.5f,impulse}}),"configure");
        const int count=static_cast<int>(rate);std::vector<float> out(count);
        for(int p=0;p<count;p+=block)g.render(out.data()+p,std::min(block,count-p),p,rate);
        for(int i=0;i<count;++i)check(near(out[i],i==std::llround(.123*rate)?1.f:i==std::llround(.456*rate)?.5f:0.f),"absolute impulse block independence");
    }
    G g;auto impulse=sound({1,0},44100);check(g.configure({{1,1,impulse}}),"seek config");
    for(int delta:{-1,0,1}) {g.reset();float out[3]={};g.render(out,3,44100+delta,44100);check(near(out[delta<0?1:0],delta>0?0:1),"seek boundary");}
    float one=0;g.reset();g.render(&one,1,44100,44100);check(one==1,"loop first");one=0;g.render(&one,1,44101,44100);check(one==0,"no duplicate");g.reset();g.render(&one,1,44100,44100);check(one==1,"loop reset repeat");
    auto longSound=sound(std::vector<float>(20,1),44100);
    check(g.configure({{0,1,longSound},{0,1,longSound},{0,1,longSound},{0,1,longSound},{0,.5f,longSound}}),"overlap");one=0;g.render(&one,1,0,44100);check(one==3.5f,"oldest steal four slots");
    check(g.configure({{0,1,longSound}}),"mute config");float muted[2]={};g.render(muted,2,0,44100,false);check(muted[0]==0&&muted[1]==0,"mute silent");one=0;g.render(&one,1,2,44100);check(one==1,"mute advances tail");
    one=0;g.render(&one,1,3,48000);check(one==0,"rate change drops tails and skips past cues");
    check(g.configure({{0,1,sound({1,0},24000)}}),"resample config");float resampled[4]={};g.render(resampled,4,0,48000);check(near(resampled[0],1)&&near(resampled[1],.5)&&resampled[2]==0,"linear source rate conversion");
    const auto previous=g.size();check(!g.configure({{-1,1,impulse}})&&g.size()==previous,"negative preserve");check(!g.configure({{2,1,impulse},{1,1,impulse}})&&g.size()==previous,"unsorted preserve");
    check(!g.configure({{NAN,1,impulse}})&&g.size()==previous,"nan preserve");check(!g.configure({{0,INFINITY,impulse}})&&g.size()==previous,"gain preserve");check(!g.configure({{0,1,sound({NAN})}})&&g.size()==previous,"invalid pcm preserve");check(!g.configure({{0,1,sound({1},0)}})&&g.size()==previous,"invalid rate preserve");
}
#ifdef WTRACKS_GUIDE_STANDALONE
}
int main(){runGuideTests();}
#else
class GuideTimelineTests:public juce::UnitTest {
public:GuideTimelineTests():UnitTest("GuideTimeline exact reconstructed scheduler","WTracks"){}
void runTest() override {beginTest("sample scheduling, voices, seek, loop, mute, rate, invalid state preservation");try{runGuideTests();expect(true);}catch(const std::exception& e){expect(false,e.what());}}
} guideTimelineTests;
}
#endif
