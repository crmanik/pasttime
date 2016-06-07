#include <stdio.h>
#include <stdlib.h>

#define GOLDEN_NUM 0x9e370001

static inline int hash(int key, int bits)
{
	unsigned long long index = key * GOLDEN_NUM;

	return (index >> (32 - bits));
}

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};

struct hlist_head {
	struct hlist_node *first;
};

#define INIT_HLIST(name, bits) struct hlist_head name[(1 << bits)]  = {[0 ... ((1 << bits) -1)] = NULL}

static inline void __hlist_add(struct hlist_node *new, struct hlist_head *head)
{
	struct hlist_node *first = head->first;

	new->next = first;
	new->pprev = &first;
	head->first = new;
	if (first) 
	first->pprev = &new->next;
	printf("new next %p new pprev %p first pprev %p\n", new->next, new->pprev, first ? first->pprev: 0);
	return;
}
	

static inline void hlist_add(struct hlist_node *new, struct hlist_head *head)
{
	__hlist_add(new, head);
	return;
}

static inline void hlist_del(struct hlist_node *node)
{
	struct hlist_node *next = node->next;
	struct hlist_node **pprev = node->pprev;
	if (node->pprev) {	
	*pprev = next;
	if (next)
	next->pprev = pprev;
	printf("*pprev %p next %p\n", *pprev, next);

	node->next = NULL;
	node->pprev = NULL;	
	}

	return;
}

#define hlist_for_each_entry_safe(pos, temp, head) for(pos = (head)->first, temp = pos->next; pos != NULL; pos = temp, temp = pos->next)
#define offset_of(type, var) (size_t)(&((type *)0)->var)
#define container_of(ptr, type, var) (type *)((char *) ptr - offset_of(type, var))
