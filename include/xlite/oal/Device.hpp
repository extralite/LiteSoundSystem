#pragma once

#include <xlite/Config.hpp>

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
