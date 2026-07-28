# WTracks Test App

App JUCE standalone (desktop + Android) para validar o `AudioEngine` em
hardware real, **sem** Flutter no meio. Interface propositalmente feia --
o objetivo é testar o motor, não a experiência visual.

## Como usar

1. Prepare uma pasta de teste com 2-4 arquivos `.wav` do mesmo comprimento
   e sample rate (ex: `guia.wav`, `click_referencia.wav`, `bateria.wav`).
   Dica: use uma música real da sua igreja, separada em stems.

2. Compile (veja seção de build abaixo) e rode o app.

3. Clique em **"Carregar música"** e selecione a pasta com os `.wav`.

4. Use os controles:
   - **Play / Pause / Stop** — transporte
   - **Barra de seek** — arraste e solte para pular de posição
   - **Slider de volume por canal + Mute** — testa isolamento de canais
   - **Click habilitado + BPM** — testa o click sintetizado

## O que observar (checklist de validação)

- [ ] Os canais permanecem sincronizados entre si depois de 5-10 minutos tocando?
- [ ] Latência entre apertar Play e o som sair é perceptível?
- [ ] Seek é instantâneo ou introduz estalo/silêncio?
- [ ] Mute/volume respondem imediatamente, sem delay perceptível?
- [ ] O click mantém o tempo exato (compare com um metrônomo físico ou app confiável)?
- [ ] Trocar de música (carregar outra pasta) enquanto uma está tocando causa crash?
- [ ] Rodar por 20-30 minutos seguidos não causa degradação de memória
      (monitore com um profiler, especialmente no build Android)

## Build desktop (Windows/Linux/macOS)

```bash
cd native/test_app
cmake -B build -S .
cmake --build build --config Release
```

## Build Android

Use o toolchain de CMake do NDK, apontando para este mesmo `CMakeLists.txt`:

```bash
cmake -B build-android -S . \
  -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-24
cmake --build build-android --config Release
```

Nota: builds Android com JUCE geralmente são mais suaves via Projucer
gerando o projeto Gradle, ou via `melatonin_audio_sparkline`/templates
comunitários de JUCE+CMake+Android. Se o CMake puro para Android
apresentar dificuldades, vale a pena migrar esse passo específico para
Projucer só para o app de teste (o motor em si continua o mesmo código).

## Próximo passo depois de validar aqui
Se os itens do checklist passarem em pelo menos 2-3 aparelhos Android
físicos diferentes, o motor está pronto para ser conectado ao
`wtracks_bindings.dart` e testado através do Flutter.