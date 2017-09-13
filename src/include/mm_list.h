#ifndef MM_LIST_H
#define MM_LIST_H

#include "mm_def.h"

typedef struct mm_list_s {
	struct mm_list_s* next;
	struct mm_list_s* prev;
} mm_list_t;

#define mm_list_init(list) do { \
	(list)->prev = (list); \
	(list)->next = (list); \
} while(0)

#define mm_list_empty(list) ((list)->next == (list))
#define mm_list_entry(p, T, M) container_of(p, T, M)
#define mm_list_unlinked(list) mm_list_empty(list)

static inline void mm_list_insert(mm_list_t* list, mm_list_t* prev,
	mm_list_t* next)
{
	list->prev = prev;
	list->next = next;

	next->prev = list;
	prev->next = list;
}

static inline void mm_list_erase(mm_list_t* prev, mm_list_t* next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void mm_list_join(mm_list_t* list, mm_list_t* l)
{
	mm_list_t *next = l->next, *prev = l->prev;

	if(mm_list_empty(l))
		return;
	list->prev->next = next;
	next->prev = list->prev;
	list->prev = prev;
	prev->next = list;

	mm_list_init(l);
}

#define mm_list_add(list, n) mm_list_insert(n, list, (list)->next)
#define mm_list_add_head(list, n) mm_list_insert(n, (list)->prev, list)
#define mm_list_del(list) do { \
	mm_list_erase((list)->prev, (list)->next); \
	mm_list_init(list); \
} while(0)

#define mm_list_for_each(pos, head) \
	for((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)

#define mm_list_for_each_safe(pos, n, head) \
	for((pos) = (head)->next, (n) = (pos)->next; (pos) != (head); \
		(pos) = (n), (n) = (pos)->next)

#define mm_list_for_each_prev(pos, head) \
	for((pos) = (head)->prev; (pos) != (head); (pos) = (pos)->prev)

#endif
