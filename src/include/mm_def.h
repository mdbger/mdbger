#ifndef MM_STDDEF_H
#define MM_STDDEF_H

#ifndef NULL
#define NULL 0
#endif

#define offsetof(type, member) ((size_t)&((type*)0)->member)
#define container_of(ptr, type, member) \
	((type *)((char *)(ptr)-offsetof(type, member)))

#define mm_int_cmp(a, b) ((int)(a)-(int)(b))

#endif
