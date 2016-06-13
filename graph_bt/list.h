struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

#define offset_of(type, name) (size_t)(&((type *)0)->name)
#define container_of(pos, type, name) (type *)((char *)pos - offset_of(type, name))

static inline void INIT_LIST_HEAD(struct list_head *ptr)
{
	ptr->next = ptr;
	ptr->prev = ptr;
	return;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
	prev->next = new;
	next->prev = new;
	new->next = next;
	new->prev = prev;
}

static inline void list_add(struct list_head *head, struct list_head *new)
{
		__list_add(new, head->prev, head);
		return;
}

#define list_for_each_entry(pos, head) for(pos = (head)->next; pos != head; pos = pos->next)
