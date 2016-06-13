#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define err(str, var...) printf("%s:%d" str, __FUNCTION__, __LINE__, ## var)
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
#define MAX(x, y) ( (x > y) ? x : y)

#define ERROR -1
#define OK 0

int global_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

typedef struct node {
	int val;
	struct node *right;
	struct node *left;
	struct node *parent;
	struct list_head list;
} node_t;	

node_t *head;

node_t* create_binary_tree(int *a, int start, int end)
{
	node_t *tmp = NULL;
	int mid = 0;

	if (start <= end) {
		mid = (start+end)/2;
		tmp = malloc(sizeof(*tmp));
		if (tmp == NULL) {
			err("Memory allocation failed\n");
			return NULL;
		}
		tmp->val = a[mid];
		//printf("val %d mid %d\n", tmp->val, mid);

		tmp->left = create_binary_tree(a, start, mid-1);
		tmp->right = create_binary_tree(a, mid+1, end);
	}

	return tmp;
}

void print_binary_tree(node_t *tmp)
{
	if (tmp == NULL) {
		return; 
	}

	printf(" %d ", tmp->val);
	print_binary_tree(tmp->left);
	print_binary_tree(tmp->right);
	return;
}

int tree_depth(node_t *tmp)
{
	if (tmp == NULL)
		return 0;
	return (1 + MAX(tree_depth(tmp->right), tree_depth(tmp->left))); 
}

int bfs(node_t *tmp, struct list_head *list_array, int depth)
{
	int level = 0;
	struct list_head *local, *pos;
	node_t *ptr;

	list_add(&list_array[level], &tmp->list); 
	local = &list_array[level];

	while(level < depth) {
		level++;
		list_for_each_entry(pos, local) {
			ptr = container_of(pos, node_t, list);
			if (ptr->left != NULL) {
				list_add(&list_array[level], &ptr->left->list);
			}

			if (ptr->right != NULL) {
				list_add(&list_array[level], &ptr->right->list);
			}
		}

		local = &list_array[level];
	}

	return 0;
}

int print_list_array(struct list_head *a, int depth)
{
	int level = 0;
	struct list_head *pos, *head;
	node_t *ptr;

	head = &a[level];

	while (level < depth) {
		list_for_each_entry(pos, head) {
			ptr = container_of(pos, node_t, list);
			printf(" %d ", ptr->val);
		}
		level++;
		printf("\n");
		head = &a[level];
	}

	return 0;
	
}

int main(int argc, char **argv)
{
	node_t *tmp;
	int depth = 0;
	int size = ARRAY_SIZE(global_array), i = 0;
	struct list_head *list_array;

	tmp = create_binary_tree(global_array, 0, size-1);
//	print_binary_tree(tmp);
	depth = tree_depth(tmp);

	list_array = malloc(sizeof(struct list_head)*depth);

	for(i = 0; i < depth; i++) {
		INIT_LIST_HEAD(&list_array[i]);
	}

	bfs(tmp, list_array, depth);

	print_list_array(list_array, depth);

	return 0;
}
