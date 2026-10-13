#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <memory>
#include <vector>
#include <unordered_set>

namespace wtracks {
// Reconstructed behavior: exact rounded sample cues, four voices, oldest steal.
// Control-thread configure/reset and render must be externally synchronized.
class GuideTimeline {
public:
    struct Sound { std::vector<float> mono; double sourceRate=44100; };
    struct Cue { double timeSeconds=0; float gain=1; std::shared_ptr<const Sound> sound; };
    bool configure(std::vector<Cue> proposed) {
        double previous=-1;
        std::unordered_set<const Sound*> validated;
        for (const auto& cue:proposed) {
            if (!std::isfinite(cue.timeSeconds) || cue.timeSeconds<0 || cue.timeSeconds>86400
                || cue.timeSeconds<previous || !std::isfinite(cue.gain) || cue.gain<0 || cue.gain>2
                || !cue.sound || cue.sound->mono.empty() || !std::isfinite(cue.sound->sourceRate)
                || cue.sound->sourceRate<1 || cue.sound->sourceRate>384000) return false;
            if (validated.insert(cue.sound.get()).second)
                for (float sample:cue.sound->mono) if (!std::isfinite(sample)) return false;
            previous=cue.timeSeconds;
        }
        cues=std::move(proposed);reset();return true;
    }
    // Cue times are song time; the audio runs `scale` times longer (processed tempo). Callers reset afterwards.
    void setTimeScale(double scale) noexcept { timeScale=scale; reset(); }
    void reset() noexcept { for (auto& v:voices) v={}; initialized=false; }
    size_t size() const noexcept { return cues.size(); }
    // Adds mono output. No memory ownership changes, allocations, or I/O here.
    void render(float* output,int count,int64_t position,double deviceRate,bool audible=true) noexcept {
        if (!output || count<=0 || position<0 || !std::isfinite(deviceRate) || deviceRate<1 || deviceRate>384000
            || position>std::numeric_limits<int64_t>::max()-count) return;
        if (!initialized || deviceRate!=rate || position!=expectedPosition) {
            for (auto& v:voices) v={};
            rate=deviceRate;next=0;
            while (next<cues.size() && eventSample(cues[next])<position) ++next;
            initialized=true;
        }
        for (int i=0;i<count;++i) {
            const auto sample=position+i;
            while (next<cues.size() && eventSample(cues[next])<=sample) {
                auto* slot=&voices[0];
                for (auto& v:voices) {
                    if (!v.sound) { slot=&v;break; }
                    if (v.serial<slot->serial) slot=&v;
                }
                const auto& cue=cues[next++];
                *slot={cue.sound.get(),cue.gain,sample,++serial};
            }
            float mixed=0;
            for (auto& v:voices) {
                if (!v.sound) continue;
                const long double cursor=static_cast<long double>(sample-v.start)*v.sound->sourceRate/rate;
                if (cursor>=v.sound->mono.size()) {v={};continue;}
                const auto frame=static_cast<size_t>(cursor);const float fraction=static_cast<float>(cursor-frame);
                const auto& pcm=v.sound->mono;
                const float right=frame+1<pcm.size()?pcm[frame+1]:0;
                mixed+=v.gain*(pcm[frame]+(right-pcm[frame])*fraction);
            }
            if (audible) output[i]+=mixed;
        }
        expectedPosition=position+count;
    }
private:
    struct Voice {const Sound* sound=nullptr;float gain=0;int64_t start=0;uint64_t serial=0;};
    int64_t eventSample(const Cue& c) const noexcept {return static_cast<int64_t>(std::llround(c.timeSeconds*timeScale*rate));}
    std::vector<Cue> cues;std::array<Voice,4> voices{};size_t next=0;double rate=44100;double timeScale=1;
    int64_t expectedPosition=0;uint64_t serial=0;bool initialized=false;
};
}
