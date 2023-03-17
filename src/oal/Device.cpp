#include <xlite/oal/Device.hpp>

#include <AL/alc.h>

using namespace Lite::Sound;

Device::Device(const char *deviceName) {
    device = alcOpenDevice(deviceName);

    ALCint attributes[5] = {
            ALC_MONO_SOURCES, LITE_MAX_MONO_SOURCES,
            ALC_STEREO_SOURCES, LITE_MAX_STEREO_SOURCES,
            0};

    context = alcCreateContext(static_cast<ALCdevice *>(device), attributes);
    alcMakeContextCurrent(static_cast<ALCcontext *>(context));
}

Device::~Device() {
    alcDestroyContext(static_cast<ALCcontext *>(context));
    alcCloseDevice(static_cast<ALCdevice *>(device));
}
