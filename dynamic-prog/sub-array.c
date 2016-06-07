#include <stdio.h>
#include <string.h>

#if 0

int* sub_array(int start, int index, int *result, int *result_size)
{
	int *sub_array;
	if (index == 0)  {
		sub_array = malloc(sizeof(int) * 1);
		sub_array[0] = start;
		*result_size = 1;
		return sub_array;
	}

	index--;

	for(i = 0; i < *result_size; i++) {
	}

	
}
#endif

#define grt(x, y) ((x > y) ? x : y)

int main(int argc, char **argv)
{

	int arr[] = {2, -1, 2, 3, 4, -5};
	int i = 0, size = 0, max = 0, sum = 0, grt_now = 0;

	size = sizeof(arr)/sizeof(arr[0]);

	for(i = 0; i < size; i++) {
		sum += arr[i];
		grt_now = grt(sum, arr[i]);
		max = grt(grt_now, max);
	}

	printf("Manximum %d\n", max);
}
