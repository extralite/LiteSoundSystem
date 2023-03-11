cmake_minimum_required(VERSION 3.0)
project(EpicSoundSystem)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

get_filename_component(OGG_SOURCE_DIR codec/ogg REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(OPUS_SOURCE_DIR codec/opus REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE ESS_SOURCES
        src/OpusStreamDecoder.cpp
        src/audio/AudioBuffer.cpp
        src/audio/AudioDevice.cpp
        src/audio/AudioSource.cpp)

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
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/codec/opusfile ${CMAKE_BINARY_DIR}/opusfile)

if (UNIX)
    set_property(TARGET opus PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()

if (NOT EMSCRIPTEN)
    set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
    set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)

    set(LIBTYPE "STATIC")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend/openal ${CMAKE_BINARY_DIR}/openal)

    if (UNIX)
        set_property(TARGET OpenAL PROPERTY POSITION_INDEPENDENT_CODE ON)
    endif ()
endif ()

add_library(EpicSoundSystem SHARED ${ESS_SOURCES})
set_property(TARGET EpicSoundSystem PROPERTY C_STANDARD 11)
set_property(TARGET EpicSoundSystem PROPERTY CXX_STANDARD 11)

if (NOT EMSCRIPTEN)
    target_link_libraries(EpicSoundSystem PRIVATE OpenAL)
    target_compile_definitions(EpicSoundSystem PRIVATE AL_LIBTYPE_STATIC)
endif ()

target_link_libraries(EpicSoundSystem PRIVATE opusfile)
install(TARGETS EpicSoundSystem DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
