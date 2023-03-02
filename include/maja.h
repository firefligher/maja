#ifndef _MAJA_H_
#define _MAJA_H_

#include <stddef.h>

#if defined(_WIN32) && defined(MAJA_BUILD)
    #define MAJA_API __declspec(dllexport)
#elif defined(_WIN32)
    #define MAJA_API __declspec(dllimport)
#else
    #define MAJA_API
#endif

#define MAJA_FRAGMENT_SIZE  (16 * 16 * 2)

struct maja_fragment
{
    size_t compressed_offset;
    char data[MAJA_FRAGMENT_SIZE];
};

MAJA_API int maja_fragment_decompress(
    struct maja_fragment *fragment
);

MAJA_API int maja_fragment_get_compressed_ptr(
    char **dst,
    struct maja_fragment *fragment,
    size_t data_length
);

MAJA_API char *maja_fragment_get_raw_ptr(
    struct maja_fragment *fragment
);

#endif
