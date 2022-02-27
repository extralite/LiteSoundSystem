#include "../audio/AudioDevice.hpp"

#include <jni.h>
#include <cstdint>

extern "C" {

JNIEXPORT jlong JNICALL Java_io_github_ve_soundsystem_AudioDevice_ncreate(JNIEnv *env, jclass clazz) {
    auto *device = new AudioDevice();

    return reinterpret_cast<intptr_t>(device);
}

JNIEXPORT void JNICALL Java_io_github_ve_soundsystem_AudioDevice_nfree(JNIEnv *env, jclass clazz, jlong _device) {
    auto *device = reinterpret_cast<AudioDevice *>(_device);

    delete device;
}

}
