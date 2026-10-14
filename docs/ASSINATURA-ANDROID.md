# Assinatura estável do APK (Fase 0.1.1 / WT-01)

Uma atualização do Android só preserva os dados do app se o novo APK for assinado com a **mesma chave** do instalado. Até hoje
as builds saem com a chave de *debug* do ambiente que compilou, que muda a cada execução do CI. Este documento é o passo a passo
para passar a uma chave persistente. **A chave privada nunca entra no repositório.**

## 1. Antes de trocar a chave: descobrir com que chave está o app instalado

```
adb shell pm path com.example.flutter_app            # caminho do base.apk instalado
adb pull <caminho>/base.apk instalado.apk
$ANDROID_HOME/build-tools/<versão>/apksigner verify --print-certs instalado.apk
```

Anote o `certificate SHA-256 digest`. Se não houver a chave privada correspondente (é o caso das builds de debug do CI), **o
Android não aceitará uma atualização assinada com a chave nova**: a primeira instalação com a chave estável exige desinstalar
a anterior, o que apaga a biblioteca. Por isso:

1. exporte a biblioteca (backup completo; Fase B do plano de consolidação) para fora do armazenamento privado do app;
2. confira o backup (abrir os arquivos e comparar os tamanhos/hashes);
3. só então desinstale e instale a versão com a chave estável, e restaure.

Não oriente ninguém a desinstalar antes do passo 2.

## 2. Gerar a chave (uma vez, na sua máquina)

```
keytool -genkeypair -v -keystore wtracks-release.jks -alias wtracks -keyalg RSA -keysize 4096 -validity 10000
```

Guarde `wtracks-release.jks` e as senhas num cofre de senhas **com uma cópia de segurança em outro lugar**: se a chave for
perdida, nenhuma atualização futura poderá ser instalada por cima das versões já distribuídas.

## 3. Configurar o CI (GitHub → Settings → Secrets and variables → Actions)

| Nome | Tipo | Valor |
|---|---|---|
| `WTRACKS_KEYSTORE_BASE64` | secret | `base64 -w0 wtracks-release.jks` |
| `WTRACKS_KEYSTORE_PASSWORD` | secret | senha do keystore |
| `WTRACKS_KEY_ALIAS` | secret | `wtracks` |
| `WTRACKS_KEY_PASSWORD` | secret | senha da chave |
| `WTRACKS_RELEASE_CERT_SHA256` | variable | `keytool -list -v -keystore wtracks-release.jks` → SHA256, sem os dois-pontos, em maiúsculas (o formato do `apksigner`) |

Com o secret `WTRACKS_KEYSTORE_BASE64` presente o workflow assina com a chave estável, exige que ela exista
(`WTRACKS_REQUIRE_RELEASE_SIGNING`) e, se a variável do certificado estiver definida, **reprova a build** quando o certificado
do APK não for o esperado. Sem o secret ele avisa e usa a chave de debug.

## 4. Build local assinada

Crie `flutter_app/android/key.properties` (ignorado pelo git):

```
storeFile=/caminho/para/wtracks-release.jks
storePassword=...
keyAlias=wtracks
keyPassword=...
```

## 5. Versionamento

O CI passa `--build-number=${{ github.run_number }}`, então o `versionCode` cresce a cada build. O `applicationId`
(`com.example.flutter_app`) **não deve mudar** sem um plano de migração separado: um id novo é outro app para o Android.
