# Perguntas ao desenvolvedor-chefe da MultiTracks sobre `authenticate`

Testando, com a conta do responsável pelo WTracks e a autorização combinada (login "como Playback iOS", conforme você orientou),
`POST https://api.multitracks.com/playback/authenticate`.

## O que já reproduzimos fielmente do Playback 8.5.3 (iOS)

Corpo JSON, `Content-Type: application/json`, `Content-Length` explícito, `User-Agent`
`Playback/8.5.3 (com.multitracks.custommixplayer; build:85308; iOS 18.4.0) Alamofire/5.11.0`, `Accept-Language: en-US;q=1.0`.
As 8 chaves do request (o `pushToken` opcional é omitido quando não há token), com nomes/tipos conferidos no encode do binário:

| chave | valor |
|---|---|
| `username` | e-mail da conta |
| `password` | a senha |
| `build` | `85308` (inteiro) |
| `language` | `"en"` |
| `deviceName` | `"iPhone 15"` |
| `deviceID` | UUID v4 em maiúsculas (36 caracteres), estável neste computador |
| `application` | `"iPhone15,4"` |
| `platform` | `"iOS"` |

## O achado que precisamos entender

A resposta é **sempre HTTP 200 e byte a byte idêntica (766 bytes)**, em todas as tentativas, variando o conjunto de chaves, o nome da
chave do aparelho (`deviceIdentifier` e `deviceID`), os cabeçalhos e o `Content-Length`:

> `result: 3`, `errorCode: 0`, `message: "Username, password and device identifier are required fields."`
> `hash` e `organizations` vêm `null`; os demais campos vêm nos valores-padrão.

Como a resposta **não muda conforme o corpo**, o servidor parece recusar a requisição **antes de ligar o JSON ao modelo** — ou seja, o
problema não está nos nomes/valores dos campos, que já conferem com o app.

## Perguntas

1. **O que falta na requisição, acima do corpo?** Há algum cabeçalho obrigatório além dos do Alamofire (uma chave/assinatura de aplicativo,
   um token de app, um header `Authorization` ou algo específico da MultiTracks) que o Playback 8.5.3 envia e que não está visível no
   `authenticate` em si?
2. **Deriva de versão:** o artefato que analisamos é o 8.5.3, mas a App Store já publica **8.6.2**. O backend passou a exigir um `build`
   mínimo, um novo contrato de `authenticate`, ou algo que mudou entre 8.5.3 e 8.6.2? Qual `build`/versão o servidor aceita hoje?
3. **Registro de aparelho:** o `deviceID` precisa estar previamente registrado na conta? Há limite por conta
   (`deviceLimit` / "três logins de aparelho") e como liberar/remover os aparelhos de teste?
4. Confirmação do formato do corpo: as 8/9 chaves acima e o tipo de cada uma (em especial `build` inteiro e `platform: "iOS"` como string) estão corretos?
5. Se possível, o formato das respostas de `organization`, `library/rentals`, `library/songs`, `content/access` e `content/request`,
   para seguirmos depois que o login passar.
