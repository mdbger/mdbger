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

#define mm_call_stack_hcode(call_stack, depth) \
	mm_jhash((u32*)(call_stack), (depth)*sizeof(void*))

#define mm_trace_node_insert(hash, node) \
	mm_hash_insert(hash, mm_obj_cast(node))
#define mm_trace_node_erase(hash, node) \
	mm_hash_erase(hash, mm_obj_cast(node))

typedef struct mm_trace_data_s {
	void** call_stack;
	u32 depth:8;
	u32 unused:24;
} mm_trace_data;

#define mm_trace_data_init(data, cs, cs_depth) do { \
	(data)->call_stack = (cs); \
	(data)->depth = (cs_depth); \
} while(0)

static inline mm_trace_node* mm_trace_node_find(mm_hash* hash,
	void** call_stack, u8 depth)
{
	mm_trace_data data;

	mm_trace_data_init(&data, call_stack, depth);
	return (mm_trace_node*)mm_hash_find(&hash->base, MM_TRACE_NODE, &data);
}

typedef struct mm_trace_s {
	mm_trace_node trace_node;
	mm_id_node id_node;
} mm_trace;

#define mm_trace_init(trace) do { \
	mm_trace_node_init(&(trace)->trace_node); \
	mm_id_node_init(&(trace)->id_node); \
} while(0)

#define mm_trace_tn_entry(tn) mm_list_entry(tn, mm_trace, trace_node)
#define mm_trace_in_entry(in) mm_list_entry(in, mm_trace, id_node)

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
	u8 depth)
{
	mm_trace_node* node = mm_trace_node_find(&hash->base, call_stack, depth);
	if(node)
		return mm_trace_tn_entry(node);
	return NULL;
}

static inline mm_trace* mm_trace_add(mm_trace_hash* hash, void** call_stack,
	u8 depth)
{
	mm_trace* trace = mm_trace_alloc(&hash->base);
	if(trace) {
		mm_trace_node_init(&trace->trace_node);
		mm_trace_node_set(&trace->trace_node, call_stack, depth);
		mm_trace_node_insert(&hash->base, &trace->trace_node);

		mm_id_node_init(&trace->id_node, hash->cur_id);
		mm_id_node_insert(&hash->base, &trace->id_node);
	}
	return trace;
}

#define mm_trace_do_del(hash, trace) do { \
	mm_trace_node_erase(&(hash)->base, &(trace)->trace_node); \
	mm_id_node_erase(&(hash)->base, &(trace)->id_node); \
	mm_trace_free(&(hash)->base, trace); \
} while(0)

static inline void mm_trace_del(mm_trace_hash* hash, void** call_stack,
	u8 depth)
{
	mm_trace* trace = mm_trace_find(hash, call_stack, depth);
	if(trace)
		mm_trace_do_del(hash, trace);
}

static inline mm_trace* mm_trace_find_by_id(mm_trace_hash* hash, mm_id_t id)
{
	mm_id_node* node = mm_id_node_find(&hash->base, id);
	if(node)
		return mm_trace_in_entry(node);
	return NULL;
}

static inline void mm_trace_del_by_id(mm_trace_hash* hash, mm_id_t id)
{
	mm_trace* trace = mm_trace_find_by_id(hash, id);
	if(trace)
		mm_trace_do_del(hash, trace);
}

#ifdef __cplusplus
extern "C" {
#endif

u32 mm_trace_node_hcode(mm_trace_node* node);
u32 mm_trace_data_hcode(mm_trace_data* data); 
int mm_trace_node_cmp(mm_trace_node* node, u8 type,
	const mm_trace_data* data);

const mm_obj_ops* mm_trace_node_ops();

#ifdef __cplusplus
}
#endif


#endif
