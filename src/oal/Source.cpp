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

void Source::Play() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    if (AL_STOPPED == state)
        alSourcei(source, AL_POSITION, 0);

    alSourcePlay(source);
}

void Source::Stop() const {
    alSourceStop(source);
}

void Source::Loop(bool loop) const {
    alSourcei(source, AL_LOOPING, loop);
}

void Source::Gain(float gain) const {
    alSourcef(source, AL_GAIN, gain);
}

bool Source::IsPlaying() const {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return AL_PLAYING == state;
}

void Source::Attach(const Buffer &buffer) const {
    alSourcei(source, AL_BUFFER, buffer.GetBuffer());
}

void Source::Detach() const {
    alSourcei(source, AL_BUFFER, AL_NONE);
}

bool Source::Available() const {
    ALenum state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return AL_STOPPED == state;
}
