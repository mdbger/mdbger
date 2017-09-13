#ifndef MM_SYS_H
#define MM_SYS_H

typedef struct mm_sys_ops_s {
	void* (*alloc)(size_t);
	void (*free)(void*);
} mm_sys_ops;

#ifdef __cplusplus
extern "C" {
#endif

const mm_sys_ops* mm_sys_ops_os();
const mm_sys_ops* mm_sys_ops_dft();

void* mm_alloc(size_t size);
void mm_free(void* ptr);

void* mm_calloc(size_t size);
void* mm_realloc(void* ptr, size_t size);

#ifdef __cplusplus
}
#endif

#define mm_os_alloc(size) mm_sys_ops_os()->alloc(size)
#define mm_os_free(ptr) mm_sys_ops_os()->free(ptr)

#endif
