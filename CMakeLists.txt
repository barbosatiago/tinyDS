#cmake_minimum_required(VERSION 3.16)
#project(DSLibrary C)
#
## Opção para selecionar o modo de compilação (Padrão: PC)
#option(TARGET_ESP32 "Compile for ESP32S3 with ESP-IDF" OFF)
#
#if (TARGET_ESP32)
#    # Usando ESP-IDF
#    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
#    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#    project(DSLibrary)
#else()
#    # Modo de teste no PC
#    add_subdirectory(src)
#    add_subdirectory(tests)
#endif()

cmake_minimum_required(VERSION 3.16)
project(DSLibrary C)

# Adicionar diretórios de código e testes
add_subdirectory(src)
add_subdirectory(tests)
