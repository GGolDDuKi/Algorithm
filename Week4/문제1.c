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

void insert_node(TreeNode** root, element key) {		//�޸𸮸� �Լ� ������ �Ҵ�ޱ� ������ ���������� ���
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

void display(TreeNode* root) {	//���� ���·� ����ϱ� ���� inorder ����
	if (root != NULL) {
		display(root->left);
		printf(" -> Ʈ����� (%s : %s)\n", root->key.word, root->key.meaning);
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
		//key���� ��ġ���� �ʴ´�.
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;
	}

	//case 1 t== NULL �˻�����, �����Ϸ��� key�� �������� �ʴ´�.
	if (t == NULL) {
		printf("�����Ϸ��� �����Ͱ� �����ϴ�.\n");
		return;
	}
	//case 2 key�� Ʈ���� �����ϴ� ���
	//case 2-1 t�� child node�� ���� ���(leaf node)
	if (t->left == NULL && t->right == NULL) {
		//case 2-1-1 parent node�� �ִ� ���
		if (p != NULL)
		{
			//case 2-1-1-1 t�� p�� ���� child�� ���
			if (p->left == t)
				p->left == NULL;
			//case 2-1-1-2 t�� p�� ������ child�� ���
			else
				p->right == NULL;
		}
		//case 2-1-2 parent node�� ���� ��� -> Ʈ���� ������ ��尡 t�� ���
		else
			*root = NULL;
	}
	//case 2-2 t�� child node�� �� ���� �ִ� ���
	else if (t->left == NULL || t->right == NULL) {
		//���� ����� �����͸� ��´�.
		child = (t->left != NULL) ? t->left : t->right;

		//case 2-2-1 parent node�� �ִ� ���
		if (p != NULL) {
			//case 2-2-1-1 t�� parent�� ���� �ڽ��� ���
			if (p->left == t)
				p->left = child;
			//case 2-2-1-2 t�� parent�� ������ �ڽ��� ���
			else
				p->right = child;
		}
		//case 2-2-2 parent node�� ���� ���
		else {
			*root = child;
		}
	}
	//case 2-3 t�� left, right node�� ��� �����ϴ� ���
	else {
		//������ ����Ʈ������ �İ��ڸ� ����
		succ_p = t;
		succ = t->right;	//left�� �ǵ� right�� �ǵ� �������?

		//������ ����Ʈ������ ���� ���� ��带 ã��
		//������ ����Ʈ������ ���� ���� ���� ���� ���� ���� �ִ� ����
		//����Ž��Ʈ���̱� ������ ������ ����
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
	char command;	//���Ͽ��� ������ ���� �ӽ÷� ������ ����
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
			printf("�ܾ� %s�� ����Ϸ�", e.word);
			printf("\n");
			break;
		case 'd':
			//delete_node()
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			delete_node(&root, e);
			printf("�ܾ� %s ���� �Ϸ�\n", e.word);
			break;
		case 's':
			//search_node()
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			tmp = search_node(root, e);
			if (tmp != NULL) {
				printf("\n�ܾ� %s�� �ǹ̴� %s�Դϴ�.\n", tmp->key.word, tmp->key.meaning);
			}
			else {
				printf("\n�ܾ� %s�� ������ �����ϴ�.\n", e.word);
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