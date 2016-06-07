#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "list.h"

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

typedef struct _graph {
	struct list_head child;
	struct list_head parent;
	int val;
	int visited;
} graph_t;

static LIST_HEAD(graph);

static int even_tree;

graph_t * parent_node(graph_t *g, int val)
{
	struct list_head *pos;
	graph_t *ptr = NULL;
	if (g == NULL)
		return g;

	if (g->val == val)
		return g;

	list_for_each_entry(pos, &g->child) {

		ptr = container_of(pos, graph_t, parent);

		if (ptr->val == val)
			break;

		ptr = parent_node(ptr, val);
		if (ptr != NULL)
			break;
	}

	return ptr;
}

int dfs(graph_t *g)
{
	struct list_head *pos;
	graph_t *ptr;
	int count = 0, mycount = 0;

	if (g == NULL)
		return count;
	
	g->visited = 1;

	list_for_each_entry(pos, &g->child) {
		ptr = container_of(pos, graph_t, parent);
		if (!ptr->visited) {
			count = dfs(ptr);

			if (!(count%2)) {
				even_tree++;
				//count = 0;
			} else {
				mycount += count;
			}
		}
	}
	return mycount+1;
}

int create_graph(int start, int end)
{
	graph_t *g;
	graph_t *child;

	child = (graph_t *) malloc(sizeof(*child));

	child->val = end;
	INIT_LIST_HEAD(&child->child);
	child->visited = 0;

	if (graph.next == &graph) {
		g = (graph_t *)malloc(sizeof(*g));
		g->val = start;
		INIT_LIST_HEAD(&g->child);
		list_add(&graph, &g->parent);
		g->visited = 0;
	} else {
		g = container_of(graph.next, graph_t, parent);
		g = parent_node(g, start);
	}

	list_add(&g->child, &child->parent);

	return 0;

	
}

int main(int argc, char **argv)
{
	int i = 0, start = 0, end = 0;
	int vertices = 0, edges = 0;
	graph_t *g;

	scanf("%d %d\n", &vertices, &edges);

	while (i < edges-1) {
		scanf("%d %d\n", &end, &start);
		create_graph(start, end);
		i++;
	}
	g = container_of(graph.next, graph_t, parent);
	dfs(g);
	printf("%d\n", even_tree);

	return 0;
}
