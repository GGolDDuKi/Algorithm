#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int partition(int list[], int left, int right) {
	int pivot, low, high;
	int temp;

	low = left;
	high = right + 1;
	pivot = list[left];

	printf("pivot : %d\n", pivot);

	do {
		do {
			low++;
		} while (low <= right && list[low] < pivot);

		do {
			high--;
		} while (high >= left && list[high] > pivot);

		printf("low : %d high %d\n", list[low], list[high]);
		printf("[ ");
		for (int i = 0; i < right - 1; i++) {
			printf("%d ", list[i]);
		}
		printf(" ]\n");

		if (low < high) {
			printf("%d와 %d를 스왑\n", list[low], list[right]);
			SWAP(list[low], list[high], temp);

			printf("[ ");
			for (int i = 0; i < right + 1; i++) {
				printf("%d ", list[i]);
			}
			printf(" ]\n");
		}

	} while (low < high);

	SWAP(list[left], list[high], temp);

	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

int main() {
	FILE* fp;
	int* list;
	int temp;
	int count = 0;

	fp = fopen("data2.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		count++;
	}

	list = (int*)malloc(sizeof(int) * count);
	rewind(fp);

	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d", &list[i]);
	}

	printf("정렬전\n");
	for (int i = 0; i < count; i++) {
		printf("%d > ", list[i]);
	}
	printf("\n");

	quick_sort(list, 0, count - 1);

	printf("정렬후\n");
	for (int i = 0; i < count; i++) {
		printf("%d > ", list[i]);
	}
	printf("\n");

	free(list);
	fclose(fp);
	return 0;
}