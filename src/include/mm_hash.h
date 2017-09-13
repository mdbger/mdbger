#ifndef MM_HASH_H
#define MM_HASH_H

#include "mm_obj_ops.h"
#include "mm_sys.h"

typedef struct mm_bucket_s {
	mm_list head;
} mm_bucket;

#define mm_bucket_init(bucket) do { \
	mm_list_init(&(bucket)->head); \
} while(0)

#define mm_bucket_insert(bucket, obj) \
	mm_list_add(&(bucket)->head, &(obj)->list)

#define mm_bucket_erase(bucket, obj) mm_list_del(&(obj)->list)

static inline mm_obj* mm_bucket_find(mm_bucket* bucket, u8 type,
	const void* data)
{
	mm_list* pos;
	mm_obj* obj;
	const mm_obj_ops* ops = mm_obj_get_ops(type);

	mm_list_for_each(pos, &bucket->head) {
		obj = mm_obj_entry(pos);
		if(ops->cmp(obj, type, data) == 0)
			return obj;
	}

	return NULL;
}

typedef struct mm_hash_s {
	mm_bucket* bucket;
	size_t size;
	const mm_sys_ops* ops;
} mm_hash;

#define mm_hash_init(hash) do { \
	(hash)->bucket = NULL; \
	(hash)->size = 0; \
	(hash)->ops = mm_sys_ops_dft(); \
} while(0)

#define mm_hash_bucket(hash, hcode) \
	((hash)->bucket+((hcode)%(hash)->size))

static inline int mm_hash_init_bucket(mm_hash* hash, size_t size)
{
	size_t i;

	hash->bucket = hash->ops->alloc(sizeof(mm_bucket)*size);
	if(!hash->bucket)
		return MM_NOMEM;

	for(i = 0; i < size; i ++)
		mm_bucket_init(hash->bucket+i);
	hash->size = size;

	return 0;
}

static inline void mm_hash_fini_bucket(mm_hash* hash)
{
	hash->ops->free(hash->bucket);
	hash->bucket = NULL;
	hash->size = 0;
}

static inline mm_obj* mm_hash_find(mm_hash* hash, u8 type, const void* data)
{
	const mm_obj_ops* ops = mm_obj_get_ops(type);
	u32 hcode = ops->data_hcode(type, data);
	return mm_bucket_find(mm_hash_bucket(hash, hcode), type, data);
}

static inline mm_bucket* mm_hash_obj_bucket(mm_hash* hash, mm_obj* obj)
{
	const mm_obj_ops* ops = mm_obj_get_ops(mm_obj_type(obj));
	u32 hcode = ops->hcode(obj);
	return mm_hash_bucket(hash, hcode);
}

static inline void mm_hash_insert(mm_hash* hash, mm_obj* obj)
{
	mm_bucket* bucket = mm_hash_obj_bucket(hash, obj);
	mm_bucket_insert(bucket, obj);
}

static inline void mm_hash_erase(mm_hash* hash, mm_obj* obj)
{
	mm_bucket* bucket = mm_hash_obj_bucket(hash, obj);
	mm_bucket_erase(bucket, obj);
}

#endif
