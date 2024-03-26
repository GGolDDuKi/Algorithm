#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef struct {
	int key;
	char animal[MAX_LEN];
}element;

typedef struct {
	int heap_size;
	element heap[MAX_LEN];
}HeapType;

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item) {
	int i;
	i = ++(h->heap_size);

	//루트노드까지 오지 않았고, 요소의 키값이 부모노드의 키값보다 클 경우 반복
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

void display(HeapType *h) {
	int i;

	for (i = 1; i < h->heap_size + 1; i++) {
		printf("%d : %s > ", h->heap[i].key, h->heap[i].animal);
	}
}

int main() {
	FILE* fp;
	element tmp;
	HeapType heap;
	init(&heap);

	fp = fopen("data.txt", "r");
	if (fp == NULL)
		exit(1);

	while (!feof(fp)) {
		fscanf(fp, "%d %s", &tmp.key, tmp.animal);
		printf("%d %s\n", tmp.key, tmp.animal);
		insert_max_heap(&heap, tmp);
		display(&heap);
	}

	printf("\n동물의 우선순위와 이름을 입력하시오(0: 완료)\n");

	while (1) {
		printf(">> ");
		scanf("%d", &tmp.key);

		if (tmp.key != 0) {
			scanf("%s", &tmp.animal);
			insert_max_heap(&heap, tmp);
			display(&heap);
			printf("\n");
		}
		else
			break;
	}

	fclose(fp);
}