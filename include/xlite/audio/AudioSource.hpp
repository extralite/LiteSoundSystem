#pragma once

#include <AL/al.h>

#include <xlite/audio/AudioBuffer.hpp>

namespace Lite::Audio {

    class Source {
    public:
        explicit Source(bool loop);

        Source() : Source(false) {}

        ~Source();

        void play() const;

        void stop() const;

        void loop(bool loop) const;

        void gain(float gain) const;

        bool isPlaying() const;

        void attach(const Buffer &buffer) const;

        void detach() const;

    private:
        ALuint source = 0;
    };

}// namespace Lite::Audio
