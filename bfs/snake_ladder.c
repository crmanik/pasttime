#include <stdio.h>
//#include "hlist.h"

int ladder[] = { [0 ... 99] = 0};
int snake[] = { [0 ... 99] = 0};

int main(int argc, char **argv)
{
	int test = 0, j = 0, temp = 0, temp1 = 0;
	int num_ladder = 0, num_snake = 0, i = 0;

	scanf("%d", &test);

	while (i < test) {
		scanf("%d", &num_ladder);

		while(j < num_ladder) {
			scanf("%d %d", &temp, &temp1);
			ladder[temp] = temp1;
			j++;
		}

		j = 0;

		scanf("%d", &num_snake);

		while(j < num_snake) {
			scanf("%d %d", &temp, &temp1);
			snake[temp] = temp1;
			j++;
		}

		i++;

	}
}
