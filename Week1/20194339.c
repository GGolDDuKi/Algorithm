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

	//1. 데이터 파일을 오픈해서 파일의 끝이 나올 때까지 반복
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		exit(0);
	}

	while (!feof(fp)) {
		//1-1. 임시 구조체 변수에 파일에서 읽은 값을 저장
		fscanf(fp, "%d %s %d %d %d", &tmp.studentNumber, tmp.name, &tmp.korean, &tmp.english, &tmp.math);
		
		//1-2. 합계와 평균을 계산해서 임시 구조체에 저장
		tmp.totalSum = tmp.korean + tmp.english + tmp.math;
		tmp.average = tmp.totalSum / 3.0;
		
		//2. 임시 구조체 크기만큼 동적으로 메모리를 할당받는다.
		//3. 연결리스트 함수한테 전달해서 노드로 추가한다.
		InsertNode(&head, CreateNode(tmp));
	}
	//4. 연결리스트를 전달해서 리스트 노드를 하나씩 출력한다.
	Display(head);

	//---------------- 2번 문제 ----------------
	char command;
	int sNo;
	//1. 명령어 화면 출력
	while (1) {
		//2. 사용자 명령 입력 (추가i, 검색s, 출력d, 종료q)
		printf("i : 입력 s : 검색 d : 출력 q : 종료\n");
		scanf("%c", &command);

		//3. Switch 분기 루틴 추가
		switch (command) {
		//4. case 'i' : 학번, 이름, 국어, 영어, 수학 점수 입력 받아서 구조체에 저장
		case 'i':
			printf("학번 : ");
			scanf("%d", &tmp.studentNumber);
			printf("이름 : ");
			scanf("%s", tmp.name);
			printf("국어 : ");
			scanf("%d", &tmp.korean);
			printf("영어 : ");
			scanf("%d", &tmp.english);
			printf("수학 : ");
			scanf("%d", &tmp.math);
			tmp.totalSum = tmp.korean + tmp.english + tmp.math;
			tmp.average = tmp.totalSum / 3.0;
			InsertNode(&head, CreateNode(tmp));
			break;
		case 's':
			printf("학번 : ");
			scanf("%d", &sNo);
			ListNode* st = Search(head, sNo);
			if (st == NULL) {
				printf("학번이 조회되지 않습니다.\n");
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
			printf("다시 입력하세요.\n");
			break;
		} //end of switch

		getchar();
	} //end of while

	//5. 열려있던 파일을 닫아준다. 메모리도 삭제해준다.
	fclose(fp);
}