cmake_minimum_required(VERSION 3.0)
project(EpicSoundSystem)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(OPUSFILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/codec/opusfile)
set(OPENAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/backend/openal)

get_filename_component(OGG_SOURCE_DIR codec/ogg REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(OPUS_SOURCE_DIR codec/opus REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option(JAVA_BINDINGS "Specify whether to build Java Native Interface bindings" OFF)

if (EMSCRIPTEN)
    set(OPUS_STACK_PROTECTOR OFF CACHE BOOL "" FORCE)
endif ()

if (MSVC)
    set(CMAKE_C_FLAGS_RELEASE "/O2")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif ()

if (UNIX)
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()

set(OP_DISABLE_HTTP ON CACHE BOOL "" FORCE)
set(OP_DISABLE_DOCS ON CACHE BOOL "" FORCE)
set(OP_DISABLE_EXAMPLES ON CACHE BOOL "" FORCE)
add_subdirectory(${OPUSFILE_DIR})

if (UNIX)
    set_property(TARGET opus PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()

set(ESS_INCLUDED_HEADERS
        ${OGG_INCLUDE_DIR}
        ${OPUS_INCLUDE_DIR}
        ${OPUSFILE_INCLUDE_DIR})

if (NOT EMSCRIPTEN)
    set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
    set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)
    add_subdirectory(${OPENAL_DIR})

    list(APPEND ESS_INCLUDED_HEADERS ${OPENAL_INCLUDE_DIR})
endif ()

file(GLOB_RECURSE ESS_SOURCES
        src/OpusStreamDecoder.cpp
        src/audio/AudioBuffer.cpp
        src/audio/AudioDevice.cpp
        src/audio/AudioSource.cpp)

if (JAVA_BINDINGS)
    find_package(JNI REQUIRED)

    list(APPEND ESS_SOURCES
            src/jni/JNIOpusDecoder.cpp
            src/jni/JNIAudioBuffer.cpp
            src/jni/JNIAudioDevice.cpp
            src/jni/JNIAudioSource.cpp)
    list(APPEND ESS_INCLUDED_HEADERS
            ${JNI_INCLUDE_DIRS})
endif ()

add_library(EpicSoundSystem STATIC
        ${ESS_SOURCES})

target_include_directories(EpicSoundSystem PRIVATE
        ${ESS_INCLUDED_HEADERS})

if (NOT EMSCRIPTEN)
    target_link_libraries(EpicSoundSystem OpenAL)
endif ()

target_link_libraries(EpicSoundSystem ogg opus opusfile)
install(TARGETS EpicSoundSystem DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
