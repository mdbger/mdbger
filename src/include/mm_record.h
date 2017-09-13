#ifndef MM_RECORD_H
#define MM_RECORD_H

typedef struct mm_record_s {
	mm_addr_t addr;
	size_t size;
	u16 act_type;
	u16 unused;
	mm_id_t trace_id;
} mm_record;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
