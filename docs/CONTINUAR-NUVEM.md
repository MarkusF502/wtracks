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

## Ciclos concluídos na sessão em nuvem (2026-10)

1–8 do plano anterior estão feitos (guias dinâmicas e pré-roll; automação do mixer; fade e transições de setlist;
medidores e fader 80%; buses e roteamento; MIDI com bancos/buses/eventos, entrada mapeada e teclado; trim de seção,
contador de laço e pastas de sons personalizados; controle remoto local com protocolo próprio). Depois da chegada do
pacote de evidências (pseudocódigo, nibs, Assets.car) foram corrigidos: regra das guias (nome em silêncio durante laço),
fade do fim (dispara o fade de 5 s em `fadeStartTimecode`), rampa de 20 ms do mixer. Detalhes, evidências e escolhas
próprias por item em `docs/playback-analysis/playback-feature-inventory.md`.

## Pendências

- Tela de performance já redesenhada no estilo do Playback (capturas em `docs/ui-performance/`); faltam as outras telas
  (biblioteca, setlists, editores) e um ajuste fino com o app real ao lado — sessão local.
- Itens ainda "escolha própria" sem evidência localizada: matemática da rampa de automação e
  `applyTransitionLengthCorrection`, valores de `storedTransition` (3 e 4 aparecem no binário), seção de tipo 7 e cues de
  tipo 1 das guias, curva do fade, balística do VU, porta por bus MIDI, protocolo do Playback Remote.
- Teste intermitente conhecido: `stabilization_harness_test.dart` "JSON atômico" (falhou 2 vezes em ~15 execuções
  completas; código de persistência anterior a estes ciclos).
- Hardware não testado: MIDI real (entrada/saída), X32, iPhone, Android físico.

## Ao terminar cada ciclo

Rode `flutter analyze`, `flutter test` e a suíte nativa (≥ 3 vezes), atualize o status em `docs/playback-analysis/playback-feature-inventory.md`, faça commits separados nativo/Flutter e resuma: o que foi verificado, o que é escolha própria, o que depende de hardware.
