#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
	int studentNumber;
	char name[20];
	int korean, english, math;
	int totalSum;
	double average;
}Student;

typedef struct ListNode {
	Student data;
	struct ListNode* link;
}ListNode;

ListNode* CreateNode(Student data) {
	ListNode* newNode;
	newNode = (ListNode*)malloc(sizeof(Student));
	newNode->data = data;
	newNode->link = NULL;

	return newNode;
}

void InsertNode(ListNode **pHead, ListNode* newData) {
	if (*pHead == NULL) {
		newData->link = NULL;
		*pHead = newData;
	}
	else {
		newData->link = *pHead;
		*pHead = newData;
	}
}

void Display(ListNode* pHead) {
	ListNode* p = pHead;

	while (p != NULL) {
		printf("%d %s %3d %3d %3d %3d %.1f\n", p->data.studentNumber, p->data.name, p->data.korean, p->data.english, p->data.math, p->data.totalSum, p->data.average);
		p = p->link;
	}
}

ListNode* Search(ListNode* pHead, int sNo) {
	ListNode* p = pHead;

	while (p != NULL) {
		if (p->data.studentNumber == sNo) {
			return p;
		}
		p = p->link;
	}

	return NULL;
}
	

int main() {
	FILE* fp = NULL;
	Student tmp;
	ListNode* head = NULL;

	//1. ������ ������ �����ؼ� ������ ���� ���� ������ �ݺ�
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		exit(0);
	}

	while (!feof(fp)) {
		//1-1. �ӽ� ����ü ������ ���Ͽ��� ���� ���� ����
		fscanf(fp, "%d %s %d %d %d", &tmp.studentNumber, tmp.name, &tmp.korean, &tmp.english, &tmp.math);
		
		//1-2. �հ�� ����� ����ؼ� �ӽ� ����ü�� ����
		tmp.totalSum = tmp.korean + tmp.english + tmp.math;
		tmp.average = tmp.totalSum / 3.0;
		
		//2. �ӽ� ����ü ũ�⸸ŭ �������� �޸𸮸� �Ҵ�޴´�.
		//3. ���Ḯ��Ʈ �Լ����� �����ؼ� ���� �߰��Ѵ�.
		InsertNode(&head, CreateNode(tmp));
	}
	//4. ���Ḯ��Ʈ�� �����ؼ� ����Ʈ ��带 �ϳ��� ����Ѵ�.
	Display(head);

	//---------------- 2�� ���� ----------------
	char command;
	int sNo;
	//1. ��ɾ� ȭ�� ���
	while (1) {
		//2. ����� ��� �Է� (�߰�i, �˻�s, ���d, ����q)
		printf("i : �Է� s : �˻� d : ��� q : ����\n");
		scanf("%c", &command);

		//3. Switch �б� ��ƾ �߰�
		switch (command) {
		//4. case 'i' : �й�, �̸�, ����, ����, ���� ���� �Է� �޾Ƽ� ����ü�� ����
		case 'i':
			printf("�й� : ");
			scanf("%d", &tmp.studentNumber);
			printf("�̸� : ");
			scanf("%s", tmp.name);
			printf("���� : ");
			scanf("%d", &tmp.korean);
			printf("���� : ");
			scanf("%d", &tmp.english);
			printf("���� : ");
			scanf("%d", &tmp.math);
			tmp.totalSum = tmp.korean + tmp.english + tmp.math;
			tmp.average = tmp.totalSum / 3.0;
			InsertNode(&head, CreateNode(tmp));
			break;
		case 's':
			printf("�й� : ");
			scanf("%d", &sNo);
			ListNode* st = Search(head, sNo);
			if (st == NULL) {
				printf("�й��� ��ȸ���� �ʽ��ϴ�.\n");
			}
			else {
				printf("%d %s %3d %3d %3d %3d %.1f\n", st->data.studentNumber, st->data.name, st->data.korean, st->data.english, st->data.math, st->data.totalSum, st->data.average);
			}
			break;
		case 'd':
			Display(head);
			break;
		case 'q':
			return 0;
			break;
		default:
			printf("�ٽ� �Է��ϼ���.\n");
			break;
		} //end of switch

		getchar();
	} //end of while

	//5. �����ִ� ������ �ݾ��ش�. �޸𸮵� �������ش�.
	fclose(fp);
}