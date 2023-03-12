#include <xlite/oal/Buffer.hpp>

#include <AL/al.h>

using namespace Lite::Sound;

Buffer::Buffer(BufferFormat format, int sampleRate)
    : format(format), sampleRate(sampleRate) {
    alGenBuffers(1, &buffer);
}

Buffer::~Buffer() {
    alDeleteBuffers(1, &buffer);
}

void Buffer::data(const void *data, size_t size) const {
    alBufferData(buffer, format, data, static_cast<ALint>(size), sampleRate);
}
