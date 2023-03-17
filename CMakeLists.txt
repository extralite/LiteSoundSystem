cmake_minimum_required(VERSION 3.0)
project(LiteSoundSystem)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

get_filename_component(OGG_SOURCE_DIR codec/ogg REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(OPUS_SOURCE_DIR codec/opus REALPATH BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE LITE_SS_SOURCES
        src/OpusStreamDecoder.cpp
        src/oal/Buffer.cpp
        src/oal/Device.cpp
        src/oal/Source.cpp
        src/sound/Audio.cpp
        src/sound/Engine.cpp
        src/sound/Pool.cpp
)

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

set(LITE_SS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        CACHE PATH "LiteSoundSystem include directory" FORCE)

add_library(LiteSoundSystem SHARED ${LITE_SS_SOURCES})
target_compile_definitions(LiteSoundSystem PRIVATE LITE_API_EXPORT)

set_property(TARGET LiteSoundSystem PROPERTY C_STANDARD 11)
set_property(TARGET LiteSoundSystem PROPERTY CXX_STANDARD 11)
set_property(TARGET LiteSoundSystem PROPERTY LIBRARY_OUTPUT_NAME litesound)

if (NOT EMSCRIPTEN)
    target_link_libraries(LiteSoundSystem PRIVATE OpenAL)
    target_compile_definitions(LiteSoundSystem PRIVATE AL_LIBTYPE_STATIC)
endif ()

target_link_libraries(LiteSoundSystem PRIVATE opusfile)
target_include_directories(LiteSoundSystem PUBLIC ${LITE_SS_INCLUDE_DIRS})
install(TARGETS LiteSoundSystem DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
