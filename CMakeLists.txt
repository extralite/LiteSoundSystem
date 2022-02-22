cmake_minimum_required(VERSION 3.0)
project(EpicSoundSystem)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(OPUSFILE_DIR ${CMAKE_SOURCE_DIR}/opusfile)
set(OPUSFILE_INCLUDE_DIR ${OPUSFILE_DIR}/include)

option(JAVA_BINDINGS "Specify whether to build Java Native Interface bindings" OFF)

if (MSVC)
    set(CMAKE_C_FLAGS_RELEASE "/O2")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif ()

set(OP_DISABLE_HTTP ON)
set(OP_DISABLE_DOCS ON)
set(OP_DISABLE_EXAMPLES ON)
add_subdirectory(${OPUSFILE_DIR})

set(${CMAKE_PROJECT_NAME}_INCLUDED_HEADERS
        ${OGG_INCLUDE_DIR} ${OPUS_INCLUDE_DIR} ${OPUSFILE_INCLUDE_DIR})

file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_SOURCES
        src/OpusStreamDecoder.cpp)

if (JAVA_BINDINGS)
    find_package(JNI REQUIRED)

    list(APPEND ${CMAKE_PROJECT_NAME}_SOURCES
            src/jni/JNIOpusDecoder.cpp)
    list(APPEND ${CMAKE_PROJECT_NAME}_INCLUDED_HEADERS
            ${JNI_INCLUDE_DIRS})
endif ()

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${${CMAKE_PROJECT_NAME}_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${${CMAKE_PROJECT_NAME}_INCLUDED_HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} ogg opus opusfile)
