#ifndef MM_OBJ_OPS_H
#define MM_OBJ_OPS_H

#include "mm_event.h"

typedef u32 (mm_obj_op_hcode)(const mm_obj*);
typedef u32 (mm_obj_op_data_hcode)(u8 type, const void* data);
typedef int (mm_obj_op_cmp)(const mm_obj*, u8 type, const void* data);

typedef struct mm_obj_ops_s {
	mm_obj_op_hcode hcode;
	mm_obj_op_data_hcode hcode;
	mm_obj_op_cmp cmp;
} mm_obj_ops;

#ifdef __cplusplus
extern "C" {
#endif

const mm_obj_ops* mm_obj_get_ops(u8 type);

#ifdef __cplusplus
}
#endif

#endif
