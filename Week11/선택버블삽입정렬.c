#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[20];
	int student_no;
	int rank;
}element;

void print_list(element list[], int n) {
	printf("--------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("| %-7s | %-8d | %-2d |\n", list[i].name, list[i].student_no, list[i].rank);
	}
	printf("--------------------------\n");
}

void selection_sort(element list[], int n) {
	int i, j, least;
	element temp;

	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {
			if (list[j].rank < list[least].rank)
				least = j;
		}

		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

void bubble_sort(element list[], int n) {
	int i, j;
	element temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (strcmp(list[j].name, list[j + 1].name) > 0) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

void insertion_sort(element list[], int n) {
	int i, j;
	element temp;

	for (i = 0; i < n; i++) {
		temp = list[i];

		for (j = i - 1; j >= 0 && list[j].student_no > temp.student_no; j--) {
			list[j + 1] = list[j];
		}

		list[j + 1] = temp;
	}
}

int main() {
	FILE* fp;
	int count = 0;
	element temp;
	element* list;

	fp = fopen("data3.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", temp.name, &temp.student_no, &temp.rank);
		count++;
	}

	list = (element*)malloc(sizeof(element) * count);
	rewind(fp);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", list[count].name, &list[count].student_no, &list[count].rank);
		count++;
	}

	printf("< 정렬전 데이터 >\n");
	print_list(list, count);

	selection_sort(list, count);
	printf("< 등수 정렬후 데이터 >\n");
	print_list(list, count);

	bubble_sort(list, count);
	printf("< 이름 정렬후 데이터 >\n");
	print_list(list, count);

	insertion_sort(list, count);
	printf("< 학번 정렬후 데이터 >\n");
	print_list(list, count);

	free(list);
	fclose(fp);
	return 0;
}