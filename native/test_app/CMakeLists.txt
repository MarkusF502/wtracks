cmake_minimum_required(VERSION 3.22)
project(wtracks_test_app VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Assume que JUCE ja foi adicionado pelo CMakeLists.txt pai (native/CMakeLists.txt).
# Se for buildar este app isoladamente, ajuste o caminho do add_subdirectory abaixo.
if (NOT TARGET juce::juce_recommended_config_flags)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../JUCE JUCE_build)
endif()

juce_add_gui_app(wtracks_test_app
    PRODUCT_NAME "WTracks Test"
    COMPANY_NAME "WTracks"
)

target_sources(wtracks_test_app PRIVATE
    src/Main.cpp
    src/MainComponent.cpp
    ../src/AudioEngine.cpp
)

target_include_directories(wtracks_test_app PRIVATE
    ../include
    src
)

target_compile_definitions(wtracks_test_app PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:wtracks_test_app,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:wtracks_test_app,JUCE_VERSION>"
)

target_link_libraries(wtracks_test_app PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_events
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags
)

# Para gerar o build Android, use o Projucer/CMake toolchain do JUCE apontando
# para este mesmo CMakeLists -- os targets juce_add_gui_app ja sabem lidar com
# Android quando o toolchain do NDK e passado no momento da configuracao.