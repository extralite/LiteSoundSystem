#include "../OpusStreamDecoder.hpp"

#include <jni.h>

#include <iostream>
#include <fstream>

extern "C" {

JNIEXPORT jlong JNICALL Java_io_github_ve_soundsystem_OpusDecoder_ncreate(JNIEnv *env, jclass clazz, jstring file) {
    const char *fileName = env->GetStringUTFChars(file, nullptr);
    std::unique_ptr<std::istream> stream(
            new std::ifstream(fileName, std::ios::in | std::ios::binary)
    );

    auto *decoder = new OpusStreamDecoder(std::move(stream));

    return reinterpret_cast<intptr_t>(decoder);
}

JNIEXPORT jshortArray JNICALL Java_io_github_ve_soundsystem_OpusDecoder_nread(JNIEnv *env, jclass clazz, jlong _decoder) {
    auto *decoder = reinterpret_cast<OpusStreamDecoder *>(_decoder);

    opus_int16 pcm[OPUS_MAX_FRAME_SAMPLE_INTERLEAVED];

    int ret = decoder->read(pcm, OPUS_MAX_FRAME_SAMPLE_INTERLEAVED);

    if (ret > 0) {
        jshortArray arr = env->NewShortArray(ret);
        env->SetShortArrayRegion(arr, 0, ret, pcm);

        return arr;
    }

    return nullptr;
}

JNIEXPORT void JNICALL Java_io_github_ve_soundsystem_OpusDecoder_nfree(JNIEnv *env, jclass clazz, jlong _decoder) {
    auto *decoder = reinterpret_cast<OpusStreamDecoder *>(_decoder);
    delete decoder;
}

}
