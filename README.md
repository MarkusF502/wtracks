# WTracks

Player de multitracks para palco (click, guias, seções com laço, mixer com buses, automação, MIDI e timecode), uma
reconstrução local do Playback (MultiTracks) em Flutter e um motor de áudio C++/JUCE.

## Baixar o app (Android)

**[⬇️ WTracks-arm64.apk (build mais recente)](https://github.com/MarkusF502/wtracks/releases/latest/download/WTracks-arm64.apk)**
— serve para quase todos os celulares e tablets Android atuais.

Outras arquiteturas e builds anteriores: [Releases](https://github.com/MarkusF502/wtracks/releases). `WTracks-armv7.apk`
é para aparelhos antigos de 32 bits, `WTracks-x86_64.apk` para emuladores e Chromebooks.

Como instalar:
1. Abra o link acima no celular e baixe o arquivo (~160 MB; a maior parte são os 541 áudios de guia).
2. Toque no arquivo baixado e permita "instalar apps desconhecidos" para o navegador ou gerenciador de arquivos.
3. Abra o **WTracks**.

Os APKs são gerados automaticamente pelo GitHub Actions (`.github/workflows/android-apk.yml`) a cada push no ramo de
desenvolvimento. Enquanto os secrets de assinatura (`docs/ASSINATURA-ANDROID.md`) não estiverem configurados, eles são
assinados com uma chave de debug que muda a cada build: para atualizar pode ser preciso desinstalar a versão anterior
(isso apaga a biblioteca local do app — **faça um backup antes**). Com a chave estável configurada, cada build atualiza a
anterior sem apagar nada.

## Estrutura

- `flutter_app/` — app Flutter (telas, estado, FFI).
- `native/` — motor de áudio C++/JUCE (`AudioEngine`, click, guias, mixer, MIDI, timecode) e testes nativos.
- `docs/` — análise do Playback (`docs/playback-analysis/`), plano de desenvolvimento (`docs/PLANO-DESENVOLVIMENTO.md`)
  e notas de continuação (`docs/CONTINUAR-NUVEM.md`).

## Compilar localmente

```
cd native && cmake -B build-linux && cmake --build build-linux -j4   # motor + testes nativos (Linux)
cd flutter_app && flutter test                                        # testes Flutter
flutter build apk --release --split-per-abi                           # APK (precisa do Android SDK + NDK 28.2)
```
