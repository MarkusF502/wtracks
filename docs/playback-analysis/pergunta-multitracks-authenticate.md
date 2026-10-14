# Perguntas ao desenvolvedor da MultiTracks sobre `authenticate` (sem dados pessoais)

Estamos testando, com a conta do responsável pelo WTracks e a autorização combinada, `POST https://api.multitracks.com/playback/authenticate`.
A resposta é sempre HTTP 200 com o mesmo erro:

> `message`: "Username, password and device identifier are required fields."   (`customerID`, `userID` etc. vêm preenchidos como padrão; `hash` e `organizations` vêm `null`)

O corpo enviado (JSON, `Content-Type: application/json; charset=utf-8`, com `Content-Length`) tem as 9 chaves que o Playback 8.5.3 usa
(extraídas do encode da requisição), todas texto:

| chave | valor enviado |
|---|---|
| `username` | e-mail da conta (25 caracteres) |
| `password` | a senha (13 caracteres) |
| `build` | `"1"` |
| `language` | `"en"` |
| `deviceName` | `"WTracks (teste)"` |
| `pushToken` | `""` (vazio) |
| `deviceIdentifier` | UUID v4 em maiúsculas (36 caracteres), fixo para este computador |
| `application` | `"WTracks"` |
| `platform` | `"linux"` |

Perguntas:
1. Está certo o nome `deviceIdentifier` e o formato do valor (UUID, outro formato)? O identificador precisa estar registrado antes do login?
2. `application`, `platform` e `build` são validados contra uma lista? Quais valores o WTracks deve usar (Android e Linux/desktop)? Precisamos de um `appID`/`application` próprio?
3. `pushToken` pode ir vazio?
4. O `username` aceita e-mail, ou é o nome de usuário da conta?
5. Há limite de aparelhos por conta (`deviceLimit`/"três logins")? Como remover os aparelhos de teste?
6. Existe algum cabeçalho obrigatório além de `Content-Type` (o Playback só define esse)?
7. Se possível: o formato das respostas de `organization`, `library/rentals`, `library/songs`, `content/access` e `content/request`.
