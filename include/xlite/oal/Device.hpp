#pragma once

#include <AL/alc.h>

namespace Lite::Sound {

    class Device {
    public:
        explicit Device(const char *deviceName);

        Device() : Device("OpenAL Soft") {}

        ~Device();

    private:
        ALCdevice *device;
        ALCcontext *context;
    };

}// namespace Lite::Sound
