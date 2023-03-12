#pragma once

namespace Lite {

    namespace Sound {

        class Device {
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
