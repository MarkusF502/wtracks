# Fase 5 — Estabilização do WTracks

Data: 2026-09-28. Flutter 3.44.0, Dart 3.12.0, flutter_riverpod 2.6.1.
Ambientes: Linux desktop e AVD `wtracks_phase5`, Android 15/API 35, x86_64.
Nenhuma versão existente de dependência foi alterada. Foi acrescentado apenas
`integration_test`, do SDK Flutter, e suas dependências de teste.

## Parte 0 — Base e patch

- `720a97a`: registra o estado preexistente do projeto, autorizado pelo usuário.
- `77bbc87`: `aplica correções do harness`, incluindo D4 no Kotlin.
- `git apply` aplicou o patch sem conflitos. Resultado inicial: **12 casos C++ e
  58 testes Flutter passando**, com os 8 avisos de analyze já descritos no relatório.
- Evidência inicial: `harness_reports/20260928-143740/native_tests.log` e
  `harness_reports/20260928-143759/`. A primeira tentativa Flutter foi impedida
  pelo cache do SDK somente leitura; a execução com acesso ao SDK passou.
- O patch histórico permanece como referência; **não reaplicar** sobre esta versão.

## Parte 1 — `_dependents.isEmpty`: reprodução e correção

Os fluxos iniciais no Android não reproduziram a assertion. Um teste adicional
reproduziu **a mesma assertion no desktop**, com a seguinte sequência:

1. Abrir a biblioteca por uma rota de navegação.
2. Abrir o diálogo de renomear e editar o texto.
3. Remover a rota da biblioteca enquanto o diálogo continua aberto.
4. Confirmar e avançar a animação de saída.

Primeiro erro: `A TextEditingController was used after being disposed`, em
`ChangeNotifier.addListener` → `_AnimatedState.didUpdateWidget`. Depois:
`InheritedElement.debugDeactivated` → `_InactiveElements._deactivateRecursively`
→ **`'_dependents.isEmpty': is not true`** durante reconstrução do Overlay.
O [stack trace anterior à correção](evidence/crash-controller-before.log) foi preservado.

Causa confirmada nesse reproducer: o `Future` de `showDialog` termina no `pop`,
antes de terminar a animação e desmontar o campo. O chamador fazia
`controller.dispose()` imediatamente. O novo `DialogTextController` possui o
controller e só o descarta no `dispose` do próprio widget do diálogo. Aplicado
às quatro ocorrências: renomear música na biblioteca/performance e
criar/renomear setlist. Layout e textos desses diálogos foram preservados.

A regressão está em `test/harness/stabilization_harness_test.dart`; falhava antes
e passa depois. Também há reproducer equivalente em
`integration_test/phase5_test.dart`. Não há stack trace do incidente original
no aparelho: a correspondência com aquele incidente é plausível, mas não pode
ser afirmada como identificação definitiva do mesmo caminho.

Auditoria das hipóteses: o item raiz de `ReorderableListView` já usa
`ValueKey(track.id)`, e `withTrackAdded` já impede duplicatas. Nenhuma `GlobalKey`
foi encontrada em `lib/`. Não houve atualização de Flutter/Riverpod.

Correções separadas de ciclo de vida: guards `mounted` após diálogos/picker e
antes do callback pós-frame da waveform; troca da waveform em `didUpdateWidget`
agora agenda a alteração para depois do frame. A extração invalida resultados
obsoletos, trata exceções e não republica estado após descarte do provider.

## Partes 2 a 7

| Parte | Implementação e evidência |
|---|---|
| 2: serviço | `START_NOT_STICKY`; intent nulo encerra o serviço. **Pause encerra o serviço**, assim como stop e fim natural detectado pelo polling. O stop Android usa `stopService`, sem criar um serviço só para encerrá-lo. |
| 2: permissão | `POST_NOTIFICATIONS` solicitada em runtime antes do primeiro play no Android 13+. Resposta negativa não impede áudio. O resultado do pedido é aguardado; stop durante o pedido invalida um play tardio. |
| 2: concorrência | Geração + fila de loads: isolates usam o mesmo singleton C++, por isso descartar apenas o resultado Dart não bastava. Load obsoleto não publica mix/track; um swap obsoleto é descarregado para não deixar áudio divergente se o próximo load falhar. Unload entra na mesma fila. Testes com FakeEngine atrasado verificam UI e engine. |
| 2: canal | Chamadas de background são aguardadas e ordenadas. `MissingPluginException` e `PlatformException` são logadas sem derrubar o transporte. Testes cobrem ambas. |
| 3: waveform | Geração/cache, leitura do cache, falha com retorno ao slider, toque/arraste para seek e exclusão durante geração cobertos no harness. A exclusão aguarda escrita/extração pendente antes de apagar o cache. Extração C++ e cache real também exercitados no Android. |
| 4: logs | Removidos `>>> [DEBUG]`/`>>> [ISOLATE]`; nenhum `print(` cru em `lib/`. Os 8 avisos originais foram resolvidos. A migração para `onReorderItem` adapta o índice ao contrato existente do modelo, preservando a ordem. |
| 5: erros | Enum C++, exportação `wtracks_get_last_error_code`, binding/enum Dart e mensagens em português. Biblioteca, setlist e import usam a tradução. Falha de inicialização apresenta aviso visível. Testes cobrem arquivo corrompido, taxas/durações incompatíveis, limpeza do erro e tradução/fallback. |
| 6: exclusão | Confirmação informa quantos setlists referenciam a música; remove referências persistidas e atualiza biblioteca/editor de setlists. Música carregada ou carregando é parada/descarregada; currentTrack é limpo. Cache e áudio são removidos. |
| 6: JSON | Tracks, setlists e waveform gravam `.json.tmp`, fazem flush e renomeiam. Escritas no mesmo destino são serializadas para reordenações rápidas não disputarem o mesmo temporário. Teste real verifica JSON íntegro, sobrescrita, concorrência e ignorar `.tmp` incompleto. |
| 7: click | N1 já recalculava `clickOffsetSamples`, **mas não `samplesPerBeat`**. `prepareToPlay` agora recalcula BPM. Teste mede a amostra do acento após mudar 44,1 → 48 kHz com offset de 0,25 s. |
| 7: lock | Mantido e documentado: o vetor de canais é substituído no load e limpo no unload. Tornar apenas volume/mute atômicos não torna seguro remover o lock de acesso ao vetor. Resolver requer política de vida útil/publicação dos canais, além de avaliar leitura de disco/alocação no callback de áudio. |

Regra de formatos mantida: **os canais de uma mesma música devem ter o mesmo
sample rate e duração com tolerância de 50 ms**. Cada canal usa resampling para
a taxa do dispositivo. WAVs 44,1 kHz em dispositivo 48 kHz são aceitos; misturar
canais 44,1 e 48 kHz na mesma música retorna `FormatMismatch`.

O build Android também revelou um comentário preexistente com `--` no manifest,
inválido em XML. A correção foi restrita ao comentário; o erro de parsing do
merger deixou de ocorrer.

## Validação

- Desktop: **14 casos C++ e 76 testes Flutter**, sem testes pulados.
- Analyze: **sem issues**. Execução desktop final: `harness_reports/20260928-150105/`.
- Android: **2 testes de integração passando**, incluindo a regressão do diálogo,
  com engine/FFI/JNI, persistência e MethodChannels reais, sem FakeEngine.
  Gera três WAVs de 8 s a 44,1 kHz em diretório exclusivo e remove as fixtures ao terminar.
- A primeira execução Android completa passou com **permissão negada no diálogo
  real**. Áudio continuou; `dumpsys activity services` confirmou serviço ativo e
  posteriormente ausente. O mixer Android reportou saída de 48 kHz em
  `dumpsys media.audio_flinger`; a conversão do engine é verificada diretamente
  pelas amostras no teste C++ N1.
- **Importador Android (D4) validado**: `integration_test/android_import_test.dart`
  passou no AVD com o seletor real (`DocumentsUI`) dirigido por `adb`/`uiautomator`,
  escolhendo `Download/PHASE5-A/Click.wav` e depois `Download/PHASE5-B/Click.wav`
  (md5 diferentes). As duas cópias foram para subpastas distintas e a primeira
  ficou byte a byte intacta. [Log](evidence/android-import-d4.log). O `-1` no
  log é do `flutter_tools`: com `--no-dds` ele não registra o listener de golden
  files (`VmServiceProxyGoldenFileComparator`); não envolve o app. Sem `--no-dds`
  o teste nem carrega (`Failed to start Dart Development Service`).
- **APKs**: `flutter build apk --debug` e `flutter build apk --release` compilam
  (release: 60 MB). O APK release foi instalado no AVD e abriu na biblioteca sem
  crash e sem o aviso de falha de áudio, ou seja, JNI (`initJuceContext`) e FFI
  sobrevivem ao R8.
- Verificação independente final do harness: **14 casos C++ sem falhas, 76 testes
  Flutter, analyze sem issues** (`harness_reports/20260928-150637/`).
- Hot reload durante navegação: executado com sucesso via `flutter run`.
  Hot restart: comando iniciou e depois perdeu temporariamente ADB/VM Service;
  não há crash no buffer Android capturado. **Não validado**, sem atribuir causa
  ao app. Primeira tentativa de `flutter run` também falhou na conexão DDS;
  `--no-dds` permitiu a sessão de hot reload.

Fluxos Android exercitados: alternar A/B/A e reordenar repetidamente; abrir,
selecionar e confirmar picker de músicas; girar editor e performance;
toque duplo na biblioteca; waveform nativa/cache, seek por toque/arraste,
slider após falha nativa; marcar primeiro tempo e fechar BPM nas duas orientações;
três músicas até o fim; pause; deletar música carregada e referenciada por setlists.

O harness agora também retorna erro se `flutter analyze` falhar, e interrompe
claramente quando `pub get` não completa.

### Comandos

```bash
tool/harness/run_harness.sh
cd flutter_app
flutter test integration_test/phase5_test.dart -d emulator-5554 --no-dds --reporter expanded
flutter build apk --debug
flutter build apk --release
```

A integração Android pode abrir o pedido de notificação: responder no AVD
(uma execução com Permitir e outra com Não permitir). O teste isolado
`integration_test/android_import_test.dart` pede dois arquivos via seletor real:
selecionar `Download/PHASE5-A/Click.wav` e depois `Download/PHASE5-B/Click.wav`,
com conteúdos distintos. Não apontar esses testes a um aparelho de produção.

## Roteiro manual no aparelho

1. Ouvir WAV 44,1 kHz em saída 48 kHz; comparar duração, afinação e alinhamento
   click/waveform com a referência. As amostras passaram no desktop, mas não
   houve escuta em hardware físico nesta execução.
2. Permitir notificação, tocar até o fim e conferir posição parada e notificação
   removida; repetir play/pause. Negar permissão em instalação limpa e conferir áudio.
3. Salvar/reabrir com Guia mutada e Bateria em 50%; conferir mixer **e áudio**.
4. Importar duas músicas com `Click.wav`/`Guia.wav` homônimos; salvar e reabrir
   ambas e conferir que o áudio da primeira não mudou.
5. Reordenar várias vezes, sair/reabrir, alternar setlists e confirmar o picker;
   repetir em retrato/paisagem e renomear/criar setlist.
6. Abrir música longa sem cache e sair durante “Gerando waveform...”; trocar
   rapidamente de música e girar a tela. Reabrir cache; testar toque e arraste.
7. Excluir música presente em dois setlists, inclusive a carregada; conferir
   confirmação, ausência em ambos, parada e cache apagado.
8. Fazer sessão contínua com pelo menos três músicas reais, incluindo play,
   pause, seek, solo/mute e alternância de telas, sem crash ou interrupção audível.
9. Repetir hot reload/hot restart com conexão de depuração estável e guardar
   a **primeira exceção** caso apareça nova assertion de árvore.

## Pendências e limites

- Escuta e comportamento com interface/saída física Android; emulador foi iniciado
  com `-no-audio`. Não declarar ausência de glitches ou latência com base no harness.
- Hot restart não concluído por perda de conexão; o crash original do aparelho
  ainda não tem stack trace para comparação direta com o reproducer corrigido.
- Estresse de longa duração, I/O lento e troca real de dispositivo de áudio.
- Remoção do lock/IO da thread de áudio exige trabalho separado, conforme Parte 7.
- JSON atômico protege cada arquivo; não transforma move de áudio + JSON + múltiplos
  setlists numa transação única. O TODO de recuperação após encerramento do processo
  entre essas operações continua válido.
