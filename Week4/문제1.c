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

void insert_node(TreeNode** root, element key) {		//메모리를 함수 내에서 할당받기 때문에 이중포인터 사용
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

	n = (TreeNode*)malloc(sizeof(TreeNode));
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

void delete_node(TreeNode** root, element key) {
	TreeNode* t, * p, * child, * succ, * succ_p;

	p = NULL;
	t = *root;

	while (t != NULL && compare(t->key, key) != 0) {
		//key값이 일치하지 않는다.
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;
	}

	//case 1 t== NULL 검색실패, 삭제하려는 key은 존재하지 않는다.
	if (t == NULL) {
		printf("삭제하려는 데이터가 없습니다.\n");
		return;
	}
	//case 2 key가 트리에 존재하는 경우
	//case 2-1 t의 child node가 없는 경우(leaf node)
	if (t->left == NULL && t->right == NULL) {
		//case 2-1-1 parent node가 있는 경우
		if (p != NULL)
		{
			//case 2-1-1-1 t가 p의 왼쪽 child인 경우
			if (p->left == t)
				p->left == NULL;
			//case 2-1-1-2 t가 p의 오른쪽 child인 경우
			else
				p->right == NULL;
		}
		//case 2-1-2 parent node가 없는 경우 -> 트리에 유일한 노드가 t인 경우
		else
			*root = NULL;
	}
	//case 2-2 t의 child node가 한 개만 있는 경우
	else if (t->left == NULL || t->right == NULL) {
		//손주 노드의 포인터를 얻는다.
		child = (t->left != NULL) ? t->left : t->right;

		//case 2-2-1 parent node가 있는 경우
		if (p != NULL) {
			//case 2-2-1-1 t가 parent의 왼쪽 자식인 경우
			if (p->left == t)
				p->left = child;
			//case 2-2-1-2 t가 parent의 오른쪽 자식인 경우
			else
				p->right = child;
		}
		//case 2-2-2 parent node가 없는 경우
		else {
			*root = child;
		}
	}
	//case 2-3 t의 left, right node가 모두 존재하는 경우
	else {
		//오른쪽 서브트리에서 후계자를 선정
		succ_p = t;
		succ = t->right;	//left가 되든 right가 되든 상관없다?

		//오른쪽 서브트리에서 가장 작은 노드를 찾자
		//오른쪽 서브트리에서 가장 작은 값은 가장 왼쪽 끝에 있는 노드다
		//이진탐색트리이기 때문에 가능한 조건
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		t->key = succ->key;
		t = succ;
	}

	free(t);
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
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			delete_node(&root, e);
			printf("단어 %s 삭제 완료\n", e.word);
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