#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//////////¿øÇüÅ¥//////////
#define MAX_QUEUE_SIZE 100
typedef TreeNode* element;

typedef struct QueueType {
	element data[MAX_QUEUE_SIZE];
	int front;
	int rear;
}QueueType;

void init_queue(QueueType * q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* root) {
	QueueType q;
	init_queue(&q);
	
	if (root == NULL)
		return;

	enqueue(&q, root);

	while (!is_empty(&q)) {
		root = dequeue(&q);
		printf("[%2d] ", root->data);
		if (root->left)
			enqueue(&q, root->left);
		if (root->right)
			enqueue(&q, root->right);
	}
}

void Init(TreeNode* n, int data, TreeNode* left, TreeNode* right) {
	n->data = data;
	n->left = left;
	n->right = right;
}

int main() {
	TreeNode* n1, * n2, * n3, * n4, * n5, * n6, * root;

	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));
	n4 = (TreeNode*)malloc(sizeof(TreeNode));
	n5 = (TreeNode*)malloc(sizeof(TreeNode));
	n6 = (TreeNode*)malloc(sizeof(TreeNode));

	Init(n1, 1, NULL, NULL);
	Init(n2, 4, n1, NULL);
	Init(n3, 16, NULL, NULL);
	Init(n4, 25, NULL, NULL);
	Init(n5, 20, n3, n4);
	Init(n6, 15, n2, n5);

	root = n6;

	level_order(root);

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);

	return 0;
}