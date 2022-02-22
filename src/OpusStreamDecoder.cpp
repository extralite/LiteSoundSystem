#include "OpusStreamDecoder.hpp"

#include <string>

OpusStreamDecoder::OpusStreamDecoder(std::unique_ptr<std::istream> istream)
        : istream(std::move(istream)), stream(OpenDecoder(this)) {}

OpusStreamDecoder::~OpusStreamDecoder() {
    op_free(stream);
}

int OpusStreamDecoder::read(opus_int16 *buffer, int size) {
    int ret = op_read_stereo(stream, buffer, size);

    if (ret < 0) {
        fprintf(stderr, "Error decoding Opus data: %d\n", ret);
    }

    return ret;
}

int OpusStreamDecoder::read(void *_stream, unsigned char *_ptr, int _nbytes) {
    auto *decoder = static_cast<OpusStreamDecoder *>(_stream);

    decoder->istream->read(
            reinterpret_cast<char *>(_ptr), _nbytes
    );

    return static_cast<int>(decoder->istream->gcount());
}

OggOpusFile *OpusStreamDecoder::OpenDecoder(OpusStreamDecoder *decoder) {
    int error = 0;

    OpusFileCallbacks cb = {
            OpusStreamDecoder::read,
            nullptr, nullptr, nullptr
    };
    OggOpusFile *stream = op_open_callbacks(decoder, &cb, nullptr, 0, &error);

    if (error < 0) {
        fprintf(stderr, "Error creating Opus decoder: %d\n", error);
    }

    return stream;
}
