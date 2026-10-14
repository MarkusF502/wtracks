# Análise do Playback e planejamento de melhorias para o WTracks

Data: 14/10/2026. Análise de produto, evidências estáticas e planejamento; nenhuma implementação realizada nesta sessão.

## 1. Conclusão

O Playback é uma referência forte de player para apresentações: integra reprodução multitrack, mapa de música, click, guias, mixer, buses, transições, automação, MIDI e timecode em um fluxo de palco. Seu valor está na coordenação dessas funções, e não apenas no número de recursos.

As oportunidades mais relevantes para o WTracks são autonomia sobre arquivos próprios, recuperação de dados, previsibilidade de tempo, preparação de apresentações e clareza do estado do aplicativo. A prioridade deve ser confiabilidade antes de ampliar recursos ou perseguir semelhança visual.

O WTracks já possui grande parte do núcleo. O trabalho futuro deve consolidar essa base, corrigir riscos próprios e escolher explicitamente onde seguir o Playback e onde oferecer um comportamento melhor.

## 2. Base, evidências e limites

- Playback analisado: binário 8.5.3, ARM64, SHA-256 `2a11a6f98134ba035c9df55d0ab5cabd376597ce83980ff40704f4f42b1ad423`. Hash conferido nesta sessão.
- Os hashes dos 24 módulos do manifesto foram conferidos: 24/24 correspondem aos artefatos locais. O relatório existente contabiliza 70.830 resultados. Seu PASS é de contabilização da exportação, não de correção do aplicativo; o executável principal tem uma função com decompilação falha.
- Evidências REA exportadas: principal `ev_602147281b6b715dcae794d752280b24d866a8e805bb45b98f9643b3c8f4b07e`; click `ev_3da155baeb6ebc8db3ce257a48b0158146b6721a9bfc80154e44e8d9551dbec7`; master `ev_bad8183edb242d2194d70a079efdfc0a470fc49c4c4232505f54fc9f18cee727`. São registros exportados de sessões anteriores. O ledger da conexão REA atual está vazio; não houve nova decompilação ampla.
- Modelo Core Data, árvores de interface e pseudocódigo ajudam a estabelecer estruturas e caminhos. Strings isoladas não comprovam execução ou disponibilidade de uma função.
- Capturas do iPhone 8.6.2 são referência visual de outra versão. A imagem `05.jpg` foi inspecionada diretamente; mostra controles densos e uma barra de modos de edição. Não demonstra usabilidade em todos os tamanhos nem comportamento do 8.5.3.
- Documentação oficial foi consultada online para contextualizar o produto atual. Essa documentação não foi tratada como comportamento comprovado do binário 8.5.3.
- WTracks: HEAD observado `2172688`. O working tree estava modificado e recebeu novas mudanças durante a análise, incluindo `transition_provider.dart`, `click_grid.dart` e testes. Afirmações negativas iniciais sobre transições foram descartadas após nova leitura. A versão final examinada já contém coordenador de transições e eventos separados.
- Não foram executados testes Flutter, builds, emulador, Playback no iOS, teste auditivo ou hardware MIDI/USB nesta sessão. Resultados anteriores são históricos e precisam ser repetidos para liberar uma versão atual.

Classificação: **observado** = presente no artefato/código/documentação; **risco inferido** = consequência plausível que exige teste; **proposta** = decisão de produto para o WTracks; **pendente** = depende de execução ou evidência adicional.

Fontes locais principais: [cobertura](coverage-report.md), [contratos](subsystem-contracts.md), [pseudocódigo e origem](subsystem-contracts.json), [tom/andamento](timepitch-contract.md), [manifesto](artifact-manifest.json). O plano atual do WTracks está em [PLANO-DESENVOLVIMENTO.md](/home/marcos/wtracks/docs/PLANO-DESENVOLVIMENTO.md).

## 3. Playback como aplicativo

### 3.1 Forças que vale preservar

| Dimensão | Força | Aplicação no WTracks |
|---|---|---|
| Operação de palco | Transporte, repertório, mapa e mixer próximos | Manter leitura rápida da música atual, seção e próxima ação |
| Flexibilidade musical | Loops, reordenação, guias e automação | Coordenar tudo no mesmo relógio musical |
| Integração técnica | Buses, MIDI, LTC e interfaces de áudio | Separar sinal para público, banda e equipamentos |
| Preparação | Arranjos, mapas e repertórios reutilizáveis | Reduzir configuração repetida e variações acidentais |
| Ecossistema | Conteúdo, colaboração e integração MultiTracks | Reconhecer o valor; concentrar WTracks em arquivos locais |

O [guia oficial](https://helpcenter.multitracks.com/en/articles/4944485-playback-user-guide) descreve o fluxo integrado de transporte, mapas, mixer e MIDI. O pacote local confirma modelos e subsistemas correspondentes. Não há fundamento para reduzir o Playback a um player simples.

### 3.2 Pontos fracos de produto e oportunidades

**Dependência do ecossistema para fluxos com conteúdo próprio.** A oferta oficial associa uso de conteúdo próprio ao Cloud Pro e recursos avançados de saída a assinaturas. Isso acrescenta preparação de conta, upload e administração ao fluxo de quem já tem stems locais. É uma limitação de autonomia, não prova de que toda reprodução exige internet. Proposta: no WTracks, importar, preparar, salvar e executar arquivos locais sem serviço remoto; distinguir preparação concluída de download ou processamento pendente. Fontes: [produto](https://www.multitracks.com/products/playback/?direct=1), [Cloud Pro](https://helpcenter.multitracks.com/en/articles/5242856-get-started-cloud-pro-subscription).

**Roteamento com escopos que podem surpreender.** A documentação oficial informa que track→bus é global e específico do aparelho, e que os mixes de buses podem ser por música. Consequência inferida: mudar uma rota para resolver uma música pode afetar outras. Proposta: mostrar claramente o escopo de cada ajuste; usar perfis de dispositivo, defaults globais e overrides explícitos por projeto, com prévia dos efeitos. Não alterar automaticamente a saída para o público após trocar de interface. Fonte: [roteamento oficial](https://helpcenter.multitracks.com/en/articles/4439220-how-to-track-bus-routing-in-playback).

**Interface densa e muitos modos.** A captura 8.6.2 e o catálogo de UI mostram controles, camadas e modos concentrados. Isso permite operação rápida para quem conhece o aplicativo, mas traz risco de baixa descoberta e confusão entre preparar e executar. É uma avaliação de design, ainda sem teste de usuários. Proposta: preservar a visão integrada, acrescentar modo palco que protege edição destrutiva, indicar modo atual por texto e tornar ações essenciais acessíveis sem gesto oculto. Cores devem ser acompanhadas por nomes e estados.

**Dependência de dispositivos e conexões externas.** O suporte oficial trata dropouts, desconexões, USB e interfaces como problemas relevantes. Não é evidência de um defeito particular do Playback. Proposta: checagem de prontidão e diagnóstico local que identifique arquivo, dispositivo, rota, memória ou leitura atrasada; política explícita para troca de USB e interrupção do sistema. Fonte: [solução de problemas de áudio](https://helpcenter.multitracks.com/en/articles/4873511-troubleshooting-playback-audio-issues).

**Complexidade de estados e recuperação.** O produto combina tempo original/processado, arranjos, loops, fades e duas músicas em transição. Erros surgem nas interações entre essas funções, mesmo quando cada uma funciona sozinha. Proposta: máquina de estados documentada, snapshots consistentes e testes de combinações. Não há evidência suficiente para afirmar que o Playback não possui undo, backup, acessibilidade ou recuperação; esses pontos permanecem perguntas de avaliação em dispositivo.

### 3.3 Riscos técnicos observados no Playback

| ID | Observado no pseudocódigo | Fraqueza/risco inferido | Melhoria proposta no WTracks |
|---|---|---|---|
| PB-T1 | MIDIClock calcula o próximo pulso somando ao índice anterior convertido para float e estreitando para int | Arredondamento acumulado e perda de precisão em execução longa | Grade absoluta em inteiro de 64 bits com fase fracionária preservada; teste de muitas horas |
| PB-T2 | Envio MIDI legacy usa malloc/free; caminhos modern/legacy usam timestamps diferentes | Trabalho e latência variáveis no caminho alcançado pelo render | Fila limitada para despacho fora do callback e timestamps coerentes |
| PB-T3 | Guide process dispara atualização de arquivo/reprodução via dispatch_async | Início de áudio não garantido na amostra do cue; possível dependência do agendamento externo | Pré-decodificar, validar e publicar agenda pronta antes de tocar |
| PB-T4 | MIDIOut usa ajuste literal de 1764 samples em uma condição de pré-transição | Intervalo temporal muda com sample rate se o ramo for usado nessas taxas | Unidade temporal explícita; caracterizar intenção antes de traduzir para samples |
| PB-T5 | Geração do vetor LTC pode realocar quando capacidade insuficiente e é alcançável pelo render | Prazo do callback pode sofrer na realocação | Buffers de capacidade fixa preparados fora do render |
| PB-T6 | Tom/andamento é renderizado em arquivo offline | Preparação tem custo de tempo, disco e cache | Mostrar prontidão, permitir cancelamento e preparar previamente o repertório |

Âncoras PB-T1/T2: `MIDIClockAUFramework` `00005548` e `000056a4`, `analysis/decompiled/MIDIClockAUFramework/8a282176f92a-2a4a38e34a84/batch-000001.json`. O envio legacy usa agora + 10 ms; isso não mede a latência final da interface.

PB-T3: `GuideAUFramework` `00006140`, `analysis/decompiled/GuideAUFramework/2522677d34ef-2a4a38e34a84/batch-000002.json`. Há aviso de decompilação; o caminho assíncrono está presente, mas atraso audível não foi reproduzido.

PB-T4: `MIDIOutAUFramework` `00005a2c`, `analysis/decompiled/MIDIOutAUFramework/a76d7007c4f1-2a4a38e34a84/batch-000001.json`. 1764 samples correspondem aritmeticamente a 40 ms em 44,1 kHz e 36,75 ms em 48 kHz. A intenção musical desse ajuste não foi recuperada.

PB-T5: `TimecodeAUFramework` `0000549c` → `000057e8` → `00005a94`, `analysis/decompiled/TimecodeAUFramework/ae88b748f0e4-2a4a38e34a84/batch-000001.json`. A realocação é condicional; não ocorre necessariamente em cada frame.

PB-T6: [contrato](timepitch-contract.md), principal `0x10000da98`, `0x10000df18`, `0x10000df64`. Processamento offline também é uma força: reduz custo de DSP durante a apresentação. A qualidade do algoritmo próprio do WTracks ainda precisa de comparação auditiva.

Nenhum desses achados autoriza afirmar que o Playback falha audivelmente em condições normais. Também não se concluiu ausência de pan, headroom ou tratamento global de clipping apenas porque um kernel soma sinais.

## 4. WTracks atual: reaproveitar e corrigir

### 4.1 Base já implementada

O código já possui read-ahead, fila/generation de carregamento, click e mapa de andamento, guias preparadas, loops contados, trim, pré-roll, mixer/buses, automação, MIDI, LTC, processamento offline de tom/andamento, persistência JSON atômica, autosave, diagnóstico e remoto próprio.

Segundo deck e transições nativas estão commitados. O working tree final examinado contém `TransitionController`, pré-carga, crossfade ao vivo, eventos separados e hand-off. **Consolidar e validar**, sem reimplementar como recurso inexistente. O plano antigo e seus status precisam ser conciliados com esse trabalho em andamento.

### 4.2 Achados próprios do WTracks

| ID / prioridade | Evidência observada | Impacto e ação |
|---|---|---|
| WT-01 / P0 | Release usa signingConfig debug; README alerta sobre desinstalação | Atualização pode apagar biblioteca. Assinatura estável, backup e teste de atualização; qualquer mudança de applicationId exige migração planejada |
| WT-02 / P0 | saveTrack move arquivos antes de publicar JSON; TODO reconhece janela inconsistente | Morte do processo pode deixar importação incompleta. Staging, journal/manifesto e recuperação de conjunto |
| WT-03 / P0 | Picker Android usa DISPLAY_NAME diretamente como destino | URIs homônimas no mesmo lote podem sobrescrever conteúdo antes da persistência. IDs próprios, basename validado, confinamento e hashes |
| WT-04 / P0 | saveCurrent publica snapshot após await se apenas o ID ainda coincide | Risco inferido de reverter edição mais recente durante gravação. Reproduzir com barreira de I/O; revisão/generation e merge de caminhos |
| WT-05 / P0 | Settings usa um único .part sem fila; leitura com erro volta ao default | Gravações concorrentes podem conflitar; corrupção pode parecer reset. Serializar, sinalizar falhas e recuperar anterior válido |
| WT-06 / P1 | renderOwn mantém channelsLock; transição mantém transitionLock durante render do próximo deck | Contenção pode estourar deadline. Medir e retirar destruição/trabalho pesado dos trechos disputados |
| WT-07 / P1 | TimePitch carrega entrada integral; vocoder mantém grandes vetores; dois workers | Pico de RAM não está limitado pelos tetos isolados de entrada/saída. Orçamento total e paralelismo adaptativo |
| WT-08 / P1 | Cache TimePitch só exige arquivo existente com >44 bytes | Arquivo incompleto pode ser reutilizado. Validar header, frames, duração e identidade antes de publicar |
| WT-09 / P1 | Inicialização de áudio solicita duas saídas; serviço Android é básico | Multicanal e interrupções precisam de contrato e execução física. Seleção de dispositivo, capacidades, foco e recuperação |
| WT-10 / P1 | Release compila/publica separado dos testes Android | Build distribuído pode não ter passado regressões. Gates comuns obrigatórios antes de publicar |
| WT-11 / P2 | Importação tem oito slots fixos; setlist omite músicas ausentes | Limita conjuntos reais e esconde repertório incompleto. Stems dinâmicos, placeholders e prontidão por item |
| WT-12 / P2 | Fader tem Semantics de valor, sem ações acessíveis; alvos de edição 26×26 | Controle por leitor de tela e precisão de toque incompletos. Labels, incremento/decremento e hitbox ampliada |
| WT-13 / P1 se remoto ativo | WS, bind em todas IPv4, PIN de quatro dígitos, sem limitação visível de tentativas/comandos | Controle por participantes não autorizados é risco inferido em rede compartilhada. Pareamento forte, expiração, revogação, limites e fila |
| WT-14 / P1 | Track aceita schemaVersion recebido, mas toJson publica versão atual e campos conhecidos | Abrir projeto de versão futura pode perder campos ao salvar. Rejeitar versão não suportada e migrar versões antigas explicitamente |
| WT-15 / P2 | Diagnóstico retém 300 entradas apenas em memória | Reinício perde evidência. Log circular persistente, versão/engine/dispositivo e saneamento de dados ao exportar |

Fontes precisas:

- WT-01: [Gradle](/home/marcos/wtracks/flutter_app/android/app/build.gradle.kts:28), [README](/home/marcos/wtracks/README.md:22).
- WT-02: [persistência](/home/marcos/wtracks/flutter_app/lib/services/persistence_service.dart:129). JSON já usa fila/flush/rename; isso não resolve atomicidade do conjunto áudio+metadados.
- WT-03: [picker](/home/marcos/wtracks/flutter_app/android/app/src/main/kotlin/com/example/flutter_app/MainActivity.kt:149). Confinamento é requisito defensivo; não houve exploração de path traversal.
- WT-04: [saveCurrent](/home/marcos/wtracks/flutter_app/lib/providers/engine_provider.dart:1191). Concorrência efetiva depende dos chamadores; hipótese a reproduzir antes de corrigir.
- WT-05: [preferências](/home/marcos/wtracks/flutter_app/lib/services/app_preferences_store.dart:18).
- WT-06: [render](/home/marcos/wtracks/native/src/AudioEngine.cpp:1470), [transição](/home/marcos/wtracks/native/src/AudioEngine.cpp:1416).
- WT-07/08: [decode](/home/marcos/wtracks/native/src/TimePitchFile.cpp:48), [vocoder](/home/marcos/wtracks/native/include/TimePitch.h:62), [cache e workers](/home/marcos/wtracks/flutter_app/lib/services/time_pitch_service.dart:118).
- WT-09: [motor](/home/marcos/wtracks/native/src/AudioEngine.cpp:57), [serviço](/home/marcos/wtracks/flutter_app/android/app/src/main/kotlin/com/example/flutter_app/PlaybackService.kt:34). Não se concluiu ausência de tratamento de dispositivos no JUCE; a lacuna está no contrato e integração do app.
- WT-10: [release](/home/marcos/wtracks/.github/workflows/android-apk.yml:48), [CI Android](/home/marcos/wtracks/.github/workflows/android-tests.yml:57). Emulador sem áudio não valida áudio ouvido.
- WT-11: [importação](/home/marcos/wtracks/flutter_app/lib/screens/import_screen.dart:22), [setlists](/home/marcos/wtracks/flutter_app/lib/services/persistence_service.dart:254).
- WT-12: [fader](/home/marcos/wtracks/flutter_app/lib/screens/performance_screen.dart:2155), [alvos](/home/marcos/wtracks/flutter_app/lib/screens/performance_screen.dart:1425). Linhas da UI podem mudar pelo trabalho concorrente.
- WT-13: [remoto](/home/marcos/wtracks/flutter_app/lib/services/remote_server.dart:38). Já possui timeout e limite de mensagem; fortalecer essa base. Protocolo próprio, sem compatibilidade comprovada com Playback Remote.
- WT-14: [schema](/home/marcos/wtracks/flutter_app/lib/models/track.dart:483), leitura em `fromJson` na linha 533 da versão examinada.
- WT-15: [diagnóstico](/home/marcos/wtracks/flutter_app/lib/services/diagnostics_log.dart:16). O compartilhamento de diagnóstico deve permitir revisão pelo usuário; não coletar credenciais.

**Cobertura de plataformas:** o diretório iOS examinado ainda apresenta scaffold (`Info.plist` com Flutter App/flutter_app, sem `UIBackgroundModes`; `AppDelegate` registra plugins). Não foi encontrada integração do motor WTracks na busca delimitada em `flutter_app/ios`. iOS exige marco separado com build/link do motor, sessão de áudio, background, MIDI, permissões e execução física; não anunciar suporte apenas por existir pasta Flutter. Android e Linux também exigem que cada capacidade seja validada na plataforma correspondente.

## 5. Direção de implementação

Preservar Flutter/Riverpod + Dart FFI + C++/JUCE. Dart organiza edição, persistência e preparação; o motor agenda eventos sensíveis a tempo. Timer de interface pode observar estado, mas não define fronteiras de áudio.

Três contratos devem orientar as mudanças:

1. **Projeto recuperável:** áudio identificado por conteúdo, biblioteca e arranjos com IDs estáveis, esquema versionado, gravações recuperáveis e exportação portátil com caminhos relativos.
2. **Sessão de palco:** estado selecionado/preparando/pronto/tocando/em transição/erro; nenhum resultado obsoleto substitui o atual; prontidão reflete os dois decks e seus recursos.
3. **Motor previsível:** buffers e agendas preparados, ownership explícito, orçamento de memória, despacho MIDI fora do render e política definida para underrun, seek, loop e perda de dispositivo.

Separar identidade do dispositivo, perfil de roteamento, arranjo musical e estado transitório. Não salvar automaticamente um fade momentâneo ou posição de reprodução como edição de arranjo sem decisão explícita.

## 6. Plano por fases e critérios de aprovação

### Fase A — consolidar a base em andamento

**Dependência:** nenhuma; executar antes de novas mudanças.

Registrar HEAD, diff e versão de FFI; preservar alterações existentes; revisar coordenador de transições, deck ownership, cancelamento, máscaras de eventos e hand-off. Conciliar inventário e plano com o código real. Criar baseline reproduzível do build que será testado.

**Aprovação:** analyze e suítes Flutter/nativas passam com biblioteca recém-compilada; todos os novos testes constam do log; cada uma das seis transições tem comportamento definido. Regressão intencional deve ser detectada por teste relevante. Nenhum resultado histórico serve como aprovação desta base.

### Fase B — dados e atualização segura (P0)

Resolver WT-01 a WT-05 e WT-14. Implementar importação em staging, manifesto recuperável, identidade própria dos stems e publicação só após validação. Manter originais até commit do conjunto. Serializar preferências e proteger autosave com revisões. Criar backup/restauração com manifesto, esquema e hashes; arquivos fornecidos pelo usuário permanecem portáveis.

Preparar assinatura persistente para futuras builds; manter applicationId existente até haver estratégia de migração. Se a versão instalada usa outra chave, a transição precisa de backup antes de uma eventual reinstalação.

**Aprovação:** duas URIs homônimas preservam conteúdos diferentes; matar o processo em cada etapa da importação não publica projeto quebrado; falta de espaço não apaga o original; editar durante save não reverte valores novos; restaurar backup em instalação limpa preserva músicas e repertórios; atualização com mesma identidade/assinatura preserva dados. Realizar testes de falha, não apenas round-trip normal.

### Fase C — continuidade e desempenho de palco (P1)

Consolidar o coordenador já em implementação. Testar pré-carga atrasada, música curta, loop ativo, cancelamento, reorder da setlist, seek durante preparação, crossfade manual e falha do próximo arquivo. Definir fallback seguro e visível quando a próxima música não fica pronta; não prometer ausência de interrupção se ainda precisa carregar.

Instrumentar duração do callback e pico de memória. Trocar publicação de recursos por snapshots preparados e retirar liberação pesada de locks disputados pelo render, onde as medições justificarem. Orçar read-ahead, dois decks, loops, guias e TimePitch em conjunto. Reduzir paralelismo/processar por blocos quando necessário; validar cache além do tamanho do arquivo.

**Aprovação:** fronteiras verificadas por samples em sinais sintéticos; nenhum cue duplicado após seek/loop; resultado obsoleto descartado; duas músicas trocam sem desalinhar estado/áudio. Em configuração-alvo, cada callback cumpre seu prazo `blockFrames/sampleRate` no cenário de teste, com máximo e percentis registrados. Testes determinísticos e soak de duas horas sem underrun não explicado nem crescimento contínuo de RAM; isso é critério de teste, não garantia universal.

### Fase D — dispositivos, roteamento e integração do sistema (P1)

Tratar WT-09, ampliar saídas para capacidades realmente reportadas pelo dispositivo, perfis por interface e teste de cada saída. Definir escopo global/arranjo para mixer e roteamento. Click/guia e LTC precisam de indicação explícita de destino; não remapear silenciosamente uma rota ausente.

Definir política de audio focus, chamada/notificação, desconexão de fone/USB, tela apagada e retorno do sistema. Notificação com controles/media session conforme plataforma. MIDI: portas persistentes, reconexão, clock e note-off no cancelamento. LTC: decoder independente, taxas fracionárias, drop-frame e seek.

**Aprovação:** testes físicos Android com tela apagada, interrupções e USB; impulses identificam todas as saídas; nenhuma troca de interface envia click/guia para saída não aprovada; receptor MIDI confirma ordem e timestamps; decoder externo confirma LTC. Sem hardware disponível, marcar cada item pendente em vez de aceitar emulador como substituto.

### Fase E — preparação, arranjos e recuperação de edição (P2)

Stems dinâmicos, seleção de pasta/ZIP/formato com limites e validação, autoidentificação com confirmação. Limites reais de canais devem ser derivados do motor/dispositivo. Para ZIP, validar confinamento, tamanho expandido e duplicatas.

Arranjos separados da música original, revisões, undo/redo para edições relevantes, copiar/restaurar e mapa não linear. Live ReOrder enfileirado para fronteira musical, grade por compasso e indicação inequívoca da seção atual/próxima. Repertórios com ocorrências de música independentes quando o mesmo título se repete; placeholders para recursos ausentes em vez de omiti-los.

**Aprovação:** projeto legado migra; editar um arranjo não altera outro; duas ocorrências da mesma música funcionam; exportar/importar em outro aparelho resolve caminhos; undo restaura mapa/mix/cues; toda pendência de arquivo permanece visível e é detectada antes do show.

### Fase F — UX de palco e autonomia (P2)

Modo palco com edição protegida, controles essenciais visíveis, estado textual de pronto/preparando/erro, próxima música e próxima ação. Barra de modos como referência, adaptada para telefone/tablet, sem obrigação de copiar cada detalhe visual. Ampliar hitboxes, labels semânticos, ajuste acessível dos faders, contraste e comportamento com texto ampliado.

Criar checagem de prontidão: arquivos, processamento concluído, espaço, interface, rotas, portas MIDI e próxima música. Os diagnósticos já existem; melhorar resumo, persistência e ação recomendada. Pastas customizadas precisam de seletor adequado à plataforma, em vez de depender de path digitado. Priorizar click-only e pad apenas depois da base; pad pode usar áudios próprios ou geração escolhida explicitamente.

**Aprovação:** operadores completam importar→preparar→repertório→tocar sem ajuda; ensaio em telefone/tablet não produz edição acidental; controles funcionam por teclado/leitor de tela; tela de prontidão identifica corretamente falhas injetadas. Comparar tempo/erros com baseline, sem inventar números de melhoria antecipados.

### Fase G — remoto e distribuição confiável

WT-13 é P1 quando remoto estiver habilitado em rede compartilhada; caso contrário, permanece posterior. Pareamento por token/QR, expiração, limites, revogação, interface de rede explícita, estado visível e fila de comandos. Decidir transporte autenticado/cifrado compatível com os clientes; não anunciar compatibilidade com Playback Remote sem evidência de protocolo.

Tornar publicação dependente de gates de analyze, Flutter, nativo e integração. Vincular APK a commit, versão da biblioteca, resultado dos testes e assinatura. Separar build de desenvolvimento de versão liberada para palco.

**Atualização pelo próprio WTracks (P0, adicionada ao planejamento em 2026-10-14):** implementar consulta de versão,
download HTTPS de APK validado e instalação pelo `PackageInstaller` Android, com confirmação do usuário e preservação
da biblioteca. A especificação está na **Fase 0.1** do [plano de desenvolvimento](/home/marcos/wtracks/docs/PLANO-DESENVOLVIMENTO.md).
Antecipar assinatura estável/versionamento na Fase B; não aguardar as funcionalidades posteriores desta Fase G.

- Preparar migração das builds debug: conferir chave antiga, manter `applicationId` e, se atualização compatível não
  for possível, validar backup/restauração antes de uma eventual reinstalação inicial.
- Publicar `update.json` por canal com versão, compatibilidade, URL de release específica, tamanho, hash e certificado.
- Criar Ajustes → Atualizações; primeira entrega com download iniciado pelo usuário, cancelamento e nova tentativa.
- Adiar atualização durante reprodução/preparação, validar APK e tratar autorização, cancelamento e erros do sistema.
- Concluir saves antes da instalação, registrar versão-alvo, migrar dados e confirmar resultado na próxima abertura.
- Aprovar A → B preservando áudios/metadados, rejeição de APK incompatível/corrompido, interrupções e testes em Android
  físico. Versão futura pela Google Play usará atualização pela loja; esta especificação é da distribuição direta.

**Aprovação:** tentativas e flood são limitados; cliente revogado não controla transporte; comandos concorrentes preservam ordem definida; publicação falha quando regressão relevante é introduzida; reinstalação/atualização e restauração são ensaiadas antes da release.

## 7. Política de testes e entrega

Cada bloco: problema e contrato → implementação pequena → regressão significativa → revisão do diff → validação → commits separados quando nativo e Flutter forem independentes. Não descartar mudanças prévias. Correções de segurança/dados devem preceder aprimoramentos visuais.

| Camada | O que comprova | O que permanece fora |
|---|---|---|
| Modelos/serviços Flutter | Migração, persistência, estado e regras | Áudio físico e comportamento do sistema |
| C++ com sinais sintéticos | Agendas, samples, DSP e fronteiras | Latência USB, som ouvido e firmware externo |
| FFI real | ABI, ownership e integração com motor atual | Qualidade auditiva e continuidade em background físico |
| Emulador Android | Arquivos, permissões e fluxos Android testados | Interface USB/MIDI física, carga térmica e áudio ouvido |
| Android físico/interface | Interrupções, saída, estabilidade e recursos | Equivalência com Playback no iOS |
| Comparação Playback/iOS | Comportamentos efetivamente comparados, com versões registradas | Recursos e versões não testados |

Repetir testes de concorrência quando o risco justificar; medir render separado dos testes funcionais. A CI pode usar sinais sintéticos, mas a release para palco precisa de uma sessão física documentada.

## 8. Decisões e investigação ainda necessárias

- Política de underrun: manter relógio, pausar ou interromper sessão? Deve ser escolhida por caso, principalmente com MIDI/LTC externos.
- Política de interrupções: parar de forma controlada, pausar ou exigir retomada explícita? Não adotar ducking arbitrário no palco.
- Routing: defaults globais + override por arranjo, com compatibilidade por dispositivo; decidir como avisar saída ausente.
- Crossfade: curva musical é escolha de produto até comparação; já existe curva quadrática no motor, sem prova de equivalência universal.
- Recursos do Playback: preservar proveniência existente; a política de distribuição dos recursos deve ser decidida separadamente do desenho do player. Áudios próprios podem eliminar dependência do pacote.
- Qualidade TimePitch: corpus com bateria, baixo, voz, teclas e mix estéreo; avaliar transientes, fase, duração e som com mudanças grandes/pequenas.
- Playback: caracterizar MIDI por taxa/tempo longo, início das guias, LTC e transições em aparelho; não classificar riscos estáticos como bugs confirmados.
- Pad, compatibilidade Playback Remote e funções cloud não são pré-requisitos para consolidar o núcleo local.

## 9. Cobertura da solicitação

Produto e arquitetura: analisados com evidências locais e fontes oficiais. Fraquezas técnicas: identificadas com distinção entre observação e consequência inferida. UX: avaliação das referências e código, pendente de testes de operadores. Dados, segurança local, desempenho e distribuição: achados estáticos e plano com critérios. Comparação auditiva, estabilidade física e equivalência iOS: pendentes.

Próximo bloco recomendado: **Fase A seguida de Fase B**, respeitando o trabalho de transições em andamento. Só depois avançar desempenho/dispositivos e preparação/UX. Não foram alterados código, configuração, banco ou histórico do WTracks nesta análise.
