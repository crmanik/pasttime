#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define err(fmt, args...) printf("%s:%d" fmt,  __FUNCTION__, __LINE__, ## args)
#define ERROR -1
#define OK 0

int *sorted_intern;

int choco_count[] = {1, 2, 5};

int* merge(int *c, int *a, int *b, int len_a, int len_b)
{

	int len = len_a + len_b;
	int i = 0, j = 0, k = 0;

	for (i = 0; i < len; i++) {
		if (k == len_a) {
			sorted_intern[i] = b[j];
			j++;
			continue;
		}

		if (j == len_b) {
			sorted_intern[i] = a[k];
			k++;
			continue;
		}

		if (a[k] <= b[j]) {
			sorted_intern[i] = a[k];
			k++;
			continue;
		}
	
		if (b[j] <= a[k]) {
			sorted_intern[i] = b[j];
			j++;
			continue;
		}
	}

	for(i = 0; i < len; i++) {
		c[i] = sorted_intern[i];
	}


	return c;
	
}

int* merge_sort(int *intern, int len)
{
	int mid, *a, *b, *c = intern;
	if (len > 1) {
		mid = len >> 1;
		a = merge_sort(intern, mid);
		b = merge_sort(intern+mid, len-mid);
		c = merge(intern, a, b, mid, len-mid);
	}

	return c;
}

int find_min_choco(int sub)
{
	int min = 0, j = 2;
	int tmp = sub;

	while(tmp) {
		printf("Before min %d tmp %d\n", min, tmp);
		min += tmp/choco_count[j];
		tmp %= choco_count[j];
		printf("After min %d tmp %d\n", min, tmp);
		j--;
	}
	return min;
}

int gdiff = 0;

int print_min_cycles(int *intern, int n)
{
	int sub = 0, i = 0;
	int min = 0;

	sorted_intern = (int *) malloc(sizeof(int) * n);

	merge_sort(intern, n);

	for(i = 0; i < n; i++) {
		printf(" %d ", sorted_intern[i]);
	}

	for(i = 1; i < n; i++) {
		sorted_intern[i] += gdiff;
		sub = (sorted_intern[i] - sorted_intern[i-1]);
		gdiff += sub;
		min += find_min_choco(sub);
	}

	printf("%d\n", min);

	return 0;
}

int main(int argc, char **argv)
{
	int n = 0, test_cases = 0, i = 0, j = 0;
	int *intern;

	scanf("%d", &test_cases);

	for (i = 0; i < test_cases; i++) {
		scanf("%d", &n);
		intern = malloc(sizeof(int) * n);

		if (intern == NULL) {
			err("Memory Allocation failed\n");
			return ERROR;
		}

		for(j = 0; j < n; j++) {
			scanf("%d", &intern[j]);
		}

		print_min_cycles(intern, n);
	}
}
