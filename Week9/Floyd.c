#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES	7
#define INF				100000

int weight[MAX_VERTICES][MAX_VERTICES];
int floyd[MAX_VERTICES][MAX_VERTICES];

void shortest_path(int n) {
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			floyd[i][j] = weight[i][j];
		}
	}

	printf("-1 상태\n");

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (floyd[i][j] == INF)
				printf(" |INF ");
			else
				printf("|%-4d", floyd[i][j]);
		}
		printf("\n");
	}

	for (k = 0; k < n; k++) {

	}
}

int main() {
	FILE* fp;
	int i, j, x, y, a;

	fp = fopen("data1.txt", "r");
	if (fp == NULL)
		return 0;

	for (i = 0; i < MAX_VERTICES; i++) {
		for (j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &a);

		weight[x][y] = a;
		weight[y][x] = a;
	}

	shortest_path(MAX_VERTICES);

	fclose(fp);

	return 0;
}