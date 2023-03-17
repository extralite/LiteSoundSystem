#pragma once

#include <xlite/Config.hpp>
#include <xlite/oal/Source.hpp>

namespace Lite {

    namespace Sound {

        class LITE_API Audio {
        public:
            Audio(BufferFormat channelFormat, int sampleRate, const void *data, size_t size);
            ~Audio() = default;

            void Play(const Source &source) const;

        private:
            Buffer buffer;
        };

    }// namespace Sound

}// namespace Lite
