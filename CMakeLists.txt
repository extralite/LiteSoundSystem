cmake_minimum_required(VERSION 3.0)
project(EpicSoundSystem)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(OPUSFILE_DIR ${CMAKE_SOURCE_DIR}/codec/opusfile)
set(OPENAL_DIR ${CMAKE_SOURCE_DIR}/backend/openal)

option(JAVA_BINDINGS "Specify whether to build Java Native Interface bindings" OFF)

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

set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)
add_subdirectory(${OPENAL_DIR})

set(${CMAKE_PROJECT_NAME}_INCLUDED_HEADERS
        ${OGG_INCLUDE_DIR}
        ${OPUS_INCLUDE_DIR}
        ${OPUSFILE_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR})

file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_SOURCES
        src/OpusStreamDecoder.cpp
        src/audio/AudioBuffer.cpp
        src/audio/AudioDevice.cpp
        src/audio/AudioSource.cpp)

if (JAVA_BINDINGS)
    find_package(JNI REQUIRED)

    list(APPEND ${CMAKE_PROJECT_NAME}_SOURCES
            src/jni/JNIOpusDecoder.cpp
            src/jni/JNIAudioBuffer.cpp
            src/jni/JNIAudioDevice.cpp
            src/jni/JNIAudioSource.cpp)
    list(APPEND ${CMAKE_PROJECT_NAME}_INCLUDED_HEADERS
            ${JNI_INCLUDE_DIRS})
endif ()

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${${CMAKE_PROJECT_NAME}_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${${CMAKE_PROJECT_NAME}_INCLUDED_HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} OpenAL ogg opus opusfile)
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
