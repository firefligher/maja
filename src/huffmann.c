#include "huffmann.h"

int huffmann_build_tree(
	struct huffmann_node *dst_root,
	struct huffmann_node *node_array,
	const char *src,
	size_t src_length,
	unsigned char leaf_count
) {
	unsigned char merge_offset, node_offset = 0;
	size_t src_index = 0;

	/* Collecting the leafs. */

	while (leaf_count > node_offset) {
		unsigned char batch_flags,
			batch_offset,
			batch_count = (leaf_count < 8) ? leaf_count : 8;

		if (batch_count * 2 + 1 > src_length - src_index) {
			return 1;
		}

		batch_flags = (unsigned char) src[src_index + batch_count * 2];
		
		for (batch_offset = 0; batch_offset < batch_count; batch_offset++) {
			struct huffmann_node *node =
				&node_array[node_offset + batch_offset];
			
			node->flags = HUFFMANN_FLAG_LEAF;

			if (batch_flags & (1 << 7 - batch_offset)) {
				node->flags |= HUFFMANN_FLAG_LEFT;
			}

			node->data.leaf.color = src[src_index + batch_offset * 2]
				| (src[src_index + batch_offset * 2 + 1] << 8);
		}

		node_offset += batch_count;
		src_index += batch_count * 2 + 1;
	}

	/* Merging the leafs. */

	merge_offset = 0;

	for (node_offset = 0; node_offset < leaf_count; node_offset++) {

	}
}
