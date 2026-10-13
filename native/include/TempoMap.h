#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

namespace wtracks {
// Tempo / meter changes along the song. Playback stores a tempo map (SongTempo{BPM, timecode}) and precomputes the click
// grid per song-map element (see analysis/click-songmap-findings.md); the segment arithmetic here is our own: a change
// restarts the bar count (accent on its downbeat) at its start time.
struct TempoChange {
    double start = 0;  // seconds on the timeline the caller renders (already scaled for processed audio)
    double bpm = 120;
    int numerator = 4, denominator = 4;
};

struct TempoLocation {
    long double origin = 0;  // sample where this segment's grid starts
    double bpm = 120;
    int numerator = 4, denominator = 4;
    int64_t limit = std::numeric_limits<int64_t>::max();  // first sample that belongs to the next segment
};

inline bool tempoChangesValid(const std::vector<TempoChange>& changes, double baseOffset) {
    if (changes.size() > 512) return false;
    double previous = baseOffset;
    for (const auto& c : changes) {
        const bool unit = c.denominator > 0 && c.denominator <= 64 && (c.denominator & (c.denominator - 1)) == 0;
        if (!std::isfinite(c.start) || c.start <= previous || c.start > 86400 || !std::isfinite(c.bpm) || c.bpm < 1 || c.bpm > 1000
            || c.numerator < 1 || c.numerator > 64 || !unit) return false;
        previous = c.start;
    }
    return true;
}

// Segment containing `sample`. The base segment starts at `baseOffset`; samples before it have no grid (index < 0 upstream).
inline TempoLocation locateTempo(double baseBpm, int baseNumerator, int baseDenominator, double baseOffset,
                                 const std::vector<TempoChange>& changes, int64_t sample, double rate) noexcept {
    TempoLocation location;
    location.origin = static_cast<long double>(baseOffset) * rate; location.bpm = baseBpm;
    location.numerator = baseNumerator; location.denominator = baseDenominator;
    if (changes.empty()) return location;
    auto boundary = [&](const TempoChange& c) { return static_cast<int64_t>(std::llround(c.start * rate)); };
    // first change whose boundary lies beyond the sample
    size_t lo = 0, hi = changes.size();
    while (lo < hi) { const size_t mid = (lo + hi) / 2; if (boundary(changes[mid]) <= sample) lo = mid + 1; else hi = mid; }
    if (lo > 0) {
        const auto& c = changes[lo - 1];
        location.origin = static_cast<long double>(c.start) * rate; location.bpm = c.bpm;
        location.numerator = c.numerator; location.denominator = c.denominator;
    }
    if (lo < changes.size()) location.limit = boundary(changes[lo]);
    return location;
}
}
