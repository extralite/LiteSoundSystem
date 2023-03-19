#pragma once

#include <xlite/Config.hpp>
#include <xlite/oal/Device.hpp>
#include <xlite/sound/Audio.hpp>
#include <xlite/sound/Pool.hpp>

#include <memory>
#include <string>

namespace lite {

namespace sound {

class LITE_API Engine {
public:
    Engine() = default;
    ~Engine() = default;

    bool Play(const Audio &audio);

private:
    Device device;
    Pool pool;
};

} // namespace sound

} // namespace lite
