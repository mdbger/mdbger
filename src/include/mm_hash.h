#ifndef MM_HASH_H
#define MM_HASH_H

#include "mm_obj.h"
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

#endif
