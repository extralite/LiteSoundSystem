#pragma once

#include <al.h>

class AudioBuffer {
    friend class AudioSource;

public:
    AudioBuffer();

    ~AudioBuffer();

    void data(const void* data, size_t size) const;

private:
    ALuint buffer = 0;
};
