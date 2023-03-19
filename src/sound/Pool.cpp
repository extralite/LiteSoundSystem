#include <xlite/sound/Pool.hpp>

#include <xlite/oal/Device.hpp>
#include <AL/al.h>

constexpr std::size_t POOL_PREFERRED_SIZE = LITE_MAX_MONO_SOURCES + LITE_MAX_STEREO_SOURCES;

namespace lite {

namespace sound {

Pool::Pool() {
    for (int i = 0; i < POOL_PREFERRED_SIZE; i++) {
        auto source = std::make_shared<Source>();
        if (alGetError() != AL_NO_ERROR)
            break;

        sources.push_back(source);
    }

    for (const auto &source : sources)
        available.push(source);
}

std::shared_ptr<Source> Pool::Fetch() {
    Update();

    if (available.empty())
        return nullptr;

    auto source = available.front();
    available.pop();

    acquired.push_back(source);
    return source;
}

void Pool::Update() {
    for (auto it = acquired.begin(); it != acquired.end();) {
        auto source = *it;
        if (source->Available()) {
            it = acquired.erase(it);

            source->Detach();
            available.push(source);
            continue;
        }

        ++it;
    }
}

} // namespace sound

} // namespace lite
