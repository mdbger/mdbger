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

#define mm_id_hcode(id) (id)

#define mm_id_node_inert(hash, node) mm_hash_inesrt(hash, mm_obj_cast(node))
#define mm_id_node_erase(hash, node) mm_hash_erase(hash, mm_obj_cast(node))

static inline mm_id_node* mm_id_node_find(mm_hash* hash, mm_id_t id)
{
	return (mm_id_node*)mm_hash_find(hash, MM_ID_NODE, &id);
}

#ifdef __cplusplus
extern "C" {
#endif

u32 mm_id_node_hcode(mm_id_node* node);
u32 mm_id_data_hcode(u8 type, mm_id_t* id);
int mm_id_node_cmp(mm_id_node* node, u8 type, mm_id_t* id);

const mm_obj_ops* mm_id_node_ops();

#ifdef __cplusplus
}
#endif

#endif
