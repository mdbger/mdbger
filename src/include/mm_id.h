#ifndef MM_ID_H
#define MM_ID_H

#include "mm_hash.h"

typedef struct mm_id_node_s {
	MM_OBJ_HDR;
	mm_id_t id;
	u32 refcnt;
} mm_id_node;

#define mm_id_node_init(node, node_id) do { \
	mm_obj_init(node, MM_ID_NODE); \
	(node)->id = (node_id); \
	(node)->refcnt = 0; \
} while(0)

static inline mm_id_insert(mm_hash* hash, mm_id_node* node)
{
	mm_bucket* bucket = mm_hash_bucket(hash, node->id);
	mm_bucket_insert(bucket, node);
}

static inline mm_id_erase(mm_hash* hash, mm_id_node* node)
{
	mm_bucket* bucket = mm_hash_bucket(hash, node->id);
	mm_bucket_erase(bucket, node);
}

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
