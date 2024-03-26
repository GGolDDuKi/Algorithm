#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES	100
#define INF				100000
#define TRUE			1
#define FALSE			0

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
	int i;
	int min, minpos;

	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}

	return minpos;
}

void print_status(GraphType* g) {
	static int step = 1;
	int i;

	printf("STEP %d : ", step++);
	printf("distance : ");

	for (i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}

	printf("\n");
	printf("found : ");
	for (i = 0; i < g->n; i++) {
		printf("%2d ", found[i]);
	}

	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;

	for (i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}

	found[start] = TRUE;
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		for (w = 0; w < g->n; w++) {
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];

		}
	}


}

int main() {
	GraphType g;
	FILE* fp;
	int i, j, x, y, a;

	fp = fopen("data1.txt", "r");

	//initialize
	for (i = 0; i < MAX_VERTICES; i++) {
		for (j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				g.weight[i][j] = 0;
			else
				g.weight[i][j] = INF;
		}
	}

	g.n = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &a);
		if (x > g.n)
			g.n = x;
		if (y > g.n)
			g.n = y;
	}
	g.n++;
	rewind(fp);

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &a);
		//무방향 그래프이기 때문에 대칭으로 만들어줌
		//방향 그래프면 대칭 X?
		g.weight[x][y] = a;
		g.weight[y][x] = a;
	}

	printf("start vertex : 0\n");
	shortest_path(&g, 0);

	fclose(fp);
	return 0;
}