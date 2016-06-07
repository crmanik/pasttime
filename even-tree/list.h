struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

#define LIST_HEAD(x) struct list_head x = {&x, &x}

#define offset_of(type, ele) (size_t)(&((type *)0)->ele)
#define container_of(ptr, type, ele) (type *)((char *)ptr - offset_of(type, ele))

static inline void INIT_LIST_HEAD(struct list_head *x)
{
	x->next = x;
	x->prev = x;
	return;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
	new->next = next;
	new->prev = prev;
	next->prev = new;
	prev->next = new;
	return;
}

static inline void list_add(struct list_head *head, struct list_head *new)
{
	__list_add(new, head, head->next);
	return;
}

#define list_for_each_entry(pos, head) for(pos = (head)->next; pos != head; pos = pos->next)
