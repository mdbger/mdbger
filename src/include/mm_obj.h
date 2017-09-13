#ifndef MM_OBJ_H
#define MM_OBJ_H

#include "mm_list.h"

enum {
	MM_ID_NODE = 1,
	MM_TRACE_NODE,
	MM_OBJ_TYPE_MAX,
};

#define MM_OBJ_HDR \
	mm_list list; \
	u32 type:8; \
	u32 rev:24

typedef struct mm_obj_s {
	MM_OBJ_HDR;
} mm_obj;

#define mm_obj_init(obj, obj_type) do { \
	mm_list_init(&(obj)->list); \
	(obj)->type = (obj_type); \
	(obj)->rev = 0; \
} while(0)

#define mm_obj_entry(pos) mm_list_entry(pos, mm_obj, list)
#define mm_obj_ptr(obj) ((mm_obj*)(obj))
#define mm_obj_cast(obj) \
	((obj)->type && (obj)->type < MM_OBJ_TYPE_MAX ? mm_obj_ptr(obj) : NULL)

#endif
