#pragma once

#include <xlite/Config.hpp>
#include <xlite/oal/Buffer.hpp>

#include <cstdint>

namespace Lite {

    namespace Sound {

        class LITE_API Source {
        public:
            Source();
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

            Source(Source &) = delete;
            Source(Source const &) = delete;
        };

    }// namespace Sound

}// namespace Lite
