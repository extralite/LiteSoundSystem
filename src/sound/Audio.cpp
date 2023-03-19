#include <xlite/sound/Audio.hpp>

namespace lite {

namespace sound {

Audio::Audio(BufferFormat channelFormat, int sampleRate, const void *data, std::size_t size)
    : buffer(channelFormat, sampleRate) {
    buffer.Data(data, size);
}

void Audio::Play(const Source &source) const {
    source.Attach(buffer);
    source.Play();
}

} // namespace sound

} // namespace lite
