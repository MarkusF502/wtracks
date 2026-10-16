# Plano de integração MultiTracks a partir das capturas do Playback

Atualizado em 2026-10-15. Complementa a Fase 6.1 de [PLANO-DESENVOLVIMENTO.md](../PLANO-DESENVOLVIMENTO.md) e o [contrato observado](multitracks-api-contract.md).

## Objetivo e proveniência

Implementar no WTracks autenticação, biblioteca, metadados e download autorizado, com base no tráfego do Playback 8.6.2 capturado pelo responsável no próprio iPhone via mitmproxy. O responsável relata autorização escrita do desenvolvedor-chefe para a integração e para a identidade transitória Playback/iOS enquanto o backend não suporta WTracks/Android. Essa autorização relatada não constitui especificação técnica do servidor.

Legenda: **confirmado** = observado no tráfego ou executado com sucesso; **inferido** = interpretação ainda não isolada em teste; **pendente** = implementação ou validação futura. Este arquivo não contém senha, hash, identificador pessoal de aparelho, IDs de conta ou URLs assinadas reutilizáveis. Datas UTC das capturas de 2026-10-15 correspondem à noite de 2026-10-14 em São Paulo.

## Estado comprovado

- [x] Proxy recebeu e decifrou HTTPS do Safari e do Playback no iPhone.
- [x] Login do Playback 8.6.2 capturado e contrato corrigido.
- [x] Login da probe Dart executado pelo responsável: HTTP 200, `result: 1`, `errorCode: 0`, `hash` não vazio.
- [x] Capturadas consultas a `library/songs`, `artists`, `albums`, `themes` e `genres`; todas retornaram sucesso com listas vazias.
- [x] Capturadas cinco chamadas a `content/download` para uma música semanal e um GET bem-sucedido do pacote `.mtrack`.
- [x] Corrigir os corpos de exploração da probe para as consultas de biblioteca capturadas.
- [x] Validar ao vivo os cinco builders corrigidos com a conta autorizada. Depois de liberar uma vaga de aparelho, a probe recebeu HTTP 200,
  `result: 1` e `errorCode: 0` nas cinco rotas. `library/songs` retornou um item; artistas, álbuns, temas e gêneros retornaram listas vazias.
- [x] Reproduzir consulta de metadados e download no WTracks para a oferta semanal. A auditoria de 2026-10-16 confirmou a
  Track persistida e os 11 WAVs; não existe recibo HTTP independente nem confirmação de que `Content-MD5` veio na resposta.
- [x] Inspecionar o resultado do pacote e validar importação, conversão, carregamento e reprodução audível no WTracks. O
  responsável confirmou stems, metrônomo e guia audíveis no aparelho após a otimização da tela de performance.

O GET original foi capturado no Playback. Em 2026-10-16, o backup e a execução no Android comprovaram também o resultado
do download/importação da oferta semanal pelo WTracks por evidência persistida e cadeia causal, sem recibo HTTP independente.
O teste semanal não valida compras permanentes nem todo o ciclo de Rentals.

## 1. Autenticação e identidade do cliente

**Confirmado:** `POST https://api.multitracks.com/playback/authenticate`, JSON, com oito campos: `username`, `password`, `build`, `language`, `deviceName`, `deviceIdentifier`, `application` e `platform`.

| Campo | Tipo / perfil capturado |
|---|---|
| `build` | inteiro `86204` |
| `platform` | inteiro `1` |
| `application` | texto `iPhone12,1` |
| `deviceName` | texto `iPhone 11 (26.2)` |
| `language` | texto `pt` |
| `deviceIdentifier` | UUID em texto; usar identidade própria estável do WTracks |
| `username`, `password` | texto, informado localmente |

Não houve `pushToken`. Sua obrigatoriedade ou aceitação em outros cenários não foi verificada. Os nomes internos Swift `deviceID` e `iOS` não demonstravam a serialização JSON; as hipóteses anteriores de `deviceID` e `platform: "iOS"` foram retiradas. A causa individual de cada tentativa antiga não foi isolada; não há prova de bloqueio do Playback 8.5.3 por versão.

Cabeçalhos capturados: `Accept: */*`, `Content-Type: application/json; charset=utf-8`, `Accept-Language: pt-BR;q=1.0` e `User-Agent: Playback/8.6.2 (com.multitracks.custommixplayer; build:86204; iOS 26.2.0) Alamofire/5.11.2`. O iPhone anuncia Brotli/gzip/deflate e `priority: u=3, i`. A probe usa `Accept-Encoding: identity`, calcula Content-Length em bytes UTF-8 e não precisa reproduzir prioridade ou assinatura TLS: seu login já funcionou.

Critério de sucesso da probe: HTTP 200, `result: 1`, `errorCode: 0` e `hash` não vazio. Erros também podem retornar HTTP 200. `latestVersion: "8.5.3"` veio do servidor apesar do cliente 8.6.2; não usar esse campo para identificar a versão do cliente. A resposta traz organização, direitos e datas sentinela (anos 0001/1900), que exigem interpretação explícita.

**Limite de dispositivos confirmado em 2026-10-15:** HTTP 200, `result: 5`, `errorCode: 4`, com orientação para remover um dispositivo da conta.
O `hash` presente nessa resposta não torna a sessão válida. A probe para imediatamente e não consulta a biblioteca. Não regenerar o UUID da probe:
isso tentaria registrar outro aparelho. A documentação oficial informa limite de dois aparelhos Playback por usuário, ou três para o usuário com
assento Playback Premium; remover um aparelho encerra a sessão dele e libera a vaga.

**Implementação:** manter senha somente durante o login; guardar a sessão em armazenamento seguro; impedir respostas de sessões antigas de publicar dados após logout/troca de organização. Não copiar o UUID do iPhone. A probe já persiste UUID próprio no diretório pessoal e gera User-Agent a partir de versões/build configuráveis.

## 2. Biblioteca: cinco contratos de consulta

**Confirmado:** todas as rotas abaixo são POST sob `/playback/`, com JSON e cabeçalhos do perfil acima. Campos comuns observados: `hash` (texto), `customerID`, `userAccessID`, `countryID`, `build`, `pageNumber`, `pageSize` (inteiros), `restricted` (booleano), `language` e `search` (texto). A captura usou página 1 e busca vazia.

| Rota | Campos específicos / valores observados |
|---|---|
| `library/songs` | `filter`: 1, 4 ou 3; `sort: 3`; `sortDirection: 2`; `siteID` inteiro; pageSize 4 ou 20 |
| `library/artists` | `purchasedContent: true`; `sort: 2`; `sortDirection: 1`; `siteID` inteiro; pageSize 20 |
| `library/albums` | Mesmo conjunto observado em artistas |
| `library/themes` | `purchasedContent: true`; `sortDirection: 1`; sem `sort` e sem `siteID`; pageSize 20 |
| `library/genres` | Mesmo conjunto observado em temas |

Resposta vazia comum: `data: []`, `pageNumber: 0`, `totalPages: 0`, `totalRecords: 0`, `result: 1`, `errorCode: 0`, mensagem de sucesso e `messageTitle`, `button`, `url` nulos. Página 0 na resposta vazia não é falha.

**Item não vazio confirmado pela probe em 2026-10-15:** `library/songs` retornou `libraryID`, `songID`, `song`, `songStatus`, `artistID`,
`artist`, `albumID`, `album`, `image`, `image2x`, `previewUrl`, `dateContentPurchased`, `rentalsAvailable` e `cloudSong`. Na amostra,
`dateContentPurchased` era nulo. IDs, textos e URLs reais não foram incorporados às fixtures. Os enums e o significado de `songStatus` continuam pendentes.

**Implementação:** substituir o campo inferido `customer` por `customerID` nessas consultas; obter contexto da sessão/organização sem fixar IDs da conta; criar builders por rota em vez de um corpo universal. Não supor o significado dos números de filtro/ordenação antes de correlacionar a seleção no app. Não generalizar o corpo de `songs` para `rentals`, cuja requisição não foi confirmada.

**Aceite:** uma página de cada rota retornou sucesso pela probe, sem consumo de crédito; listas vazias encerram paginação; fixture sintética cobre
o primeiro modelo não vazio de música. Continuam pendentes sessão inválida, troca de organização e itens não vazios de artistas, álbuns, temas e gêneros.

## 3. Conteúdo: consulta, resgate e emissão de link

**Confirmado:** o endpoint central neste fluxo é `POST /playback/content/download`. Ele retorna JSON; não retorna diretamente o pacote de áudio. Campos externos observados: `hash`, `customerID`, `userAccessID`, `language`, `countryID`, `build`, `restricted`, `items[]`. Não foi enviado `siteID` nesses cinco pedidos.

Exemplo do item capturado (IDs de conteúdo são exemplos observados, não padrões fixos):

```json
{
  "contentID": 48052,
  "contentType": 26,
  "metadata": true,
  "redemptionID": 0,
  "keyID": 30,
  "midiBankID": 0,
  "demoSetlistSongID": 0,
  "redeemPreview": false,
  "downloadLink": true,
  "redeemRental": false
}
```

| Pedido | metadata | downloadLink | redeemRental | redemptionID |
|---|---|---|---|---|
| 1 | true | false | false | ausente |
| 2 | true | true | true | 0 |
| 3, 4 e 5 | true | true | false | 0 |

**Inferência:** consulta inicial, resgate e posteriores solicitações de link. As chamadas posteriores têm o mesmo conjunto de valores; isso não comprova idempotência. O significado geral de `contentType: 26`, `contentStatus`, `songStatus` e demais enums continua pendente.

**Implementação:** separar operações `consultarMetadados`, `resgatar` e `solicitarLink`. Consulta inicial deve reproduzir `downloadLink: false`, `redeemRental: false` e `redeemPreview: false`; nenhum modo de exploração pode ativar resgate automaticamente. Confirmar com o serviço efeitos colaterais, consumo e mecanismo de reconciliação/idempotência. Não inventar cabeçalho de idempotência nem repetir resgate após timeout sem consultar o estado.

**Estado da implementação (2026-10-15):** `MultiTracksContentRequestBuilder` e `MultiTracksContentProvider` mantêm as três operações separadas.
O provider descarta respostas quando a sessão é trocada ou apagada durante a chamada. A probe consulta metadados primeiro e só solicita link com
`--download-content`; `--redeem-rental` exige a confirmação literal `--confirm-redeem-rental CONSUMIR` e nunca é repetido automaticamente. Se um
resgate aceito não trouxer `downloadUrl`, a probe reproduz uma única consulta posterior de link com `redeemRental: false`.

**Validação ao vivo (2026-10-15):** a identidade própria da probe recebeu `result: 1` e `errorCode: 0` tanto na consulta de metadados quanto na
solicitação de link para o conteúdo capturado. As duas respostas trouxeram `downloadUrl: null`, `rentalsInfo: null` e `rentalPreviewInfo: null`;
portanto nenhum GET ao Blob foi iniciado e nenhum arquivo foi criado. Isso confirma o contrato de consulta, mas não uma concessão para esse UUID.
O valor de `playOfTheWeek` foi redigido pelo relatório de esquema e não deve ser inferido desta execução.

`content/access` e `content/request` foram encontrados na análise estática, mas não observados como etapas deste download. Não implementá-los como pré-requisitos obrigatórios com base na hipótese antiga.

## 4. Resposta: metadados e direitos

**Confirmado:** envelope com `data`, `result`, `errorCode`, `message`, `messageTitle`, `button`, `url`; `data` contém `rentalsRemaining`, `rentalsPreviews`, `items[]`. No item final foram observados:

- Estado: `contentStatus`, `songStatus`, `message`, `products`.
- Identificação: `libraryID`, `contentID`, `version`, `title`, `artistID`, `artist`, `albumID`, `album`, `originalKey`, `bpm`, `duration`, `image`, `previewUrl`, `fileSize`, `multiTracksType`, `rehearsalMixOnly`, `padCategoryID`.
- Download: `downloadUrl`, `stemsVersion`, `waveFormUrl`.
- Estrutura: `keys`, `stems`, `tempos`, `timeSignatures`, `sections`, `clicks`, `keyChanges`.
- Recursos adicionais: `midiBanks`, `midiEvents`, `arrangements`, `availableProductionCues`.
- Direitos temporários: `rentalsInfo`, `rentalPreviewInfo`, `playOfTheWeek`, `freeContentDateExpiration`, `freeDateExpiration`.

O item continha 12 tonalidades, 120 entradas de stems, 16 seções, 11 entradas de andamento e 3 de compasso. As entradas de stems incluem variantes por tonalidade: não representam necessariamente 120 arquivos no pacote. Campos observados por stem: `contentType`, `stemID`, `partID`, `keyID`, `range`, `part`, `abbreviation`, `anyKey`, `clickOrGuide`, `vocal`, `order`. Tonalidades também trazem `stemKeyID` e estado de acesso.

**Implementação:** modelar conteúdo de catálogo, instância concedida/Rental, tonalidade, stem e arquivo local separadamente. O `contentID` de catálogo era diferente do `rentalsInfo.contentID`, que correspondia ao nome do pacote. Não substituir um pelo outro. Preservar ordem e precisão dos metadados; não interpretar `time` como segundos por suposição: confrontar `time`, `beats`, `ticks` e `timeCode` com o áudio e o Playback. Não reduzir músicas com mudanças de andamento/compasso a um único BPM/compasso.

## 5. Oferta semanal e validade

**Confirmado:** resposta final com `playOfTheWeek: true`, `rentalsInfo` preenchido, `status: 2`, `transferCount: 0`, `transferAvailable: true`, e `rentalDateExpiration: 2026-10-22T03:40:00Z` (22/10/2026 às 00h40 em São Paulo). `freeContentDateExpiration` e `freeDateExpiration` estavam nulos.

**Implementação:** não tratar a oferta como compra permanente; interpretar também `rentalsInfo`. Usar datas com timezone quando disponíveis. Expiração do direito de reprodução e expiração da URL SAS são conceitos distintos. A emissão/renovação do link não renova por si só a licença. Confirmar janela offline, revogação, transferência e política de remoção com a MultiTracks.

**Aceite:** fixtures sintéticas cobrem oferta válida/expirada, datas nulas/sentinela e atualização de estado; testes de relógio/offline não prolongam direitos localmente. Validar compras permanentes e Rentals pagas separadamente deste caso semanal.

## 6. Transferência do pacote

**Confirmado:** GET HTTPS separado em `playback.blob.core.windows.net`, com caminho `/cloud/<contexto>/streaming/<conteudo>.mtrack` e query SAS com `sv`, `spr`, `se`, `sip`, `sr`, `sp`, `rscd`, `sig`. Não houve hash de sessão, Cookie ou Authorization no GET observado; a URL transporta a autorização.

User-Agent do GET: `Playback/86204 CFNetwork/3860.300.31 Darwin/25.2.0`, diferente do cliente Alamofire da API. A resposta foi HTTP/1.1 200, `application/octet-stream`, Content-Length 41324454 bytes (aproximadamente 39,4 MiB), Content-Disposition de `.mtrack`, Content-MD5, ETag e `Accept-Ranges: bytes`. A transferência levou aproximadamente 15 segundos na captura.

**Implementação:** download em staging privado, progresso e cancelamento, validação de tamanho e MD5 fornecido (integridade da transferência, não autenticação criptográfica do conteúdo), publicação atômica. Não encaminhar o hash da API para o Azure. Manter URL SAS opaca em memória, sem alterar a query ou registrá-la; considerar expiração e restrição de IP ao retomar/trocar de rede. Permitir somente HTTPS e hosts de download explicitamente confiáveis, inclusive após redirecionamentos.

**Estado da implementação (2026-10-15):** `MultiTracksPackageDownloader` aplica HTTPS e allowlist de host também após redirecionamentos,
limite de 2 GiB, staging `.part`, tamanho anunciado, Content-MD5 incremental, cancelamento e publicação com rollback. A probe possui um caminho
equivalente para obter a primeira amostra no Linux sem imprimir ou gravar a URL SAS; a integração de UI/progresso no Android permanece pendente.

**Pendente:** testar Range/206 e If-Range/ETag: `Accept-Ranges` anuncia suporte, mas retomada não foi exercitada. Após URL expirada, reconciliar estado e obter novo link sem resgatar novamente. Confirmar unidade de `fileSize`; não usá-la como bytes sem validação.

## 7. Pacote e importação

**Confirmado na amostra autorizada (2026-10-15):** `48052.mtrack` tem 41.324.454 bytes e SHA-256
`16dae28c5d99e4f999994efda8c9c811b6f8b5f145f3c4c5fa687dfc3a1a71dc`. É um frame LZ4 independente com dez blocos armazenados sem
recompressão, checksum de conteúdo e um ZIP interno de 41.324.399 bytes. O ZIP passou na validação de todos os CRCs e contém 19 membros:
11 arquivos numéricos `.m4a`, duas capas JPEG e seis waveforms PNG. Não existe manifesto dentro do pacote; a resposta JSON da API é o
manifesto necessário para nomear e ordenar os stems. Os nomes numéricos dos M4A correspondem aos `stemID` presentes na resposta.

Os 11 stems observados são AAC em contêiner M4A, estéreo, 44,1 kHz e duração idêntica de aproximadamente 267,225 segundos. Não foi observada
criptografia interna no ZIP ou nos M4A. Isso é evidência desta amostra, não garantia para todos os `contentType` ou versões futuras.

**Implementação (2026-10-15):** `MultiTracksPackageImporter` valida magic/opções/checksums LZ4, suporta blocos crus e comprimidos, impõe limites,
abre o ZIP sem confiar em caminhos, rejeita membros inesperados/duplicados, verifica tamanho e CRC de cada stem e exige correspondência única com
o `stemID` e a tonalidade selecionada. A ordem e os nomes vêm dos descritores da API; click/guia preserva `clickOrGuide`. A publicação dos WAVs é
atômica e preserva a versão anterior em caso de falha.

O JUCE atual não decodifica AAC/M4A no Android. A ponte `wtracks/multitracks_audio` usa `MediaExtractor`/`MediaCodec` fora da thread da interface
para produzir PCM WAV de 16 bits antes de entregar os arquivos ao motor. A auditoria Android de 2026-10-16 confirmou 11 WAVs PCM, estéreo,
44,1 kHz e aproximadamente 267,225 s, com hashes e caminhos coerentes, além do carregamento e avanço do transporte. O responsável confirmou
reprodução audível dos stems, metrônomo e guia. Essa conversão aumenta significativamente o uso de disco e deve ser apresentada no progresso/estimativa da UI.

**Backup (2026-10-16):** o backup do WTracks (formato 2) não leva mais o áudio das músicas com `origin` MultiTracks: entra só o JSON
(referência e metadados, sem segredo) e o manifesto conta essas músicas em `counts.tracksWithoutAudio`. Na restauração elas voltam à
biblioteca sem áudio; abrir uma delas explica o motivo e leva à Biblioteca MultiTracks, e o novo download (mesmo id
`multitracks-<contentId>-<keyId>`) substitui a entrada mantendo o mixer. Escolha própria: vale para todo direito de uso, inclusive compras,
enquanto o tipo de direito não é confirmado pela API. Teste: `backup_test.dart`.

**Estrutura musical (2026-10-16, confirmado):** valores obtidos com a probe (`--structure-out`, só leitura de metadados, arquivo local fora
do Git) para o conteúdo 48052 e conferidos contra o áudio do pacote:

| Campo | Significado | Evidência |
|---|---|---|
| `timeCode` | texto `MM:SS:mmm` (minutos, segundos, milissegundos); em compassos vem com um espaço no fim | seção `00:07:058` = 8 tempos a 68 BPM |
| `time` (andamentos e compassos) | posição em **tempos**, arredondada | `time: 282` ↔ `04:08:823` = 282 × 60/68 s |
| `beats` | a mesma posição sem arredondar | 285,75 e 286,0 aparecem os dois como `time: 286` |
| `tempos` | mapa por degraus; cada ponto vem em par (fecha o trecho anterior, abre o novo); mudanças podem cair no meio de um tempo | segundos recalculados pelos tempos batem com todos os `timeCode` em ±1 ms |
| `timeSignatures` | `beatsPerBar`/`beatUnit`; `timeID` é o id do catálogo de compassos do Playback (3 = 4/4) | 2/4 em 272 tempos = 240 s |
| `sections` | só o início; o fim é o início da seguinte e a última vai até `duration`; nome pelo `sectionID` no catálogo `sections-*.json` do Playback | 16 seções, de Contagem (7) a Final (8) |
| `clicks.accents/quarters/eighths/sixteenths` | instantes em segundos do arquivo de áudio; o último é sentinela (duração + 1 s); quartos incluem os tempos fortes, colcheias e semicolcheias só as do contratempo | 581 ataques do stem de click a −1,5…+3,6 ms das listas (detector) |

O atraso de codificação do AAC é descartado tanto pelo GStreamer quanto pelo `MediaCodec` do Android (os WAVs do aparelho têm 11.784.619
quadros, o mesmo número do GStreamer), então essa linha do tempo vale para os WAVs do WTracks.

**Implementação:** `MultiTracksStructure` converte seções (guia falado do WTracks desligado quando o pacote traz stem de guia, para não
tocar dois guias), BPM e compasso iniciais, `TempoChange` por ponto de mudança e `FixedClicks`. O motor ganhou `setClickTimes`: o click das
músicas MultiTracks toca pelos instantes da MultiTracks (como o Playback faz com `SongClicks`), o que mantém exato o ritardando com
mudanças no meio do tempo; a grade (`TempoChange`) continua para relógio MIDI e crossfade ao vivo, e reinicia nesses pontos (escolha
própria). Editar andamento, compasso ou deslocamento do click descarta os instantes fixos. O que não confere com o `timeCode` é descartado
com aviso no Diagnóstico. Um novo download dá a estrutura a uma música importada antes dela; seções já existentes são do usuário e ficam.

**Pendente:** `midiEvents`, `midiBanks`, `arrangements` e `keyChanges` vieram vazios/falsos na amostra, então não foram convertidos; compasso
com unidade 8 não foi observado (a unidade do BPM fica sem confirmação e gera aviso); validar progresso, falta de espaço, cancelamento e
falhas reais na UI.

**Aceite:** mapear cada arquivo ao stem/tonalidade correto; conferir duração, sample rate, canais, click/guia e alinhamento; converter seções/andamentos/compassos sem perder precisão. Falha mantém o conteúdo fora da biblioteca utilizável. O motor de áudio só recebe arquivos locais validados; nenhuma rede no callback.

## 8. Outras chamadas e limites da captura

- `POST settings` e `POST settings/busRouting` ocorreram após login; contratos ainda não documentados. Não importar configurações oficiais para o WTracks sem uma necessidade funcional definida.
- `HEAD alive.json` verifica conectividade e teve fallback observado entre CDN e Blob; sucesso não comprova sessão válida.
- `POST search/mtcomplete` observado com `hash`, `customerID`, `search`, `countryID`, `siteID`, `language`, `build`, `pageNumber`, `pageSize`, `restricted`, `order`; na amostra página 2, tamanho 20, ordem 1. Resposta paginada com `searchID`, `data[]`, resultado/erro; itens com `mtCompleteID`, título, artista, álbum e imagens. Não equivale à biblioteca adquirida nem comprova a origem da oferta semanal.
- Capas são GETs separados. Telemetria Sentry, WhatsApp e serviços Apple presentes no proxy não integram o contrato WTracks.

## Sequência de entregas

1. **Contrato e fixtures:** consolidar os esquemas acima, sem credenciais, e marcar enums/unidades desconhecidos. Preservar a distinção entre observação e inferência.
2. **Probe de biblioteca:** corrigir builders por rota e contexto da organização; validar as cinco listagens vazias e depois uma não vazia. Manter `organization`/`library/rentals` experimentais até captura própria.
3. **Probe de metadados:** item explícito e consulta sem resgate/link; imprimir apenas esquema/resultado. Validar contra o Playback sem IDs de conta fixos.
4. **Provider e sessão:** `MultiTracksContentProvider`, armazenamento seguro, cancelamento por geração de sessão e erros de negócio no JSON.
5. **Resgate e download:** interação explícita para concessão, reconciliação de timeout, emissão de link e download privado validado. Não automatizar compras, resgates ou consumo em testes.
6. **Pacote e importação:** inspeção autorizada, manifesto, mapeamento de stems e metadados, staging e publicação atômica.
7. **Licença e ciclo de vida:** expiração, revalidação, offline, logout, transferência e revogação; conteúdo protegido fora de exportação/backup conforme escopo acordado.
8. **Validação Android:** falta de espaço, background, cancelamento, queda de rede, URL expirada/restrita por IP, retomada, troca de conta e falha de pacote. Validar compra permanente e Rental paga com conteúdo/conta de teste aprovados.

Concluído até aqui: login, biblioteca, metadados, resgate, download e importação reais da oferta semanal. A auditoria de 2026-10-16 confirmou no
Android 11 WAVs válidos e alinhados, persistência 11/11, carregamento no motor e avanço do transporte; o responsável confirmou reprodução audível
dos stems, metrônomo e guia. Permanecem pendentes recibo HTTP independente, compra permanente, Rental paga, ciclo de licença e cenários de falha.
