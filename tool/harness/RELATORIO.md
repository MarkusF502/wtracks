# Relatório de testes automatizados — WTracks

Data: 2026-09-28 · Executado em Linux desktop, sem celular nem emulador.

## Resumo

| | Antes das correções | Com `correcoes.patch` |
|---|---|---|
| Testes C++ (engine JUCE) | 8 ok · **4 falhando** | 12 ok |
| Testes Flutter (unit + widget) | 52 ok · **6 falhando** | 58 ok |
| `flutter analyze` | 8 avisos de estilo (pré-existentes) | igual |

Foram encontrados **8 bugs reproduzidos por teste**. Todos têm correção no
[`correcoes.patch`](correcoes.patch), validada rodando o harness completo sobre uma cópia do projeto com o patch
aplicado. Mais 5 pontos encontrados só por leitura de código estão no fim do relatório.

## Como rodar

```bash
tool/harness/run_harness.sh              # build nativo + C++ + analyze + flutter test
tool/harness/run_harness.sh --skip-native
git apply tool/harness/correcoes.patch   # aplica as correções
```

Os logs e o `summary.md` de cada execução ficam em `harness_reports/<data>/` (pasta ignorada no git).

### O que o harness faz

1. Compila `native/` para Linux (`native/build-linux/`), gerando a `libwtracks_engine.so` e o executável de testes
   `wtracks_engine_tests`. Os testes C++ chamam `getNextAudioBlock()` na mão, então não precisam de placa de som.
2. Roda `flutter analyze`.
3. Roda `flutter test` com `LD_LIBRARY_PATH` apontando para a `.so` Linux. O `CurrentTrackNotifier.load()` usa o engine
   nativo real via FFI (dentro do `Isolate.run`). O resto usa dublês:
   - `FakeEngine` registra cada chamada ao engine, por exemplo `volume(0,0.5)` ou `muted(1,true)`;
   - `InMemoryPersistence` substitui o disco;
   - o MethodChannel `wtracks/background` e o `file_selector`/`path_provider` também são mockados.
4. Renderiza todas as telas em tamanho de celular, em retrato (390x844) e em paisagem (844x390), com a fonte Roboto
   real. A fonte padrão dos testes desenha cada letra como um quadrado e gerava falsos overflows.

### Arquivos novos

- `tool/harness/run_harness.sh`: o runner.
- `native/tests/HarnessRegressionTests.cpp`: testes N1–N3. Também foi registrado no `native/CMakeLists.txt`.
- `flutter_app/test/harness/harness_support.dart`: fakes, gerador de WAV e mocks.
- `flutter_app/test/harness/providers_harness_test.dart`: mixer ↔ engine (D1) e polling do transporte (D7).
- `flutter_app/test/harness/screens_harness_test.dart`: smoke de telas, transporte/mixer e diálogo de BPM (D2, D3).
- `flutter_app/test/harness/import_harness_test.dart`: cache de importação (D4).
- `flutter_app/pubspec.yaml`: 3 dev_dependencies para os mocks de plataforma.

---

## Bugs encontrados (reproduzidos por teste)

### D1 — Alta · Mix salvo não é aplicado no engine ao abrir a música

**Sintoma:** você salva uma música com a guia mutada ou com o volume da bateria em 50%. Ao reabrir, o mixer mostra
"M" aceso e 50%, mas o engine toca **todos os canais a 100% e sem mute**. No culto, isso pode significar a guia vazando
para o PA.

**Causa:** [engine_provider.dart:71](../../flutter_app/lib/providers/engine_provider.dart#L71). O `load()` só envia BPM,
compasso e offset. O `loadTrack` nativo cria canais novos com volume 1.0 e sem mute, e o Dart nunca reenvia o
`volume`/`muted`/`soloed` de `track.channels`.

**Correção:** depois do load, chamar `setChannelVolume(i, …)` em cada canal e `_syncEffectiveMutes()` (resolve mute e
solo).

**Teste:** `providers_harness_test.dart › [D1]`

### N1 — Alta · Sem conversão de sample rate: música acelerada e desafinada

**Sintoma:** quando o device de áudio abre a 48 kHz (comum no Android) e o WAV é 44.1 kHz, a música toca cerca de
8,8% mais rápida e mais aguda. A duração exibida também fica errada: o teste mostrou 1,84 s para um arquivo de 2 s. O
click fica desalinhado da música.

**Causa:** `AudioFormatReaderSource` não faz resampling, apesar do comentário em
[AudioEngine.cpp:96](../../native/src/AudioEngine.cpp#L96) dizer que o resampler é configurado ali. Além disso,
`seekToSeconds` ([:171](../../native/src/AudioEngine.cpp#L171)) e `getTotalLengthSeconds`
([:206](../../native/src/AudioEngine.cpp#L206)) misturam amostras do arquivo com o sample rate do device.

**Correção:** envolver cada `readerSource` num `juce::ResamplingAudioSource` com a razão
`fileSampleRate / deviceSampleRate`, e guardar o `fileSampleRate` por canal para seek e duração.

**Teste:** `HarnessRegressionTests.cpp › [N1]` (2 casos)

### N2 — Média · A reprodução nunca termina

**Sintoma:** ao chegar no fim da música, `isPlaying` continua `true` e a posição segue crescendo, por exemplo
"5:12 / 4:00". O botão continua como "pause" e a notificação "Tocando em segundo plano" não some.

**Causa:** [AudioEngine.cpp:401](../../native/src/AudioEngine.cpp#L401) incrementa a posição sem comparar com a duração.

**Correção:** ao passar do fim, travar a posição na duração e setar `playing = false`.

**Teste:** `HarnessRegressionTests.cpp › [N2]`

### D4 — Média · Importar outra música com arquivos de mesmo nome apaga o áudio da anterior

**Sintoma:** multitracks costumam vir com os mesmos nomes (`Click.wav`, `Guia.wav`…). Se você importa a música A, não
salva e importa a música B, os arquivos de B **sobrescrevem** os de A no cache. Salvar A depois grava o áudio de B.

**Causa:** tudo vai para o mesmo diretório `wtracks_import/<nome>`:
- Dart: [file_import_service.dart:61](../../flutter_app/lib/file_import_service.dart#L61);
- Android: [MainActivity.kt:138](../../flutter_app/android/app/src/main/kotlin/com/example/flutter_app/MainActivity.kt#L138).

**Correção:** criar uma subpasta por importação. No Dart está no patch. No Kotlin, que não é testável no desktop,
aplicar o equivalente manualmente:

```kotlin
val batchDir = File(cacheDir, "wtracks_import/${System.nanoTime()}").apply { mkdirs() }
// ...
val outFile = File(batchDir, name)
```

**Teste:** `import_harness_test.dart › [D4]` (cobre o caminho Dart/file_selector)

### D3 — Média · Diálogo de BPM/offset não cabe em paisagem nem em celulares menores

**Sintoma:** overflow de 228 px em paisagem (844x390) e de 87 px em 360x640. Os botões "Marcar 1º tempo" e "Zerar
offset" ficam cortados e **não recebem toque**. Em 390x844 cabe no limite.

**Causa:** [performance_screen.dart:408](../../flutter_app/lib/screens/performance_screen.dart#L408). O
`showModalBottomSheet` sem `isScrollControlled` limita a altura a 9/16 da tela, e o conteúdo não rola.

**Correção:** `isScrollControlled: true`, `useSafeArea: true` e o conteúdo dentro de um `SingleChildScrollView`.

**Teste:** `screens_harness_test.dart › [D3]` (3 tamanhos de tela)

### D2 — Baixa · "Marcar 1º tempo" não atualiza o offset exibido

**Sintoma:** o engine recebe o offset (por exemplo 1,25 s), mas o diálogo continua mostrando "+0.00s" até ser fechado e
aberto de novo.

**Causa:** [performance_screen.dart:496](../../flutter_app/lib/screens/performance_screen.dart#L496) lê o `track`
capturado quando o diálogo abriu. O `setState(() {})` redesenha com o valor antigo.

**Correção:** envolver o texto num `Consumer` que observa
`currentTrackProvider.select((t) => t?.clickSettings.beatOffsetSeconds)`.

**Teste:** `screens_harness_test.dart › [D2]`

### N3 — Baixa · Após um seek exatamente num tempo forte, o acento cai no tempo errado

**Causa:** `seekToSeconds` já posiciona `currentBeatIndex` no tempo certo, e
[AudioEngine.cpp:372](../../native/src/AudioEngine.cpp#L372) incrementa de novo na primeira amostra.

**Correção:** calcular o índice direto da posição absoluta: `(effectiveSample / spb) % numerator`. Isso também elimina o
caso especial de `effectiveSample == 0`.

**Teste:** `HarnessRegressionTests.cpp › [N3]`

### D7 — Baixa · Transporte reconstrói a UI 10 vezes por segundo mesmo parado

**Causa:** [engine_provider.dart:298](../../flutter_app/lib/providers/engine_provider.dart#L298). O polling cria um
`TransportState` novo a cada 100 ms, e a classe não tem `==`, então todo tick notifica os widgets. É gasto de bateria à
toa em telas paradas.

**Correção:** implementar `==`/`hashCode` em `TransportState` e só atribuir `state` quando o valor mudar.

**Teste:** `providers_harness_test.dart › [D7]`

---

## Observações sem teste automatizado (leitura de código)

Estes pontos dependem do Android e não são exercitáveis no desktop. As sugestões abaixo **não foram testadas**.

1. **`PlaybackService` retorna `START_STICKY`**
   ([PlaybackService.kt:49](../../flutter_app/android/app/src/main/kotlin/com/example/flutter_app/PlaybackService.kt#L49)).
   Se o sistema matar o processo, o serviço é recriado com `intent == null` e mostra "Tocando em segundo plano" sem
   engine nem áudio. Sugestão: `START_NOT_STICKY`.
2. **Pause não encerra nem atualiza a notificação.** Só o stop chama `wtracks/background.stop`. Junto com o N2, a
   notificação fica eterna depois que a música acaba.
3. **`POST_NOTIFICATIONS` nunca é pedida em runtime.** O comentário no manifest diz que precisa ser. No Android 13+ a
   notificação do foreground service fica oculta.
4. **Toque duplo rápido numa música da biblioteca** dispara dois `load()` em paralelo. Se o primeiro `Isolate.run`
   terminar por último, a UI mostra a música A enquanto o engine tem a B. Sugestão: descartar resultados de loads
   antigos com um contador de geração.
5. **`TransportNotifier.play/stop`** chamam `invokeMethod` sem `await` nem `catch`. Fora do Android (build Linux ou
   Windows) isso gera `MissingPluginException` não tratada.

## Limites do harness e próximo passo

- Não há áudio real: os testes C++ validam as amostras geradas, não o que sai pela placa de som.
- A camada Android (Kotlin, JNI, foreground service, seletor `content://`) não é coberta. O Android SDK desta máquina
  já tem o `emulator`. Um próximo passo seria rodar `integration_test` num AVD headless (`emulator -no-window`) pelo
  mesmo script.
