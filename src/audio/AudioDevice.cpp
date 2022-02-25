#include "AudioDevice.hpp"

AudioDevice::AudioDevice(const char *deviceName) {
    device = alcOpenDevice(deviceName);

    ALCint attributes[5] = {
            ALC_MONO_SOURCES, 256,
            ALC_STEREO_SOURCES, 256,
            0
    };

    context = alcCreateContext(device, attributes);
    alcMakeContextCurrent(context);
}

AudioDevice::~AudioDevice() {
    alcDestroyContext(context);
    alcCloseDevice(device);
}
