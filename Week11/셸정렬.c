#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char name[10];
	int id;
	char number[20];
}student;

void inc_insertion_sort(student list[], int first, int last, int gab) {
	int i, j;
	student temp;

	for (i = first + gab; i <= last; i = i + gab) {
		temp = list[i];

		for (j = i - gab; j >= first && list[j].id < temp.id; j = j - gab) {
			list[j + gab] = list[j];
		}
		list[j + gab] = temp;
	}
}

void shell_sort(student list[], int n) {
	int i, gab;

	for (gab = n / 2; gab > 0; gab = gab / 2) {
		if ((gab % 2) == 0) {
			gab++;
		}

		for (i = 0; i < gab; i++) {
			inc_insertion_sort(list, i, n - 1, gab);
		}
	}
}

int main() {
	FILE* fp;
	int count = 0;
	student temp;
	student* list;

	fp = fopen("data3.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", temp.name, &temp.id, temp.number);
		count++;
	}

	list = (student*)malloc(sizeof(student) * count);
	rewind(fp);
	for (int i = 0; i < count; i++) {
		fscanf(fp, "%s %d %s", list[i].name, &list[i].id, list[i].number);
	}

	printf("< 정렬 전 >\n");

	for (int i = 0; i < count; i++) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].number);
	}

	shell_sort(list, count);
	printf("\n< 정렬 후 >\n");

	for (int i = 0; i < count; i++) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].number);
	}

	free(list);
	fclose(fp);
	return 0;
}