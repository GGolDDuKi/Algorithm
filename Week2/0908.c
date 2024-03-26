#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//스택
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p) {
	if (top < SIZE - 1)
		stack[++top] = p;
}

TreeNode* pop() {
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

//큐
#define MAX_QUEUE_SIZE 100
typedef struct QueueType {
	TreeNode* data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType* q) {
	return (q->front == q->rear);
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, TreeNode* item) {
	if (is_full(q))
		return;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

TreeNode* dequeue(QueueType* q) {
	if (is_empty(q))
		return;
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

TreeNode n1 = { 05, NULL, NULL };
TreeNode n2 = { 22, NULL, NULL };
TreeNode n3 = { 95, NULL, NULL };
TreeNode n4 = { 15, &n1, NULL };
TreeNode n5 = { 35, &n2, NULL };
TreeNode n6 = { 93, &n5, &n3 };
TreeNode n7 = { 17, &n4, &n6 };
TreeNode* root = &n7;

TreeNode t1 = { 1, NULL, NULL };
TreeNode t2 = { 4, NULL, NULL };
TreeNode t3 = { '*', &t1, &t2 };
TreeNode t4 = { 16, NULL, NULL };
TreeNode t5 = { 25, NULL, NULL };
TreeNode t6 = { '+', &t4, &t5 };
TreeNode t7 = { '+', &t3, &t6 };
TreeNode* exp = &t7;

void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%2d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(TreeNode* root) {
	if (root != NULL) {
		preorder(root->left);
		printf("[%2d] ", root->data);
		preorder(root->right);
	}
}

void inorder_iter(TreeNode* root) {
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[%2d] ", root->data);
		root = root->right;
	}
}

void postorder(TreeNode* root) {
	if (root != NULL) {
		preorder(root->left);
		preorder(root->right);
		printf("[%2d] ", root->data);
	}
}

void level_order(TreeNode* ptr) {
	QueueType q;
	init_queue(&q);

	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("[%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

int evaluate(TreeNode* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return root->data;
	else {
		int op1 = evaluate(root->left);
		int op2 = evaluate(root->right);
		printf("%2d %c %2d 을 계산합니다. \n", op1, root->data, op2);
		switch (root->data) {
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		case '*':
			return op1 * op2;
		case '/':
			return op1 / op2;
		}
	}
	return 0;
}

int main() {
	////1번
	//printf("중위순회 : ");
	//inorder(root);
	//printf("\n");
	//printf("전위순회 : ");
	//preorder(root);
	//printf("\n");
	//printf("후위순회 : ");
	//postorder(root);
	//printf("\n");

	////2번
	//printf("반복 중위 순회 : ");
	//inorder_iter(root);
	//printf("\n");

	//3번
	//printf("레벨 순회 : ");
	//level_order(root);
	//printf("\n");
	
	//4번
	printf("수식의 값은 %d 입니다.\n", evaluate(exp));

	return 0;
}