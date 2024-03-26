#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search(int key, int low, int high, int list[]) {
	int middle;

	while (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}

	return -1;
}

int main() {
	FILE* fp;
	int count = 0, i = 0, KEY = 0, flag;
	int* list = NULL;
	clock_t start, end;
	float result;

	fp = fopen("data1.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &i);
		count++;
	}

	rewind(fp);

	list = (int*)malloc(sizeof(int) * count);
	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d", &list[count]);
		count++;
	}

	printf("ã���� �ϴ� ������ �Է��Ͻÿ� : ");
	scanf("%d", &KEY);

	start = clock();
	flag = binary_search(KEY, 0, count - 1, list);
	end = clock();

	result = (float)(end - start) / CLOCKS_PER_SEC;

	if (flag == -1)
		printf("Ž�� ����\n");
	else {
		printf("Ž�� ����\n");
		printf("%d��° �ε������� �˻� ����\n", flag + 1);
		printf("����Ž�� ���� �ð� : %f\n\n", result);
	}

	free(list);
	fclose(fp);
	return 0;
}