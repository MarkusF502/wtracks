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
//
// Dynamic guides: Playback's GuideCue carries a normal and a replacement resource (cueFilePath /
// replacementCountCueFilePath) and GuideAU "selects normal or replacement resource" when a cue fires
// (subsystem-contracts.md). The selection rule is not recovered; ours (own choice): a cue announcing a section
// (`targetSeconds`, song time) that the playhead will not reach because the active loop wraps first plays its
// replacement (a spoken count) instead. A cue may have only a replacement: it is silent unless the loop wraps.
class GuideTimeline {
public:
    struct Sound { std::vector<float> mono; double sourceRate=44100; };
    struct Cue {
        double timeSeconds=0; float gain=1; std::shared_ptr<const Sound> sound;
        std::shared_ptr<const Sound> replacement; double targetSeconds=-1;  // -1: announces nothing, never replaced
    };
    bool configure(std::vector<Cue> proposed) {
        double previous=-1;
        std::unordered_set<const Sound*> validated;
        for (const auto& cue:proposed) {
            if (!std::isfinite(cue.timeSeconds) || cue.timeSeconds<0 || cue.timeSeconds>86400
                || cue.timeSeconds<previous || !std::isfinite(cue.gain) || cue.gain<0 || cue.gain>2
                || (!cue.sound && !cue.replacement) || !(cue.targetSeconds==-1
                || (std::isfinite(cue.targetSeconds) && cue.targetSeconds>=0 && cue.targetSeconds<=86400))) return false;
            for (const auto* s:{cue.sound.get(),cue.replacement.get()}) {
                if (!s) continue;
                if (s->mono.empty() || !std::isfinite(s->sourceRate) || s->sourceRate<1 || s->sourceRate>384000) return false;
                if (validated.insert(s).second)
                    for (float sample:s->mono) if (!std::isfinite(sample)) return false;
            }
            previous=cue.timeSeconds;
        }
        cues=std::move(proposed);reset();return true;
    }
    // Cue times are song time; the audio runs `scale` times longer (processed tempo). Callers reset afterwards.
    void setTimeScale(double scale) noexcept { timeScale=scale; reset(); }
    void reset() noexcept { for (auto& v:voices) v={}; initialized=false; }
    size_t size() const noexcept { return cues.size(); }
    // Adds mono output. No memory ownership changes, allocations, or I/O here. `wrapSample` (processed timeline) is
    // where the active loop jumps back during this pass, or -1 when the playhead will run on past the loop end.
    void render(float* output,int count,int64_t position,double deviceRate,bool audible=true,int64_t wrapSample=-1) noexcept {
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
                const Sound* chosen=replaced(cue,wrapSample) ? cue.replacement.get() : cue.sound.get();
                if (!chosen) continue;
                *slot={chosen,cue.gain,sample,++serial};
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
    // The target counts as unreachable from 1 ms before the wrap point on (section boundaries round independently).
    bool replaced(const Cue& c,int64_t wrapSample) const noexcept {
        return wrapSample>=0 && c.targetSeconds>=0
            && static_cast<long double>(c.targetSeconds)*timeScale*rate >= static_cast<long double>(wrapSample)-rate*0.001;
    }
    std::vector<Cue> cues;std::array<Voice,4> voices{};size_t next=0;double rate=44100;double timeScale=1;
    int64_t expectedPosition=0;uint64_t serial=0;bool initialized=false;
};
}
