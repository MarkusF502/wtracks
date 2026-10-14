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
