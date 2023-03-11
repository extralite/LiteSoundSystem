#pragma once

#include <AL/al.h>
#include <cstddef>

namespace Lite::Sound {

    enum Format : ALenum {
        MONO_SIGNED_16_BIT = AL_FORMAT_MONO16,
        STEREO_SIGNED_16_BIT = AL_FORMAT_STEREO16,
    };

    class Buffer {
    public:
        Buffer(Format format, int sampleRate);

        ~Buffer();

        void data(const void *data, size_t size) const;

        inline ALuint getBuffer() const {
            return buffer;
        }

    private:
        ALuint buffer = 0;

        Format format;
        int sampleRate;
    };

}// namespace Lite::Sound
