#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef struct {
	int key;
	char name[MAX_LEN];
}element;

typedef struct {
	int heap_size;
	element heap[MAX_LEN];
}HeapType;

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//루트노드까지 오지 않았고, 요소의 키값이 부모노드의 키값보다 클 경우 반복
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
			child++;

		if (temp.key <= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	printf(">> 손님 (%s) 퇴장\n", item.name);

	for (int k = 1; k < h->heap_size; k++) {
		h->heap[k].key--;
	}
	return item;
}

void inorder(HeapType* h, int key) {
	if (key <= h->heap_size) {
		inorder(h, key * 2);
		printf("%d - %s\n", h->heap[key].key, h->heap[key].name);
		inorder(h, (key * 2) + 1);
	}
}

int main() {
	FILE* fp;
	element tmp;
	char cmd;
	int count = 1;
	HeapType heap;
	init(&heap);

	fp = fopen("data2.txt", "r");
	if (fp == NULL)
		exit(1);

	while (!feof(fp)) {
		fscanf(fp, "%c", &cmd);

		switch (cmd) {
		case 'i':
			fscanf(fp, "%s", &tmp.name);
			printf(">> 손님 (%s) 입장\n", tmp.name);
			tmp.key = count;
			insert_min_heap(&heap, tmp);
			inorder(&heap, 1);
			count++;
			break;
		case 'o':
			delete_min_heap(&heap);
			count--;
			inorder(&heap, 1);
			break;
		}
	}

	fclose(fp);
}