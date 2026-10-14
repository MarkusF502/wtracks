# Contrato observado da API do Playback (rascunho 1, 2026-10-14)

Documento da Fase 6.1.1. **Nada aqui foi informado pela MultiTracks**; tudo foi *observado* no executável do Playback 8.5.3 (strings e
pseudocódigo já extraídos em `docs/playback-analysis/`, mais a lista de URLs em `~/Playback/analysis/playback-urls.txt`). Sem segredos:
o binário embute uma URL assinada de exemplo (expirada) e ela **não** é reproduzida aqui. Legenda: **[O]** observado no binário,
**[I]** inferência a confirmar, **[?]** desconhecido, **[D]** decisão do WTracks.

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
| Login (`authenticate`) | `username`, `password`, `language`, `deviceName`, `pushToken`, `application`, `platform` |
| Cadastro (`register`) | `organization`, `firstname`, `lastname`, `email`, `username`, `password`, `language` |
| Sessão / chamadas autenticadas | `hash` (o `userHash` do usuário), `customer`, `language`, `siteID` (nas listagens: `pageNumber`, `pageSize`, `sort`, `sortDirection`) |
| Usuário (`APIUser`) | `userID`, `userHash`, `organizations[]`, `subscriptionExpirationDate`, `firstName`, `email`, `isAdmin` |
| Direitos da conta | `userAccess`, `cloud`, `rentals`, `restricted`, `teamShare`, `countryID`, `customer` |
| Rentals | `rentalID`, `expireDate`, `targetAppID`, `transferCount`, `contentID`, `status`, `rentalsPlan`/`items` |
| Conteúdo | `contentID`, `contentType`, `download`, `stemKeyID`, `redeem…`, `metadata`, `previewURL`, `songState`, `stems`, `genre` |

## Resposta de `authenticate` medida em 2026-10-14 (primeira chamada real, tentativa sem identificador do aparelho) [M]

O host `https://api.multitracks.com/playback/` respondeu (HTTP 200, JSON, servidor ASP.NET atrás do Azure). **Erros vêm com HTTP 200**: o
resultado está no corpo (`result`, `errorCode`, `message`, `messageTitle`, `button`, `url`). Mensagem recebida: *"Username, password and device
identifier are required fields."* — ou seja, o login exige também um **identificador do aparelho** (o nome exato da chave não está no binário; a
ferramenta de teste envia `deviceIdentifier`, `deviceID` e `deviceId`). Esquema (valores redigidos): `customerID`, `userID`, `userAccessID`, `appID`,
`firstName`, `lastName`, `hash` (null neste erro; é onde virá o hash da sessão), `appSubscriptionLevel`, `hasOldPro`, `appSubscriptionDateExpiration`,
`appSubscriptionExpiration`, `subscriptionReceipt`, `siteID`, `appSubscriptionType`, `internal`, `countryID`, `restricted`, `rentalsLicenseID`,
`teamSharingLicenseID`, `appLicenseID`, `latestVersion`, `organizations`, `cloudPro`, `planningCenter`, `playbackSnapshot`, `mtCompleteEnabled`,
`mtCompleteEngineer`, `result`, `errorCode`, `message`, `messageTitle`, `button`, `url`, `isAdmin`, `roleID`.

### Nomes de chave vistos no binário (strings de reflexão do Swift) [O]

Perto dos campos do login aparecem, em sequência: `username`, `password`, `pushToken`, `receipt`, `production` e, em outro grupo, `organization`, `resultID`, `errorCodeID`,
`responseMessageTitle`, `responseMessage`, `responseButtonTitle`, `responseButtonURL`, `customerID`, `userID`, `userHash`, `pushToken`, `application`, `platform`, `deviceID`, `deviceName`,
`android`, `windows`, `title`, `build`, `language`. Outras strings: `deviceUUID`, `deviceIdentifier`, `identifierForVendor`, `deviceLimit`, `threeDeviceLogins`,
`rentalsOtherDevices`, `rentalsThisDevice`, `playbackDeviceKeychainStorageFailed` (o Playback guarda a identidade do aparelho no Keychain). **[I]** `platform` pode ser
validado contra uma lista (`ios`, `android`, `windows`…); há um limite de aparelhos por conta (`deviceLimit`, "três logins de aparelho").

## Fluxo provável [I]

1. `authenticate` com usuário/senha devolve o usuário (`userHash`, organizações, direitos). **A senha vai no corpo da requisição**; não há OAuth
   neste endpoint. O `userHash` passa a ser a credencial das demais chamadas.
2. `organization` seleciona a organização ativa; `library/*` lista o que a conta tem; `library/rentals` lista os Rentals.
3. `content/access` informa se o item está liberado para esta conta/aparelho; `content/request` devolve a URL assinada do arquivo
   (`https://playback.blob.core.windows.net/cloud/<id>/streaming/<id>.mtrack?...`, SAS com expiração e IP) **[O para o formato da URL]**.
4. Rentals: `rentals/extend` e `rentals/expire`; a transferência entre aparelhos usa `transferCount`/`rentalID`/`status`.
5. O arquivo baixado é um **`.mtrack`** **[O]**. O app embute `SSZipArchive`, então o `.mtrack` provavelmente é um zip (ou contém um) **[I]**;
   o conteúdo (stems, marca-d'água, chaves) é **[?]** e vem na próxima investigação.

## Decisões do responsável pelo projeto

1. **Senha — decidido (2026-10-14): opção B.** A MultiTracks não oferece OAuth para este projeto; o desenvolvedor-chefe orientou usar o login por
   usuário e senha do endpoint. A senha só existe em memória durante a chamada; guarda-se apenas o `userHash` no armazenamento seguro
   (detalhes na Fase 6.1.2 do plano).
2. **Primeiro teste de comunicação:** `tool/multitracks_probe.dart`, executado por você no terminal. Pede usuário e senha localmente, chama
   `authenticate` (e, se você pedir, `organization`, `library/rentals`, `library/songs`) e imprime só o **esquema** das respostas — chaves e tipos,
   com todos os valores redigidos. O arquivo de saída (`--out`) pode ser compartilhado para eu descrever as respostas neste contrato.
3. **Identidade do aparelho.** `deviceName`, `application` e `platform` identificam o cliente; o WTracks envia valores próprios e estáveis, nunca se
   passa por iPhone/Playback (Fase 6.1.4). **[?]** se o servidor valida `platform`/`application` contra uma lista.
