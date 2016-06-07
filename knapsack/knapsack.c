#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *garray;

int* merge(int *arr, int *a, int *b, int len_a, int len_b)
{
	int len = len_a + len_b;
	int i = 0, j = 0, k = 0;

	for (k = 0; k < len; k++) {
		if (len_a == i) {
			garray[k] = b[j];
			j++;
			continue;
		}

		if (len_b == j) {
			garray[k] = a[i];
			i++;
			continue;
		}

		if (a[i] <= b[j]) {
			garray[k] = a[i];
			i++;
			continue;
		}

		if (b[j] <= a[i]) {
			garray[k] = b[j];
			j++;
			continue;
		}
	}

	for (k = 0; k < len; k++) {

		arr[k] = garray[k];
		
	}

	return arr;


}

int* sort(int *arr, int len)
{
	int *a, *b, *c;
	int temp;

	if (len <= 1) {
		return arr;
	}

	temp = (len >> 1);
	
	a = sort(arr, temp);
	b = sort(arr+temp, (len - temp));
	c = merge(arr, a, b, temp, len - temp);

	return c;

	
}

int find_near_max(int *array, int array_size, int max_val)
{
	int temp = 0, *weight;
	int j = 0, val = 0, i = 0;

	garray = malloc(sizeof(int) * array_size);
	sort(array, array_size);

	weight = malloc(sizeof(int) * max_val+1);
	memset(weight, 0, (sizeof(int) * max_val+1));
	for (i = 0; i < max_val+1; i++) {
		for(j = 0; j < array_size; j++) {
			if (i < array[j]) {
				//weight[i] = 0;
				continue;
			}
			temp = array[j] + weight[i - array[j]];
			weight[i] = ((weight[i] > temp) ? weight[i] : temp);
		}
	}
	temp = weight[max_val];
	free(weight);
	return temp;

	
}

int main(int argc, char **argv)
{
	int num_test_cases, *result;
	int i = 0, j = 0;
	int *array, array_size, max_val;

	scanf("%d\n", &num_test_cases);

	result = malloc(num_test_cases * sizeof(int));

	for(i = 0; i < num_test_cases; i++) {
		scanf("%d %d\n", &array_size, &max_val);
		array = malloc(sizeof(int)*array_size);
		for(j = 0; j < array_size; j++) {
			scanf("%d", &array[j]);
		}

		result[i] = find_near_max(array, array_size, max_val);
		free(array);
	}


	for(i = 0; i < num_test_cases; i++) {
		printf("%d\n", result[i]);
	}

	return 0;
}
