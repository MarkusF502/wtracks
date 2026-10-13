cmake_minimum_required(VERSION 3.22)
project(wtracks_engine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE é adicionado como subdiretório (git submodule) ou via find_package
# Ex: git submodule add https://github.com/juce-framework/JUCE.git native/JUCE
add_subdirectory(JUCE)

# Biblioteca compartilhada que sera consumida via Dart FFI
add_library(wtracks_engine SHARED
    src/AudioEngine.cpp
    src/WaveformExtractor.cpp
    src/TimePitchFile.cpp
    src/ffi_bridge.cpp
)

target_include_directories(wtracks_engine PRIVATE include)

target_link_libraries(wtracks_engine PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_core
    juce::juce_events
)

target_compile_definitions(wtracks_engine PRIVATE
    JUCE_STANDALONE_APPLICATION=0
    # O app nunca faz networking (juce::URL aqui so e usado para ler
    # content:// URIs no Android, que passa por API nativa, nao por HTTP).
    # Desligar isso evita que o juce_core exija libcurl -- dependencia que
    # nao existe pronta pra cross-compilar com o NDK do Android.
    JUCE_USE_CURL=0
)

# Necessario para exportar simbolos C corretamente em cada plataforma
set_target_properties(wtracks_engine PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

# ---------------------------------------------------------------------------
# Testes (desktop apenas -- valida a logica de mixagem sem precisar de um
# dispositivo de audio real nem do emulador Android). Liga o AudioEngine.cpp
# diretamente ao executavel de teste, entao nao depende de linkar contra a
# lib compartilhada (que tem simbolos ocultos por causa de CXX_VISIBILITY_PRESET).
# ---------------------------------------------------------------------------
option(WTRACKS_BUILD_TESTS "Build the wtracks_engine desktop unit tests" ON)

if(WTRACKS_BUILD_TESTS AND NOT ANDROID)
    add_executable(wtracks_engine_tests
        src/AudioEngine.cpp
        src/WaveformExtractor.cpp
        src/TimePitchFile.cpp
        tests/GuideTimelineTests.cpp
        tests/GuideEngineTests.cpp
        tests/MixerTests.cpp
        tests/TimePitchTests.cpp
        tests/TimeScaleTests.cpp
        tests/MidiTests.cpp
        tests/TimecodeTests.cpp
        tests/TempoMapTests.cpp
        tests/LoopTests.cpp
        tests/ReadAheadTests.cpp
        tests/ClickTimelineTests.cpp
        tests/AudioEngineTests.cpp
        tests/WaveformExtractorTests.cpp
        tests/HarnessRegressionTests.cpp
        tests/TestRunnerMain.cpp
    )

    target_include_directories(wtracks_engine_tests PRIVATE include)

    target_link_libraries(wtracks_engine_tests PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_core
        juce::juce_events
    )

    target_compile_definitions(wtracks_engine_tests PRIVATE
        JUCE_STANDALONE_APPLICATION=1
        JUCE_USE_GUI=0 # Desabilita a necessidade de um backend gráfico
        JUCE_WEB_BROWSER=0 # Desabilita o componente de navegador web
        JUCE_USE_CURL=0
    )

    # Facilita achar o executavel e rodar via `ctest` se quiser integrar ao CI depois.
    enable_testing()
    add_test(NAME wtracks_engine_tests COMMAND wtracks_engine_tests)
endif()