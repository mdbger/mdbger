#include <mm_sys.h>

static s_mm_sys_ops_os = { 0 };

void mm_sys_init()
{
	static sys_inited = 0;
	if(!sys_inited) {
		mm_sys_ops_load(&s_mm_sys_ops_os);
		sys_inited = 1;
	}
}

void* mm_alloc(size_t size)
{
	return mm_os_alloc(size);
}

void mm_free(void* ptr)
{
}

void* mm_calloc(size_t size)
{
}

void* mm_realloc(void* ptr, size_t size)
{
}

static s_mm_sys_ops_dft = {
}
