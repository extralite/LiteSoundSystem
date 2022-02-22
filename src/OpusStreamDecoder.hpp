#pragma once

#include <opusfile.h>

#define OPUS_MAX_FRAME_SAMPLE 120 * 48                              // 120ms 48000hz
#define OPUS_MAX_FRAME_SAMPLE_INTERLEAVED OPUS_MAX_FRAME_SAMPLE * 2 // 2 channels

#include <istream>
#include <memory>

class OpusStreamDecoder {
public:

    explicit OpusStreamDecoder(std::unique_ptr<std::istream> istream);

    ~OpusStreamDecoder();

    int read(opus_int16 *buffer, int size);

private:
    std::unique_ptr<std::istream> istream;
    OggOpusFile *stream;

    static int read(void *_stream, unsigned char *_ptr, int _nbytes);

    static OggOpusFile *OpenDecoder(OpusStreamDecoder *decoder);
};
