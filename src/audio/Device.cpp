#include <xlite/audio/Device.hpp>

using namespace Lite::Audio;

Device::Device(const char *deviceName) {
    device = alcOpenDevice(deviceName);

    ALCint attributes[5] = {
            ALC_MONO_SOURCES, 256,
            ALC_STEREO_SOURCES, 256,
            0};

    context = alcCreateContext(device, attributes);
    alcMakeContextCurrent(context);
}

Device::~Device() {
    alcDestroyContext(context);
    alcCloseDevice(device);
}
