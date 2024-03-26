#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%2d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%2d] ", root->data);
		inorder(root->right);
	}
}

void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%2d] ", root->data);
	}
}

void Init(TreeNode* n, int data, TreeNode* left, TreeNode* right) {
	n->data = data;
	n->left = left;
	n->right = right;
}

void main() {
	TreeNode* n1, * n2, * n3, * n4, * n5, * n6;

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

	printf("중위순회 = ");
	inorder(n6);
	printf("\n");

	printf("전위순회 = ");
	preorder(n6);
	printf("\n");

	printf("후위순회 = ");
	postorder(n6);
	printf("\n");

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);

	return 0;
}