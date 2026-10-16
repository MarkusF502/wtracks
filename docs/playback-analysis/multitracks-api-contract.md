# Contrato observado da API do Playback (revisão 2, 2026-10-15)

Documento da Fase 6.1.1. Combina análise estática do Playback 8.5.3 com captura autorizada do Playback 8.6.2 em iPhone via mitmproxy. A captura real prevalece sobre inferências do binário. Nenhuma credencial, identidade pessoal, UUID do aparelho ou URL assinada é reproduzida aqui.

Legenda: **[O]** observado no binário 8.5.3; **[M]** medido em chamadas/captura; **[I]** inferência; **[?]** desconhecido; **[D]** decisão do WTracks. A data do servidor da captura é 2026-10-15 UTC (2026-10-14 em America/Sao_Paulo).

## Login confirmado por captura do Playback 8.6.2 [M]

`POST https://api.multitracks.com/playback/authenticate`, observado em HTTP/2 e TLS 1.3. Corpo JSON com oito campos:

```json
{
  "build": 86204,
  "deviceName": "iPhone 11 (26.2)",
  "username": "<usuario>",
  "deviceIdentifier": "<UUID-estavel-proprio>",
  "language": "pt",
  "password": "<senha>",
  "platform": 1,
  "application": "iPhone12,1"
}
```

`build` e `platform` são números inteiros; os demais campos são texto. `pushToken` não foi enviado; sua aceitação e obrigatoriedade em outros contextos não foram verificadas. A captura não determina os valores numéricos das demais plataformas.

Cabeçalhos observados:

```text
accept: */*
content-type: application/json; charset=utf-8
accept-encoding: br;q=1.0, gzip;q=0.9, deflate;q=0.8
user-agent: Playback/8.6.2 (com.multitracks.custommixplayer; build:86204; iOS 26.2.0) Alamofire/5.11.2
priority: u=3, i
accept-language: pt-BR;q=1.0
```

`Content-Length` é calculado a partir dos bytes UTF-8 do corpo, nunca fixado no tamanho da captura. A probe solicita `Accept-Encoding: identity`, pois Dart não decodifica Brotli automaticamente, e não reproduz `priority`. Seu transporte usa `HttpClient` do Dart; não reproduz a assinatura TLS nem garante HTTP/2. A equivalência funcional do login foi confirmada pela execução da probe pelo responsável; as operações posteriores ainda precisam de validação.

### Resultado confirmado [M]

HTTP 200, JSON, `result: 1`, `errorCode: 0` e `hash` não vazio. `hash` é a credencial retornada efetivamente pelo login; `userHash` permanece um nome observado no modelo interno. HTTP 200 sozinho não comprova sucesso.

A resposta contém `customerID`, `userID`, `userAccessID`, `appID`, `firstName`, `lastName`, `hash`, `appSubscriptionLevel`, `hasOldPro`, `appSubscriptionDateExpiration`, `appSubscriptionExpiration`, `subscriptionReceipt`, `siteID`, `appSubscriptionType`, `internal`, `countryID`, `restricted`, `rentalsLicenseID`, `teamSharingLicenseID`, `appLicenseID`, `latestVersion`, `organizations`, `cloudPro`, `planningCenter`, `playbackSnapshot`, `mtCompleteEnabled`, `mtCompleteEngineer`, `result`, `errorCode`, `message`, `messageTitle`, `button`, `url`, `isAdmin` e `roleID`.

Em 2026-10-15 também foi confirmado o erro de limite de aparelhos: HTTP 200, `result: 5`, `errorCode: 4`, com mensagem para remover um dispositivo
Playback da conta. Embora a resposta ainda contenha `hash`, ela não representa login aceito; o cliente deve validar os códigos de negócio antes de
usar qualquer campo de sessão. A probe não repetiu a chamada nem acessou a biblioteca.

`organizations[]` contém identidade da organização, `default`, avatar, indicadores de direitos, contadores e datas de Rentals/Cloud/Team Sharing/licenças. `cloudPro` contém `tierID` e indicadores de recursos. Datas sentinela como anos 0001 e 1900 aparecem na resposta; não devem ser tratadas automaticamente como assinaturas válidas. Direitos de conteúdo continuam dependentes da validação do servidor.

O servidor retornou `latestVersion: "8.5.3"` mesmo com o cliente 8.6.2. Esse campo não identifica a versão do cliente e não comprova bloqueio de versões antigas. Depois do login foram observados `POST settings` e `POST settings/busRouting`; seus corpos ainda não foram documentados.

## Host e transporte

- **[O]** URL base por modelo: `https://api.%@.com/playback/` (o `%@` é o site da conta; o app lista os sites `multitracks.com`,
  `.com.br`, `.co.kr`, `.id`, `.ph`, `multitracksafrica.com`, `multitracksfr.com` e `secuencias.com`). **[?]** qual valor entra no `%@` para cada site.
- **[O]** Sessão `Alamofire`, JSON nos dois sentidos: `JSONEncoder` no corpo e `JSONDecoder` (estratégia de data própria) na resposta.
- **[O]** Todas as rotas abaixo são `POST` com `Content-Type` JSON; timeout de 120 s nas chamadas de login. Downloads usam uma
  `URLSession` em segundo plano (`APISession`, delegate de download com progresso).
- **[O]** Conferência de conectividade em `https://multitracks.blob.core.windows.net/public/alive.json` (e `mtracks.azureedge.net`).
- **[D]** HTTPS com validação normal do certificado; sem pinning (o plano só aceita se a MultiTracks fornecer).

## Rotas (relativas à base) — lista mínima [O]

Autenticação e conta: `authenticate`, `register`, `logout`, `forgot`, `organization`, `settings`, `push`.
Biblioteca: `library/songs`, `library/albums`, `library/artists`, `library/genres`, `library/pads`, `library/themes`, `library/rentals`,
`library/search`.
**Conteúdo e direitos:** `content/access`, `content/request`, `rentals/extend`, `rentals/expire`.
Setlists e MIDI (fora da primeira entrega): `setlists`, `setlists/create|delete|demo|people|save|update`, `midi/createBank|updateBank`.
Outras (não usadas pelo WTracks): `playbackremote`, `playbacksync`, `triggerevent`, `sos`.
A lista é um **piso**: nomes com mais de 15 caracteres podem não ter sido decodificados.

## Campos observados [O] (nomes das chaves JSON; o mapeamento rota → campos é [I])

| Contexto | Chaves |
|---|---|
| Login (`authenticate`) | **[M]** `username`, `password`, `build` (inteiro), `language`, `deviceName`, `deviceIdentifier`, `application`, `platform` (inteiro `1` no iOS). Oito campos na captura 8.6.2, sem `pushToken`. |
| Cadastro (`register`) | `organization`, `firstname`, `lastname`, `email`, `username`, `password`, `language` |
| Sessão / chamadas autenticadas | **[M]** Nas listagens capturadas: `hash`, `customerID`, `userAccessID`, `countryID`, `restricted`, `build`, `language`, paginação e campos específicos por rota. `siteID` aparece em músicas/artistas/álbuns, mas não em temas/gêneros. `customer` era inferência antiga; ver plano detalhado. |
| Usuário (`APIUser`) | `userID`, `userHash`, `organizations[]`, `subscriptionExpirationDate`, `firstName`, `email`, `isAdmin` |
| Direitos da conta | `userAccess`, `cloud`, `rentals`, `restricted`, `teamShare`, `countryID`, `customer` |
| Rentals | `rentalID`, `expireDate`, `targetAppID`, `transferCount`, `contentID`, `status`, `rentalsPlan`/`items` |
| Conteúdo | `contentID`, `contentType`, `download`, `stemKeyID`, `redeem…`, `metadata`, `previewURL`, `songState`, `stems`, `genre` |

### Biblioteca validada pela probe [M]

Em 2026-10-15, os cinco builders capturados foram executados fora do iPhone e retornaram HTTP 200, `result: 1` e `errorCode: 0`.
`library/songs` retornou um item com 14 campos: `libraryID`, `songID`, `song`, `songStatus`, `artistID`, `artist`, `albumID`, `album`, `image`,
`image2x`, `previewUrl`, `dateContentPurchased`, `rentalsAvailable` e `cloudSong`. As outras quatro rotas retornaram listas vazias. Essa execução
confirma os corpos das requisições e o envelope de resposta; não define ainda o significado dos enums nem os schemas não vazios das outras categorias.

## Histórico de hipóteses corrigidas

As tentativas da probe em 2026-10-14 receberam HTTP 200 com `result: 3`, `hash: null` e a mensagem "Username, password and device identifier are required fields." Houve variações de campos e cabeçalhos, sem sucesso.

A análise estática encontrou os nomes internos `deviceID` e os casos do enum `iOS`, `android`, `mac`, `windows`. Isso **não comprovava** as chaves ou os valores serializados. As afirmações anteriores de que a API exigia `deviceID` e `platform: "iOS"` estão retiradas: a captura confirma `deviceIdentifier` e `platform: 1` no Playback 8.6.2.

Respostas iguais não demonstram rejeição antes da leitura do JSON. O bloqueio por versão era uma hipótese, não uma conclusão medida. Ainda não foi isolada a causa de cada tentativa antiga nem capturado o contrato real do 8.5.3. A execução posterior da probe confirmou o login fora do iPhone, sem isolar a causa de cada tentativa anterior.

## Capturas posteriores e plano de implementação

O login da probe Dart foi executado com sucesso pelo responsável (HTTP 200, `result: 1`, `errorCode: 0`, `hash` preenchido), confirmando o perfil corrigido fora do iPhone. A captura posterior confirmou as cinco categorias de biblioteca vazia e o fluxo de oferta semanal em `content/download` + GET de `.mtrack` no Azure.

O [plano detalhado das capturas](plano-integracao-multitracks-capturas.md) consolida os corpos por rota, variantes de consulta/resgate/link, esquema de metadados, validade da oferta semanal, cabeçalhos do pacote, pendências e critérios de aceite. Ele prevalece sobre o fluxo inferido abaixo nos pontos já medidos. Login, biblioteca, metadados, resgate, emissão de link e transferência da probe foram validados contra a API.

## Fluxo anteriormente inferido [I] — parcialmente substituído pelas capturas

1. `authenticate` com usuário/senha devolve a sessão (`hash`, organizações, direitos). **A senha vai no corpo da requisição**; não há OAuth
   neste endpoint. O `hash` passa a ser a credencial das demais chamadas.
2. `organization` seleciona a organização ativa; `library/*` lista o que a conta tem; `library/rentals` lista os Rentals.
3. **Hipótese antiga, não confirmada neste fluxo:** `content/access` validaria acesso e `content/request` devolveria a URL. A captura 8.6.2 observou `content/download` retornando metadados/direitos e `downloadUrl`, seguido de GET do arquivo
   (`https://playback.blob.core.windows.net/cloud/<id>/streaming/<id>.mtrack?...`, SAS com expiração e IP) **[O para o formato da URL]**.
4. Rentals: `rentals/extend` e `rentals/expire`; a transferência entre aparelhos usa `transferCount`/`rentalID`/`status`.
5. O arquivo baixado é um **`.mtrack`** **[O]**. A amostra autorizada é um frame LZ4 independente, com checksum de conteúdo, contendo um ZIP válido **[O]**. O ZIP possui 11 stems AAC/M4A e oito imagens, sem manifesto próprio; os nomes numéricos dos M4A correspondem aos `stemID` devolvidos pela API **[O]**. Outras variantes de pacote ainda são **[?]**.

## Decisões do responsável pelo projeto

1. **Senha — decidido (2026-10-14): opção B.** A MultiTracks não oferece OAuth para este projeto; o desenvolvedor-chefe orientou usar o login por
   usuário e senha do endpoint. A senha só existe em memória durante a chamada; guarda-se apenas o `hash` no armazenamento seguro
   (detalhes na Fase 6.1.2 do plano).
2. **Primeiro teste de comunicação:** `tool/multitracks_probe.dart`, executado por você no terminal. Pede usuário e senha localmente, chama
   `authenticate` (e, se você pedir, `organization`, `library/rentals`, `library/songs`) e imprime só o **esquema** das respostas — chaves e tipos,
   com todos os valores redigidos. O arquivo de saída (`--out`) pode ser compartilhado para eu descrever as respostas neste contrato.
3. **Identidade do aparelho — decisão atualizada em 2026-10-15.** Após as tentativas com a identidade do WTracks retornarem a mesma validação,
   o desenvolvedor-chefe informou que o servidor ainda não está preparado para outras plataformas e autorizou testar o login com a identidade
   do Playback no iOS. O probe usa por padrão `application=iPhone12,1`, `platform=1` e `build=86204` como inteiros e
   `deviceName=iPhone 11 (26.2)`; os valores continuam explícitos e substituíveis por flags. Isso é uma compatibilidade transitória autorizada para o
   endpoint atual, não uma afirmação de que o WTracks seja o aplicativo oficial.

## Execução da probe corrigida

```powershell
dart tool/multitracks_probe.dart --site multitracks --out "$env:TEMP/multitracks-schema.txt"
```

O perfil padrão usa idioma `pt`, `Accept-Language: pt-BR;q=1.0`, Playback 8.6.2, build 86204, iOS 26.2.0 e Alamofire 5.11.2. Flags `--app-version`, `--build`, `--ios-version` e `--alamofire-version` compõem o User-Agent; `--platform` aceita inteiro. O UUID é próprio e persistido em `~/.config/wtracks-probe/device-id`, usando HOME ou USERPROFILE, e não é impresso nem copiado do iPhone.

A probe só prossegue se houver HTTP 200, `result: 1`, `errorCode: 0` e `hash` não vazio. Os builders das cinco listagens observadas foram implementados,
mas a primeira validação ao vivo parou no limite de dispositivos antes de chamá-los. `organization` e `library/rentals` permanecem fora da exploração
até captura própria. Não salvar capturas completas, senhas, hashes ou cookies no repositório. A captura bruta permanece local e privada.

## Registro da autorização

Esta seção documenta a autorização mencionada nas decisões acima. Enquanto não houver resposta por escrito do CTO, o status é
**pendente de confirmação**. Preencha os campos entre «» quando enviar a mensagem e quando receber a resposta; guarde o e-mail/print da
resposta junto a este repositório.

| Campo | Valor |
|---|---|
| Quem autoriza | «Benjamin Thomas Edwards, diretor de tecnologia da MultiTracks |
| Quem recebe | «Marcos Marinho», responsável pelo WTracks |
| Conversa verbal | «13/10/2026» · «canal: reunião via google meet» |
| Pedido de confirmação enviado | «14/10/2026» · «canal» Whatsapp  |
| Confirmação recebida | 14/10/2026 · «canal» Whatsapp · status: confirmado |
| Escopo autorizado | Autenticar o WTracks no endpoint `authenticate` usando o perfil de cliente iOS do Playback, como compatibilidade transitória, com a conta do próprio responsável |

### Mensagem de confirmação (rascunho para enviar ao CTO)

> **Assunto:** Confirmação por escrito — autorização para o WTracks autenticar pelo endpoint do Playback (perfil iOS)
>
> Prezado «Benjamin Thomas Edwards»,
>
> Conforme conversamos em 13 de outubro pelo google meet, gostaria de registrar por escrito o que combinamos, para termos a autorização documentada.
> Entendi o seguinte — peço que confirme se está correto:
>
> 1. A MultiTracks autoriza o WTracks (projeto sob minha responsabilidade) a autenticar na API do Playback
>    (`POST https://api.multitracks.com/playback/authenticate`) usando o **perfil de cliente iOS do Playback**, já que o servidor ainda não está
>    preparado para outras plataformas.
> 2. É uma **medida transitória de compatibilidade**, enquanto o suporte a outras plataformas está sendo planejado; **não** significa afirmar que
>    o WTracks seja o aplicativo oficial.
> 3. O acesso é feito com a **minha própria conta** MultiTracks e minhas credenciais.
>
> Se estiver tudo certo, pode me responder apenas confirmando? Assim fica o registro com data e canal. Se algo no escopo acima precisar de
> ajuste, me avise. Obrigado pela ajuda.
>
> Atenciosamente,
> Marcos Marinho — WTracks

> Observação de escopo: esta autorização cobre apenas o uso descrito acima. Ela não autoriza redistribuir o aplicativo Playback, suas chaves ou
> conteúdo, nem contornar proteções de conteúdo; a análise do binário é feita sobre cópia obtida de forma autorizada, apenas para interoperar com a conta do próprio responsável.
