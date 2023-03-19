#include <xlite/sound/Engine.hpp>

namespace lite {

namespace sound {

bool Engine::Play(const Audio &audio) {
    auto source = pool.Fetch();
    audio.Play(*source);

    return true;
}

} // namespace sound

} // namespace lite
