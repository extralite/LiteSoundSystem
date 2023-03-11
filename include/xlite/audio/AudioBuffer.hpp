#pragma once

#include <AL/al.h>
#include <cstddef>

enum AudioFormat : ALenum {
    MONO_SIGNED_16_BIT = AL_FORMAT_MONO16,
    STEREO_SIGNED_16_BIT = AL_FORMAT_STEREO16,
};

class AudioBuffer {
    friend class AudioSource;

public:
    AudioBuffer(AudioFormat format, int sampleRate);

    ~AudioBuffer();

    void data(const void *data, size_t size) const;

private:
    ALuint buffer = 0;

    AudioFormat format;
    int sampleRate;
};
