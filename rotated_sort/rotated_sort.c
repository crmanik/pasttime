#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])
int num[] = {23, 28, 10, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void swap(int *num, int i, int j)
{
	int tmp = num[i];
	num[i] = num[j];
	num[j] = tmp;
	return;
}

int partition(int *num, int s, int e)
{
	int p = s, i = s+1, j = s+1;

	for(i = s+1; i < e; i++) {
		if (num[p] > num[i]) {
			swap(num, i, j);
			j++;
		}
	}
	swap(num, p, j-1);
	return j-1;
}

int* sort(int *num, int s, int e)
{
	int m;

	if (s < e) {
		m = partition(num, s, e);
		sort(num, s, m);
		sort(num, m+1, e);
	}
}

int rotate(int n) 
{
	int size = ARRAY_SIZE(num), i = 0, j = 0, k = 0, last = 0;
	int N = size - 1;

	for (i = 0; i < n; i++) {
			last = num[N];
		for (j = N, k = N-1; j > 0; j--, k--) { 	
			num[j] = num[k];
		}
		num[0] = last;
	}
	return 0;
}

void print_array(void) {
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(num); i++) {
		printf(" %d ", num[i]);
	}
	printf("\n");

	return;
}

int bst(int *a, int s, int e, int find)
{
	int mid = (s + e)/2, found = -1;

	if (s <= e) {
		if (find == a[mid]) {
			return mid;
		}
		if ((a[s] <= a[mid]) && (a[e] >= a[mid])) {
			if ((find <= a[mid]) && (find >= a[e]))
				return bst(a, s, mid-1, find);
			return bst(a, mid+1, e, find);
		} else {
			found = bst(a, mid+1, e, find);
			if (found < 0) {
				found = bst(a, s, mid-1, find);
			}
		}
	}
	return found;
}

#if 0
int bst(int *arr, int l, int h, int key)
{
	 if (l > h) return -1;
 
    	int mid = (l+h)/2;
    	if (arr[mid] == key) return mid;
 
    	/* If arr[l...mid] is sorted */
    	if (arr[l] <= arr[h])
    	{
        	/* As this subarray is sorted, we can quickly
           	check if key lies in half or other half */
        	if (key >= arr[l] && key <= arr[mid])
           		return bst(arr, l, mid-1, key);
 
        	return bst(arr, mid+1, h, key);
    	}
 
    	/* If arr[l..mid] is not sorted, then arr[mid... r]
       	must be sorted*/
    	if (key >= arr[mid] && key <= arr[h])
        	return bst(arr, mid+1, h, key);
 
    	return bst(arr, l, mid-1, key);
}
#endif
int search(int n)
{
	int size = ARRAY_SIZE(num), index = 0;
	if ((index = bst(num, 0, size, n)) < 0) {
		printf("Unable to find %d\n", n);
		return 0;
	}	

	printf("Found %d at %d\n", n, index);
	return 0;
}

int main(int argc, char **argv)
{
	int i = atoi(argv[1]);
	int size = ARRAY_SIZE(num);
	print_array();
	sort(num, 0, size);
	print_array();
	rotate(7);	
	print_array();
	search(i);
	return 0;
}
