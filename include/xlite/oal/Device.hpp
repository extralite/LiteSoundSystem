#pragma once

#include <xlite/Config.hpp>

constexpr std::size_t LITE_MAX_MONO_SOURCES = 64;
constexpr std::size_t LITE_MAX_STEREO_SOURCES = 64;

namespace lite {

namespace sound {

class LITE_API Device {
public:
    explicit Device(const char *deviceName);

    Device() : Device("OpenAL Soft") {}

    ~Device();

private:
    void *device;
    void *context;
};

} // namespace sound

} // namespace lite
