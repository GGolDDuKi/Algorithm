#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 100
typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

int compare(element e1, element e2) {
	return strcmp(e1.word, e2.word);
}

void insert_node(TreeNode ** root, element key) {		//메모리를 함수 내에서 할당받기 때문에 이중포인터 사용
	TreeNode* t, * p;
	TreeNode* n;

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (compare(key, t->key) == 0)
			return;

		p = t;
		if (compare(key, t->key) < 0)
			t = t->left;
		else
			t = t->right;
	}

	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL)
		return;

	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
		if (compare(key, p->key) < 0)
			p->left = n;
		else
			p->right = n;
	else
		*root = n;
}

void display(TreeNode* root) {	//정렬 상태로 출력하기 위해 inorder 구현
	if (root != NULL) {
		display(root->left);
		printf(" -> 트리노드 (%s : %s)\n", root->key.word, root->key.meaning);
		display(root->right);
	}
}

TreeNode* search_node(TreeNode* root, element key) {
	TreeNode* p = root;

	while (p != NULL) {
		switch (compare(key, p->key)) {
		case 0:
			return p;
		case -1:
			p = p->left;
			break;
		case 1:
			p = p->right;
			break;
		}
	}
	return NULL;
}

int main() {
	FILE* fp;
	char command;	//파일에서 가져온 값을 임시로 저장할 변수
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;

	fp = fopen("data.txt", "r");
	if (fp == NULL)
		return;

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);
		
		switch (command) {
		case 'i':
			//insert_node()
			fscanf(fp, "%s %s", e.word, e.meaning);
			insert_node(&root, e);
			printf("단어 %s를 저장완료", e.word);
			printf("\n");
			break;
		case 'd':
			//delete_node()
			break;
		case 's':
			//search_node()
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			tmp = search_node(root, e);
			if (tmp != NULL) {
				printf("\n단어 %s의 의미는 %s입니다.\n", tmp->key.word, tmp->key.meaning);
			}
			else {
				printf("\n단어 %s는 사전에 없습니다.\n", e.word);
			}
			break;
		case 'p':
			//print_node()
			display(root);
			break;
		case 'q':
			fclose(fp);
			exit(1);
			break;
		}
	}
}