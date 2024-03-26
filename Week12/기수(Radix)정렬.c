#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define BUCKETS			10
#define DIGITS			3
#define MAX_QUEUE_SIZE  100

typedef int element;

typedef struct{
	element queue[MAX_QUEUE_SIZE];
	int front;
	int rear;
}QueueType;

void init(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE) == q->front;
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		printf("큐가 포화상태입니다.\n");
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q)) {
		printf("큐가 비어있습니다.\n");
	}

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void radix_sort(int list[], int n) {
	QueueType queues[BUCKETS];
	int b = 0;	//buckets
	int d = 0;	//digits
	int i = 0;
	int factor = 1;
	int x = 0;

	for (b = 0; b < BUCKETS; b++) {
		init(&queues[b]);
	}

	for (d = 0; d < DIGITS; d++) {
		printf("\nDigits : %d\n", d + 1);
		
		for (i = 0; i < n; i++) {
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		}

		for (b = i = 0; b < BUCKETS; b++) {
			printf("Bucket[%d] : ", b);

			if (is_empty(&queues[b])) {
				printf("Empty");
			}

			while (!is_empty(&queues[b])) {
				list[i] = dequeue(&queues[b]);
				printf("%d ", list[i++]);
			}
			printf("\n");
		}

		for (x = 0; x < n; x++) {
			printf("%d > ", list[x]);
		}
		printf("\n");

		factor *= 10;
	}
}

int main() {
	FILE* fp;
	int list[MAX_QUEUE_SIZE] = { 0 };
	int n = 0;
	int i = 0;

	fp = fopen("data1.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &list[n]);
		n++;
	}

	printf("정렬전 데이터\n");
	for (i = 0; i < n; i++) {
		printf("%d > ", list[i]);
	}
	printf("\n");

	printf("\n");
	printf("정렬후 데이터");
	radix_sort(list, n);
	/*for (i = 0; i < n; i++) {
		printf("%d > ", list[i]);
	}
	printf("\n");*/

	fclose(fp);
	return 0;
}