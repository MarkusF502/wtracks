// Soak acelerado (Fase C do plano de consolidação): duas horas de setlist renderizadas mais rápido que o tempo real, pelo mesmo
// caminho do dispositivo (DeckSwitch → AudioEngine), com os dois decks, transições, pré-carga em outra thread, seek, laço contado,
// fade, click com mudança de andamento, buses, automação e cues MIDI. Mede underruns, esperas de read-ahead que estouram, blocos
// mudos enquanto uma música toca, cues duplicados ou perdidos, crescimento de RSS e a duração de cada callback contra o prazo.
//
// Uso: wtracks_soak [--minutes 120] [--block 512] [--rate 44100]. Código de saída 0 = todos os critérios passaram.
// Não substitui o soak em tempo real no aparelho: aqui o render não dorme entre blocos, então o prazo mede custo de CPU, não
// agendamento do sistema, e a leitura do disco tem tempo de sobra (esperamos o read-ahead antes de cada bloco, como teria em tempo real).
#include "AudioEngine.h"
#include "MidiRouter.h"
#include <cstdio>
#include <fstream>
#include <map>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace wtracks;

namespace {
constexpr int kStems = 5;
constexpr double kCueTimes[2] = {5.0, 30.0};   // sem cues dentro do laço contado (10–14 s)

double rssMb() {
    std::ifstream statm("/proc/self/statm");
    long pages = 0, resident = 0;
    statm >> pages >> resident;
    return static_cast<double>(resident) * static_cast<double>(sysconf(_SC_PAGESIZE)) / (1024.0 * 1024.0);
}

juce::File writeStem(const juce::File& dir, const juce::String& name, double rate, double seconds, double freq) {
    auto file = dir.getChildFile(name);
    juce::WavAudioFormat format;
    auto stream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream());
    std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(), rate, 2, 16, {}, 0));
    stream.release();
    const int frames = static_cast<int>(rate * seconds);
    juce::AudioBuffer<float> block(2, 8192);
    for (int offset = 0; offset < frames; offset += 8192) {
        const int n = juce::jmin(8192, frames - offset);
        for (int i = 0; i < n; ++i) {
            const float v = 0.08f * std::sin(2.0f * juce::MathConstants<float>::pi * static_cast<float>(freq) * static_cast<float>(offset + i) / static_cast<float>(rate));
            block.setSample(0, i, v); block.setSample(1, i, v);
        }
        writer->writeFromAudioSampleBuffer(block, 0, n);
    }
    writer.reset();
    return file;
}

// Conta cada cue entregue, identificado pela execução da música (play) e pelo cue (CC: data1 = play % 128, data2 = cue + 2 * (play / 128)).
class CountingSink : public MidiSink {
public:
    void send(const uint8_t* bytes, int size, double) override {
        if (size != 3 || (bytes[0] & 0xF0) != 0xB0) return;
        const int play = bytes[1] + 128 * (bytes[2] >> 1), cue = bytes[2] & 1;
        std::lock_guard<std::mutex> lock(mutex);
        ++counts[{play, cue}];
    }
    std::map<std::pair<int, int>, int> snapshot() { std::lock_guard<std::mutex> lock(mutex); return counts; }
private:
    std::mutex mutex;
    std::map<std::pair<int, int>, int> counts;
};

struct Song { juce::String id; std::vector<juce::File> stems; double length; };

enum class Kind { Crossfade, Overlap, AutoLink, CueNext };
const char* name(Kind k) { switch (k) { case Kind::Crossfade: return "crossfade"; case Kind::Overlap: return "overlap"; case Kind::AutoLink: return "autolink"; default: return "cue-next"; } }
}

int main(int argc, char** argv) {
    double minutes = 120; int block = 512; double rate = 44100;
    for (int i = 1; i + 1 < argc; i += 2) {
        const juce::String key(argv[i]);
        if (key == "--minutes") minutes = std::atof(argv[i + 1]);
        else if (key == "--block") block = std::atoi(argv[i + 1]);
        else if (key == "--rate") rate = std::atof(argv[i + 1]);
    }
    juce::ScopedJuceInitialiser_GUI juce;  // MidiRouter usa uma thread JUCE
    auto dir = juce::File::getSpecialLocation(juce::File::tempDirectory).getNonexistentChildFile("wtracks_soak", "", false);
    dir.createDirectory();
    std::printf("soak: %.0f min simulados, bloco %d, %.0f Hz, arquivos em %s\n", minutes, block, rate, dir.getFullPathName().toRawUTF8());

    // Três músicas de durações diferentes, cinco stems cada.
    std::vector<Song> songs;
    for (int s = 0; s < 3; ++s) {
        Song song{"song" + juce::String(s), {}, 50.0 + 9.0 * s};
        for (int t = 0; t < kStems; ++t)
            song.stems.push_back(writeStem(dir, song.id + "-" + juce::String(t) + ".wav", rate, song.length, 110.0 * (t + 1) + 7 * s));
        songs.push_back(song);
    }

    AudioEngine deckA; AudioEngine deckB(deckA.sharedIo());
    deckA.prepareToPlay(block, rate); deckB.prepareToPlay(block, rate);
    deckA.activate();
    auto* sink = new CountingSink; deckA.attachMidiSink(std::unique_ptr<MidiSink>(sink));
    AudioEngine* active = &deckA; AudioEngine* idle = &deckB;

    std::map<std::pair<int, int>, int> expected;
    int failures = 0;
    const auto fail = [&](const char* what) { ++failures; std::printf("FALHA: %s\n", what); };

    // Configura a música `play` no deck: o mesmo que o Dart faz ao carregar (click, andamento, buses, automação, cues).
    const auto configure = [&](AudioEngine& deck, int play) -> bool {
        const auto& song = songs[static_cast<size_t>(play % 3)];
        if (!deck.loadTrack(song.id, song.stems)) return false;
        bool ok = deck.configureClick(120 + play % 3 * 7, 4, 4, 4, 0, 1, 1, 0.5, 0);
        const double starts[1] = {20.0}, bpms[1] = {96.0}; const int nums[1] = {3}, dens[1] = {4};
        ok = ok && deck.setClickTempoChanges(starts, bpms, nums, dens, 1);
        deck.setClickEnabled(true);
        ok = ok && deck.configureBuses(2) && deck.setChannelBus(0, 0) && deck.setChannelBus(1, 1) && deck.setBus(1, 0.8f, false, 0, false);
        const double aS[1] = {15.0}, aE[1] = {17.0}; const int aP[1] = {2}; const float aV[1] = {0.6f};
        ok = ok && deck.configureMixerAutomation(aS, aE, aP, aV, 1);
        deck.setAutomationEnabled(true);
        uint8_t bytes[6], sizes[2] = {3, 3};
        for (int c = 0; c < 2; ++c) { bytes[3 * c] = 0xB0; bytes[3 * c + 1] = static_cast<uint8_t>(play % 128); bytes[3 * c + 2] = static_cast<uint8_t>(c + 2 * ((play / 128) % 64)); }
        ok = ok && deck.configureCues(kCueTimes, bytes, sizes, 2);
        return ok;
    };
    // Cada cue dispara uma vez por passagem; a música toca até `until` segundos (o fim, ou o fim da janela de transição).
    const auto expectCues = [&](int play, double from, double until) {
        for (int c = 0; c < 2; ++c) if (kCueTimes[c] >= from && kCueTimes[c] < until) ++expected[{play, c}];
    };

    if (!configure(*active, 0)) { std::printf("não carregou a primeira música\n"); return 2; }
    active->play();

    const int64_t totalBlocks = static_cast<int64_t>(minutes * 60.0 * rate / block);
    const double deadlineMs = 1000.0 * block / rate;
    juce::AudioBuffer<float> out(2, block);
    int play = 0;                   // execução atual (índice crescente; a música é play % 3)
    Kind kind = Kind::Crossfade;
    bool preloading = false, preloaded = false, scheduled = false, seekDone = false, loopDone = false, fadeDone = false, cancelDone = false;
    std::thread loader; std::atomic<bool> loadOk{false};
    double playFrom = 0;            // posição de onde a passagem atual começou (para os cues esperados)
    uint64_t readAheadTimeouts = 0, silentBlocks = 0, nonFinite = 0, transitions = 0, cuts = 0;
    std::vector<std::pair<double, double>> rss;  // (minuto simulado, MB)
    const auto started = std::chrono::steady_clock::now();

    for (int64_t b = 0; b < totalBlocks; ++b) {
        const double pos = active->getCurrentPositionSeconds(), length = active->getTotalLengthSeconds();
        const double windowStart = kind == Kind::AutoLink ? length - 0.064 : length - 5.0;

        // Ações de palco em pontos fixos de cada música (variam com a execução).
        if (!seekDone && pos >= 20.0 && play % 4 == 1) {      // volta para antes do primeiro cue: ele toca de novo
            active->seekToSeconds(2.0); expectCues(play, playFrom, 20.0); playFrom = 2.0; seekDone = true;
        }
        if (!loopDone && pos >= 8.0 && pos < 9.0 && play % 3 == 2) { active->setLoop(10.0, 14.0, true, 2); loopDone = true; }
        if (!fadeDone && pos >= 24.0 && play % 5 == 3) { active->setFade(true, 1.0); fadeDone = true; }
        if (fadeDone && pos >= 27.0 && active->isFadeDown()) active->setFade(false, 1.0);

        // Pré-carga da próxima em outra thread, 20 s antes da janela (TransitionController.preloadLeadSeconds).
        if (kind != Kind::CueNext && !preloading && !preloaded && pos >= windowStart - 20.0 && !active->getLoopEnabled()) {
            preloading = true; loadOk = false;
            AudioEngine* target = idle; const int next = play + 1;
            loader = std::thread([&, target, next] { loadOk = configure(*target, next); });
        }
        if (preloading && loader.joinable() && b % 8 == 0) {
            // Sem bloquear o render: só junta a thread quando o carregamento já terminou.
            if (idle->getChannelCount() == kStems || loadOk) { loader.join(); preloading = false; preloaded = loadOk; if (!loadOk) fail("pré-carga falhou"); }
        }
        if (preloaded && !scheduled) {
            const double duration = kind == Kind::AutoLink ? 0.064 : 5.0;
            if (!active->scheduleTransition(idle, kind == Kind::Crossfade ? TransitionKind::Crossfade : TransitionKind::Overlap, windowStart, duration))
                fail("o motor recusou a janela");
            scheduled = true;
            if (!cancelDone && play % 7 == 5) {  // edição da setlist: cancela e agenda de novo
                active->cancelTransition();
                if (!active->scheduleTransition(idle, TransitionKind::Overlap, windowStart, 5.0)) fail("reagendar falhou");
                cancelDone = true;
            }
        }

        // Read-ahead pronto antes do bloco, como teria em tempo real (só conta se estourar 2 s).
        if (!active->waitForReadAhead(block, 2000)) ++readAheadTimeouts;
        if (scheduled && idle->isPlaying() && !idle->waitForReadAhead(block, 2000)) ++readAheadTimeouts;

        juce::AudioSourceChannelInfo info(&out, 0, block);
        active->sharedIo()->deckSwitch.getNextAudioBlock(info);
        const float peak = out.getMagnitude(0, block);
        if (!std::isfinite(peak)) ++nonFinite;
        if (peak < 1e-4f && active->isPlaying() && active->getFadeGain() > 0.05 && pos > 0.2 && pos < length - 0.2) ++silentBlocks;

        const uint32_t events = active->pollTransportEvents();
        if ((events & AudioEngine::TransitionFinished) != 0) {
            // Hand-off como em wtracks_handoff: o deck que entrou vira o ativo; o que saiu para e libera a música.
            expectCues(play, playFrom, windowStart);
            if (!idle->isPlaying()) fail("a música que entrou não está tocando no hand-off");
            idle->activate(); active->finishTransitionAsOutgoing(); active->stop();
            std::swap(active, idle);
            idle->unloadCurrentTrack();
            ++transitions; ++play;
            playFrom = 0;
            preloaded = scheduled = seekDone = loopDone = fadeDone = cancelDone = false;
            kind = static_cast<Kind>(play % 4);
        } else if ((events & AudioEngine::EndReached) != 0 && kind == Kind::CueNext) {
            // Preparar próxima música: carrega no deck que tocava e começa (o app espera o usuário; aqui toca na hora).
            expectCues(play, playFrom, length + 1);
            ++play; ++cuts;
            if (!configure(*active, play)) fail("carregar a próxima no fim falhou");
            active->play();
            playFrom = 0; preloaded = scheduled = seekDone = loopDone = fadeDone = cancelDone = false;
            kind = static_cast<Kind>(play % 4);
        } else if ((events & AudioEngine::EndReached) != 0 && !scheduled) {
            fail("a música acabou sem a transição agendada");
        }

        if (b % static_cast<int64_t>(600.0 * rate / block) == 0) {   // a cada 10 min simulados
            const double minute = static_cast<double>(b) * block / rate / 60.0;
            rss.push_back({minute, rssMb()});
            const auto s = active->getRenderStats();
            std::printf("  %6.1f min: RSS %.1f MB, %d músicas, callback p99 %.1f%% máx %.2f ms (prazo %.2f ms)\n",
                        minute, rss.back().second, play, 100 * s.p99Load, s.maxMs, deadlineMs);
            std::fflush(stdout);
        }
    }
    if (loader.joinable()) loader.join();
    expectCues(play, playFrom, active->getCurrentPositionSeconds());  // a passagem que ainda tocava quando o soak acabou
    juce::Thread::sleep(300);  // o roteador MIDI entrega com atraso fixo

    // ---- critérios ----
    const auto delivered = sink->snapshot();
    int missing = 0, duplicated = 0;
    for (auto& [key, count] : expected) {
        const auto it = delivered.find(key);
        const int got = it == delivered.end() ? 0 : it->second;
        if (got < count) missing += count - got;
        if (got > count) duplicated += got - count;
        if (got != count) std::printf("  cue: execução %d (%s), cue %d em %.0f s: esperado %d, entregue %d\n", key.first,
                                      name(static_cast<Kind>(key.first % 4)), key.second, kCueTimes[key.second], count, got);
    }
    for (auto& [key, count] : delivered) if (key.first < play && !expected.count(key)) {  // cue que não devia tocar
        duplicated += count;
        std::printf("  cue: execução %d (%s), cue %d em %.0f s: não esperado, entregue %d\n", key.first,
                    name(static_cast<Kind>(key.first % 4)), key.second, kCueTimes[key.second], count);
    }
    const auto stats = [&] { auto a = deckA.getRenderStats(), b = deckB.getRenderStats(); return std::make_pair(a, b); }();
    const uint64_t underruns = deckA.getUnderrunCount() + deckB.getUnderrunCount();
    const uint64_t overruns = stats.first.overruns + stats.second.overruns;
    const double maxMs = std::max(stats.first.maxMs, stats.second.maxMs);
    const double p99 = std::max(stats.first.p99Load, stats.second.p99Load);
    // Crescimento depois do aquecimento: a partir dos 10 min, o maior valor contra o primeiro.
    double growth = 0;
    if (rss.size() >= 3) { double peak = 0; for (size_t i = 1; i < rss.size(); ++i) peak = std::max(peak, rss[i].second); growth = peak - rss[1].second; }
    const double wall = std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count();

    std::printf("\nresultado (%.0f min simulados em %.0f s, %.0fx o tempo real):\n", minutes, wall, minutes * 60 / wall);
    std::printf("  músicas tocadas: %d (transições %llu, cortes de Preparar próxima %llu)\n", play, (unsigned long long)transitions, (unsigned long long)cuts);
    std::printf("  underruns: %llu; esperas de read-ahead estouradas: %llu; blocos mudos tocando: %llu; amostras não finitas: %llu\n",
                (unsigned long long)underruns, (unsigned long long)readAheadTimeouts, (unsigned long long)silentBlocks, (unsigned long long)nonFinite);
    std::printf("  cues: %zu esperados, %d perdidos, %d duplicados\n", expected.size(), missing, duplicated);
    std::printf("  RSS: %.1f MB aos 10 min, crescimento máximo depois disso %.1f MB\n", rss.size() > 1 ? rss[1].second : 0.0, growth);
    std::printf("  callback (CPU, sem dormir): p99 %.1f%% do prazo, máx %.2f ms de %.2f ms, %llu acima do prazo\n",
                100 * p99, maxMs, deadlineMs, (unsigned long long)overruns);

    if (underruns) fail("underrun");
    if (readAheadTimeouts) fail("read-ahead não ficou pronto em 2 s");
    if (silentBlocks) fail("bloco mudo com a música tocando");
    if (nonFinite) fail("amostra não finita");
    if (missing || duplicated) fail("cues perdidos ou duplicados");
    if (play < static_cast<int>(minutes / 1.5)) fail("menos músicas do que o esperado (a setlist travou?)");
    if (growth > 24.0) fail("RSS cresce depois do aquecimento");
    if (overruns) std::printf("  aviso: %llu callbacks passaram do prazo (sem dormir entre blocos, pode ser preempção do sistema)\n", (unsigned long long)overruns);

    deckA.attachMidiSink(nullptr);
    dir.deleteRecursively();
    std::printf(failures == 0 ? "\nSOAK OK\n" : "\nSOAK FALHOU (%d)\n", failures);
    return failures == 0 ? 0 : 1;
}
