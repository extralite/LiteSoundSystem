#include <xlite/sound/Engine.hpp>

using namespace Lite::Sound;

bool Engine::Play(const Audio &audio) {
    auto source = pool.Fetch();
    audio.Play(*source);

    return true;
}
