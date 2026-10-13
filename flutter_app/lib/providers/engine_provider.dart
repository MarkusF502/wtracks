import 'dart:async';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/track.dart';
import '../models/song_section.dart';
import '../models/guide_cue.dart';
import '../services/guide_resource_service.dart';
import '../services/guide_preferences_store.dart';
import '../services/dynamic_guides.dart';
import '../models/guide_settings.dart';
import '../models/app_settings.dart';
import '../services/app_preferences_store.dart';
import '../services/time_pitch_service.dart';
import '../services/midi_preferences_store.dart';
import '../models/automation_cue.dart';
import '../models/mixer_automation.dart';
import '../models/timecode_settings.dart';
import '../models/tempo_change.dart';
import '../models/time_pitch_settings.dart';
import 'setlist_provider.dart';
import 'waveform_provider.dart';
import '../native/wtracks_bindings.dart';
import '../services/persistence_service.dart';
import '../services/click_resource_service.dart';

final clickResourceServiceProvider = Provider<ClickResourceService>(
  (ref) => ClickResourceService(),
);
final midiPreferencesProvider = Provider<MidiPreferencesStore>((ref) => MidiPreferencesStore());

@immutable
class MidiState {
  final List<MidiDevice> devices;
  final String? selectedId; // saída escolhida (persistida)
  final bool connected;
  final String? error;
  const MidiState({this.devices = const [], this.selectedId, this.connected = false, this.error});
  MidiState copyWith({List<MidiDevice>? devices, Object? selectedId = _keep, bool? connected, Object? error = _keep}) => MidiState(
        devices: devices ?? this.devices,
        selectedId: identical(selectedId, _keep) ? this.selectedId : selectedId as String?,
        connected: connected ?? this.connected,
        error: identical(error, _keep) ? this.error : error as String?,
      );
  static const _keep = Object();
}

/// Escolha e conexão da saída MIDI. O motor guarda a conexão; aqui ficam a
/// lista, a preferência persistida e a mensagem de erro para a interface.
class MidiController extends Notifier<MidiState> {
  @override
  MidiState build() => const MidiState();

  Future<void> refresh() async {
    final engine = ref.read(engineProvider);
    final saved = state.selectedId ?? await ref.read(midiPreferencesProvider).loadOutputId();
    state = state.copyWith(devices: engine.listMidiOutputs(), selectedId: saved, connected: engine.midiOutputOpen);
  }

  /// Conecta à saída [id] e a memoriza; em falha mantém a conexão anterior.
  Future<bool> select(String id) async {
    final engine = ref.read(engineProvider);
    final previous = state.selectedId;
    if (!engine.openMidiOutput(id)) {
      state = state.copyWith(error: 'Não foi possível abrir a saída MIDI.', connected: engine.midiOutputOpen);
      return false;
    }
    state = state.copyWith(selectedId: id, connected: true, error: null);
    if (previous != id) {
      try {
        await ref.read(midiPreferencesProvider).saveOutputId(id);
      } on Exception catch (e) {
        debugPrint('Não foi possível memorizar a saída MIDI: $e');
      }
    }
    return true;
  }

  void disconnect() {
    ref.read(engineProvider).closeMidiOutput();
    state = state.copyWith(connected: false, error: null);
  }

  /// Abre a saída preferida se necessário (melhor esforço, usado ao carregar músicas com MIDI).
  Future<bool> ensureOpen() async {
    final engine = ref.read(engineProvider);
    if (engine.midiOutputOpen) return true;
    final id = state.selectedId ?? await ref.read(midiPreferencesProvider).loadOutputId();
    if (id == null) return false;
    return select(id);
  }

  bool sendTest(List<int> bytes) {
    final ok = ref.read(engineProvider).sendMidi(bytes);
    if (!ok) state = state.copyWith(error: 'Conecte uma saída MIDI antes de testar.');
    return ok;
  }
}

final midiControllerProvider = NotifierProvider<MidiController, MidiState>(MidiController.new);

/// Click ligado no transporte (o motor guarda o estado; aqui fica a interface).
final clickEnabledProvider = StateProvider<bool>((ref) => false);

/// Última automação entregue pelo motor (para a interface mostrar).
final firedAutomationProvider = StateProvider<AutomationCue?>((ref) => null);

/// Valores do mixer movidos pela automação na posição atual (null quando a automação não age na música).
final automatedMixProvider = StateProvider<MixState?>((ref) => null);

final timePitchServiceProvider = Provider<TimePitchService>(
  (ref) => TimePitchService(),
);
final guideResourceServiceProvider = Provider<GuideResourceService>(
  (ref) => GuideResourceService(),
);
final guideResourcesProvider = FutureProvider<List<Map<String, dynamic>>>(
  (ref) => ref.read(guideResourceServiceProvider).resources(),
);
final guideCatalogProvider = FutureProvider<GuideCatalog>(
  (ref) async => GuideCatalog((await ref.watch(guideResourcesProvider.future)).map((r) => r['name'] as String)),
);
final guidePreferencesProvider = Provider<GuidePreferencesStore>((ref) => GuidePreferencesStore());
final appPreferencesProvider = Provider<AppPreferencesStore>((ref) => AppPreferencesStore());

/// Preferências gerais (começa nos padrões e assume o arquivo quando ele é lido).
class AppSettingsNotifier extends Notifier<AppSettings> {
  bool _touched = false;

  bool _disposed = false;

  @override
  AppSettings build() {
    ref.onDispose(() => _disposed = true);
    _load(ref.read(engineProvider), ref.read(appPreferencesProvider));
    return const AppSettings();
  }

  Future<void> _load(WTracksEngine engine, AppPreferencesStore store) async {
    final saved = await store.load();
    if (_touched || _disposed) return;
    state = saved;
    engine.setStereoSplit(saved.stereoSplit);
    _applyCustomDirectories(saved);
  }

  /// As pastas personalizadas valem a partir do próximo catálogo lido.
  void _applyCustomDirectories(AppSettings settings) {
    ref.read(clickResourceServiceProvider).customDirectory = settings.customClicksDirectory;
    ref.read(guideResourceServiceProvider).customDirectory = settings.customGuidesDirectory;
    ref.invalidate(guideResourcesProvider);
    ref.invalidate(clickFamiliesProvider);
  }

  Future<void> apply(AppSettings settings) async {
    _touched = true;
    final directoriesChanged = settings.customClicksDirectory != state.customClicksDirectory ||
        settings.customGuidesDirectory != state.customGuidesDirectory;
    state = settings;
    ref.read(engineProvider).setStereoSplit(settings.stereoSplit);
    if (directoriesChanged) {
      _applyCustomDirectories(settings);
      ref.read(currentTrackProvider.notifier).invalidateGuideResources();
      unawaited(ref.read(currentTrackProvider.notifier).refreshGuides());
    }
    try {
      await ref.read(appPreferencesProvider).save(settings);
    } on Exception catch (e) {
      debugPrint('Não foi possível salvar as preferências: $e');
    }
  }
}

final appSettingsProvider = NotifierProvider<AppSettingsNotifier, AppSettings>(AppSettingsNotifier.new);

/// Preferências globais de guia. Começa nos padrões; quando o arquivo é lido, as guias da música carregada são
/// refeitas (o carregamento de músicas não espera pelo disco).
class GuideSettingsNotifier extends Notifier<GuideSettings> {
  bool _touched = false;

  @override
  GuideSettings build() {
    _load();
    return const GuideSettings();
  }

  Future<void> _load() async {
    final saved = await ref.read(guidePreferencesProvider).load();
    if (_touched || saved == state) return;
    state = saved;
    await ref.read(currentTrackProvider.notifier).refreshGuides();
  }

  /// Aplica e salva; as guias da música carregada são refeitas.
  Future<bool> apply(GuideSettings settings) async {
    _touched = true;
    if (settings == state) return true;
    state = settings;
    final ok = await ref.read(currentTrackProvider.notifier).refreshGuides();
    try {
      await ref.read(guidePreferencesProvider).save(settings);
    } on Exception catch (e) {
      debugPrint('Não foi possível salvar as preferências de guia: $e');
    }
    return ok;
  }
}

final guideSettingsProvider = NotifierProvider<GuideSettingsNotifier, GuideSettings>(GuideSettingsNotifier.new);

/// Guias dinâmicas da música carregada (para as telas); o motor recebe a mesma geração.
final dynamicGuidePlanProvider = Provider<DynamicGuidePlan?>((ref) {
  final track = ref.watch(currentTrackProvider);
  final catalog = ref.watch(guideCatalogProvider).asData?.value;
  if (track == null || catalog == null) return null;
  return generateDynamicGuides(sections: track.sections, click: track.clickSettings, tempoChanges: track.tempoChanges,
      settings: ref.watch(guideSettingsProvider), catalog: catalog);
});

final clickFamiliesProvider = FutureProvider<List<String>>(
  (ref) => ref.read(clickResourceServiceProvider).families(),
);

/// Instância única do engine nativo -- todo o app depende deste provider.
/// keepAlive porque o engine precisa sobreviver enquanto o app estiver
/// rodando, não só enquanto uma tela específica estiver montada.
final engineProvider = Provider<WTracksEngine>((ref) {
  final engine = WTracksEngine();
  final ready = engine.initialise();

  ref.onDispose(engine.shutdown);

  if (!ready) {
    // A tela que consome isso decide como avisar o usuário -- aqui só
    // deixamos registrado pra depuração via wtracks_get_last_error().
    debugPrint('WTracksEngine.initialise() falhou.');
  }

  return engine;
});

/// A música atualmente carregada no engine (ou null se nenhuma).
/// Widgets de mixer/canal leem daqui em vez de perguntar pro engine
/// canal por canal.
class CurrentTrackNotifier extends Notifier<Track?> {
  int _generation = 0;
  bool _disposed = false;
  Future<void> _pending = Future.value();
  int get loadGeneration => _generation;
  String? loadingTrackId;

  @override
  Track? build() {
    ref.onDispose(() { _disposed = true; _generation++; });
    return null;
  }

  /// Serialize native loads: every isolate addresses the same C++ engine.
  /// A superseded result must not publish UI state or mixer settings.
  Future<bool> load(Track track) {
    final generation = ++_generation;
    loadingTrackId = track.id;
    final engine = ref.read(engineProvider);
    final transport = ref.read(transportProvider.notifier);
    final operation = _pending.then((_) async {
      if (_disposed || generation != _generation) return false;
      await transport.stop();
      if (_disposed || generation != _generation) return false;
      try {
        final clickPaths = await ref
            .read(clickResourceServiceProvider)
            .prepare(track.clickSettings.timbreFamily);
        if (_disposed || generation != _generation) return false;
        // Processed stems (tom/andamento) are rendered offline and cached; failures leave the engine untouched.
        final audioPaths = track.timePitch.isIdentity
            ? track.channelFilePaths
            : await ref.read(timePitchServiceProvider).prepare(engine, track);
        if (_disposed || generation != _generation) return false;
        final loaded = await engine.loadTrackAsync(track.id, audioPaths);
        if (_disposed || generation != _generation) {
          if (!_disposed && loaded) {
            engine.unloadTrack();
            state = null;
          }
          return false;
        }
        if (!loaded) {
          debugPrint('Falha ao carregar música: ${engine.lastError}');
          return false;
        }
        if (!track.timePitch.isIdentity && !engine.setTimeScale(track.timePitch.timeFactor)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        final bankLoaded = await engine.loadClickBankAsync(clickPaths);
        if (_disposed || generation != _generation) {
          if (!_disposed) engine.unloadTrack();
          return false;
        }
        if (!bankLoaded) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        if (!engine.configureClick(track.clickSettings)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        if (!engine.setClickTempoChanges(track.tempoChanges)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        await _syncPresetLoops(engine, track.sections, force: true);
        await _syncSkips(engine, track.sections, force: true);
        if (_disposed || generation != _generation) {
          if (!_disposed) engine.unloadTrack();
          return false;
        }
        _guideSchedule = null;
        _prerollSignature = null;
        final guidesLoaded = await _syncGuides(engine, track);
        if (_disposed || generation != _generation) {
          if (!_disposed) engine.unloadTrack();
          return false;
        }
        if (!guidesLoaded) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        engine.setGuidesEnabled(track.guidesEnabled);
        if (!_sendMidiSchedule(engine, track)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        if (!_applyBuses(engine, track)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        engine.setStereoSplit(ref.read(appSettingsProvider).stereoSplit);
        if (!engine.configureMixerAutomation(_automationPointsFor(track))) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        engine.setAutomationEnabled(track.automationEnabled);
        engine.setEndFade(track.endFade ? Track.fadeSeconds : 0);
        engine.setMidiClockEnabled(track.midiClockEnabled);
        if (!engine.configureTimecode(track.timecode)) {
          engine.unloadTrack();
          state = null;
          return false;
        }
        if (track.midiClockEnabled || track.automationCues.any((c) => c.midiBytes.isNotEmpty)) {
          await ref.read(midiControllerProvider.notifier).ensureOpen(); // best effort: the song plays without MIDI
        }
        state = track;
        for (var i = 0; i < track.channels.length; i++) {
          engine.setChannelVolume(i, track.channels[i].volume);
          engine.setChannelRoute(i, track.channels[i].route);
          engine.setChannelExcludedFromFade(i, track.channels[i].excludeFromFade);
        }
        engine.setMasterVolume(track.masterVolume);
        _syncEffectiveMutes();
        return true;
      } catch (e) {
        debugPrint('Exceção ao carregar música: $e');
        return false;
      } finally {
        if (generation == _generation) loadingTrackId = null;
      }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  Future<void> unload() {
    final generation = ++_generation;
    loadingTrackId = null;
    final engine = ref.read(engineProvider);
    final stopping = ref.read(transportProvider.notifier).stop();
    final operation = _pending.then((_) async {
      await stopping;
      engine.unloadTrack();
      if (!_disposed && generation == _generation) state = null;
    });
    _pending = operation;
    return operation;
  }

  void setChannelVolume(int index, double volume) {
    final track = state;
    if (track == null) return;

    ref.read(engineProvider).setChannelVolume(index, volume);

    final updatedChannels = [...track.channels];
    updatedChannels[index] = updatedChannels[index].copyWith(volume: volume);
    state = track.copyWith(channels: updatedChannels);
  }

  double? timePitchProgress; // 0..1 enquanto renderiza; null fora disso
  final timePitchListeners = <void Function()>[];
  void _notifyTimePitch() {
    for (final listener in timePitchListeners.toList()) {
      listener();
    }
  }

  /// Cancela a renderização de tom/andamento em andamento.
  void cancelTimePitch() => ref.read(timePitchServiceProvider).cancel(ref.read(engineProvider));

  /// Aplica tom/andamento: renderiza primeiro (o motor não é tocado se falhar),
  /// recarrega a música processada e volta à mesma posição. A reprodução fica
  /// pausada e laços ativos são descartados.
  Future<bool> setTimePitch(String trackId, TimePitchSettings settings) async {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null || !settings.isValid) return false;
    if (track.timePitch == settings) return true;
    final engine = ref.read(engineProvider);
    final position = engine.currentPositionSeconds;
    final generation = _generation;
    final updated = track.copyWith(timePitch: settings);
    try {
      if (!settings.isIdentity) {
        timePitchProgress = 0;
        _notifyTimePitch();
        await ref.read(timePitchServiceProvider).prepare(engine, updated, onProgress: (p) {
          timePitchProgress = p;
          _notifyTimePitch();
        });
      }
    } catch (e) {
      debugPrint('Falha no tom/andamento: $e');
      return false;
    } finally {
      timePitchProgress = null;
      _notifyTimePitch();
    }
    if (_disposed || generation != _generation || state?.id != trackId) return false;
    if (await load(updated)) {
      engine.seekToSeconds(position);
      return true;
    }
    // Reload failed: restore the previous rendering so the song stays playable.
    await load(track);
    return false;
  }

  /// Troca a saída do canal; o estado só muda se o motor aceitou a rota.
  bool setChannelRoute(int index, ChannelRoute route) {
    final track = state;
    if (track == null || index < 0 || index >= track.channels.length) return false;
    if (!ref.read(engineProvider).setChannelRoute(index, route)) return false;
    final updatedChannels = [...track.channels];
    updatedChannels[index] = updatedChannels[index].copyWith(route: route);
    state = track.copyWith(channels: updatedChannels);
    return true;
  }

  void setMasterVolume(double volume) {
    final track = state;
    if (track == null || !volume.isFinite) return;
    final clamped = volume.clamp(0.0, 2.0).toDouble();
    ref.read(engineProvider).setMasterVolume(clamped);
    state = track.copyWith(masterVolume: clamped);
  }

  void setChannelMuted(int index, bool muted) {
    final track = state;
    if (track == null) return;

    final updatedChannels = [...track.channels];
    updatedChannels[index] = updatedChannels[index].copyWith(muted: muted);
    state = track.copyWith(channels: updatedChannels);

    _syncEffectiveMutes();
  }

  /// Alterna solo no canal [index]. Solo não existe no AudioEngine nativo --
  /// é resolvido aqui: quando 1+ canais estão solados, todo canal NÃO
  /// solado recebe mute efetivo no engine, preservando o mute manual do
  /// usuário para quando o solo for desligado.
  void toggleChannelSolo(int index) {
    final track = state;
    if (track == null) return;

    final updatedChannels = [...track.channels];
    updatedChannels[index] =
        updatedChannels[index].copyWith(soloed: !updatedChannels[index].soloed);
    state = track.copyWith(channels: updatedChannels);

    _syncEffectiveMutes();
  }

  /// Recalcula, para cada canal, se ele deve estar mutado de fato no
  /// engine (mute manual OU existe solo ativo e este canal não é ele) e
  /// aplica via setChannelMuted -- sem alterar o campo `muted` do modelo,
  /// que continua refletindo só a intenção manual do usuário.
  void _syncEffectiveMutes() {
    final track = state;
    if (track == null) return;

    final engine = ref.read(engineProvider);
    final anySoloed = track.channels.any((c) => c.soloed) || track.buses.any((b) => b.soloed);
    bool busSoloed(String? id) => track.buses.any((b) => b.id == id && b.soloed);

    // O solo tem sua própria porta no motor: um mute automatizado não pode desfazê-lo. Escolha própria para buses:
    // com algo solado, soa a faixa solada ou de bus solado, e o bus solado ou que contém uma faixa solada.
    for (var i = 0; i < track.channels.length; i++) {
      final channel = track.channels[i];
      engine.setChannelMuted(i, channel.muted);
      engine.setChannelSoloMuted(i, anySoloed && !channel.soloed && !busSoloed(channel.busId));
    }
    for (var b = 0; b < track.buses.length; b++) {
      final bus = track.buses[b];
      final holdsSolo = track.channels.any((c) => c.busId == bus.id && c.soloed);
      engine.setBusSoloMuted(b, anySoloed && !bus.soloed && !holdsSolo);
    }
  }

  /// Substitui a track atual por [track] sem tocar no engine nativo --
  /// usado pelo [TrackLibraryNotifier.saveCurrent] pra refletir os
  /// `filePath`s atualizados depois que os arquivos de áudio são movidos
  /// pro diretório permanente pelo PersistenceService.
  void setLoadedTrack(Track track) {
    state = track;
  }

  /// Renomeia a track atual (só o estado em memória -- não persiste
  /// sozinho; quem chamar decide se quer também salvar em disco, ex: via
  /// [TrackLibraryNotifier.saveCurrent]).
  void renameCurrent(String title) {
    final track = state;
    if (track == null) return;
    state = track.copyWith(title: title);
  }

  /// Agenda MIDI enviada ao motor (o índice disparado aponta para cá).
  List<ScheduledMidi> midiSchedule = const [];

  bool _sendMidiSchedule(WTracksEngine engine, Track track) {
    final schedule = buildMidiSchedule(track.automationCues, track.midiBuses, track.activeMidiBankId);
    if (!engine.configureMidiSchedule(schedule)) return false;
    midiSchedule = schedule;
    return true;
  }

  /// Troca o MIDI da música (cues, bancos, buses, banco ativo); o motor valida antes de o estado mudar.
  bool updateMidi(String trackId, {List<AutomationCue>? cues, List<MidiBank>? banks, List<MidiBus>? buses, Object? activeBankId = _keepBank,
      bool? clockEnabled}) {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null) return false;
    final updated = track.copyWith(
      automationCues: cues == null ? null : List.unmodifiable(cues),
      midiBanks: banks == null ? null : List.unmodifiable(banks),
      midiBuses: buses == null ? null : List.unmodifiable(buses),
      activeMidiBankId: activeBankId,
      midiClockEnabled: clockEnabled,
    );
    final bankIds = {for (final b in updated.midiBanks) b.id};
    if (!AutomationCue.validSequence(updated.automationCues) ||
        (updated.activeMidiBankId != null && !bankIds.contains(updated.activeMidiBankId)) ||
        updated.midiBanks.length != bankIds.length ||
        updated.midiBuses.map((b) => b.id).toSet().length != updated.midiBuses.length ||
        !updated.midiBanks.every((b) => b.isValid) ||
        !updated.midiBuses.every((b) => b.isValid)) {
      return false;
    }
    final engine = ref.read(engineProvider);
    if (!_sendMidiSchedule(engine, updated)) return false;
    engine.setMidiClockEnabled(updated.midiClockEnabled);
    state = updated;
    return true;
  }

  static const _keepBank = Object();

  /// Troca automações e relógio MIDI; o motor valida antes de o estado mudar.
  bool updateAutomation(String trackId, List<AutomationCue> cues, bool clockEnabled) =>
      updateMidi(trackId, cues: cues, clockEnabled: clockEnabled);

  List<AutomationPoint> _automationPointsFor(Track track) => automationPoints(
      track.mixerAutomation, track.clickSettings, track.tempoChanges,
      channelCount: track.channels.length, busCount: track.buses.length);

  /// Envia os buses e a atribuição das faixas ao motor (a ordem de [Track.buses] é o índice nativo).
  bool _applyBuses(WTracksEngine engine, Track track) {
    if (track.buses.length > SongBus.maxBuses || !engine.configureBuses(track.buses.length)) return false;
    for (var b = 0; b < track.buses.length; b++) {
      if (!engine.setBus(b, track.buses[b])) return false;
    }
    for (var i = 0; i < track.channels.length; i++) {
      if (!engine.setChannelBus(i, track.busIndex(track.channels[i].busId))) return false;
    }
    return true;
  }

  /// Troca a lista de buses/atribuições: o motor recebe tudo de novo (buses removidos soltam suas faixas).
  bool _replaceBuses(Track updated) {
    final engine = ref.read(engineProvider);
    if (!_applyBuses(engine, updated)) {
      final previous = state;
      if (previous != null) _applyBuses(engine, previous);
      return false;
    }
    state = updated;
    _resendMixerAutomation(updated);
    _syncEffectiveMutes();
    return true;
  }

  bool addBus(SongBus bus) {
    final track = state;
    if (track == null || track.buses.length >= SongBus.maxBuses || !bus.isValid || track.buses.any((b) => b.id == bus.id)) {
      return false;
    }
    return _replaceBuses(track.copyWith(buses: [...track.buses, bus]));
  }

  bool removeBus(String id) {
    final track = state;
    if (track == null || !track.buses.any((b) => b.id == id)) return false;
    return _replaceBuses(track.copyWith(
      buses: track.buses.where((b) => b.id != id).toList(),
      channels: [for (final c in track.channels) c.busId == id ? c.copyWith(busId: null) : c],
    ));
  }

  bool assignChannelToBus(int index, String? busId) {
    final track = state;
    if (track == null || index < 0 || index >= track.channels.length || (busId != null && track.busIndex(busId) < 0)) return false;
    final channels = [...track.channels];
    channels[index] = channels[index].copyWith(busId: busId);
    return _replaceBuses(track.copyWith(channels: channels));
  }

  /// Volume, mute, rota ou nome de um bus.
  bool updateBus(SongBus bus) {
    final track = state;
    final index = track?.busIndex(bus.id) ?? -1;
    if (track == null || index < 0 || !bus.isValid) return false;
    if (!ref.read(engineProvider).setBus(index, bus)) return false;
    final buses = [...track.buses];
    buses[index] = bus;
    state = track.copyWith(buses: buses);
    _syncEffectiveMutes();
    return true;
  }

  void toggleBusSolo(String id) {
    final bus = state?.buses.where((b) => b.id == id).firstOrNull;
    if (bus != null) updateBus(bus.copyWith(soloed: !bus.soloed));
  }

  /// Troca a automação do mixer; o motor valida antes de o estado mudar.
  bool updateMixerAutomation(String trackId, List<MixerAutomationCue> cues) {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null || !MixerAutomationCue.validSequence(cues)) return false;
    final updated = track.copyWith(mixerAutomation: List.unmodifiable(cues));
    if (!ref.read(engineProvider).configureMixerAutomation(_automationPointsFor(updated))) return false;
    state = updated;
    return true;
  }

  /// Botão de transporte "Automação": desligado, valem os faders manuais.
  void setAutomationEnabled(bool enabled) {
    final track = state;
    if (track == null) return;
    ref.read(engineProvider).setAutomationEnabled(enabled);
    state = track.copyWith(automationEnabled: enabled);
  }

  /// Fade nos últimos 5 s da música (SongArrangement.endFade).
  void setEndFade(bool enabled) {
    final track = state;
    if (track == null) return;
    ref.read(engineProvider).setEndFade(enabled ? Track.fadeSeconds : 0);
    state = track.copyWith(endFade: enabled);
  }

  void setChannelExcludedFromFade(int index, bool excluded) {
    final track = state;
    if (track == null || index < 0 || index >= track.channels.length) return;
    ref.read(engineProvider).setChannelExcludedFromFade(index, excluded);
    final channels = [...track.channels];
    channels[index] = channels[index].copyWith(excludeFromFade: excluded);
    state = track.copyWith(channels: channels);
  }

  /// O que a setlist faz quando esta música termina.
  void setTransition(SongTransition transition) {
    final track = state;
    if (track != null) state = track.copyWith(transition: transition);
  }

  /// A duração das transições é medida em tempos: mudanças de andamento movem o início das rampas.
  void _resendMixerAutomation(Track track) {
    if (track.mixerAutomation.isEmpty) return;
    if (!ref.read(engineProvider).configureMixerAutomation(_automationPointsFor(track))) {
      debugPrint('Automação do mixer recusada: ${ref.read(engineProvider).lastError}');
    }
  }

  /// Aplica o timecode; o motor valida antes de o estado mudar.
  bool updateTimecode(String trackId, TimecodeSettings settings) {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null || !settings.isValid) return false;
    if (!ref.read(engineProvider).configureTimecode(settings)) return false;
    state = track.copyWith(timecode: settings);
    return true;
  }

  List<ScheduledGuide>? _guideSchedule;
  String? _prerollSignature;

  /// Envia ao motor a agenda de guias (manuais + dinâmicas das seções) e o pré-roll de [track]. Só decodifica o que
  /// mudou. Se a parte dinâmica falhar, fica a agenda só com as manuais (a música toca); false só quando nem essa
  /// é aceita (o motor mantém a anterior). Falha no pré-roll só é registrada.
  Future<bool> _syncGuides(WTracksEngine engine, Track track) async {
    final settings = ref.read(guideSettingsProvider);
    final needsCatalog = track.sections.isNotEmpty &&
        (settings.sectionPreroll ||
            (settings.dynamicEnabled && (settings.countIntoEachSection || track.sections.any((s) => s.playGuideCue || s.playCountIn))));
    final catalog = needsCatalog ? await ref.read(guideCatalogProvider.future) : GuideCatalog(const []);
    final service = ref.read(guideResourceServiceProvider);
    final plan = generateDynamicGuides(sections: track.sections, click: track.clickSettings, tempoChanges: track.tempoChanges,
        settings: settings, catalog: catalog);
    final schedule = buildGuideSchedule(track.guideCues, plan.cues);
    if (_guideSchedule == null || !listEquals(schedule, _guideSchedule)) {
      Future<bool> send(List<ScheduledGuide> guides) async {
        try {
          final names = {for (final g in guides) ...[?g.resource, ?g.replacement]}.toList();
          final paths = names.isEmpty ? <String, String>{} : Map.fromIterables(names, await service.prepare(names));
          if (await engine.configureGuideScheduleAsync(guides, paths)) {
            _guideSchedule = guides;
            return true;
          }
          debugPrint('Agenda de guias recusada: ${engine.lastError}');
        } catch (e) {
          debugPrint('Falha ao preparar guias: $e');
        }
        return false;
      }
      if (!await send(schedule)) {
        final manual = buildGuideSchedule(track.guideCues, const []);
        if (plan.cues.isEmpty || !await send(manual)) return false;
        debugPrint('Guias dinâmicas indisponíveis; ficam só as manuais.');
      }
    }
    final counts = settings.sectionPreroll ? prerollCounts(catalog, settings) : const <String?>[];
    final starts = settings.sectionPreroll ? [for (final s in track.sections) s.playStart] : const <double>[];
    final signature = '${settings.sectionPreroll}|$starts|$counts';
    if (signature != _prerollSignature) {
      try {
        final names = counts.whereType<String>().toList();
        final paths = names.isEmpty ? <String, String>{} : Map.fromIterables(names, await service.prepare(names));
        if (await engine.configurePrerollAsync(settings.sectionPreroll, starts, [for (final n in counts) n == null ? null : paths[n]])) {
          _prerollSignature = signature;
        } else {
          debugPrint('Pré-roll indisponível: ${engine.lastError}');
        }
      } catch (e) {
        debugPrint('Falha ao preparar o pré-roll: $e');
      }
    }
    return true;
  }

  /// Os arquivos por trás dos nomes de recurso mudaram (pasta personalizada): a próxima sincronização envia tudo de novo.
  void invalidateGuideResources() {
    _guideSchedule = null;
    _prerollSignature = null;
  }

  /// Refaz as guias da música carregada (seções, andamento ou preferências mudaram).
  Future<bool> refreshGuides() {
    final generation = _generation;
    final operation = _pending.then((_) async {
      if (_disposed || generation != _generation || loadingTrackId != null) return false;
      final track = state;
      if (track == null) return false;
      try {
        return await _syncGuides(ref.read(engineProvider), track);
      } catch (e) {
        debugPrint('Falha nas guias: $e');
        return false;
      }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  Future<bool> updateGuides(String trackId, List<GuideCue> cues, bool enabled) {
    if (state?.id != trackId || loadingTrackId != null || !GuideCue.validSequence(cues)) return Future.value(false);
    final generation=_generation;
    final operation=_pending.then((_) async {
      try {
        final engine=ref.read(engineProvider);
        final current=state;
        if (_disposed || generation != _generation || current == null || current.id != trackId) return false;
        // Only the switch changed: the native schedule stays as prepared.
        if (!listEquals(current.guideCues, cues) && !await _syncGuides(engine, current.copyWith(guideCues: cues))) return false;
        if (_disposed || generation != _generation || state?.id != trackId) return false;
        engine.setGuidesEnabled(enabled);
        state=state!.copyWith(guideCues:List.unmodifiable(cues),guidesEnabled:enabled);
        return true;
      } catch(e) { debugPrint('Falha nas guias: $e'); return false; }
    });
    _pending=operation.then((_){});
    return operation;
  }

  int _loopRequest = 0;
  void cancelLoopPreparation() { ++_loopRequest; }
  bool _loopBusy = false;
  bool get loopBusy => _loopBusy;

  Future<bool> setSectionLoop(SongSection section, {bool queue = false}) {
    final track = state;
    if (track == null || loadingTrackId != null || _loopBusy ||
        !track.sections.any((s) => s.id == section.id && s.playStart == section.playStart && s.playEnd == section.playEnd)) {
      return Future.value(false);
    }
    final generation = _generation;
    final request = _loopRequest;
    _loopBusy = true;
    final operation = _pending.then((_) async {
      try {
        if (_disposed || generation != _generation) return false;
        final engine = ref.read(engineProvider);
        final ok = queue ? await engine.enqueueLoopAsync(section.playStart, section.playEnd, repeats: section.loopCount)
          : await engine.setLoopAsync(section.playStart, section.playEnd, true, repeats: section.loopCount);
        if (_disposed || generation != _generation || request != _loopRequest) {
          if (!_disposed) {
            engine.setLoop(0, 0, false);
            ref.read(transportProvider.notifier).refresh();
          }
          return false;
        }
        ref.read(transportProvider.notifier).refresh();
        return ok;
      } catch (e) {
        debugPrint('Falha ao preparar loop: $e');
        return false;
      } finally { _loopBusy = false; }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  List<String> _presetSignature = const [];

  /// Keeps the engine's preset (auto-engaging) loops in line with the sections. Failures are logged: the song still plays,
  /// only the automatic vamp loop is missing.
  Future<bool> _syncPresetLoops(WTracksEngine engine, List<SongSection> sections, {bool force = false}) async {
    final presets = [for (final s in sections) if (s.presetInfiniteLoop) s];
    final signature = [for (final s in presets) '${s.id}:${s.playStart}:${s.playEnd}'];
    if (!force && listEquals(signature, _presetSignature)) return true;
    try {
      final ok = await engine.configurePresetLoopsAsync(presets);
      if (ok) {
        _presetSignature = signature;
      } else {
        debugPrint('Laços predefinidos indisponíveis: ${engine.lastError}');
      }
      return ok;
    } catch (e) {
      debugPrint('Falha nos laços predefinidos: $e');
      return false;
    }
  }

  List<(double, double)> _skipSignature = const [];

  /// Áreas cortadas das seções no motor (falha só é registrada: a música toca sem pular).
  Future<bool> _syncSkips(WTracksEngine engine, List<SongSection> sections, {bool force = false}) async {
    final areas = SongSection.trimAreas(sections);
    if (!force && listEquals(areas, _skipSignature)) return true;
    try {
      final ok = await engine.configureSkipsAsync(areas);
      if (ok) {
        _skipSignature = areas;
      } else {
        debugPrint('Cortes de seção indisponíveis: ${engine.lastError}');
      }
      return ok;
    } catch (e) {
      debugPrint('Falha nos cortes de seção: $e');
      return false;
    }
  }

  bool updateSections(String trackId, List<SongSection> sections) {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null || _loopBusy || !SongSection.validSequence(sections)) return false;
    final engine = ref.read(engineProvider);
    final loop = engine.loopState;
    bool matches(SongSection s, double start, double end) =>
      (s.playStart - start).abs() <= 0.001 && (s.playEnd - end).abs() <= 0.001;
    bool removed(double start, double end) => track.sections.any((s) => matches(s, start, end)) && !sections.any((s) => matches(s, start, end));
    if (loop[0] == 1 && removed(loop[1], loop[2])) {
      if (!engine.setLoop(0, 0, false)) return false;
    } else if (loop[3] == 1 && removed(loop[4], loop[5])) {
      engine.clearQueuedLoop();
    }
    ref.read(transportProvider.notifier).refresh();
    state = track.copyWith(sections: List.unmodifiable(sections));
    final generation = _generation;
    _pending = _pending.then((_) async {
      if (_disposed || generation != _generation) return;
      await _syncPresetLoops(engine, sections);
      await _syncSkips(engine, sections);
    });
    refreshGuides();
    return true;
  }

  Future<bool> updateClickTimbre(String family) {
    final track = state;
    if (track == null || loadingTrackId != null) return Future.value(false);
    final generation = _generation;
    final operation = _pending.then((_) async {
      try {
        final paths = await ref
            .read(clickResourceServiceProvider)
            .prepare(family);
        if (_disposed || generation != _generation || state?.id != track.id) {
          return false;
        }
        final engine = ref.read(engineProvider);
        final bankLoaded = await engine.loadClickBankAsync(paths);
        if (_disposed || generation != _generation || !bankLoaded) return false;
        return updateClickSettings(
          state!.clickSettings.copyWith(timbreFamily: family),
        );
      } catch (e) {
        debugPrint('Falha no timbre: $e');
        return false;
      }
    });
    _pending = operation.then((_) {});
    return operation;
  }

  /// Mudanças de andamento/compasso da música; o motor valida antes de o estado mudar.
  bool updateTempoChanges(String trackId, List<TempoChange> changes) {
    final track = state;
    if (track == null || track.id != trackId || loadingTrackId != null ||
        !TempoChange.validSequence(changes, baseOffset: track.clickSettings.beatOffsetSeconds)) {
      return false;
    }
    if (!ref.read(engineProvider).setClickTempoChanges(changes)) return false;
    state = track.copyWith(tempoChanges: List.unmodifiable(changes));
    _resendMixerAutomation(state!);
    refreshGuides();
    return true;
  }

  bool updateClickSettings(ClickSettings settings) {
    final track = state;
    if (track == null || loadingTrackId != null || !settings.isValid) {
      return false;
    }
    final engine = ref.read(engineProvider);
    if (!engine.configureClick(settings)) return false;
    // The engine drops changes at or before the new click offset; mirror that so state and engine agree.
    final keep = TempoChange.validSequence(track.tempoChanges, baseOffset: settings.beatOffsetSeconds);
    state = track.copyWith(clickSettings: settings, tempoChanges: keep ? track.tempoChanges : const []);
    if (!keep) engine.setClickTempoChanges(const []);
    _resendMixerAutomation(state!);
    refreshGuides(); // the bar before each section moved with the grid
    return true;
  }

  void updateBpm(double bpm) {
    final settings = state?.clickSettings;
    if (settings != null) updateClickSettings(settings.copyWith(bpm: bpm));
  }

  void applyCalibratedBpm(double bpm) {
    final settings = state?.clickSettings;
    if (settings != null) {
      updateClickSettings(settings.copyWith(bpm: bpm, calibrated: true));
  }
  }

  void applyClickOffset(double offsetSeconds) {
    final settings = state?.clickSettings;
    if (settings != null) {
      updateClickSettings(settings.copyWith(beatOffsetSeconds: offsetSeconds));
    }
  }
}

final currentTrackProvider =
    NotifierProvider<CurrentTrackNotifier, Track?>(CurrentTrackNotifier.new);

/// Instância única do serviço de persistência em disco (JSON local).
final persistenceServiceProvider = Provider<PersistenceService>((ref) => PersistenceService());

/// Lista de tracks salvas, carregada do disco via [PersistenceService].
/// Alimenta a tela de biblioteca.
class TrackLibraryNotifier extends Notifier<List<Track>> {
  @override
  List<Track> build() {
    _load();
    return [];
  }

  Future<void> _load() async {
    final tracks = await ref.read(persistenceServiceProvider).loadAllTracks();
    state = tracks;
  }

  Future<void> refresh() => _load();

  /// Salva a track atualmente carregada no engine (via [currentTrackProvider])
  /// em disco -- move os arquivos de áudio pro diretório permanente e grava
  /// o JSON. Atualiza tanto [currentTrackProvider] (com os paths novos)
  /// quanto esta lista, sem precisar reler tudo do disco.
  Future<void> saveCurrent() async {
    final track = ref.read(currentTrackProvider);
    if (track == null) return;

    final saved = await ref.read(persistenceServiceProvider).saveTrack(track);

    if (ref.read(currentTrackProvider)?.id == saved.id) {
      ref.read(currentTrackProvider.notifier).setLoadedTrack(saved);
    }

    final index = state.indexWhere((t) => t.id == saved.id);
    if (index >= 0) {
      final updated = [...state];
      updated[index] = saved;
      state = updated;
    } else {
      state = [...state, saved];
    }
  }

  Future<void> deleteTrack(String id) async {
    final persistence = ref.read(persistenceServiceProvider);
    final current = ref.read(currentTrackProvider.notifier);
    if (ref.read(currentTrackProvider)?.id == id || current.loadingTrackId == id) {
      await current.unload();
    }
    await ref.read(waveformProvider.notifier).forget(id);
    for (final setlist in await persistence.loadAllSetlists()) {
      if (setlist.tracks.any((track) => track.id == id)) {
        await persistence.saveSetlist(setlist.withTrackRemoved(id));
      }
    }
    await persistence.deleteTrack(id);
    await ref.read(setlistLibraryProvider.notifier).refresh();
    final editor = ref.read(setlistEditorProvider);
    if (editor != null) {
      ref.read(setlistEditorProvider.notifier).setLoadedSetlist(editor.withTrackRemoved(id));
    }
    state = state.where((t) => t.id != id).toList();
  }

  /// Troca a transição de setlist da música [id] (carregada ou não) e salva.
  Future<void> setTransition(String id, SongTransition transition) async {
    final index = state.indexWhere((t) => t.id == id);
    if (index < 0) return;
    final saved = await ref.read(persistenceServiceProvider).saveTrack(state[index].copyWith(transition: transition));
    state = [...state]..[index] = saved;
    if (ref.read(currentTrackProvider)?.id == id) ref.read(currentTrackProvider.notifier).setTransition(transition);
    final editor = ref.read(setlistEditorProvider);
    if (editor != null && editor.tracks.any((t) => t.id == id)) {
      ref.read(setlistEditorProvider.notifier).setLoadedSetlist(
          editor.copyWith(tracks: [for (final t in editor.tracks) t.id == id ? t.copyWith(transition: transition) : t]));
    }
  }

  /// Renomeia a track [id] direto na biblioteca (não precisa estar
  /// carregada no engine). Se for a track atualmente carregada, atualiza
  /// também o [currentTrackProvider] pra UI de performance refletir na
  /// hora.
  Future<void> renameTrack(String id, String newTitle) async {
    final index = state.indexWhere((t) => t.id == id);
    if (index < 0) return;

    final renamed = state[index].copyWith(title: newTitle);
    final saved = await ref.read(persistenceServiceProvider).saveTrack(renamed);

    final updated = [...state];
    updated[index] = saved;
    state = updated;

    if (ref.read(currentTrackProvider)?.id == id) {
      ref.read(currentTrackProvider.notifier).setLoadedTrack(saved);
    }
  }
}

final trackLibraryProvider =
    NotifierProvider<TrackLibraryNotifier, List<Track>>(TrackLibraryNotifier.new);

/// Estado de transporte (posição/duração/tocando) atualizado por polling a
/// cada 100ms -- mesmo princípio do Timer do app de teste JUCE, só que
/// centralizado aqui em vez de espalhado pela UI.
class TransportState {
  final double positionSeconds;
  final double lengthSeconds;
  final bool isPlaying;
  final bool loopEnabled;
  final double loopStart, loopEnd;
  final bool queuedLoopEnabled;
  final double queuedLoopStart, queuedLoopEnd;
  final int underrunCount;
  /// Contagem do pré-roll de seção em curso (a posição espera no início da seção).
  final bool prerolling;
  /// Fade de saída em curso (botão de transporte).
  final bool fading;
  const TransportState({this.positionSeconds = 0, this.lengthSeconds = 0, this.isPlaying = false,
    this.loopEnabled = false, this.loopStart = 0, this.loopEnd = 0,
    this.queuedLoopEnabled = false, this.queuedLoopStart = 0, this.queuedLoopEnd = 0, this.underrunCount = 0,
    this.prerolling = false, this.fading = false, this.loopPass = 0, this.loopRepeats = 0});
  /// Volta atual do laço (1..) e repetições (0 = até soltar).
  final int loopPass, loopRepeats;
  bool activeSection(SongSection section) => loopEnabled &&
      (loopStart - section.playStart).abs() <= 0.001 && (loopEnd - section.playEnd).abs() <= 0.001;
  bool queuedSection(SongSection section) => queuedLoopEnabled &&
      (queuedLoopStart - section.playStart).abs() <= 0.001 && (queuedLoopEnd - section.playEnd).abs() <= 0.001;
  @override
  bool operator ==(Object other) => other is TransportState &&
      other.positionSeconds == positionSeconds && other.lengthSeconds == lengthSeconds && other.isPlaying == isPlaying &&
      other.loopEnabled == loopEnabled && other.loopStart == loopStart && other.loopEnd == loopEnd &&
      other.queuedLoopEnabled == queuedLoopEnabled && other.queuedLoopStart == queuedLoopStart && other.queuedLoopEnd == queuedLoopEnd && other.underrunCount == underrunCount &&
      other.prerolling == prerolling && other.fading == fading && other.loopPass == loopPass && other.loopRepeats == loopRepeats;
  @override
  int get hashCode => Object.hash(positionSeconds, lengthSeconds, isPlaying, loopEnabled, loopStart, loopEnd,
      queuedLoopEnabled, queuedLoopStart, queuedLoopEnd, underrunCount, prerolling, fading, loopPass, loopRepeats);
}

class TransportNotifier extends Notifier<TransportState> {
  Timer? _timer;
  static const _bgChannel = MethodChannel('wtracks/background');

  @override
  TransportState build() {
    final engine = ref.watch(engineProvider);
    _timer = Timer.periodic(const Duration(milliseconds: 100), (_) {
      final next = _snapshot(engine);
      // Parado, nada muda entre ticks -- evita rebuild 10x/s à toa.
      if (_backgroundActive && !next.isPlaying) {
        _backgroundActive = false;
        unawaited(_background('stop'));
      }
      if (next != state) state = next;
      final events = engine.pollTransportEvents();
      if (events != 0) unawaited(ref.read(setlistSessionProvider.notifier).songFinished());
      final track = ref.read(currentTrackProvider);
      final automated = track != null && track.automationEnabled && track.mixerAutomation.isNotEmpty;
      final mix = automated ? engine.mixState() : null;
      if (mix != ref.read(automatedMixProvider)) ref.read(automatedMixProvider.notifier).state = mix;
      final cues = track?.automationCues ?? const <AutomationCue>[];
      if (cues.isNotEmpty) {
        final fired = engine.pollCues();
        if (fired.isNotEmpty) {
          final schedule = ref.read(currentTrackProvider.notifier).midiSchedule;
          final last = fired.last;
          final source = last >= 0 && last < schedule.length ? schedule[last].source : -1;
          if (source >= 0 && source < cues.length) ref.read(firedAutomationProvider.notifier).state = cues[source];
        }
      }
    });
    ref.onDispose(() {
      _timer?.cancel();
      ++_playGeneration;
    });
    return const TransportState();
  }

  TransportState _snapshot(WTracksEngine engine) {
    final loop = engine.loopState;
    final pass = engine.loopPass;
    return TransportState(positionSeconds: engine.currentPositionSeconds,
      lengthSeconds: engine.totalLengthSeconds, isPlaying: engine.isPlaying,
      loopEnabled: loop[0] == 1, loopStart: loop[1], loopEnd: loop[2],
      queuedLoopEnabled: loop[3] == 1, queuedLoopStart: loop[4], queuedLoopEnd: loop[5],
      underrunCount: engine.underrunCount, prerolling: engine.isPrerolling, fading: engine.fadeGain >= 0,
      loopPass: pass.$1, loopRepeats: pass.$2);
  }
  void refresh() { final next = _snapshot(ref.read(engineProvider)); if (next != state) state = next; }
  bool disableLoop() { final ok = ref.read(engineProvider).setLoop(0, 0, false); if (ok) refresh(); return ok; }
  void clearQueuedLoop() { ref.read(engineProvider).clearQueuedLoop(); refresh(); }

  bool _backgroundActive = false;
  int _playGeneration = 0;
  Future<void> _backgroundQueue = Future.value();

  Future<void> _background(String method, [Map<String, Object>? arguments]) {
    final operation = _backgroundQueue.then((_) async {
      try {
        await _bgChannel.invokeMethod<void>(method, arguments);
      } on MissingPluginException catch (e) {
        debugPrint('Background indisponível: $e');
      } on PlatformException catch (e) {
        debugPrint('Falha no background: $e');
      }
    });
    _backgroundQueue = operation;
    return operation;
  }

  Future<void> play() async {
    final generation = ++_playGeneration;
    final engine = ref.read(engineProvider);
    final title = ref.read(currentTrackProvider)?.title ?? 'WTracks';
    await _background('requestNotificationPermission');
    if (generation != _playGeneration) return;
    engine.play();
    if (!engine.isPlaying) return;
    _backgroundActive = true;
    await _background('start', {'title': title});
  }

  Future<void> pause() async {
    ++_playGeneration;
    ref.read(engineProvider).pause();
    _backgroundActive = false;
    await _background('stop');
  }

  Future<void> stop() async {
    ++_playGeneration;
    ref.read(currentTrackProvider.notifier).cancelLoopPreparation();
    ref.read(engineProvider).stop();
    refresh();
    _backgroundActive = false;
    await _background('stop');
  }

  void seekTo(double seconds) => ref.read(engineProvider).seekToSeconds(seconds);

  /// Botão de transporte "5 Second Fade Out": termina pausando (e a setlist segue a transição da música).
  bool fadeOut() {
    final ok = ref.read(engineProvider).startFadeOut(Track.fadeSeconds);
    refresh();
    return ok;
  }
}

/// Setlist em execução: a música atual é `setlist.tracks[index]`.
@immutable
class SetlistSession {
  final Setlist setlist;
  final int index;
  const SetlistSession(this.setlist, this.index);
  Track get current => setlist.tracks[index];
  Track? get next => index + 1 < setlist.tracks.length ? setlist.tracks[index + 1] : null;
  Track? get previous => index > 0 ? setlist.tracks[index - 1] : null;
}

/// Navegação na setlist e transições ao fim da música (Playback: "Cue Next Song" carrega a próxima, parada no
/// início; "Stay In Song" fica). A música aberta fora de uma setlist encerra a sessão.
class SetlistSessionNotifier extends Notifier<SetlistSession?> {
  @override
  SetlistSession? build() => null;

  void begin(Setlist setlist, int index) {
    if (index >= 0 && index < setlist.tracks.length) state = SetlistSession(setlist, index);
  }

  void end() => state = null;

  /// Carrega a música [index] da setlist (versão mais recente da biblioteca).
  Future<bool> go(int index) async {
    final session = state;
    if (session == null || index < 0 || index >= session.setlist.tracks.length) return false;
    final listed = session.setlist.tracks[index];
    final track = ref.read(trackLibraryProvider).where((t) => t.id == listed.id).firstOrNull ?? listed;
    final ok = await ref.read(currentTrackProvider.notifier).load(track);
    if (ok && identical(state, session)) state = SetlistSession(session.setlist, index);
    return ok;
  }

  Future<bool> next() => go((state?.index ?? -2) + 1);
  Future<bool> previous() => go((state?.index ?? 0) - 1);

  /// Fim da música ou do fade: aplica a transição da música atual.
  Future<void> songFinished() async {
    final session = state;
    final track = ref.read(currentTrackProvider);
    if (session == null || track == null || track.id != session.current.id) return;
    if (track.transition == SongTransition.stayInSong || session.next == null) return;
    await go(session.index + 1);
  }
}

final setlistSessionProvider = NotifierProvider<SetlistSessionNotifier, SetlistSession?>(SetlistSessionNotifier.new);

final transportProvider =
    NotifierProvider<TransportNotifier, TransportState>(TransportNotifier.new);