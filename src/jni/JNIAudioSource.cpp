#include "../audio/AudioSource.hpp"

#include <jni.h>

extern "C" {

JNIEXPORT jlong
JNICALL Java_io_github_ve_soundsystem_AudioSource_ncreate(JNIEnv *env, jclass clazz) {
    auto *source = new AudioSource();

    return reinterpret_cast<intptr_t>(source);
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_nplay(JNIEnv *env, jclass clazz, jlong _source) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    source->play();
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_nstop(JNIEnv *env, jclass clazz, jlong _source) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    source->stop();
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_nloop(JNIEnv *env, jclass clazz, jlong _source, jboolean loop) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    source->loop(loop);
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_ngain(JNIEnv *env, jclass clazz, jlong _source, jfloat gain) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    source->gain(gain);
}

JNIEXPORT jboolean
JNICALL Java_io_github_ve_soundsystem_AudioSource_nisPlaying(JNIEnv *env, jclass clazz, jlong _source) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    return source->isPlaying();
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_nattach(JNIEnv *env, jclass clazz, jlong _source, jlong _buffer) {
    auto *source = reinterpret_cast<AudioSource *>(_source);
    auto *buffer = reinterpret_cast<AudioBuffer *>(_buffer);

    source->attach(*buffer);
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_ndetach(JNIEnv *env, jclass clazz, jlong _source) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    source->detach();
}

JNIEXPORT void
JNICALL Java_io_github_ve_soundsystem_AudioSource_nfree(JNIEnv *env, jclass clazz, jlong _source) {
    auto *source = reinterpret_cast<AudioSource *>(_source);

    delete source;
}

}
