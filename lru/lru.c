#include "hash.h"

struct data {
	int val;
	struct hlist_node node;
};

static INIT_HLIST(myhash, 5);

int main(int argc, char **argv)
{

	int i = 0, index = 0;
	struct data *ptr;
	struct hlist_node *pos = NULL, *temp = NULL;

	for(i = 0; i < 32; i++) {
		index = hash(i, 5);
		printf("Adding %d at Index  %d\n", i, index);
		ptr = (struct data *)malloc(sizeof(struct data));
		ptr->val = i;
		hlist_add(&ptr->node, &myhash[index]);
	}

	for(i = 0; i < 16; i++) {
		index = hash(i, 5);

		if (myhash[index].first != NULL) {

			printf("\nDeleting data from Index: %d\n", index);

			//hlist_for_each_entry_safe(pos, temp, &myhash[index]) {
			for(pos = myhash[index].first; pos && ({temp = pos->next; 1;}); pos = temp) {

				ptr = container_of(pos, struct data, node);
				printf(" %d ", ptr->val);
				hlist_del(pos);
				pos = NULL;
				free(ptr);
			
			}
		
		}
		myhash[index].first = NULL;
	}

	for(i = 0; i < 32; i++) {
		index = hash(i, 5);

		if (myhash[index].first != NULL) {

			printf("\nRetriving data from Index: %d\n", index);

			//hlist_for_each_entry_safe(pos, temp, &myhash[index]) {
			for(pos = myhash[index].first; pos && ({temp = pos->next; 1;}); pos = temp) {

				ptr = container_of(pos, struct data, node);
				printf(" %d ", ptr->val);
			
			}
		
		}
	}

	return 0;

}



