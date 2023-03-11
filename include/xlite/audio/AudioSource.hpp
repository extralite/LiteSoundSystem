#pragma once

#include <AL/al.h>

#include <xlite/audio/AudioBuffer.hpp>

class AudioSource {
public:
    explicit AudioSource(bool loop);

    AudioSource() : AudioSource(false) {}

    ~AudioSource();

    void play() const;

    void stop() const;

    void loop(bool loop) const;

    void gain(float gain) const;

    bool isPlaying() const;

    void attach(const AudioBuffer &buffer) const;

    void detach() const;

private:
    ALuint source = 0;
};
