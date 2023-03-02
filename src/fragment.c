#include <string.h>
#include "maja.h"

static int _decodeHuffmann(char* dst, const char* src, size_t src_length);
static int _decodeRunLength(char *dst, const char *src, size_t src_length);

__declspec(dllexport) int maja_fragment_decompress(
    struct maja_fragment *fragment
) {
    return _decodeRunLength(
        fragment->data,
        &fragment->data[fragment->compressed_offset],
        MAJA_FRAGMENT_SIZE - fragment->compressed_offset
    );
}

__declspec(dllexport) int maja_fragment_get_compressed_ptr(
    char **dst,
    struct maja_fragment *fragment,
    size_t data_length
) {
    if (data_length > MAJA_FRAGMENT_SIZE) {
        return 1;
    }

    /*
     * The data is expanded from right to left. Hence, we need to ensure
     * right-alignment.
     */

    fragment->compressed_offset = MAJA_FRAGMENT_SIZE - data_length;
    *dst = &fragment->data[fragment->compressed_offset];

    return 0;
}

__declspec(dllexport) char *maja_fragment_get_raw_ptr(
    struct maja_fragment *fragment
) {
    return fragment->data;
}

static int _decodeHuffmann(char* dst, const char* src, size_t src_length) {
}

static int _decodeRunLength(char *dst, const char *src, size_t src_length) {
    unsigned short next_repetition;
    size_t src_pos = 0, dst_pos = 0;

    while (src_pos < src_length) {
        size_t delta;
        char value;
        unsigned char count;

        /*
         * Read the variable integer that encodes the offset of the next
         * repetition.
         */

        if (src_length - src_pos < 2) {
            return 1;
        }

        next_repetition = src[src_pos] & 0x7F;

        if (src[src_pos++] & 0x80) {
            next_repetition |= (src[src_pos] & 0x7F) << 7;

            if (src[src_pos++] & 0x80) {
                next_repetition |= (src[src_pos] & 0x2F) << 14;

                if (src[src_pos++] & 0x80) {
                    return 1;
                }
            }
        }

        /* If next_repetition is zero, there is no further repetition. */

        if (!next_repetition) {
            delta = src_length - src_pos;

            memcpy(&dst[dst_pos], &src[src_pos], delta);
            src_pos += delta;
            dst_pos += delta;
            continue;
        }

        /* Otherwise, copy all bytes in front of the next repetition. */

        delta = ((size_t) next_repetition) - 1;

        if (delta > src_length - src_pos) {
            return 1;
        }

        memcpy(&dst[dst_pos], &src[src_pos], delta);
        src_pos += delta;
        dst_pos += delta;

        /* Decode the repetition, but NOT the jump. */

        if (src_length - src_pos < 2) {
            return 1;
        }

        value = src[src_pos++];
        count = (unsigned char) src[src_pos++];

        for (; count > 0; count--) {
            dst[dst_pos++] = value;
        }
    }

    return 0;
}
