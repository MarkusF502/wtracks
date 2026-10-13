# Prompt para o Claude Code (ambiente em nuvem) — continuar o WTracks

Cole o bloco abaixo como primeira mensagem da sessão na nuvem. Antes disso o usuário precisa **publicar a branch** (`git push origin fase5-estabilizacao`; no momento ela está 6 commits à frente do remoto) e conceder à sessão acesso ao repositório `MarkusF502/wtracks`.

---

Você continuará a reconstrução, em Flutter + C++/JUCE, do player local do **Playback 8.5.3** no projeto **WTracks** (branch `fase5-estabilizacao`). Responda e comente em português.

## Contexto e regras

- Stack: Flutter/Riverpod + Dart FFI + motor C++/JUCE (`native/`). Nenhum Timer do Dart para áudio: todo agendamento sensível a tempo fica no motor.
- Escopo: player local completo (click, reprodução, seções/loops, guias, mixer/buses, tom/andamento, MIDI/automação, timecode). **Fora do escopo:** contas, nuvem, compras, downloads, anúncios, Planning Center, licenças de igreja.
- Evidência do Playback (decompilação Ghidra/REA já feita fora da nuvem): `docs/playback-analysis/` — `playback-feature-inventory.md` (lista de funcionalidades com status e evidência), `coredata-model-145.json` (modelo de dados real, 39 entidades), `subsystem-contracts.md`, `timepitch-contract.md`, `click-songmap-findings.md`, `main-ui-strings.txt` (1472 textos de UI). **Não há acesso ao binário nem ao Ghidra na nuvem**: trabalhe a partir desses documentos; quando faltar evidência, escolha um comportamento razoável, marque-o como "escolha própria" no código/documento e não afirme equivalência com o iOS.
- Cada ciclo = investigação nos documentos, contrato, implementação, testes, commit próprio (mensagem em inglês no estilo dos commits existentes, terminando com a linha de coautoria exigida pelo ambiente). Não reescreva histórico, não faça force-push, não descarte alterações alheias.
- Registrar origem/hash dos recursos reutilizados do pacote (guias em `flutter_app/assets/playback/guide/` e sons de click em `assets/playback/click/` já têm manifesto).
- Dispositivos indisponíveis: iPhone, X32, hardware MIDI e Android físico. Testes MIDI usam sinks gravadores. Se um dia houver comparação com iOS, registrar versão/build do iOS e do Playback.

## Como construir e testar (Linux)

```bash
# Flutter (instale o SDK estável 3.44 se não houver) e JUCE já vem como submódulo/subpasta em native/JUCE
cd native && cmake -S . -B build-linux && cmake --build build-linux -j4
cd build-linux && ./wtracks_engine_tests            # deve sair com código 0
cd ../../flutter_app && flutter pub get
export LD_LIBRARY_PATH=$PWD/../native/build-linux   # para os testes que usam o .so real
flutter analyze && flutter test
```

**Armadilha já vivida:** ao compilar, filtre a saída por `error:` (não ` error `). Um erro de compilação filtrado deixou um binário de teste velho rodando e testes não verificados. Depois de adicionar um arquivo de teste, confirme que a linha `Completed tests in <nome>` dele aparece no log. As "JUCE Assertion failure" de MIDI/AsyncUpdater nos logs são ruído conhecido (sem dispositivos), não falha. Rode a suíte nativa algumas vezes: já apareceu uma corrida (flush do MidiRouter) que só se mostrou na repetição.

## Estado (cada item tem testes nativos e/ou Flutter)

Click sample-exato com 4 vozes, mapa de andamento/compasso (`TempoMap.h`), MIDI clock na mesma grade; reprodução com read-ahead; seções com loops atual/próximo, **loops contados** e **loops predefinidos automáticos** (nativo); guias sample-exatas (541 WAVs); mixer com rampa de 10 ms, rota por canal (estéreo/esq./dir.) e volume geral; tom/andamento por renderização offline própria (vocoder de fase) + `setTimeScale` (tudo em tempo da música); MIDI (clock, 0xFA/FB/FC, cues com mensagem, router com thread de despacho, saída `juce::MidiOutput`); timecode LTC (11 taxas do binário, drop-frame, 50/60 fps com rótulo à metade). Telas: guias, seções (com contagem de repetições, laço automático, guia, contagem), mapa de andamento, MIDI/automações/timecode, tom e andamento. Menu "Mais" no `PerformanceScreen`.

## Próximos ciclos (nesta ordem; detalhes e evidência em `playback-feature-inventory.md`)

1. **Guias dinâmicas a partir das seções** (`GuideCue(cueType, sectionTypeID, cueSequenceTimecode, songMapElementStartTimecode, cueEnabled, cueFilePath, replacementCountCueFilePath)`): gerar, em Dart, a lista de `GuideCue` derivada de `SongSection` + mapa de andamento + configurações (idioma/gênero extraídos do nome dos arquivos `guidecue-{count,section}-<lang>-<gender>-<nome>`, "Contar ao entrar em cada seção", "Pré-roll de seção"). Os flags `playGuideCue`/`playCountIn` das seções já existem. Contagem ao saltar para o início de uma seção (pré-roll) ainda não existe — exige apoio do motor (tocar um compasso antes sem os stems) e é escolha própria.
2. **Automação de mixer** (hoje só há cues MIDI): `AutomationCue{name, transitionBeats, sequenceTimecode, applyTransitionLengthCorrection, items[AutomationItem{automationID, value}]}`. Pontos na linha do tempo que movem faders de canal/bus/master em `transitionBeats` batidas antes do ponto (rampa linear; mute/unmute instantâneo), com snapshot, copiar/colar, salvar por arranjo. Implementar no motor (agenda por sample, como `CueTimeline`) e UI de edição.
3. **Fade de saída** (botão de transporte "5 Second Fade Out", `SongArrangement.endFade`, `excludeFromFade`) e **transições de setlist** (cue próxima música / ficar na música, `storedTransition`).
4. **Medidores VU** por canal e master (picos no motor, leitura por FFI sem alocar no callback) e nível padrão de fader 80% (opção).
5. **Buses**: `SongBus{volume, muted}` por música, `GlobalBus`, roteamento track→bus→canal de saída (`OutputRouting`/`OutputChannel`), opção "enviar click & guia para a esquerda e faixas para a direita", master por música.
6. **MIDI**: bancos/buses (`MIDIBank`, `MIDIBus{port, channel, enabled, allChannels}`, `MIDIEvent{note, velocity, duration, type, bank, bus}`), copiar/colar cues de seção; **MIDI de entrada com mapeamento** (`ControlMapping{mappingID, mappingTypeID, intValue1..3, stringValue1}`) e atalhos de teclado.
7. Pastas de sons personalizados (click/guias), trim de seção (`storedStart/EndTimeTrimOffset`), contagem de repetições na UI de transporte, reconstrução visual (a UI do iOS não foi decodificada; use os textos em `main-ui-strings.txt` e Material 3 escuro).
8. Opcional/baixa prioridade: Playback Remote (servidor WebSocket local).

## Ao terminar cada ciclo

Rode `flutter analyze`, `flutter test` e a suíte nativa (≥ 3 vezes), atualize o status em `docs/playback-analysis/playback-feature-inventory.md`, faça commits separados nativo/Flutter e resuma: o que foi verificado, o que é escolha própria, o que depende de hardware.
