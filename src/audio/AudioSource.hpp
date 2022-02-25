#pragma once

#include <al.h>

#include "AudioBuffer.hpp"

class AudioSource {
public:
    explicit AudioSource(bool loop);

    AudioSource() : AudioSource(false) {}

    ~AudioSource();

    void play() const;

    void stop() const;

    bool isPlaying() const;

    void attach(const AudioBuffer &buffer) const;

    void detach() const;

private:
    ALuint source = 0;
};
