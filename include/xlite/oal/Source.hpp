#pragma once

#include <xlite/oal/Buffer.hpp>

#include <cstdint>

namespace Lite::Sound {

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
        uint32_t source = 0;
    };

}// namespace Lite::Sound
