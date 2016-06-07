#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
int c[5];



int* merge(int *a, int *b, int len_a, int len_b)
{
	int len = len_a + len_b;
	int i = 0, j = 0, k = 0;

	if (a == NULL || b == NULL)
		return NULL;

	for(k = 0; k < len; k++) {
		if (i == len_a) {
			c[k] = b[j];
			j++;
			continue;
		}
	
		if (j == len_b) {
			c[k] = a[i];
			i++;
			continue;
		}

		if (a[i] < b [j]) {
			c[k] = a[i];
			i++;
			continue;
		}

		if (b[j] < a[i]) {
			c[k] = b[j];
			j++;
			continue;
		}
	}

	for(k = 0; k < len; k++) {
		a[k] = c[k];
		
	}

	return a;
}

int* merge_sort(int *arr, int len)
{
	int *a, *b, *d, temp = 0;
	if (len <= 1) {
		return arr;
	}

	temp = (len >> 1);

	a = merge_sort(arr, temp);
	b = merge_sort(arr+temp, (len - temp));
	d = merge(a, b, temp, (len - temp));
	return d;
}

int main(int argc, char **argv)
{
	int *d, i;

	int a[] = {5,4,3,2,1,0};
	int *c;
	for (i = 0; i < ARRAY_SIZE(a); i++) {
		printf(" %d ", a[i]);
	}
	printf("\n");
	merge_sort(a, ARRAY_SIZE(a));
	for (i = 0; i < ARRAY_SIZE(a); i++) {
		printf(" %d ", a[i]);
	}
	printf("\n");
	return 0;
}
