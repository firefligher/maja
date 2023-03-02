#ifndef _MAJA_H_
#define _MAJA_H_

#include <stddef.h>

#define MAJA_FRAGMENT_SIZE  (16 * 16 * 2)

struct maja_fragment
{
    size_t compressed_offset;
    char data[MAJA_FRAGMENT_SIZE];
};

__declspec(dllexport) int maja_fragment_decompress(
    struct maja_fragment *fragment
);

__declspec(dllexport) int maja_fragment_get_compressed_ptr(
    char **dst,
    struct maja_fragment *fragment,
    size_t data_length
);

__declspec(dllexport) char *maja_fragment_get_raw_ptr(
    struct maja_fragment *fragment
);

#endif
