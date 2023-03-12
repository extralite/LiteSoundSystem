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

            void Play() const;
            void Stop() const;
            void Loop(bool loop) const;
            void Gain(float gain) const;
            bool IsPlaying() const;
            void Attach(const Buffer &buffer) const;
            void Detach() const;

        private:
            uint32_t source = 0;

            Source(Source &) = delete;
            Source(Source const &) = delete;
        };

    }// namespace Sound

}// namespace Lite
