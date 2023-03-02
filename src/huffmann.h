#ifndef _HUFFMANN_H_
#define _HUFFMANN_H_

#include <stddef.h>

#define HUFFMANN_FLAG_LEAF	0x01
#define HUFFMANN_FLAG_LEFT	0x02

struct huffmann_node {
	int flags;

	union {
		struct {
			struct huffmann_node *left_child, *right_child;
		} intermediate;

		struct {
			unsigned short color;
		} leaf;
	} data;
};

int huffmann_build_tree(
	struct huffmann_node *dst_root,
	struct huffmann_node *node_array,
	const char* src,
	size_t src_length,
	unsigned char leaf_count
);

#endif
