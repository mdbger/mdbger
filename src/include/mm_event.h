#ifndef MM_EVENT_H
#define MM_EVENT_H

#include "mm_obj.h"

typedef struct mm_event_s {
	u16 type;
	u16 unused;
	mm_obj* sender;
	mm_obj* receiver;
	void* data;
	int code;
} mm_event;

#endif
