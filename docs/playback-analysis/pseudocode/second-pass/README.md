# Segunda passada no Ghidra — Fase 1 (transporte)

Saídas de `tool/playback_lookup.py fn <endereço> 0` sobre o export completo do executável principal
(`~/Playback/analysis/decompiled/Playback/…`, Ghidra 12.1.4, 38 855 funções). Pseudocódigo de decompilador de Swift/ObjC:
campos aparecem como `unaff_x20 + _TtC8Playback…::campo`, e a tipagem dos retornos pode estar errada.

## Conclusões

| Pergunta | Resposta | Evidência |
|---|---|---|
| O fade de fim usa quantos segundos? | **5,0 s fixos antes do fim** (`fim × razão − 5.0`). | `1004fbb78` |
| Quando o fade de fim dispara? | `arrangement.endFade` ligado, `fadeStartTimecode` definido, **sem** crossfade com próxima música, `fadeOutAtEndDidBegin` falso e agulha ≥ início do fade. Então chama o mesmo caminho do botão (`100647c80(1,…)`) e liga o botão. | `1004f2edc` |
| O fade manual termina a música ou pausa? | Não. O botão só chama `100647c80(selected, …)` e marca o botão; nenhum evento de fim. | `10086ba58` |
| Quais canais entram no fade? | `100647c80` percorre `SongChannelGroup.allChannels` filtrado por um protocolo (`10064458c`, os canais de faixa) e aplica a rampa em cada um (`10002a5fc`). Parado, o ganho é aplicado direto; `currentFadeVolume` fica em 0 quando desligado e parado. | `100647c80`, `10064458c` |
| Click/guia no fade? | `isClickOrGuide` fica **fora**, salvo partID cujo tipo mapeado é 1 (rawValue 0x33) ou 8 (0x4bd). `10056fe0c` é o `init(rawValue:)` de um enum de 17 casos (default 0x10 = nenhum); os **nomes** dos casos não aparecem nesta função → **pendente**. | `1000c5708`, `1000c588c`, `10056fe0c` |
| O RTZ para a música? | **Não há parada.** Ele limpa o crossfade ao vivo, desliga o fade, zera `liveLoopCount` e restaura `privateInfiniteLoop = presetInfiniteLoop` em cada elemento do mapa, e chama `Sequencer` `1004f1918`, que **reposiciona no primeiro elemento do mapa e em `storedStartTime × razão`** (`didReachSongEnd = false`). `1002c4ea4(1)` descarta o *próximo* sequenciador (+0x28) e finaliza o grupo de canais anterior (`1007337d4`, com atraso de 1 s): é limpeza de crossfade/pré-carga, não parada. | `10086a1c0`, `1004f1918`, `1002c4ea4`, `1007337d4` |
| MIDI no RTZ? | Só reativa o MIDI Out se ele foi cortado por crossfade (`MIDIOutAVAudioUnit.isCrossfading`). O MUTE MIDI do usuário não é tocado. | `10086a1c0` |
| Rampa do fade por faixa | Linear de `início` a `alvo` em `duração`, passos de `duração/(duração×30)` = 1/30 s, a partir do ganho atual; troca de alvo no meio reinicia a rampa do ganho corrente. | `10002c318` |

## Pendente

- Nomes dos casos do enum de `10056fe0c` (o que são rawValue 0x33 e 0x4bd). Até lá, todo canal click/guia fica fora do fade
  (**escolha própria**).

# Segunda passada — Fase 2 (transições)

| Pergunta | Resposta | Evidência |
|---|---|---|
| Curva do **Crossfade** (transição 3) | Por faixa: `t = (agora − início) / duração`. A música que **sai**: ganho = `clamp(1 − t, 0, 1)² × volume`. A que **entra**: `t² × volume` (zerado se a faixa está silenciada). Quadráticas, não lineares. O Playback atualiza a cada `duração / (duração × 5)` = **0,2 s**; o WTracks segue a mesma curva por amostra. | `1006513dc` (parâmetro `param_6` = saindo) |
| Curva da **Sobreposição** (transição 2) | Não há curva: `1002c662c` só chama o ramo do crossfade (`FUN_1002c7f08` → `1002c6eb0` → `100647514`) quando `uVar21 == 3`. Na 2 as duas tocam no volume total e a que sai simplesmente acaba. | `1002c662c` |
| O que 2 e 3 têm em comum | `(transição & 0xfe) == 2`. Para ambas: corta o click da que sai (`1006471c8`, `ClickChannel`), zera `soloState`, desliga o MIDI Out da que sai e, com a configuração "mestre por música" ligada, faz uma **rampa linear** do volume mestre do valor da música que sai para o da que entra (`100736e24`, passo de 0,17 s). | `1002c662c`, `1006471c8`, `100736e24` |
| MIDI no crossfade | O MIDI Out da música que **entra** fica cortado (`isCrossfading = 1`) até o RTZ ou o fim, e a da que sai é desligada. O WTracks não replica isso: as duas músicas enviam seus cues. | `100647514`, `10086a1c0` |
| Retorno de `FUN_1002da058` | O decompilador a tipou como `void`, mas o chamador compara o retorno com 3 e com `(v & 0xfe) == 2`: é a **transição efetiva**. Só a parte final (comparar com a última música da setlist) é visível; o resultado exato para a última música não aparece. Decisão (escolha própria): última música com 1/2/3 não tem para onde ir e fica como "Continuar na música"; 5 volta à primeira. | `1002da058`, `1004f2edc` |
| Janela e pré-carga | Constantes já documentadas em `transition.c` (0,064 s, 5 s). A pré-carga do Playback acontece na própria janela (`preloadNextSongSequenceTime`); no WTracks o carregamento é mais lento, então a próxima é carregada [`TransitionController.preloadLeadSeconds`] = 20 s antes (escolha própria). | `100502c78`, `1002c6100` |

## O que foi implementado (Fase 2)

- `AudioEngine` ganhou um segundo deck: dois motores compartilham o dispositivo, a saída MIDI e a entrada MIDI (`SharedIo`) e o
  dispositivo só enxerga um `DeckSwitch`, de modo que o hand-off é a troca atômica de um ponteiro, sem preparar nem esvaziar o motor
  que assume.
- A música que sai mistura a que entra por amostra (`scheduleTransition`): Sobreposição = as duas cheias; Transição Cruzada = (1−t)² e t².
  O click e as guias da que sai são cortados ao começar (escolha própria: dois clicks ao mesmo tempo atrapalham no palco).
- Com laço ativo a janela espera; ao soltar o laço ela começa na hora e encurta até o fim da música.
- O FFI ganhou o prefixo `wtracks_n_*` (deck 1) e `wtracks_prepare_next_deck`, `wtracks_schedule_transition`, `wtracks_handoff`.
- Dart: `TransitionController` pré-carrega a próxima no deck 1 com o mesmo caminho de carga (`NextTrackNotifier`), agenda, e adota a música
  depois do hand-off. Crossfade ao vivo por toque duplo no cartão ou teclas 1–9: 2 compassos da próxima, início no próximo tempo do click
  a pelo menos 0,15 s menos uma semicolcheia.

## Pendente

- Duração do crossfade ao vivo para o tipo de conteúdo 0xd (5 s) e para próxima música que começa com contagem (1 compasso + contagem):
  o WTracks não tem esses tipos, usa sempre 2 compassos (ou 2 s sem andamento).
- Rampa do volume mestre entre músicas (`100736e24`): só faz sentido com "mestre por música" global (Fase 4); hoje cada deck mantém o seu.
- Timecode e relógio MIDI da música que entra só ligam depois do hand-off (escolha própria, para não somar dois sinais).
