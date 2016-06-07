static inline void list_replace(struct list_head *old, struct list_head *new)
{

	struct list_head *next = old->next, *prev = old->prev;
	new->next = old->next;
	new->prev = old->prev;
	next->prev = new;
	prev->next = new;
}
