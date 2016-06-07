#include <stdio.h>
#include <string.h>

int **distance;

int min(int a, int b, int c)
{
	if (a > b) {
		if (b > c) {
			return c;
		} else  {
			return b;
		} 
	} else if (a > c) {
		return c;
	} else {
		return a;	
	}

	printf("Why a %d b %d c %d\n", a, b, c);

	return 0;
}

int edit_distance(char *s, char *t, int n, int m)
{
	int i = n, j = m, size = 0;
	int a = 0, b = 0, diff = 0, c = 0;

	if (n == 0 && m == 0)
		return 0;

	if (n == 0) {
		distance[n][m] = m;
		return m;
	}
	if (m == 0) {
		distance[n][m] = n;
		return n;
	}
        
	diff = ((s[n] == t[m]) ? 0 : 1);

	a = edit_distance(s, t, n-1, m);
	b = edit_distance(s, t, n, m-1);
	c = edit_distance(s, t, n-1, m-1);

	distance[n][m] = min(1+a, 1+b, diff+c);

	return distance[n][m];

}

int main(int argc, char **argv)
{
	int i, j, n, m;
	char *str1, *str2;
	int *row;

	str1 = argv[1];
	str2 = argv[2];

	n = strlen(str1);
	m = strlen(str2);

	printf("str1 %s str2 %s n %d m %d\n", str1, str2, n, m);


	distance = malloc(sizeof(int *) * n);

	for(i = 0; i < n; i++) {
		row = malloc(sizeof(int) * m);
		memset(row, 0, sizeof(int) * m);
		distance[i] = row;
	}

	edit_distance(str1, str2, n-1, m-1);

	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			printf(" %d ", distance[i][j]);
		}
		printf("\n");
	}

	return 0;

}
