#include "../audio/AudioBuffer.hpp"

#include <jni.h>
#include <cstdint>

extern "C" {

JNIEXPORT jlong
JNICALL Java_io_github_ve_soundsystem_AudioBuffer_ncreate(JNIEnv *env, jclass clazz, jint format, jint sampleRate) {
    auto *buffer = new AudioBuffer(static_cast<AudioFormat>(format), sampleRate);

    return reinterpret_cast<intptr_t>(buffer);
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioBuffer_ndata(JNIEnv *env, jclass clazz, jlong _buffer, jobject byteBuffer) {
    auto *buffer = reinterpret_cast<AudioBuffer *>(_buffer);

    const void *data = env->GetDirectBufferAddress(byteBuffer);
    jlong size = env->GetDirectBufferCapacity(byteBuffer);

    buffer->data(data, size);
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioBuffer_nfree(JNIEnv *env, jclass clazz, jlong _buffer) {
    auto *buffer = reinterpret_cast<AudioBuffer *>(_buffer);

    delete buffer;
}

}
