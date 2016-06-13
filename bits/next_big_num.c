#include <stdio.h>
#include <stdlib.h>

int test_bit(int n, int i)
{
	unsigned long mask;
	mask = (1 << i);
	if (n & mask) {
		return 1;
	}
	return 0;
}

int set_bit(int *n, int pos, int val)
{
	unsigned long mask;
	mask = (1 << pos);

	if (val) {
		*n |= mask;	
	} else {
		mask = ~mask;
		*n &= mask;
	}

	return *n;
}

void print_binary(int n)
{
	int i = n, mask = 0, tmp = 0;
	while (i) {
		tmp++;
		i >>= 1;
	}
	mask = (1 << tmp);
	printf("0x");
	while (mask) {
		(n & mask) ? printf("1") : printf("0");
		mask >>= 1;
			
	}
	printf("\n");
	return;
}

int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	int index = 0, i = 0;
	int num_ones = 0, set_ones = 0;
	int start = 0;
	
	//Find zero after ones
	start = num;
//	print_binary(num);
	while (!test_bit(num, index)) {
		//Traverse all zeroes	
		index++;
	}
	//Found a one
	while(test_bit(num, index)) {
		//Traverse all ones	
		index++;
		num_ones++;
	}
	//set first zero to 1
	set_bit(&num, index, 1);
	index--;
	//set previous one to 0
	set_bit(&num, index, 0);
	index--;
	num_ones--;
	//Turn off all ones and remember how many ones were turned off
	for(i = index; num_ones > 0; num_ones--,i--) {
		set_bit(&num, i, 0);
		index--;
		set_ones++;
		
	}
	i = 0;
	// Set one from the begining till we exhaust turned off ones.	
	while (set_ones) {
		if (!test_bit(num, i)) {
			set_bit(&num, i, 1);
			set_ones--;
		}
		i++;
	}
	for (i = start; i <= num; i++) {
		printf("%d: ", i);
		print_binary(i);
	}
	return 0;
}
