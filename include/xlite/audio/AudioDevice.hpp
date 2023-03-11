#pragma once

#include <AL/alc.h>

class AudioDevice {
public:
    explicit AudioDevice(const char *deviceName);

    AudioDevice() : AudioDevice("OpenAL Soft") {}

    ~AudioDevice();

private:
    ALCdevice *device;
    ALCcontext *context;
};
