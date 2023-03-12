#pragma once

#include <xlite/Config.hpp>

#include <cstddef>
#include <cstdint>

namespace Lite {

    namespace Sound {

        enum BufferFormat : int {
            /** Signed 16-bit mono buffer format. */
            MONO_SIGNED_16_BIT = 0x1101,
            /** Unsigned 8-bit mono buffer format. */
            MONO_UNSIGNED_8_BIT = 0x1100,
            /** Signed 16-bit stereo buffer format. */
            STEREO_SIGNED_16_BIT = 0x1103,
            /** Unsigned 8-bit stereo buffer format. */
            STEREO_UNSIGNED_8_BIT = 0x1102,
        };

        class LITE_API Buffer {
        public:
            Buffer(BufferFormat format, int sampleRate);

            ~Buffer();

            void data(const void *data, size_t size) const;

            inline uint32_t getBuffer() const {
                return buffer;
            }

        private:
            uint32_t buffer = 0;

            BufferFormat format;
            int sampleRate;
        };

    }// namespace Sound

}// namespace Lite
