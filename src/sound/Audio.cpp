#include <xlite/sound/Audio.hpp>

using namespace Lite::Sound;

Audio::Audio(BufferFormat channelFormat, int sampleRate, const void *data, size_t size)
    : buffer(channelFormat, sampleRate) {
    buffer.Data(data, size);
}

void Audio::Play(const Source &source) const {
    source.Attach(buffer);
    source.Play();
}
