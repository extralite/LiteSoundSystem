#pragma once

#include <xlite/Config.hpp>

#define LITE_MAX_MONO_SOURCES 64
#define LITE_MAX_STEREO_SOURCES 64

namespace Lite {

    namespace Sound {

        class LITE_API Device {
        public:
            explicit Device(const char *deviceName);

            Device() : Device("OpenAL Soft") {}

            ~Device();

        private:
            void *device;
            void *context;
        };

    }// namespace Sound

}// namespace Lite
