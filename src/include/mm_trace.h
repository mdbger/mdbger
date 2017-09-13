#ifndef MM_TRACE_H
#define MM_TRACE_H

#include "mm_id.h"

#define MM_TRACE_DEPTH 16

typedef struct mm_trace_node_s {
	MM_OBJ_HDR;
	void* call_stack[MM_TRACE_DEPTH];
	u32 depth:8;
	u32 unused:24;
} mm_trace_node;

#define mm_trace_node_init(node) do { \
	memset(node, 0, sizeof(*(node))); \
	mm_obj_init(node, MM_TRACE_NODE); \
} while(0)

#define mm_trace_cs_hcode(call_stack, depth) \
	mm_jhash((u32*)(call_stack), (depth)*sizeof(void*))

#define mm_trace_node_hcode(node) \
	mm_trace_cs_hcode((node)->call_stack, (node)->depth)

static inline mm_trace_insert(mm_hash* hash, mm_trace_node* node)
{
	u32 hcode = mm_trace_node_hcode(node);
	mm_bucket* bucket = mm_hash_bucket(hash, hcode);
	mm_bucket_insert(bucket, node);
}

static inline mm_trace_erase(mm_hash* hash, mm_trace_node* node)
{
	u32 hcode = mm_trace_node_hcode(node);
	mm_bucket* bucket = mm_hash_bucket(hash, hcode);
	mm_bucket_erase(bucket, node);
}

typedef struct mm_trace_s {
	mm_trace_node trace_node;
	mm_id_node id_node;
} mm_trace;

#define mm_trace_init(trace) do { \
	mm_trace_node_init(&(trace)->trace_node); \
	mm_id_node_init(&(trace)->id_node); \
} while(0)

#define mm_trace_alloc(owner) \
	((mm_trace*)(owner)->ops->alloc(sizeof(mm_trace)))
#define mm_trace_free(owner, trace) (owner)->ops->free(trace)

typedef struct mm_trace_hash_s {
	mm_hash base;
	mm_id_t cur_id;
} mm_trace_hash;

#define mm_trace_hash_init(hash) do { \
	mm_hash_init(&(hash)->base); \
	(hash)->cur_id = 1; \
} while(0)

static inline mm_trace* mm_trace_find(mm_trace_hash* hash, void** call_stack,
	size_t depth)
{
	u32 hcode = mm_trace_cs_hcode(call_stack, depth);
	mm_hash_schctx ctx;

	mm_hash_schctx_init(&ctx, hcode, mm_trace_node_comp);

	mm_hash_find(&hash->base, hcode, , obj);
}

static inline mm_trace* mm_trace_add(mm_trace_hash* hash, void** call_stack,
	size_t depth)
{
	mm_trace* trace = mm_trace_alloc(hash);
	if(trace) {
		mm_trace_node_init(&trace->trace_node);
		mm_trace_node_set(&trace->trace_node, call_stack, depth);
		mm_trace_insert(&hash->base, &trace->trace_node);

		mm_id_node_init(&trace->id_node, hash->cur_id);
		mm_id_insert(&hash->base, &trace->id_node);
	}
	return trace;
}

static inline mm_trace* mm_trace_find_by_id(mm_trace_hash* hash, mm_id_t id)
{
}

static inline void mm_trace_del_by_id(mm_trace_hash* hash, mm_id_t id)
{
}

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif
