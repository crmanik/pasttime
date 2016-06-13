#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int num = atoi(argv[1]), flag = 0;

	int tmp = num, mask = 0, count = 0;

	while(tmp) {
		count++;
		tmp >>= 1;
	}	

	count--;

	mask = (1 << count);
	while(mask) {

		if (num & mask) {
			if (flag) {
				printf("+");
			}
			printf("2^%d ", count);
			flag = 1;
		}

		mask >>= 1; 
		count--;
	}

	printf("\n");

	return 0;
}
