#include "AudioSource.hpp"

AudioSource::AudioSource(bool loop) {
    alGenSources(1, &source);
    alSourcei(source, AL_LOOPING, loop);
    alSourcef(source, AL_GAIN, 1.f);
}

AudioSource::~AudioSource() {
    alDeleteSources(1, &source);
}

void AudioSource::play() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    if (AL_STOPPED == state)
        alSourcei(source, AL_POSITION, 0);

    alSourcePlay(source);
}

void AudioSource::stop() const {
    alSourceStop(source);
}

void AudioSource::loop(bool loop) const {
    alSourcei(source, AL_LOOPING, loop);
}

void AudioSource::gain(float gain) const {
    alSourcef(source, AL_GAIN, gain);
}

bool AudioSource::isPlaying() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return AL_PLAYING == state;
}

void AudioSource::attach(const AudioBuffer &buffer) const {
    alSourcei(source, AL_BUFFER, buffer.buffer);
}

void AudioSource::detach() const {
    alSourcei(source, AL_BUFFER, 0);
}
