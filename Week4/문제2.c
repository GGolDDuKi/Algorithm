#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 100
typedef int element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

void insert_node(TreeNode** root, element key) {		//메모리를 함수 내에서 할당받기 때문에 이중포인터 사용
	TreeNode* t, * p;
	TreeNode* n;

	t = *root;
	p = NULL;

	while (t != NULL) {
		//if (compare(key, t->key) == 0)
		if(key == t->key)
			return;

		p = t;
		//if (compare(key, t->key) < 0)
		if(key < t->key)
			t = t->left;
		else
			t = t->right;
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL)
		return;

	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
		//if (compare(key, p->key) < 0)
		if(key < p->key)
			p->left = n;
		else
			p->right = n;
	else
		*root = n;
}

void preorder(TreeNode* root) {
	if (root) {
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int pow(int a) {
	int result = 1;
	for (int i = 0; i < a; i++) {
		result *= 2;
	}
	return result;
}

int get_height(TreeNode* root) {
	int height = 0;
	if(root != NULL){
		height = 1 +
			max(get_height(root->left),
				get_height(root->right));
	}
	return height;
}

int get_leaf_count(TreeNode* root) {
	int count = 0;
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL)
			return 1;
		else
			count = get_leaf_count(root->left) + get_leaf_count(root->right);
	}

	return count;
}

int main() {
	FILE* fp;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	int tree_height;
	int leaf_node_count;

	fp = fopen("data1.txt", "r");
	if (fp == NULL)
		return;

	while (!feof(fp)) {
		fscanf(fp, "%d", &e);
		insert_node(&root, e);
		printf("inserted %d\n", e);
	}

	preorder(root);
	printf("\n");

	tree_height = pow(get_height(root) - 1);
	leaf_node_count = get_leaf_count(root);

	if (tree_height == leaf_node_count)
		printf("완전이진트리입니다.\n");
	else
		printf("완전이진트리가 아닙니다.\n");

	fclose(fp);
}

//while (!feof(fp)) {
//	fscanf(fp, "%c", &command);
//
//	switch (command) {
//	case 'i':
//		//insert_node()
//		fscanf(fp, "%s %s", e.word, e.meaning);
//		insert_node(&root, e);
//		printf("단어 %s를 저장완료", e.word);
//		printf("\n");
//		break;
//	case 'd':
//		//delete_node()
//		fscanf(fp, "%s", e.word);
//		strcpy(e.meaning, "");
//		delete_node(&root, e);
//		printf("단어 %s 삭제 완료\n", e.word);
//		break;
//	case 's':
//		//search_node()
//		fscanf(fp, "%s", e.word);
//		strcpy(e.meaning, "");
//		tmp = search_node(root, e);
//		if (tmp != NULL) {
//			printf("\n단어 %s의 의미는 %s입니다.\n", tmp->key.word, tmp->key.meaning);
//		}
//		else {
//			printf("\n단어 %s는 사전에 없습니다.\n", e.word);
//		}
//		break;
//	case 'p':
//		//print_node()
//		display(root);
//		break;
//	case 'q':
//		fclose(fp);
//		exit(1);
//		break;
//	}
//}