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
| Login (`authenticate`) | **9 CodingKeys [O]**: `username`, `password`, `build`, `language`, `deviceName`, `pushToken`, `deviceID`, `application`, `platform`. **Correção 2026-10-14:** a chave do aparelho é `deviceID`, não `deviceIdentifier` — ver bloco de reflexão abaixo. `build` é inteiro; os demais valores codificados são texto. Como `pushToken` é `String?`, uma instalação sem token o omite e envia 8 chaves. |
| Cadastro (`register`) | `organization`, `firstname`, `lastname`, `email`, `username`, `password`, `language` |
| Sessão / chamadas autenticadas | `hash` (o `userHash` do usuário), `customer`, `language`, `siteID` (nas listagens: `pageNumber`, `pageSize`, `sort`, `sortDirection`) |
| Usuário (`APIUser`) | `userID`, `userHash`, `organizations[]`, `subscriptionExpirationDate`, `firstName`, `email`, `isAdmin` |
| Direitos da conta | `userAccess`, `cloud`, `rentals`, `restricted`, `teamShare`, `countryID`, `customer` |
| Rentals | `rentalID`, `expireDate`, `targetAppID`, `transferCount`, `contentID`, `status`, `rentalsPlan`/`items` |
| Conteúdo | `contentID`, `contentType`, `download`, `stemKeyID`, `redeem…`, `metadata`, `previewURL`, `songState`, `stems`, `genre` |

## Respostas de `authenticate` medidas em 2026-10-14 [M]

O host `https://api.multitracks.com/playback/` respondeu (HTTP 200, JSON, servidor ASP.NET atrás do Azure). **Erros vêm com HTTP 200**: o
resultado está no corpo (`result`, `errorCode`, `message`, `messageTitle`, `button`, `url`). Cinco formatos tentados receberam a mesma mensagem:
*"Username, password and device identifier are required fields."* A última chamada enviou somente as nove chaves do Playback, com usuário, senha e
`deviceIdentifier` não vazios, `Content-Length` explícito e corpo confirmado localmente. Isso descartou corpo vazio/chunked e indicou divergência nos
 tipos ou valores do perfil do cliente.

**Hipótese corrigida (2026-10-14):** a mensagem cita "device identifier", e a chave enviada era `deviceIdentifier`. No bloco contíguo de reflexão do login (`...customerID, userID, userHash, pushToken, application, platform, deviceID, deviceName, android, windows, ... build, language`) a chave do aparelho é **`deviceID`**; `deviceIdentifier` só aparece no despejo alfabético de símbolos (ao lado de `deviceUUID`, `deviceLimit`), nunca em uma função de encode. Como o campo do aparelho não liga, o servidor devolve a validação genérica que nomeia os três campos de credencial. A probe passou a enviar `deviceID`; próxima execução confirma ou refuta. Esquema (valores redigidos): `customerID`, `userID`, `userAccessID`, `appID`,
`firstName`, `lastName`, `hash` (null neste erro; é onde virá o hash da sessão), `appSubscriptionLevel`, `hasOldPro`, `appSubscriptionDateExpiration`,
`appSubscriptionExpiration`, `subscriptionReceipt`, `siteID`, `appSubscriptionType`, `internal`, `countryID`, `restricted`, `rentalsLicenseID`,
`teamSharingLicenseID`, `appLicenseID`, `latestVersion`, `organizations`, `cloudPro`, `planningCenter`, `playbackSnapshot`, `mtCompleteEnabled`,
`mtCompleteEngineer`, `result`, `errorCode`, `message`, `messageTitle`, `button`, `url`, `isAdmin`, `roleID`.

### Nomes de chave vistos no binário (strings de reflexão do Swift) [O]

Perto dos campos do login aparecem, em sequência: `username`, `password`, `pushToken`, `receipt`, `production` e, em outro grupo, `organization`, `resultID`, `errorCodeID`,
`responseMessageTitle`, `responseMessage`, `responseButtonTitle`, `responseButtonURL`, `customerID`, `userID`, `userHash`, `pushToken`, `application`, `platform`, `deviceID`, `deviceName`,
`android`, `windows`, `title`, `build`, `language`. Outras strings: `deviceUUID`, `deviceIdentifier`, `identifierForVendor`, `deviceLimit`, `threeDeviceLogins`,
`rentalsOtherDevices`, `rentalsThisDevice`, `playbackDeviceKeychainStorageFailed` (o Playback guarda a identidade do aparelho no Keychain). Há um
limite de aparelhos por conta (`deviceLimit`, "três logins de aparelho").

### Tipos e valores construídos pelo Playback 8.5.3 [O]

- O descritor Swift de `UserRequest` em `0x1009b42d0` declara `build: Int`, `language: String`, `username: String`, `password: String`,
  `application: String`, `platform: UserRequest.Platform`, `deviceID: String`, `deviceName: String` e `pushToken: String?`.
- O construtor em `0x1006d25ac` lê `CFBundleVersion` e converte-o para inteiro (`85308` neste artefato); escolhe o idioma entre
  `en`, `fr`, `id`, `ko`, `pt` e `es`; usa `uname.machine` em `application`; usa `identifierForVendor`/Keychain como identificador estável;
  e gera uma descrição legível do modelo/versão do sistema em `deviceName`.
- O enum `UserRequest.Platform` em `0x1009b43e0` tem os casos exatos `iOS`, `android`, `mac` e `windows`. O login de iPhone constrói o
  primeiro caso, portanto o JSON usa `platform: "iOS"`, com maiúsculas exatas.
- **Correção da probe:** o perfil padrão agora envia `build` como número, `application: "iPhone15,4"` como identificador de modelo de iPhone,
  `platform: "iOS"` e `deviceName: "iPhone 15"`. O modelo e o nome continuam substituíveis para reproduzir outro aparelho autorizado.
- O login usa `Alamofire.Session.default`. O Alamofire 5.11.0 embutido instala `Accept-Encoding`, `Accept-Language` e um `User-Agent` no formato
  `Playback/8.5.3 (com.multitracks.custommixplayer; build:85308; iOS <versão>) Alamofire/5.11.0`. A probe reproduz o `User-Agent` com iOS 18.4.0,
  envia `Accept-Language: en-US;q=1.0`, usa `Content-Type: application/json; charset=utf-8` (31 caracteres, confirmado no builder `FUN_1000596a4`: um único `setValue:forHTTPHeaderField:`, método `POST`) e não anuncia Brotli, que o cliente Dart não decodifica. **Correção 2026-10-14:** uma versão anterior da probe removeu o `; charset=utf-8`; o app o envia.
- **[M] Risco de deriva:** em 2026-10-14 a [App Store](https://apps.apple.com/us/app/playback/id751755884) publica Playback 8.6.2, enquanto o artefato disponível para análise é 8.5.3. Se o backend
  recusar o perfil corrigido, não se deve adivinhar o novo `CFBundleVersion` nem o contrato: é necessário obter o artefato 8.6.2 autorizado ou
  capturar uma requisição dessa versão em um aparelho de teste.

## Estado da investigação do login — 2026-10-14 (tarde) [M]

Sete tentativas. A probe foi alinhada ao 8.5.3 campo a campo: 9 chaves com nomes/tipos do encode (`deviceID`, `build` inteiro, `platform:"iOS"`), `POST`, `Content-Type: application/json; charset=utf-8` (31 chars, único header do builder `FUN_1000596a4`), User-Agent do Alamofire. **A resposta é byte a byte idêntica (766 bytes, `result:3`, mesma mensagem) em todas as tentativas, variando chaves, nome da chave do aparelho, cabeçalhos e Content-Length.** Como não varia com o corpo, o servidor recusa antes de ligar o JSON. Verificado também: o login usa `Session.default` (o `RequestInterceptor` fica na `APISession` de download, não no login), então não há header de app injetado no `authenticate`. **Conclusão:** a forma do request do 8.5.3 está esgotada; o que resta (gate de versão 8.5.3→8.6.2, ou um fator fora da análise estática) exige ou (a) capturar via proxy uma requisição real do Playback em um iPhone — verdade de campo, sem reversing — ou (b) o binário **decifrado** do 8.6.2 (o IPA da App Store vem cifrado; o ipatool sozinho não basta).

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
3. **Identidade do aparelho — decisão atualizada em 2026-10-14.** Após as tentativas com a identidade do WTracks retornarem a mesma validação,
   o desenvolvedor-chefe informou que o servidor ainda não está preparado para outras plataformas e autorizou testar o login com a identidade
   do Playback no iOS. O probe usa por padrão `application=iPhone15,4`, `platform=iOS`, `build=85308` como inteiro e
   `deviceName=iPhone 15`; os valores continuam explícitos e substituíveis por flags. Isso é uma compatibilidade transitória autorizada para o
   endpoint atual, não uma afirmação de que o WTracks seja o aplicativo oficial.
