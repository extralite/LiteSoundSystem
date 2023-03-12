#include <xlite/oal/Source.hpp>

#include <AL/al.h>

using namespace Lite::Sound;

Source::Source() {
    alGenSources(1, &source);
    alSourcef(source, AL_GAIN, 1.f);
}

Source::~Source() {
    alDeleteSources(1, &source);
}

void Source::play() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    if (AL_STOPPED == state)
        alSourcei(source, AL_POSITION, 0);

    alSourcePlay(source);
}

void Source::stop() const {
    alSourceStop(source);
}

void Source::loop(bool loop) const {
    alSourcei(source, AL_LOOPING, loop);
}

void Source::gain(float gain) const {
    alSourcef(source, AL_GAIN, gain);
}

bool Source::isPlaying() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return AL_PLAYING == state;
}

void Source::attach(const Buffer &buffer) const {
    alSourcei(source, AL_BUFFER, buffer.getBuffer());
}

void Source::detach() const {
    alSourcei(source, AL_BUFFER, AL_NONE);
}
