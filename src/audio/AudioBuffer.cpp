#include "AudioBuffer.hpp"

AudioBuffer::AudioBuffer(AudioFormat format, int sampleRate)
        : format(format), sampleRate(sampleRate) {
    alGenBuffers(1, &buffer);
}

AudioBuffer::~AudioBuffer() {
    alDeleteBuffers(1, &buffer);
}

void AudioBuffer::data(const void *data, size_t size) const {
    alBufferData(buffer, format, data, static_cast<ALint>(size), sampleRate);
}
