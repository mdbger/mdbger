#ifndef MM_TYPES_H
#define MM_TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#ifdef __LP64__
typedef unsigned long u64;
#else
typedef unsigned long long u64;
#endif

typedef u64 mm_addr_t;

#endif
