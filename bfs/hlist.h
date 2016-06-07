struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **prev;
};

static inline void __hlist_add(struct hlist_node *new, struct hlist_head *head)
{
	struct hlist_node *first = head->first;
	if (first) {
		first->prev = &new->next;
	}
	new->prev = &head->first;
	new->next = first;
	first = new;
	
	return;
}

static inline void hlist_add(struct hlist_node *new, struct hlist_head *head)
{
	__hlist_add(new, head);
}

static inline void hlist_del(struct hlist_node *node)
{
	struct hlist_node *next = node->next, **prev = node->prev;

	if (*prev)
	*prev = next;

	next->prev = prev;
	return;
}
