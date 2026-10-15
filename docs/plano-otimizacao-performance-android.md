# Plano de diagnóstico e otimização da performance de áudio no Android

Atualizado em 2026-10-15. Este plano trata travamentos, pausas e percepção ocasional de reprodução lenta ao executar uma música MultiTracks com múltiplos stems no WTracks.

## 1. Estado observado

- O pacote gratuito semanal foi baixado, validado, convertido e persistido em um aparelho Android real.
- A música possui múltiplos WAVs estéreo a 44,1 kHz e abre corretamente após reiniciar o WTracks.
- A reprodução completa apresenta travamentos e, às vezes, percepção de lentidão.
- Com a faixa de referência em Solo, o problema não foi percebido.
- Testes informais de volume e quantidade de faixas não foram conclusivos.
- O aparelho disponível para validação é um Xiaomi `23053RN02A`, Android 15/API 35, MediaTek MT6768, conectado ao computador por ADB via Wi-Fi.

Essas observações confirmam o sintoma, mas não distinguem ainda entre callback de áudio atrasado, falta de dados no read-ahead, sample rate incorreto, custo do mixer, pressão de CPU, renderização Flutter ou comportamento da saída de áudio.

## 2. Objetivo

Identificar a causa medida dos travamentos e aplicar a menor correção que:

1. mantenha todas as faixas sincronizadas;
2. preserve tom, velocidade e duração;
3. não aumente desnecessariamente a latência de controles ao vivo;
4. não introduza cliques ao usar Mute, Solo, seek, loop ou troca de música;
5. continue funcionando em aparelhos modestos;
6. produza evidência reproduzível em aparelho físico, além de testes automatizados.

## 3. Hipóteses e sinais de confirmação

| Hipótese | Evidência que confirma | Evidência que enfraquece |
|---|---|---|
| Callback excede o prazo | `renderStats.overruns > 0`, P99 próximo/acima de 100%, máximo acima do deadline | carga P99 baixa durante falha audível |
| Read-ahead não acompanha | `underrunCount` cresce enquanto carga do callback permanece moderada | nenhum underrun durante a falha |
| Buffer de 256 é pequeno | 512/1024 elimina falhas sem outra mudança | falhas idênticas em todos os buffers |
| Conversão 44,1→48 kHz custa demais | carga cresce com stems e cai ao usar WAVs no sample rate do dispositivo | dispositivo opera em 44,1 kHz ou custo não muda |
| Sample rate incorreto | áudio fica continuamente mais grave/agudo e duração diverge do relógio | apenas pausas, mantendo tom e duração |
| Mixer/roteamento/medidores pesam | carga cai com fast path de canais silenciosos ou medidores suspensos | callback permanece igual |
| Flutter/UI disputa CPU | jank e CPU da UI acompanham a falha, mas callback nativo isolado é estável | falha ocorre com tela simples e UI ociosa |
| Armazenamento/temperatura | falha aparece com aquecimento ou leitura baixa e desaparece em condição fria | comportamento estável entre repetições |

Solo não encerra o diagnóstico: atualmente canais em Solo continuam sendo lidos e reamostrados; a etapa final de mistura dos canais silenciados é que pode ser evitada. Isso torna I/O puro menos provável, mas não o elimina.

## 4. Entrega 0 — Preservação e baseline

Antes de alterar comportamento:

1. registrar `git status` e preservar todas as mudanças não commitadas;
2. confirmar que o aparelho aparece como `device` em `adb devices -l`;
3. resolver o serial dinamicamente, sem gravar endereço ADB no código ou documentação operacional;
4. instalar uma build debug produzida a partir do checkout atual;
5. confirmar que a música de teste persiste e abre;
6. desativar economia de bateria para o WTracks durante a medição;
7. usar primeiro o alto-falante ou saída cabeada; Bluetooth fica para uma rodada separada;
8. fechar tarefas pesadas, manter o aparelho sem carregamento térmico intenso e anotar temperatura/estado aproximado.

### Cenário baseline

- Reiniciar o WTracks.
- Abrir a mesma música MultiTracks.
- Não usar mudança de tom/andamento, loop, automação, MIDI ou segundo deck.
- Tocar por dois minutos em cada cenário:
  1. referência em Solo;
  2. todas as faixas ativas;
  3. painel Tracks visível;
  4. painel Waveform visível.
- Repetir a sequência duas vezes, uma com o aparelho frio e outra após uso contínuo.

Não usar percepção auditiva como única métrica. Registrar o instante aproximado de cada falha para correlacionar com contadores.

## 5. Entrega 1 — Instrumentação obrigatória

### 5.1 Configuração real do dispositivo

Expor pelo motor/FFI os valores efetivamente entregues por `prepareToPlay`, não apenas os valores solicitados por `initialise`:

- sample rate preparado;
- frames por callback;
- deadline calculado em milissegundos;
- quantidade de canais carregados;
- sample rate dos arquivos;
- razão de resampling por canal, resumida sem caminhos de arquivo.

Arquivos prováveis:

```text
native/include/AudioEngine.h
native/src/AudioEngine.cpp
native/include/ffi_bridge.h
native/src/ffi_bridge.cpp
flutter_app/lib/native/wtracks_bindings.dart
```

### 5.2 Métricas já existentes

Usar os contadores existentes, sem criar medição pesada no callback:

- `underrunCount`;
- callbacks contabilizados;
- overruns;
- tempo máximo do callback;
- carga P50, P95 e P99;
- deadline do callback.

Adicionar deltas por sessão de medição. Um contador histórico não deve ser interpretado como falha da execução atual.

### 5.3 Tela Diagnóstico

Adicionar uma seção **Áudio em tempo real** com:

- configuração real;
- métricas atuais;
- botão **Iniciar nova medição**, que zera apenas estatísticas apropriadas;
- marcador de início e duração;
- ação **Copiar diagnóstico** sem caminhos privados, credenciais ou dados MultiTracks;
- indicação textual: estável, underruns detectados ou callback acima do prazo.

A tela pode atualizar a cada 500 ms. Não atualizar essas métricas no callback nem adicionar polling global quando a tela estiver fechada.

### 5.4 Evidência externa via ADB

Durante cada rodada, registrar separadamente:

```bash
adb devices -l
adb shell dumpsys cpuinfo com.example.flutter_app
adb shell dumpsys gfxinfo com.example.flutter_app
adb shell top -b -n 1 -p "$(adb shell pidof com.example.flutter_app)"
```

Usar `logcat` filtrado somente para eventos técnicos do WTracks. Não registrar respostas de API, sessão, URLs ou dados pessoais.

### Aceite da Entrega 1

- Métricas aparecem e podem ser copiadas.
- Polling da tela de diagnóstico não altera contadores de áudio de forma relevante.
- Valores exportados não contêm segredos ou caminhos privados.
- Testes cobrem parsing/FFI e apresentação de estados.

## 6. Entrega 2 — Matriz A/B no aparelho

Executar a mesma música e o mesmo trecho em cada combinação abaixo. Alterar uma variável por vez.

### 6.1 Carga de áudio

1. referência em Solo;
2. duas faixas audíveis;
3. metade das faixas audíveis;
4. todas as faixas audíveis;
5. todas as faixas com ganho reduzido;
6. todas as faixas mutadas, mantendo o transporte.

Registrar se o ganho reduzido altera o sintoma. Se alterar sem mudar métricas de prazo, investigar clipping/saída; não confundir saturação com travamento.

### 6.2 Interface

1. Tracks com medidores;
2. Waveform sem a grade, quando aplicável;
3. Buses;
4. tela Diagnóstico;
5. app em background, somente se o serviço de reprodução atual sustentar esse cenário.

### 6.3 Buffer

Testar `256`, `512` e `1024` frames com o mesmo sample rate efetivo. A troca deve ocorrer com transporte parado e, inicialmente, pode exigir reinício do motor/app.

Não implementar adaptação automática antes de medir a estabilidade e a latência percebida de cada opção.

### 6.4 Sample rate

Comparar:

- arquivos atuais em 44,1 kHz com dispositivo no rate efetivo;
- uma cópia de teste convertida offline para o rate efetivo do dispositivo;
- nenhuma mudança de tom/tempo.

Não substituir os arquivos permanentes até o teste demonstrar benefício e preservar duração/alinhamento.

### Registro por cenário

| Campo | Valor |
|---|---|
| Cenário e duração | |
| Saída de áudio | alto-falante/cabo/Bluetooth |
| Sample rate / buffer | |
| Canais carregados / audíveis | |
| Underruns antes/depois | |
| Callbacks / overruns | |
| P50 / P95 / P99 / máximo | |
| CPU app / jank Flutter | |
| Falha audível e instante | |
| Tom/velocidade alterados | sim/não |

## 7. Entrega 3 — Otimizações de baixo risco

Estas mudanças podem ser preparadas após a instrumentação, mas devem permanecer separadas para permitir comparação.

### 7.1 Medidores e repaint

- reduzir o polling dos medidores de 50 ms para 100 ms;
- suspender o provider quando Tracks/Buses não estiver visível;
- não consultar medidores de canais fora da visualização quando isso puder ser feito sem alterar o motor;
- envolver waveform e regiões animadas apropriadas em `RepaintBoundary`;
- manter `select` por canal para evitar reconstruir o mixer inteiro;
- confirmar com `gfxinfo` que a mudança reduz frames lentos.

### 7.2 Buffer configurável

- introduzir opção de diagnóstico `256/512/1024`;
- aplicar somente com transporte parado;
- informar o compromisso entre estabilidade e latência;
- não escolher automaticamente um valor definitivo até a matriz A/B.

### 7.3 Logs e tarefas concorrentes

- evitar escrita em disco, serialização e logs frequentes durante reprodução;
- verificar se autosave, waveform e tarefas MultiTracks já concluídas permanecem ociosas;
- garantir que limpeza de staging/conversão não continue após a música estar pronta.

### Aceite da Entrega 3

- Nenhuma regressão visual ou funcional.
- Redução mensurável de jank ou carga, ou mudança descartada por falta de benefício.
- Testes de widgets e providers passam com timers controlados.

## 8. Entrega 4 — Correções condicionadas ao diagnóstico

Implementar apenas o ramo confirmado pelas medições.

### A. Callback acima do prazo

- aumentar buffer padrão apenas se 512/1024 comprovar estabilidade;
- perfilar mixer, automação, buses, click/guias, timecode e medidores por blocos;
- evitar cálculos por amostra quando puderem ser vetorizados sem mudar rampas;
- preservar ausência de alocação e locks bloqueantes no callback.

### B. Underrun com callback abaixo do prazo

- revisar um único `TimeSliceThread` para múltiplos `BufferingAudioSource`;
- medir read-ahead por canal e prioridade da thread;
- testar capacidade/estratégia de prefill, sem aumentar memória cegamente;
- não ler arquivo diretamente no callback.

### C. Resampling como gargalo

- converter os WAVs para o sample rate efetivo durante a importação ou primeira preparação;
- manter todos os stems com rate, duração e quantidade de frames compatíveis;
- publicar atomicamente e preservar a versão anterior em falha;
- evitar reconversão a cada abertura.

### D. Canais silenciados como gargalo

Criar fast path somente com testes sample-exact:

- canal em silêncio deve avançar sua posição sem renderizar/misturar áudio desnecessariamente;
- ao sair de Mute/Solo, retomar na amostra correta;
- prefill deve impedir atraso ou clique ao reativar;
- automação de volume/mute e fades têm precedência e podem impedir o fast path;
- loops, seek, transições e troca de sample rate devem invalidar/realinhar o estado.

Não simplesmente deixar de chamar o resampler: isso congelaria o playhead interno do canal e quebraria sincronização.

### E. Sample rate incorreto

- comparar rate solicitado, rate preparado e cabeçalho WAV;
- corrigir a origem da divergência sem alterar duração ou transporte;
- adicionar regressão 44,1↔48 kHz e teste de pitch/duração.

### F. UI como gargalo dominante

- reduzir atualizações e área de repaint;
- separar widgets que observam transporte, waveform, mixer e medidores;
- não mover processamento de áudio para Dart;
- comprovar que a mudança melhora `gfxinfo` e não apenas aparência subjetiva.

## 9. Testes automatizados

### Nativos

- estatísticas sem alocação no callback;
- rate e buffer reais expostos corretamente;
- 1, 2, 8, 11, 32 e 64 stems;
- arquivos 44,1 e 48 kHz;
- Mute/Solo com alinhamento ao reativar;
- loops, seek, fades, automação e transições após fast path;
- nenhum overrun no cenário controlado existente.

### Flutter

- tela Diagnóstico e exportação redigida;
- polling existe somente enquanto observado;
- medidores suspendem e retomam sem vazamento de timer;
- seleção de buffer não ocorre durante reprodução;
- configurações antigas continuam válidas.

### Build

Executar, nesta ordem:

1. testes nativos específicos;
2. testes Flutter específicos;
3. `flutter analyze`;
4. suíte Flutter completa;
5. build Android debug;
6. instalação no aparelho conectado.

## 10. Validação física e audível

O agente pode operar o aparelho conectado via ADB para instalar, iniciar, coletar métricas, alternar telas e executar passos determinísticos. A avaliação audível continua humana: o agente não deve afirmar ausência de falhas sonoras apenas porque contadores ou automação passaram.

### Procedimento final

1. instalar a APK recém-gerada sem apagar os dados da música;
2. confirmar versão/build exibida ou instalada;
3. iniciar nova medição;
4. tocar a música completa com todas as faixas por pelo menos cinco minutos;
5. testar Mute/Solo, seek e alternância Tracks/Waveform;
6. reiniciar app e aparelho, repetir o cenário;
7. repetir uma rodada em saída cabeada e, separadamente, Bluetooth se desejado;
8. copiar o diagnóstico e anexar os números ao relatório, sem dados de conta.

## 11. Critérios de aprovação

- [ ] Nenhum underrun durante cinco minutos no cenário padrão aprovado.
- [ ] Nenhum callback acima do prazo após aquecimento normal.
- [ ] P99 possui margem definida; alvo inicial inferior a 75% do deadline.
- [ ] Tom, velocidade e duração permanecem corretos entre 44,1 e 48 kHz.
- [ ] Todas as faixas permanecem alinhadas após Solo/Mute, seek e loop.
- [ ] UI permanece responsiva sem frames lentos recorrentes.
- [ ] Buffer escolhido possui latência aceitável para operação ao vivo.
- [ ] Reiniciar app/aparelho não muda o comportamento.
- [ ] Testes, análise e build passam.
- [ ] Validação audível é registrada separadamente da evidência automática.

## 12. Prompt executável

```text
Implemente o plano em /home/marcos/wtracks/docs/plano-otimizacao-performance-android.md por entregas pequenas e mensuráveis.

Comece pela instrumentação; não aplique uma correção definitiva antes de obter baseline no Xiaomi 23053RN02A conectado por ADB via Wi-Fi. Resolva o serial com `adb devices -l` em cada execução e não o grave no código. Preserve todas as mudanças não commitadas e não faça commits sem solicitação explícita.

Regras:
- Não atribua o problema ao aparelho sem evidência.
- Não registre credenciais, sessão, UUID, URL SAS, IDs pessoais ou respostas MultiTracks.
- Não execute rede, arquivo, alocação ou locks bloqueantes no callback de áudio.
- Use as métricas nativas existentes de underrun e RenderStats.
- Mude uma variável por rodada e mantenha resultados A/B.
- Otimizações de UI, buffer, read-ahead, resampling e canais silenciosos devem ficar separadas.
- Não pule o playhead de canais silenciados nem comprometa alinhamento.
- O agente pode instalar e operar o WTracks no aparelho via ADB, mas deve pedir ao responsável a confirmação de qualidade audível.
- Diferencie testes nativos, Flutter, build, execução física e validação auditiva no relatório final.

Pare uma otimização que não demonstre benefício mensurável e documente o resultado negativo. Ao final, deixe recomendação de configuração padrão baseada nos números coletados.
```


## 13. Resultados — 2026-10-15

Aparelho Xiaomi `23053RN02A` (Android 15), alto-falante, carregando por USB, ~34–36 °C. Música MultiTracks de 11 stems estéreo 44,1 kHz,
mix do usuário, painel Tracks (waveform + mixer com medidores) visível, 2 min por rodada salvo indicação.

### Configuração real encontrada (Entrega 1)

- Backend JUCE **Oboe → AAudio, modo Shared**, burst nativo 256 frames, HAL 48 kHz.
- O WTracks pedia 44,1 kHz / 256: o stream abria a 44,1 kHz (o AAudio reamostra para 48 kHz) com `BufferSizeInFrames = 256`, ou seja,
  **um único burst de folga**.
- O APK instalado era **debug**: nessa variante o C++ nativo é compilado sem `-O` (equivale a `-O0`).

### Matriz A/B (Entrega 2) — uma variável por vez

| Rodada | Build | Rate pedido | Buffer | Xruns do dispositivo | Underrun AudioFlinger (frames) | Acima do prazo | P50/P95/P99 | Máximo |
|---|---|---|---|---|---|---|---|---|
| A1 | debug | 44,1k | 256 | **297** | ~75 800 (~1,7 s) | 35 | 37,5/67,5/82,5% | 159% |
| A2 | debug | 44,1k | 512 | **0** | 0 | 23 | 37,5/65/77,5% | 143% |
| A3 | release | 44,1k | 256 | 4 | 1 024 | 0 | 22,5/35/37,5% | 96,5% |
| A4 | release | 44,1k | 512 | **0** | 0 | **0** | 22,5/35/37,5% | 66,6% |
| A5 | release | 48k | 256 | 4 | 1 024 | 2 | 27,5/42,5/45% | 116% |
| A6 | release | 48k | 512 | 0 | 0 | 2 | 27,5/42,5/47,5% | 119% |
| V1 | release | 44,1k | 512 (novo padrão), 5 min | **0** | 0 | 2 de 52 506 | 22,5/35/37,5% | 124% |

Underruns do read-ahead: **0 em todas as rodadas**.

### Leitura

- **Causa principal confirmada: fila de saída de 1 burst.** Com 256 frames qualquer atraso de agendamento vira xrun no Oboe/AudioFlinger,
  mesmo com o callback dentro do prazo (A3). Com 512 (2 bursts) os xruns zeraram em debug e em release.
- **Build debug dobra a carga do callback** (P99 82,5% → 37,5%) e gera dezenas de callbacks acima do prazo. Não é o que o usuário final
  executa, mas explica por que o problema era mais audível nos testes com `flutter run`.
- **Hipóteses enfraquecidas:** read-ahead (0 underruns sempre); pedir 48 kHz (aumenta a carga por reamostrar 11 stems no motor e não reduz xruns).
- **Não medido de forma confiável:** jank do Flutter — `gfxinfo` não enxerga o surface do Flutter (0 frames). A thread de raster ficou em 12–19% de CPU.
- Restam callbacks isolados acima de 5,8 ms em release (2 em 5 min); a folga de 512 os absorveu sem xrun. Provável preempção do SO, já que
  P99 = 37,5%; não investigado.

### Mudanças aplicadas

- Instrumentação: `wtracks_get_audio_config`, `wtracks_set_buffer_size`, `wtracks_get_available_buffer_sizes`; seção **Áudio em tempo real**
  na tela Diagnóstico (medição com deltas, xruns do Oboe, exportação sem dados privados, troca de buffer só parado, polling de 500 ms só com a tela aberta).
- **Padrão novo: 44,1 kHz / 512 frames** (`engine_provider.dart`); `--dart-define=WTRACKS_SAMPLE_RATE` / `WTRACKS_BUFFER` para novas medições.
  Latência adicional: ~5,8 ms.
- Entregas 3.1 (medidores/repaint) e 4.B–D não foram implementadas: as medições não apontaram mixer, read-ahead ou canais silenciados como gargalo.

### Validação audível

- 2026-10-15, pelo responsável, build release com o padrão 44,1 kHz / 512: duas músicas, incluindo a MultiTracks de 11 stems, com todas as
  faixas ativas — reprodução sem travamentos nem lentidão, "muito mais fluida que antes".

### Pendente

- Repetir a validação audível após reiniciar o aparelho e com saída cabeada/Bluetooth.
- Opcional: compilar o nativo com `-O2` também na variante debug, para que `flutter run` reflita o desempenho real.
