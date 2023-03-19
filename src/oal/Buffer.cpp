#include <xlite/oal/Buffer.hpp>

#include <AL/al.h>

namespace lite {

namespace sound {

Buffer::Buffer(BufferFormat format, int sampleRate)
    : format(format), sampleRate(sampleRate) {
    alGenBuffers(1, &buffer);
}

Buffer::~Buffer() {
    alDeleteBuffers(1, &buffer);
}

void Buffer::Data(const void *data, std::size_t size) const {
    alBufferData(buffer, format, data, static_cast<ALint>(size), sampleRate);
}

} // namespace sound

} // namespace lite
