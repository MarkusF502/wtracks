# Plano de desenvolvimento — o que falta no WTracks segundo o Playback decompilado

Base: pacote de evidências em `docs/playback-analysis/`, ou seja, o pseudocódigo do executável e dos frameworks de
áudio, o modelo Core Data 145, 1472 textos de interface, 208 nibs/storyboards e o guia do usuário em
`ui/helpcenter/`. A comparação foi feita com o código em `native/` e `flutter_app/` em 2026-10-14.

Continuam fora do escopo: contas, nuvem, compras e aluguéis, downloads, anúncios, Planning Center, licenças de igreja,
a loja MultiTracks e a importação de cues da nuvem.

Regras de sempre:
- Dart não agenda nada de áudio.
- O que não tem evidência é marcado como "escolha própria".
- Cada ciclo segue investigação → contrato → implementação → testes → commits separados para nativo e Flutter.
- `flutter analyze`, `flutter test` e a suíte nativa rodam 3 vezes por ciclo.

Legenda: **[G]** precisa de uma segunda passada no Ghidra antes (ou durante) a implementação; a lista completa está
no fim.

## Correções ao que já está documentado

1. **Transições.** `FUN_1004bad90` (transition.c, por volta da linha 10337) monta o rótulo a partir de `storedTransition`:
   - 0 = Cue Next Song
   - 1 = AutoLink
   - 2 = Overlap
   - 3 = Crossfade
   - 4 = Stay In Song
   - 5 = Cue First Song

   "Continue Pad" vale só para 0, 4 e 5 (máscara `0x31`); Overlap e Crossfade compartilham o código (`(v & 0xfe) == 2`).
   O inventário dizia "3 e 4 provavelmente Overlap e Crossfade", o que está errado: 4 é Stay In Song.
2. **Automação do mixer.** `AutomationDSPKernel` não faz rampa: `startRamp` em 0x5c44 é vazio. O kernel só dispara o
   cue (UUID) para o delegate. A rampa dos faders fica no executável principal, em `FUN_1001b4b38` **[G]**. A
   "transition length correction" (`FUN_1008223d4`) é uma correção de grade de tempos para compassos x/8 e não a regra
   "não começar antes do ponto anterior" que o `MixerAutomation.h` assumiu. Hoje o WTracks implementa uma regra diferente.
3. **Fade do transporte.** É um liga/desliga: abaixa e volta. Não pausa (`fadeButtonTouchUpInside:` → `FUN_10086ba58`).
   O passo é linear a cada 1/30 s (`FUN_10002c318`), com 5 s por padrão. Click e guia ficam de fora (`FUN_1000c5708`).
   **Corrigido na Fase 1 (2026-10-14).**
4. **Medidores.** No Playback a queda é linear em unidades de tela, `maxDecayDelta` = 1/30 por atualização, com a
   subida instantânea. O WTracks cai 24 dB/s (escolha própria). A taxa de atualização não foi achada **[G]**.
5. **MIDI clock.** O primeiro 0xF8 sai um período depois do start. Não existe SPP (0xF2).
6. **Timecode.** O sinal LTC sai com amplitude ×0,5.

## Fase 0 — Salvamento no Android (bloqueador, antes de tudo)

**Status (2026-10-14): itens 1–4 feitos, 5 com você.** O item 4 existe como `integration_test/persistence_test.dart` e
`engine_init_test.dart` e `.github/workflows/android-tests.yml`. Os dois testes passaram no emulador local `wtracks_phase5`
(Android 35, x86_64, motor falso no teste de salvamento); o workflow do CI ainda não rodou (falta o push).
Resultado importante: no Android emulado, o salvamento real em disco (importar → editar → setlist → reabrir) **funciona**;
se o defeito continuar no seu aparelho, a causa está em algo do aparelho (permissão, caminho do seletor de arquivos ou
motor de áudio), e o registro de Diagnóstico deve mostrar onde.

Causa encontrada:
- A tela de importação só carregava a música, sem gravar.
- O "Salvar" ficava escondido em ≡ → Editar música…, e mexer no mixer nunca gravava.
- As falhas não apareciam: nem o usuário nem o código viam a perda.

Correções:
- Salvamento automático de toda mudança da música aberta (`TrackLibraryNotifier`; espera o carregamento terminar e
  ignora o eco do próprio salvamento).
- Avisos na tela com "Detalhes" e registro em Ajustes → Diagnóstico (copiável).
- Cópia do áudio conferida pelo tamanho, e erro claro quando o áudio de um canal não existe.
- Falhas de leitura da biblioteca e das setlists passam a ser avisadas.
- O menu da música e o metrônomo não usam mais o `ref` de um diálogo já fechado.
- A tela de tom e andamento avisa quando não consegue salvar.
- "Adicionar música → Importar" usa a música já carregada, em vez de recarregar pelos caminhos antigos do cache.

Teste: `test/persistence_autosave_test.dart` (importar → editar → setlist → reabrir o app, com gravação real em
disco).

Relato do teste no Android (2026-10-14): músicas novas, setlists e edições não ficam salvas. Também não deu para testar
tom e andamento, que só se aplicam depois de salvar.

O que já foi verificado:
- No Linux, `PersistenceService` grava e relê músicas (simples, importadas, com seções e buses) e setlists sem perda,
  com teste de ida e volta feito em 2026-10-14.
- O defeito é, portanto, específico do aparelho ou do fluxo de interface, e a causa ainda **não foi confirmada**.

Pontos do código que escondem falhas e precisam ser corrigidos primeiro:
- `TimePitchSheet._apply` não captura erro de `saveCurrent()`. Se salvar falhar, nada aparece e o painel fica aberto.
- O menu "Editar música" chama `_save` e `_renameTrack` com o `ref` do diálogo depois de fechá-lo.
- `setTransition` e `updateSections` na tela engolem o erro (`catch (_) {}`).
- `loadAllTracks` e `loadAllSetlists` pulam arquivos ilegíveis só com um `debugPrint`, que não aparece no APK de release.
- Não existe um "Salvar" visível na tela principal. Ele fica em ≡ → Editar música… → Salvar. O Playback salva sozinho
  e só pede ação para arranjos.

Plano:
1. Mostrar toda falha de leitura ou gravação, com mensagem e caminho do arquivo, e manter um registro local exportável
   (Ajustes → Diagnóstico, como o "Diagnostic Information" do Playback).
2. **Salvar automaticamente** cada edição (mixer, seções, transição, MIDI, tom e andamento), como o Playback faz. A
   gravação vale para a música da biblioteca, e a importação já grava ao terminar.
3. Mover o áudio importado do cache para `files/` com cópia verificada (tamanho igual) antes de apagar a origem, e
   não apagar enquanto o motor está lendo. Hoje é `rename` e, se falhar, copiar + apagar.
4. Teste instrumentado no emulador Android no CI (o runner do GitHub tem KVM; `android-emulator-runner`):
   importar → salvar → recriar o app → a música e a setlist continuam lá.
5. Testar de novo no seu aparelho com o registro de diagnóstico ligado.

## Novidades vistas nas capturas do Playback 8.6.2 no iPhone

Ver `docs/playback-analysis/ui/iphone-8.6.2/`.

- **Barra de modos de edição.** Ao tocar em EDITAR (que vira PRONTO), aparece no rodapé uma barra rolável: Repertório
  / Mapa da Música, Gatilhos MIDI, Automação, Mapeamento MIDI, Mapeamento do Teclado, (Seções da Música do Cloud) e
  SMPTE. No WTracks os modos ficam no "segurar EDITAR" e abrem telas separadas; a barra entra na Fase 7, com os modos
  agindo na própria tela.
- **Música só de click** ("Click & Pad": cartão com metrônomo e título "120 BPM 4/4 (F)"). É uma música sem áudio, só
  com click e guia, com fader Click (grupo Acento / 1/4 / 1/8 / 1/16) e fader Guia. Entra na Fase 6 junto com a
  importação ("Add Click Section to Songs", "Click Section Length").
- **Tela vazia e "Novo Repertório"** com Nome e Data ("Tipo de Culto" e "Horário dos Cultos" são de organização e
  ficam fora do escopo). O título da tela é o nome do repertório; em modo de edição mostra o nome do modo. Fases 6 e 7.
- **Menu ≡ como painel lateral** (Ajustes, versão, notificações), **dicas de primeiro uso** (balão azul "NOVO" com
  ENTENDI) e o ponto vermelho de novidade no ≡. Fase 7.
- **Console com pontos de página** (⋮), que indicam quantos painéis existem (Faixas / Buses / Pad). Fase 7. O painel
  do pad (12 tons + LINK) entra na Fase 8.

## Fase 1 — Transporte fiel (curta, maior impacto ao vivo)

**Status (2026-10-14): feita**, nos commits nativo `d146bcf` e Flutter `6305771`. Evidência da segunda passada em
`docs/playback-analysis/pseudocode/second-pass/README.md`. O que mudou em relação ao texto abaixo:
- **Fade:** rampa linear por amostra (`FadeRamp`), sem pausa nem `FadeFinished`; o nível persiste em pausa e seek e volta a
  cheio em parar, RTZ e música nova (escolha própria); parado, vale na hora. Click, guias internos, `excludeFromFade` e os
  canais Click/Guia (`ChannelInfo.isClickOrGuide`, preenchido pelos slots da importação e inferido pelo rótulo nas músicas
  antigas) ficam de fora. A exceção dos partID 1 e 8 **continua pendente** (os nomes do enum de `FUN_10056fe0c` não aparecem
  nas funções extraídas); até lá todo canal click/guia fica fora (escolha própria).
- **Fade de fim:** fim − 5,0 s fixos (`FUN_1004fbb78`), mesma rampa, só se o fade estiver desligado; a música termina com
  `EndReached`. A condição "sem crossfade com próxima música" fica como gancho para a Fase 2 (`_endFadeFor`).
- **Início e fim:** `Track.startSeconds/endSeconds` (migram para o arranjo na Fase 3), `setPlayRange` no motor, tela
  `SongRangeSheet` aberta pelo relógio e pelo menu da música. Play a partir do 0 começa no início personalizado; o seek é livre.
- **RTZ:** **não para a música** (`FUN_1004f1918` reposiciona no início personalizado; `FUN_1002c4ea4(1)` só descarta o
  próximo sequenciador e fecha o grupo anterior). `TransportNotifier.returnToZero` faz seek ao início, descarta laço ao
  vivo e enfileirado e solta o fade; **não** mexe no MUTE MIDI (o Playback só reativa o MIDI cortado por crossfade; gancho
  para a Fase 2) nem nos laços predefinidos.
- **Pendente da fase:** os nomes dos casos de `FUN_10056fe0c`. Testes: nativo 3 execuções sem falhas; Flutter 221 testes e
  `flutter analyze` limpo, 3 execuções (com `LD_LIBRARY_PATH=native/build-linux` para ligar os testes de FFI real).

- **Fade em liga/desliga.** Rampa linear de 5 s para baixo e de volta para cima, reversível no meio. Não pausa e não
  gera `FadeFinished`. O transporte segue tocando.
  - Exclusões: o click e as guias internos do WTracks, os canais marcados como click ou guia, e `excludeFromFade`.
  - Durante um crossfade ao vivo o botão fica desativado.
  - Nativo: estender `FadeOut` para `FadeToggle` (alvo 0 ou 1, ponto de partida = ganho atual).
  - **[G]** `FUN_10064458c` (quais canais são "Fadeable"), `FUN_1000c588c` (segunda exclusão, talvez o pad),
    `FUN_10056fe0c` (o que são partID 1 e 8, que entram no fade mesmo sendo click/guia).
- **Pontos de início e fim da música** (`SongArrangement.storedStartTime/storedEndTime`). Play e RTZ começam no
  início personalizado. `EndReached` e o fade de fim usam o fim personalizado, escalado pela razão de tempo
  (`FUN_1003220ec`, `FUN_1002da1dc`). Na interface, tocar no relógio edita esses pontos.
  - Nativo: fim lógico da música e posição inicial no motor.
- **RTZ completo** (`FUN_10086a1c0`): parar, zerar o laço ao vivo, restaurar o laço infinito predefinido de cada
  seção, cancelar o crossfade ao vivo, apagar o botão de fade (volta o ganho) e reativar o MIDI.
- **Condições do fade de fim** (`FUN_1004f2edc`): não dispara se houver crossfade (transição 3 ou ao vivo) com uma
  próxima música. **[G]** `FUN_1004fbb78` e quem grava `fadeStartTimecode`.
- Testes: rampas, reversão no meio, exclusões, início e fim personalizados, RTZ restaurando os predefinidos.

## Fase 2 — Transições completas e segunda música carregada (nativo grande)

- **Modelo.** `SongTransition` com os 6 valores. "Cue First Song" na última música volta para a primeira. Continue Pad
  fica preso aos valores 0, 4 e 5.
- **Dois sequenciadores** (Playback: `Sequencer` atual em +0x20 e o próximo em +0x28). O motor ganha um segundo
  "deck":
  - a próxima música é pré-carregada em `preloadNextSongSequenceTime` = max(1, fim − duração − 0,064);
  - AutoLink começa a próxima em fim − 0,064 s;
  - Overlap e Crossfade usam uma janela = min(5 s, o que falta da atual, a primeira seção da próxima);
  - nada é pré-carregado enquanto um laço está ativo ou depois de um Live ReOrder a partir da última seção;
  - o limiar de fim é |fim − agulha| < 0,6 s.

  Constantes: `songTransitionBufferOffset` 0,064 s e duração 5,0 s (transition.c, linhas 12930–13420;
  `FUN_1004f25d4`).
- **Crossfade ao vivo** (toque duplo num cartão; `FUN_1004f9cd8`):
  - Duração:
    - 5 s para o tipo de conteúdo 0xd;
    - fora isso, 2 compassos no andamento inicial da próxima música;
    - se a próxima começa com contagem (tipo 0x19), 1 compasso mais a contagem;
    - 2 s quando a música não tem andamento.
  - O início se alinha ao próximo click que esteja a pelo menos 0,15 s, menos uma semicolcheia.
  - Durante o crossfade, o fade de fim e o fade do botão ficam suspensos.
- **[G]** As curvas de ganho de Overlap (próxima entra cheia, a atual termina sem fade) e de Crossfade não aparecem.
  Endereços: `FUN_100504f30`, `FUN_10056b3d8`, `FUN_100502888`, `FUN_1002c4ea4`, `FUN_10034293c`, `FUN_10050cb68`.
  `FUN_1002da058` precisa ser redecompilada com retorno `uint8`, porque o Ghidra a tipou como `void` e perdeu o valor
  da última música.
- Testes: cada transição com duas músicas sintéticas, pré-carga a tempo (sem underrun), cancelamento por laço,
  crossfade ao vivo alinhado ao click.

## Fase 3 — Mapa da música, Live ReOrder e arranjos

- **Tipos de seção** (`SongSection.storedSectionType/editedSectionTypeID`, catálogo `MetadataSection` com sigla e cores):
  - 0x19 é contagem ("Co"): sem guia nem contagem, a não ser em laço;
  - 0x18 é pulado, a não ser em laço;
  - 7 é especial nas guias;
  - 0 e 1 não têm guia.

  As cores e siglas das seções passam a vir do tipo e não da inicial do nome. **[G]** `FUN_1000344fc`, que dá o
  tipo e não está nos dumps, e a tabela de tipos (`MetadataSection.partID`).
- **Live ReOrder.**
  - O Playback guarda `Sequencer.enqueuedSongMapElement` e o aplica em `nextPreparationSequenceTime` (constantes 10,0
    e 0,05; `FUN_1004fdbe0`). A seção enfileirada pisca, e Loop e Laço infinito agem sobre ela.
  - Navegação anterior / confirmar / próxima, também pelo teclado: ←/→ e Return.
  - No WTracks: o toque duplo no selo hoje pula na hora e deve passar a enfileirar.
  - **[G]** `FUN_1005013b4`, os corpos de `previous/select/nextNavigationAction` e `FUN_1001b45c8`
    (`didLiveReorderFromFinalSection`).
- **Arranjos** (`SongArrangement`: vários por música, o padrão é só leitura, cópia de trabalho; cada um guarda seções,
  mixer, buses, início e fim, transição, fade de fim, master, banco MIDI e SMPTE).
  - Salvar, Salvar como novo, Renomear, Excluir e Restaurar.
  - Editar o mapa: duplicar, excluir, reordenar, combinar, aparar compassos, mover por compasso, e voltar a seção ou o
    mapa ao padrão.
  - Nativo: tocar um mapa **não linear**, ou seja, uma lista de elementos com intervalos de origem. É a generalização
    dos saltos de trim que já existem (`configureSkips`).
  - "Follow Default Arrangement" é só para o SMPTE (`storedSMPTEFollowsDefaultArrangement`, `FUN_1001b18dc`).
  - **[G]** Extrair por nome de classe (o filtro por palavra-chave não pegou): `SongMenuArrangementsViewController`,
    `SongMapEditViewController`, `SongMapAddSectionViewController`, `SongMapAdjunctSectionViewController`.
- **Grade com encaixe** na edição de seções e cues (o guia diz que a grade é "visual e snapping").

## Fase 4 — Mixer, roteamento e dispositivo de áudio

- **Buses globais × por música** ("Song Specific Buses") e **master global × por música** ("Song Specific Master
  Fader"). Hoje o WTracks só tem a versão por música. Precisa de um `GlobalBus` com nome e sigla, e de abreviação no
  bus. **[G]** quem lê `songSpecificBusesEnabled` além de `FUN_1001748e0`.
- **Saídas além do estéreo** (`OutputChannel{number,isPair}`, saídas 1, 2, 3, 4, 1/2, 3/4…, "Up to 32 MultiOuts"):
  - escolha do dispositivo de áudio (`AudioDevice`), rota bus → par ou canal mono;
  - a rota é lembrada por dispositivo, e o Auto Pan bloqueia o roteamento.
  - Nativo: o `BusChannel` já segue o contrato (outL, isStereo, mono = (L+R)/2). Falta o mapeamento para N canais e
    a escolha do dispositivo no JUCE.
- **Seleção de faixas por música** (`SongTrack.included`; "Select Tracks", "selecione ao menos 1 faixa que não seja
  guia").
- **Faixa de referência** (mostrar ou ocultar a mixagem original).
- **VU "estilo metrônomo"**: no início de cada click o medidor vai a 1,0 e volta a 0 em 0,05 s (`FUN_1005468f4`).
  Ajustar também a queda dos medidores para o modelo do Playback. **[G]** `FUN_10012d330` e a taxa do timer.
- **Rampa real da automação** (corrige o item 2 das correções). **[G]** `FUN_1001b4b38`, `FUN_1008223d4` e as
  chamadas `FUN_10085ca74`, `FUN_100860ea8`, `FUN_1003224d0` e `FUN_100823b10` (o que é o campo 0x14 da fórmula de
  compasso e como tempos viram segundos).

## Fase 5 — MIDI

- **Buses MIDI globais e nomeados** (Lyrics, Lights 1/2, Patches 1/2, Guitar, Aux 1/2), cada um com porta, canal e
  liga/desliga (`MIDIBus.storedPortID`, `lastConnectedPortName`; `FUN_10042f27c`, `10042f988`, `10042fd3c`).
- Escolha de várias portas para o MIDI clock e liga/desliga global do MIDI Out.
- **Mapeamentos:**
  - aviso de conflito ("Input Already Mapped");
  - mais ações: Laço, Laço infinito, MUTE MIDI, confirmar o Live ReOrder, faders e Master, selecionar música por número.
  - **[G]** a lista real de `mappingTypeID` nos consumidores de `ControlMapping` em midi.c.
- **ProPresenter Playlist e Item**, enviados como notas no início da música pelo bus de Lyrics. **[G]** `FUN_1004f5388`:
  quais notas são; o "F-1/F#-1" do guia não tem confirmação no binário.
- Edição de cues na waveform (◁ ··· ▷, Editar, Nudge em 1/16, Excluir) e o "tap" de Lyrics ao vivo (nota G-1 com
  velocidade crescente).
- Fidelidade: primeiro 0xF8 um período depois do start.

## Fase 6 — Biblioteca, setlists e importação

- **Importação:** pastas, .zip e AIFF, com número livre de faixas e detecção de click e guia pelo nome
  (`MetadataTrack.clickorguide`, `vocal`). Hoje são 8 WAVs fixos.
- **Biblioteca:** busca e ordenação; tom com enarmonia (`MetadataKey`).
- **Setlists** (`Setlist.notes`, `performanceDate`, `pinned`):
  - notas, data, duplicar, Salvar como nova e Sobrescrever;
  - limpeza das setlists antigas;
  - "Cue First Song" ligado à Fase 2.

## Fase 7 — Ajustes e interface restante

- **Painel de ajustes em abas** (Geral, Faixas, Buses, MIDI, Sobre). Os campos padrão vêm de `DefaultsManager`
  (`FUN_1001742d0`).
- O menu da música passa a editar no próprio painel (tom e andamento, início e fim, faixas, pad, MIDI Out).
- Dicas na primeira vez ("Reset Tool Tips"), reset de fábrica (três toques no rótulo do Master), Sobre e diagnóstico,
  avisos de pouca memória ou disco.
- **Economia de energia.** **[G]** quem lê `powerSaver` a partir de `FUN_1001742d0`.

## Fase 8 — Pad Player (precisa de áudios de pad fornecidos por você)

- `Pad`, `PadTrack` (uma faixa por tom) e `SongPadTrack`. `LoopingFilePlaybackAU` repete o arquivo inteiro, sem
  crossfade interno.
- A troca de pad e de tom usa um `fadeMixer` em passos (`FUN_100033820`, `FUN_100048768`).
- Iniciar com a música, só intro/outro (5 s), Continue Pad nas transições 0, 4 e 5, painel do pad com 12 tons e LINK.
- **[G]** quem chama `FUN_100033820` (intervalo e passo do fade).

## Fase 9 — Ajustes finos de fidelidade

- Timecode: amplitude ×0,5 e a tabela `DAT_00006538` (8 doubles) junto com `rateForFrameRate` em 0x5a70 **[G]**.
- Medidor mutado mostra 0. Seno de teste de 440 Hz × 0,1 (só se houver uso; parece ferramenta interna).
- Manter as escolhas melhores que o original: click calculado pelo mapa de andamento, guias pré-carregadas.

## Fase 10 — Validação em hardware

MIDI real de entrada e saída, interfaces multicanal, Android físico, iPhone, X32. Remote: nome do aparelho, escolha da
interface de rede, limpar cache. O protocolo do Playback Remote só fica compatível com uma captura de rede.

## Segunda passada no Ghidra — lista por prioridade

| Prioridade | Endereço / alvo | Por quê |
|---|---|---|
| Alta (Fase 2) | `FUN_1002da058` | Tipada como `void`; o valor de retorno (transição efetiva da última música) se perdeu. Redecompilar com retorno `uint8`. |
| Alta (Fase 2) | `FUN_100504f30`, `FUN_10056b3d8`, `FUN_100502888`, `FUN_1002c4ea4`, `FUN_10034293c`, `FUN_10050cb68` | Blocos despachados que não estão nos dumps: curvas de ganho de Overlap e Crossfade e início do AutoLink. |
| Alta (Fase 1) | `FUN_10056fe0c` | **Parcial:** `10064458c`/`1000c588c` resolvidas (canais de faixa; click/guia fora). Falta o nome dos casos do enum (rawValue 0x33 e 0x4bd). |
| ~~Alta (Fase 1)~~ | `FUN_1004fbb78` | **Resolvida:** fim × razão − 5,0 s. Quem grava `fadeStartTimecode` não foi localizado (não muda o comportamento). |
| Alta (Fase 3) | `FUN_1000344fc` e a tabela `MetadataSection` | Tipos de seção (0x18, 0x19, 7, 0, 1…). |
| Alta (Fase 3) | Classes `SongMenuArrangementsViewController`, `SongMapEditViewController`, `SongMapAddSectionViewController`, `SongMapAdjunctSectionViewController` | Edição do mapa e arranjos; extrair por nome de classe. |
| Média (Fase 3) | `FUN_1005013b4`, `previous/select/nextNavigationAction`, `FUN_1001b45c8` | Live ReOrder e navegação. |
| Média (Fase 4) | `FUN_1001b4b38`; `FUN_1008223d4` e as chamadas `FUN_10085ca74`, `FUN_100860ea8`, `FUN_1003224d0`, `FUN_100823b10` | Rampa real da automação e correção de duração. |
| Média (Fase 4) | `FUN_10012d330`, timer dos medidores, `FUN_100171178`, `FUN_1001711d0` | Fonte do nível, taxa de atualização e leitura do VU estilo metrônomo. |
| Média (Fase 4) | Leitores de `songSpecificBusesEnabled` e `songSpecificMasterFaderEnabled` | Como alterna entre o estado global e o da música. |
| Média (Fase 5) | `FUN_1004f5388` | Notas do ProPresenter Playlist e Item. |
| Média (Fase 5) | Consumidores de `ControlMapping.mappingTypeID` em midi.c | Lista real de ações mapeáveis. |
| Baixa (Fase 7) | Leitores de `powerSaver` e `referenceTrack` a partir de `FUN_1001742d0` | O que de fato mudam. |
| Baixa (Fase 8) | Quem chama `FUN_100033820`, e `FUN_100048768` | Passo e intervalo do fade do pad. |
| Baixa (Fase 9) | `DAT_00006538`, `rateForFrameRate` em 0x5a70 (Timecode), `FUN_1004f240c` | Tabela de multiplicadores e posição com e sem "Follow Default Arrangement". |
| Baixa | `DSPKernel::handleOneEvent` 0x4000 (jumptable) e os callbacks `std::function` (vtable+0x30) em Automation 0x5920 e Buffered 0x6298 | Chamadas indiretas que não foram resolvidas. |
| Baixa | Referências do executável a `ClickAudioUnit configureDSPKernelWithFileURL:clickTimes:` e `SineWaveAudioUnit` | Como o acento e o click normal se dividem em instâncias; para que serve o seno. |

Para cada item, exportar o pseudocódigo da função com as funções que ela chama (profundidade 2), as strings e os dados
referenciados, e colocar o resultado em `docs/playback-analysis/pseudocode/second-pass/<endereço>.c`.
