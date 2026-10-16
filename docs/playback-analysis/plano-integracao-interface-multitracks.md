# Plano de desenvolvimento da interface MultiTracks no WTracks

Atualizado em 2026-10-15. Este plano transforma os contratos já capturados e implementados em um fluxo de usuário Android integrado ao WTracks. Ele complementa o [contrato da API](multitracks-api-contract.md) e o [plano técnico das capturas](plano-integracao-multitracks-capturas.md); não substitui nenhum deles.

## 1. Objetivo

Permitir que uma pessoa autenticada com sua própria conta MultiTracks:

1. entre na sua conta pelo WTracks;
2. consulte as músicas da biblioteca da organização autorizada;
3. examine metadados, tonalidades e todas as faixas disponíveis;
4. confirme explicitamente qualquer uso de Rental;
5. baixe e importe um pacote `.mtrack`;
6. acompanhe download, validação, extração e conversão AAC/M4A para WAV;
7. encontre a música pronta na biblioteca local do WTracks e possa adicioná-la a uma setlist.

O primeiro lançamento deve integrar a **biblioteca já pertencente à organização**, pois esse é o contrato validado. Ele não deve anunciar pesquisa no catálogo completo, compra de conteúdo, upload Cloud, MT Complete, Pads, Soundbeds ou sincronização de repertórios enquanto esses contratos não forem capturados e testados.

## 2. Referências de produto e limites de uso

### Guias oficiais

- [Pesquisar e Adicionar Músicas no Playback](https://helpcenter.multitracks.com/pt-BR/articles/12660048-pesquisar-e-adicionar-musicas-no-playback), consultado em 2026-10-15. O guia descreve o fluxo atual: abrir/criar repertório, tocar em **Adicionar Música**, pesquisar ou abrir a biblioteca, configurar a música e concluir com **Adicionar** ou **Alugar**.
- [Guia do Usuário do Playback](https://helpcenter.multitracks.com/pt-BR/articles/4944485-guia-do-usuario-do-playback), consultado em 2026-10-15. O guia detalha login, organização, biblioteca, produto, canais, tom/andamento e início do download.
- Evidência visual local extraída do aplicativo autorizado em [`ui/ui-index.md`](ui/ui-index.md), incluindo estados como baixar, alugar, atualizar, erro e concluído.

### Como usar as referências visuais

Os prints dos guias servem para compreender hierarquia, sequência, feedback e nomenclatura. A implementação deve:

- conservar a identidade visual escura, cores, tipografia e componentes do WTracks;
- adotar padrões compreensíveis do Playback, como configuração antes do download e estado visível por música;
- não copiar marca, logotipo, imagens proprietárias, layout pixel a pixel ou textos promocionais do Playback;
- identificar o serviço como **MultiTracks** e o aplicativo como **WTracks**;
- tratar o guia como referência de produto, não como prova de contrato da API.

### Diferenças deliberadas da primeira versão

| Guia do Playback | Primeira versão do WTracks |
|---|---|
| Busca em todo o catálogo | Busca somente na biblioteca validada da organização |
| Produtos, arranjos e seleção arbitrária de canais | Tonalidade e visualização de todas as faixas; importar todos os stems válidos do pacote |
| Repertório Cloud | Biblioteca e setlists locais do WTracks |
| Download integrado ao ecossistema Playback | Download, validação, transcodificação e persistência local explícitos |
| Diversas modalidades de conteúdo | Conteúdo adquirido/concedido e Rental somente quando o backend indicar essa ação |

## 3. Princípios obrigatórios

1. **Sem efeitos colaterais implícitos:** abrir uma música ou consultar metadados nunca resgata Rental.
2. **Confirmação de Rental:** chamar `redeemRental` somente após uma ação explícita e uma confirmação clara. Não repetir automaticamente após timeout.
3. **Credenciais protegidas:** senha existe apenas durante a autenticação; não vai para logs, JSON de música, diagnósticos ou memória persistente. Apenas a sessão deve ser guardada em armazenamento seguro.
4. **Identidade estável:** não copiar o UUID do iPhone nem gerar novo identificador a cada execução. Usar a identidade própria persistida do WTracks com o perfil transitório autorizado.
5. **URL opaca:** nunca mostrar ou registrar a URL SAS de download.
6. **Conteúdo confiável:** uma música só entra na biblioteca após tamanho, MD5 quando disponível, LZ4, ZIP, CRC, mapeamento de stems e WAVs terem sido validados.
7. **Cancelamento real:** cancelar deve interromper a etapa em curso, remover staging e preservar qualquer versão válida já publicada.
8. **Sem trabalho pesado na UI:** rede, hash, descompactação e transcodificação não podem bloquear frames nem o callback de áudio.
9. **Estado honesto:** sucesso de HTTP não basta; `result`, `errorCode`, direitos e presença de `downloadUrl` determinam o resultado.
10. **Offline honesto:** a biblioteca local continua visível offline, mas o WTracks não deve inventar renovação, validade ou direito de reprodução.

## 4. Arquitetura proposta

### 4.1 Camadas

```text
Telas/widgets
    ↓ ações e AsyncValue/estado imutável
Providers Riverpod
    ↓ casos de uso
Sessão | Biblioteca | Conteúdo | Trabalho de importação
    ↓
Transportes HTTP | armazenamento seguro | downloader | importer | persistência WTracks
```

Separar as seguintes responsabilidades:

- `MultiTracksAuthService`: autenticação e interpretação do envelope de login.
- `MultiTracksSessionStore`: armazenamento seguro da sessão e do identificador estável; nunca da senha.
- `MultiTracksLibraryService`: paginação e busca em `library/songs` usando `MultiTracksLibraryRequestBuilder`.
- `MultiTracksContentProvider`: consulta de metadados, link e Rental, mantendo proteção contra sessão obsoleta.
- `MultiTracksPackageDownloader`: transferência validada para staging privado.
- `MultiTracksPackageImporter`: validação do pacote, mapeamento de todas as faixas e conversão para WAV.
- `MultiTracksImportCoordinator`: máquina de estados que orquestra as operações acima e publica progresso para a UI.
- `TrackLibraryNotifier`: carregamento e salvamento final na biblioteca local já existente.

### 4.2 Arquivos previstos

Usar os nomes abaixo como direção, adaptando-os apenas se o código existente exigir:

```text
flutter_app/lib/models/multitracks_session.dart
flutter_app/lib/models/multitracks_library_song.dart
flutter_app/lib/models/multitracks_import_job.dart
flutter_app/lib/providers/multitracks_provider.dart
flutter_app/lib/services/multitracks_auth_service.dart
flutter_app/lib/services/multitracks_session_store.dart
flutter_app/lib/services/multitracks_library_service.dart
flutter_app/lib/services/multitracks_import_coordinator.dart
flutter_app/lib/screens/multitracks_login_screen.dart
flutter_app/lib/screens/multitracks_library_screen.dart
flutter_app/lib/screens/multitracks_song_screen.dart
flutter_app/lib/widgets/multitracks_import_progress.dart
```

Reutilizar, sem duplicar lógica:

- `multitracks_contract.dart` para builders e modelos do conteúdo;
- `multitracks_content_provider.dart` para operações de conteúdo;
- `multitracks_package_downloader.dart` para a transferência;
- `multitracks_package_importer.dart` para o pacote e as faixas;
- `trackLibraryProvider` e `PersistenceService` para a publicação local.

### 4.3 Persistência de origem

Adicionar ao modelo `Track`, de forma opcional e retrocompatível, uma origem equivalente a:

```text
provider: multitracks
contentId
libraryId, quando presente
keyId
contentType
stemsVersion/packageVersion, quando presentes
entitlementKind: owned | rental | weekly | unknown
entitlementExpiresAt, quando informado com timezone
lastValidatedAt
```

Não persistir `hash`, senha, URL SAS, identificador do aparelho ou resposta bruta. A origem permite distinguir atualização de duplicação, explicar a procedência das faixas e exibir validade sem codificar tudo no `Track.id`.

Até a política de expiração ser confirmada, conteúdo vencido deve ser sinalizado e revalidado antes de novo download; não apagar áudio automaticamente nem prolongar direitos localmente.

## 5. Mapa de navegação

```text
Biblioteca WTracks / Adicionar música
    └── MultiTracks
        ├── sem sessão → Login MultiTracks
        └── com sessão → Biblioteca MultiTracks
                             └── Detalhes da música
                                  ├── selecionar tonalidade
                                  ├── conferir faixas e direito
                                  ├── Baixar
                                  └── confirmar Rental → Alugar e baixar
                                         ↓
                              Progresso da importação
                                         ↓
                              Música local pronta
                                  ├── Abrir no WTracks
                                  └── Adicionar à setlist atual
```

### Pontos de entrada

1. Em `LibraryScreen`, trocar a ação única do botão `+` por um seletor com:
   - **Importar arquivos**;
   - **Biblioteca MultiTracks**.
2. Em `_AddSongDialog`, incluir **Biblioteca MultiTracks…** junto de **Importar música…**.
3. Se a importação começou a partir de uma setlist, devolver a `Track` pronta ao fluxo de inserção existente. Se começou da biblioteca, abrir a música ou voltar à lista local conforme a escolha final.

## 6. Especificação das telas

### 6.1 Login MultiTracks

**Conteúdo:** título, explicação curta, usuário/e-mail, senha com revelar/ocultar, botão **Entrar**, indicador de atividade e link textual para política/ajuda se existir destino aprovado.

**Comportamento:**

- desabilitar duplo envio;
- usar autofill e ação de teclado apropriada;
- manter a senha apenas no controller durante a chamada e limpá-la após sucesso ou descarte;
- traduzir erros de negócio conhecidos, incluindo credenciais inválidas, limite de aparelhos e falta de permissão;
- em limite de aparelhos, mostrar a mensagem do servidor de forma segura, sem tratar `hash` eventualmente presente como sessão válida;
- restaurar sessão válida sem reapresentar senha.

**Organizações:** no MVP, usar a organização padrão retornada e validada pelo login. Se houver mais de uma e os dados não forem suficientes para montar o contexto com segurança, informar que a seleção ainda não é suportada; não chamar uma rota de seleção ainda não capturada.

### 6.2 Biblioteca MultiTracks

**Barra superior:** voltar, título **Biblioteca MultiTracks**, estado de conexão e menu com atualizar/sair.

**Corpo:**

- campo de busca com debounce entre 300 e 500 ms;
- lista de músicas da organização, com capa remota opcional, título, artista, álbum e indicador de acesso;
- paginação incremental ao aproximar do fim;
- pull-to-refresh sem apagar a página válida enquanto carrega;
- skeleton ou progresso na primeira carga;
- estados separados para vazio, busca sem resultado, offline, sessão expirada e erro recuperável.

Não exibir abas Artistas/Álbuns/Temas/Gêneros no MVP apenas porque os endpoints existem: os schemas não vazios dessas categorias ainda não foram confirmados. A estrutura pode ser preparada sem tornar a função visível.

### 6.3 Detalhes e configuração da música

Seguir a sequência conceitual do guia oficial, adaptada ao que foi validado:

1. capa, título, artista, álbum, BPM, tom original e duração;
2. estado do direito: adquirido, Rental disponível/ativo, oferta semanal ou desconhecido;
3. seletor de tonalidade somente com as tonalidades devolvidas pelo backend;
4. lista completa e ordenada das faixas, marcando Click/Guia e vocais quando os metadados permitirem;
5. tamanho do pacote e estimativa de expansão para WAV, claramente identificada como estimativa;
6. ação final fixa: **Baixar** ou **Alugar e baixar**.

No MVP a lista de canais é informativa e todos os stems válidos da tonalidade são importados. Só habilitar seleção parcial quando o importer, a estimativa e os testes garantirem que o subconjunto é preservado corretamente.

Se a música e a mesma tonalidade já estiverem locais, substituir a ação por **Abrir** e oferecer **Baixar novamente/Atualizar** em ação secundária. Se outra tonalidade estiver local, explicar que a nova tonalidade será uma variante separada até existir uma política explícita de substituição.

### 6.4 Confirmação de Rental

Modal obrigatória, sem confirmação preselecionada:

- nome da música e tonalidade;
- texto inequívoco de que um crédito poderá ser consumido;
- créditos restantes, se a resposta informar;
- expiração, se informada;
- botões **Cancelar** e **Confirmar aluguel**.

Após confirmação, bloquear novos toques. Em timeout ou resposta ambígua, não repetir `redeemRental`: consultar metadados/estado e orientar a pessoa caso não seja possível reconciliar.

### 6.5 Progresso de download e importação

Usar um painel ou tela que sobreviva à reconstrução de widgets e represente etapas reais:

```text
Preparando
Obtendo autorização
Baixando — bytes / total e percentual quando houver total
Validando pacote
Extraindo pacote
Convertendo faixa X de N — nome da faixa
Salvando na biblioteca
Concluído
```

O progresso não deve saltar para 100% ao terminar a rede, porque a conversão para WAV pode ser a etapa mais demorada e consumir muito mais espaço. Mostrar **Cancelar** até a publicação final; ao cancelar, informar que nenhum crédito já confirmado pode ser automaticamente devolvido.

Na conclusão, oferecer **Abrir música** como ação principal. Erros devem indicar a etapa, permitir nova tentativa segura quando aplicável e nunca revelar URL, hash ou caminhos privados completos.

## 7. Máquina de estados

### Sessão

```text
unknown → restoring → signedOut
                    → authenticated
signedOut → authenticating → authenticated
                         └→ failure
authenticated → signingOut → signedOut
authenticated → expired → signedOut
```

Cada login/logout/troca de organização incrementa uma geração. Respostas de gerações antigas não podem atualizar a tela nem iniciar download.

### Biblioteca

```text
idle → initialLoading → data | empty | failure
data → refreshing → data | failureComDadosAntigos
data → loadingMore → data | fimDaLista | failureComDadosAntigos
data → searching → data | empty | failure
```

### Importação

```text
idle
→ consultingMetadata
→ awaitingRentalConfirmation (quando necessário)
→ redeemingRental (somente após confirmação)
→ requestingDownloadLink
→ downloading
→ validating
→ extracting
→ transcoding
→ loadingEngine
→ saving
→ completed
```

Todos os estados ativos podem chegar a `cancelled` ou `failed`. A transição `redeemingRental` não possui retry automático. O coordinator deve manter um único trabalho ativo por `contentId + keyId` para evitar downloads e resgates duplicados.

## 8. Sequência de implementação

### Entrega 0 — Preparação e contratos de UI

- inventariar alterações não commitadas e preservá-las;
- criar modelos de sessão, item de biblioteca, origem da Track e estado do trabalho;
- criar fixtures sintéticas redigidas para login, biblioteca, metadados, direito adquirido, Rental e erros;
- introduzir abstração de armazenamento seguro e sua implementação Android;
- cobrir serialização retrocompatível de `Track`.

**Aceite:** nenhum segredo em fixture/log; tracks antigas continuam abrindo; testes dos modelos passam.

### Entrega 1 — Sessão e login

- implementar serviço/provider de autenticação e restauração;
- criar tela de login e logout;
- tratar limite de aparelhos e sessão obsoleta;
- usar a organização padrão validada.

**Aceite:** login real somente em teste manual autorizado; testes automatizados usam transporte falso; senha nunca é persistida.

### Entrega 2 — Biblioteca e pontos de entrada

- criar serviço/provider paginado de `library/songs`;
- criar tela responsiva com busca, refresh, paginação e estados vazios/erro;
- integrar os dois pontos de entrada do WTracks;
- manter a biblioteca local intacta e disponível offline.

**Aceite:** abrir MultiTracks não altera a música tocando; busca atrasada não sobrescreve busca mais nova; páginas não duplicam itens.

### Entrega 3 — Detalhes, tonalidade e direitos

- consultar metadados sem link e sem resgate;
- mostrar todas as faixas reconhecidas e tonalidades válidas;
- calcular estimativa de expansão e verificar espaço livre;
- implementar confirmação explícita de Rental e reconciliação segura.

**Aceite:** abrir detalhes gera apenas consulta; cancelar Rental não produz chamada de resgate; seleção inválida não inicia download.

### Entrega 4 — Download, importação e persistência

- implementar coordinator com progresso e cancelamento;
- obter link, baixar, validar, importar e converter fora da UI;
- carregar a Track no motor, salvar via fluxo existente e atualizar `trackLibraryProvider`;
- devolver a Track ao fluxo de setlist quando aplicável;
- manter staging e pacote fora de backup/exportação.

**Aceite:** falha em qualquer etapa não publica música parcial; todas as faixas esperadas aparecem na ordem correta; Click/Guia preservam sua marcação; sucesso aparece imediatamente na biblioteca local.

### Entrega 5 — Robustez e validação Android

- testar falta de espaço, cancelamento, perda de rede, URL expirada, app em background, rotação e processo recriado;
- definir retenção do `.mtrack` e dos M4A após sucesso;
- medir tempo, tamanho temporário e expansão em aparelho físico;
- validar reprodução audível, alinhamento e duração de todas as faixas.

**Aceite:** build e testes passam, mas a entrega só é considerada validada em runtime após exercício em Android físico com conta e conteúdo autorizados.

## 9. Estratégia de testes

### Unidade

- parsing e redaction de login/biblioteca/conteúdo;
- paginação, deduplicação e descarte de resposta antiga;
- estados e transições do coordinator;
- regra de não repetir Rental;
- estimativa de disco com overflow e valores ausentes;
- serialização retrocompatível da origem MultiTracks.

### Widget

- login: carregando, erro, limite de aparelhos e sucesso;
- biblioteca: loading, vazio, lista, busca, paginação e sessão expirada;
- detalhes: tonalidades, faixas, adquirido, Rental e já baixado;
- modal de Rental: cancelar não chama resgate; confirmar chama uma vez;
- progresso: todas as etapas, cancelamento, falha e conclusão;
- acessibilidade: labels, contraste, escala de texto e alvos de toque.

### Integração automatizada

- servidor/transportes falsos; nenhuma API real em CI;
- fluxo adquirido: login falso → biblioteca → metadata → link → pacote sintético → importar → salvar;
- fluxo Rental com confirmação única;
- logout no meio de cada chamada;
- falhas de MD5, LZ4, ZIP, CRC, stem ausente e transcoder.

### Android físico

- validar `MediaExtractor`/`MediaCodec` com pacote autorizado mantido fora do Git;
- comparar número, nome, ordem, duração e alinhamento das faixas;
- reproduzir, mutar/solar, buscar e reabrir após reiniciar o app;
- medir uso de disco antes, durante e depois;
- confirmar que cancelamento e falhas limpam staging;
- registrar separadamente evidência visual, runtime e audível.

## 10. Critérios de pronto do MVP

- [ ] Login e restauração de sessão funcionam sem persistir senha.
- [ ] A biblioteca validada da organização possui busca e paginação.
- [ ] A tela de detalhes mostra tonalidades e todas as faixas reconhecidas.
- [ ] Consulta não resgata Rental; resgate exige confirmação inequívoca.
- [ ] Download exibe bytes/progresso e valida integridade.
- [ ] Conversão mostra faixa atual e não bloqueia a interface.
- [ ] Falha/cancelamento não deixa música parcial na biblioteca.
- [ ] Track pronta é salva, aberta e adicionável à setlist.
- [ ] Origem e direito são persistidos sem credenciais ou URL SAS.
- [ ] Testes unitários/widget/integração passam.
- [ ] Build Android passa.
- [x] Um aparelho Android físico valida todas as faixas e reprodução audível para a amostra semanal de 11 stems. Arquivos,
  carregamento e transporte foram auditados; o responsável confirmou stems, metrônomo e guia audíveis.
- [ ] Pendências de licença, expiração e retenção estão documentadas sem comportamento inventado.

## 10.1 Estado da implementação (2026-10-15)

Entregas 0 a 4 implementadas no Flutter/Android. A Entrega 5 foi iniciada em aparelho físico para a oferta semanal:
download/importação persistidos, WAVs e carregamento no motor foram comprovados; robustez e audição ainda estão pendentes.

| Evidência | Estado |
|---|---|
| Análise estática (`flutter analyze`) | sem problemas |
| Testes automatizados (unidade, provider, widget; transportes falsos, sem API real) | 340 passando, dos quais 49 novos para a interface MultiTracks |
| Build Android (`flutter build apk --debug`) | passa (Kotlin do Keystore e do espaço livre compila); nada foi executado em aparelho |
| Login, biblioteca, download e importação reais da oferta semanal em Android físico | **validado com evidência persistida; sem recibo HTTP independente** |
| 11 WAVs e carregamento no motor | **validado; transporte avançou de 0:00 para 0:08** |
| Reprodução fisicamente audível | **validada por confirmação humana para a amostra semanal** |

Arquivos: `models/multitracks_{origin,session,song_details,import_job}.dart`, `services/multitracks_{auth_service,session_store,library_service,import_coordinator}.dart`, `providers/multitracks_provider.dart`, `screens/multitracks_{login,library,song}_screen.dart`, `widgets/multitracks_import_progress.dart`, `MultiTracksSecureStore.kt`. O item de biblioteca reutiliza `MultiTracksSongSummary` (não há `multitracks_library_song.dart`).

Decisões tomadas na implementação:

- **Sem etapa "carregando no motor".** A importação publica na biblioteca local sem trocar a música aberta; o motor só recebe a música quando a pessoa toca em **Abrir música** (ou quando o fluxo "Adicionar música" a insere na setlist). Carregar durante a importação interromperia uma apresentação.
- **Retenção:** o `.mtrack`, o ZIP e os M4A são apagados ao fim de cada trabalho (sucesso, falha ou cancelamento). Ficam só os WAV na biblioteca. Staging fica no diretório temporário, fora de `wtracks_data` e do backup.
- **Sessão:** hash e contexto cifrados com AES-GCM do Android Keystore, em preferências excluídas do backup automático. Fora do Android, o login fica indisponível em vez de gerar uma identidade nova a cada execução.
- **Atualização:** baixar de novo a mesma música e tonalidade substitui os canais e mantém as preferências da música e, por rótulo, as dos canais. Os áudios antigos só são apagados depois que o JSON novo é gravado. Não é possível atualizar a música que está aberta.
- **Rental:** um único `redeemRental` por `contentId:keyId` em cada sessão do app. Resposta perdida → uma consulta de link sem resgate; nova tentativa nunca pede outro aluguel.
- **Espaço:** conferido depois do download, quando o tamanho real é conhecido (estimativa de 27× o pacote: pacote, ZIP, M4A e WAV, com os WAV contados duas vezes por causa da cópia ao salvar). `fileSize` não é usado porque a unidade não foi confirmada.
- **Organizações:** usa o contexto de nível superior do login; com mais de uma organização, apenas avisa que a troca ainda não é suportada.

Pendências por falta de contrato capturado (funções paradas, não inventadas):

1. **Vínculo biblioteca → conteúdo.** `library/songs` devolve `songID`/`libraryID`; `content/download` exige `contentID`, `contentType` e `keyID`. A correspondência não foi capturada, então tocar num item da biblioteca mostra os dados do item e a pendência, sem nenhuma chamada. Até a captura, detalhes e download funcionam pela ação experimental **Abrir por identificador…** (os mesmos três números da probe; só consulta metadados).
2. Corpo da rota `logout`: a saída é local (sessão apagada do aparelho), sem chamada ao servidor.
3. Código de negócio de sessão expirada: só HTTP 401/403 são tratados como expiração.
4. Unidade de `duration` e `fileSize`: não exibidos como tempo/tamanho.
5. Mapeamento seções/andamentos/compassos/MIDI do JSON para a `Track`: não convertido.
6. Política de expiração/offline do conteúdo: conteúdo vencido é sinalizado na biblioteca, nunca apagado nem prolongado.
7. O áudio importado entra no backup do WTracks como qualquer outra música; a política de backup de conteúdo licenciado ainda não foi acordada.

## 11. Fora do MVP

- catálogo global e compra;
- seleção por artistas, álbuns, temas ou gêneros sem schemas reais não vazios;
- preview de áudio remoto;
- MT Complete, Click & Pad, Pads Ambiente e Soundbeds;
- upload Cloud, repertórios/arranjos Cloud e sincronização entre aparelhos;
- transferência de Rentals;
- retomada HTTP por Range antes de teste real;
- downloads em background com serviço persistente;
- seleção parcial de canais;
- iOS, Windows e macOS;
- reprodução de conteúdo vencido sem política formal confirmada.

## 12. Prompt executável para um agente de desenvolvimento

```text
Implemente a integração de interface MultiTracks no WTracks, em /home/marcos/wtracks, seguindo integralmente:

- docs/playback-analysis/plano-integracao-interface-multitracks.md
- docs/playback-analysis/plano-integracao-multitracks-capturas.md
- docs/playback-analysis/multitracks-api-contract.md

Use os guias oficiais apenas como referência de fluxo e hierarquia visual:
- https://helpcenter.multitracks.com/pt-BR/articles/12660048-pesquisar-e-adicionar-musicas-no-playback
- https://helpcenter.multitracks.com/pt-BR/articles/4944485-guia-do-usuario-do-playback

Regras obrigatórias:
1. Inspecione AGENTS.md, git status e os diffs antes de editar. Preserve todo trabalho não commitado e não faça commit sem pedido explícito.
2. Mantenha a identidade visual do WTracks. Não copie marca, assets ou layout pixel a pixel do Playback.
3. O MVP oferece “Biblioteca MultiTracks”, não pesquisa no catálogo global.
4. Reutilize MultiTracksContentProvider, MultiTracksPackageDownloader e MultiTracksPackageImporter; não duplique os contratos.
5. Senha somente em memória. Hash da sessão em armazenamento seguro. Nunca registre senha, hash, UUID, IDs pessoais, URL SAS ou respostas completas.
6. Abrir detalhes só pode consultar metadados. Nunca resgate Rental automaticamente. Exija confirmação explícita e não repita o resgate após timeout.
7. Importe e reconheça todas as faixas válidas do pacote, preservando ordem e Click/Guia. Não habilite seleção parcial nesta entrega.
8. Modele progresso real para autorização, download, validação, extração, conversão por faixa, carregamento e salvamento. Suporte cancelamento e rollback.
9. Integre a entrada em LibraryScreen e no diálogo “Adicionar música”. Ao concluir, salve na biblioteca local e devolva a Track ao fluxo de setlist quando houver.
10. Adicione origem MultiTracks retrocompatível à Track sem persistir credenciais. Não invente política de expiração ou remoção.
11. Comece com testes específicos e depois execute a suíte Flutter, análise e build Android. API real e conteúdo autorizado nunca entram em CI.
12. Diferencie no relatório final: validação estática, testes automatizados, build Android e validação real em aparelho/audível.

Implemente em entregas pequenas na ordem do plano. Ao encontrar contrato não capturado, pare apenas aquela função, marque-a como pendente e continue no restante seguro do MVP. Não invente endpoint, enum, direito ou unidade.
```
