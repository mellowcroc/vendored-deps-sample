/* Inflates an uploaded zlib stream into a fixed buffer. Built against third_party/zlib. */
#include <stdio.h>
#include <string.h>
#include "zlib.h"

#define OUT_SIZE 65536

int inflate_upload(const unsigned char *in, size_t in_len, unsigned char *out, size_t *out_len) {
    z_stream stream;
    memset(&stream, 0, sizeof(stream));
    if (inflateInit(&stream) != Z_OK) {
        return -1;
    }
    stream.next_in = (unsigned char *)in;
    stream.avail_in = (uInt)in_len;
    stream.next_out = out;
    stream.avail_out = OUT_SIZE;
    int result = inflate(&stream, Z_FINISH);
    *out_len = stream.total_out;
    inflateEnd(&stream);
    return result == Z_STREAM_END ? 0 : -1;
}

int main(void) {
    unsigned char in[OUT_SIZE];
    unsigned char out[OUT_SIZE];
    size_t in_len = fread(in, 1, sizeof(in), stdin);
    size_t out_len = 0;
    if (inflate_upload(in, in_len, out, &out_len) != 0) {
        fprintf(stderr, "inflate failed\n");
        return 1;
    }
    fwrite(out, 1, out_len, stdout);
    return 0;
}
