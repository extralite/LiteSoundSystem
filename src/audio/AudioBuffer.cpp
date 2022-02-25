#include "AudioBuffer.hpp"

AudioBuffer::AudioBuffer() {
    alGenBuffers(1, &buffer);
}

AudioBuffer::~AudioBuffer() {
    alDeleteBuffers(1, &buffer);
}

void AudioBuffer::data(const void *data, size_t size) const {
    alBufferData(buffer, AL_FORMAT_STEREO16, data, static_cast<ALint>(size), 48000);
}
