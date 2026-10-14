#pragma once
#include <array>
#include <atomic>
#include <cstdint>

// Duração do callback de áudio em relação ao prazo (numSamples / sampleRate). Seguro para a thread de áudio: só atômicos,
// sem alocação e sem lock. Os percentis vêm de um histograma da carga (duração/prazo) em passos de 2,5 %, então são
// limites superiores com essa resolução; o máximo é exato.
class RenderStats {
public:
    static constexpr int kBuckets = 40;  // 0..100 % em passos de 2,5 %; o 41º conta o que passou do prazo

    struct Snapshot {
        uint64_t callbacks = 0;
        uint64_t overruns = 0;       // callbacks que levaram mais que o prazo
        double maxMs = 0;            // maior duração
        double maxLoad = 0;          // maior duração / prazo
        double p50Load = 0, p95Load = 0, p99Load = 0;
        double lastDeadlineMs = 0;
    };

    void record(int64_t durationNs, int64_t deadlineNs) noexcept
    {
        if (deadlineNs <= 0) return;
        const double load = static_cast<double>(durationNs) / static_cast<double>(deadlineNs);
        int bucket = static_cast<int>(load * kBuckets);
        if (bucket < 0) bucket = 0;
        if (bucket > kBuckets) bucket = kBuckets;
        histogram[static_cast<size_t>(bucket)].fetch_add(1, std::memory_order_relaxed);
        callbacks.fetch_add(1, std::memory_order_relaxed);
        if (durationNs > deadlineNs) overruns.fetch_add(1, std::memory_order_relaxed);
        raise(maxNs, durationNs);
        raise(maxLoadMicro, static_cast<int64_t>(load * 1e6));
        lastDeadline.store(deadlineNs, std::memory_order_relaxed);
    }

    Snapshot snapshot() const noexcept
    {
        Snapshot s;
        std::array<uint64_t, kBuckets + 1> h {};
        uint64_t total = 0;
        for (size_t i = 0; i < h.size(); ++i) { h[i] = histogram[i].load(std::memory_order_relaxed); total += h[i]; }
        s.callbacks = callbacks.load(std::memory_order_relaxed);
        s.overruns = overruns.load(std::memory_order_relaxed);
        s.maxMs = static_cast<double>(maxNs.load(std::memory_order_relaxed)) / 1e6;
        s.maxLoad = static_cast<double>(maxLoadMicro.load(std::memory_order_relaxed)) / 1e6;
        s.lastDeadlineMs = static_cast<double>(lastDeadline.load(std::memory_order_relaxed)) / 1e6;
        s.p50Load = percentile(h, total, 0.50);
        s.p95Load = percentile(h, total, 0.95);
        s.p99Load = percentile(h, total, 0.99);
        return s;
    }

    void reset() noexcept
    {
        for (auto& b : histogram) b.store(0, std::memory_order_relaxed);
        callbacks.store(0); overruns.store(0); maxNs.store(0); maxLoadMicro.store(0);
    }

private:
    static void raise(std::atomic<int64_t>& target, int64_t value) noexcept
    {
        auto current = target.load(std::memory_order_relaxed);
        while (value > current && !target.compare_exchange_weak(current, value, std::memory_order_relaxed)) {}
    }

    static double percentile(const std::array<uint64_t, kBuckets + 1>& h, uint64_t total, double q) noexcept
    {
        if (total == 0) return 0;
        const auto target = static_cast<uint64_t>(q * static_cast<double>(total - 1)) + 1;  // posição 1-based
        uint64_t seen = 0;
        for (size_t i = 0; i < h.size(); ++i) {
            seen += h[i];
            if (seen >= target) return static_cast<double>(i + 1) / kBuckets;  // limite superior do balde
        }
        return 1.0 + 1.0 / kBuckets;
    }

    std::array<std::atomic<uint64_t>, kBuckets + 1> histogram {};
    std::atomic<uint64_t> callbacks { 0 }, overruns { 0 };
    std::atomic<int64_t> maxNs { 0 }, maxLoadMicro { 0 }, lastDeadline { 0 };
};
