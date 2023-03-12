#pragma once

namespace Lite::Sound {

    class Device {
    public:
        explicit Device(const char *deviceName);

        Device() : Device("OpenAL Soft") {}

        ~Device();

    private:
        void *device;
        void *context;
    };

}// namespace Lite::Sound
