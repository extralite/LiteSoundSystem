set(FFMPEG_CONFIGURE_OPTIONS
    --disable-debug
    --disable-autodetect
    --disable-programs
    --disable-everything
    --disable-network
    --disable-avdevice
    --disable-swscale
    --disable-postproc
    --disable-avfilter
    --enable-decoder=mp3,opus
    --enable-demuxer=mp3,ogg
    --enable-parser=opus
)

if(MSVC)
    set(TARGET_OS win32)
    set(TARGET_ARCH x86)

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(TARGET_OS win64)
        set(TARGET_ARCH x86_64)
    endif()

    set(FFMPEG_CONFIGURE_OPTIONS
        --toolchain=msvc
        --target-os=${TARGET_OS}
        --arch=${TARGET_ARCH}
        ${FFMPEG_CONFIGURE_OPTIONS}
    )
endif()

set(FFMPEG_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg)
set(FFMPEG_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg)
file(MAKE_DIRECTORY ${FFMPEG_OUTPUT})

set(AVCODEC_LIB ${FFMPEG_OUTPUT}/lib/libavcodec.a)
set(AVFORMAT_LIB ${FFMPEG_OUTPUT}/lib/libavformat.a)
set(AVUTIL_LIB ${FFMPEG_OUTPUT}/lib/libavutil.a)
set(SWRESAMPLE_LIB ${FFMPEG_OUTPUT}/lib/libswresample.a)
 
set(FFMPEG_INCLUDE_DIRS ${FFMPEG_OUTPUT}/include)
set(FFMPEG_TARGET_LIBRARIES ${AVCODEC_LIB} ${AVFORMAT_LIB} ${AVUTIL_LIB} ${SWRESAMPLE_LIB})

message(STATUS "Running configuration for FFmpeg (this may take a while)")
execute_process(COMMAND $ENV{SHELL}
    ${FFMPEG_SOURCE}/configure --prefix=${FFMPEG_OUTPUT} ${FFMPEG_CONFIGURE_OPTIONS}
    WORKING_DIRECTORY ${FFMPEG_OUTPUT}
)

add_custom_command(OUTPUT ${FFMPEG_TARGET_LIBRARIES}
    COMMAND make -j$(nproc)
    COMMAND make install
    WORKING_DIRECTORY ${FFMPEG_OUTPUT}
)

add_custom_target(ffmpeg ALL DEPENDS ${FFMPEG_TARGET_LIBRARIES})

add_library(avcodec STATIC IMPORTED)
set_property(TARGET avcodec PROPERTY IMPORTED_LOCATION ${AVCODEC_LIB})
add_dependencies(avcodec ffmpeg)

add_library(avformat STATIC IMPORTED)
set_property(TARGET avformat PROPERTY IMPORTED_LOCATION ${AVFORMAT_LIB})
add_dependencies(avformat ffmpeg)

add_library(avutil STATIC IMPORTED)
set_property(TARGET avutil PROPERTY IMPORTED_LOCATION ${AVUTIL_LIB})
add_dependencies(avutil ffmpeg)

add_library(swresample STATIC IMPORTED)
set_property(TARGET swresample PROPERTY IMPORTED_LOCATION ${SWRESAMPLE_LIB})
add_dependencies(swresample ffmpeg)
