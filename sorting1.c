#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct {
	double time; 
	int swaps;
	int comprassion;
	//int calls;
} result;

int arrA[10000];
int testArr[10000];
result r[10][4];;//[max amount of n][max amount of technique]
FILE* fptr;

void fillArray(int begsec, int endsec);
void fillTestArray(int endsec);
void bubble(int size, int a);
void selection(int size, int a);
void insertion(int size, int a);
void count(int size, int a);
//void merge(int a, int lb, int ub);
//void merg(int a, int lb, int mid, int ub);
void bubbleT(int size, int a);
void selectionT(int size, int a);
void insertionT(int size, int a);
void countT(int size, int a);
void chek(int size);

void main() {
	fopen_s(&fptr, "C:\\Users\\aufme\\OneDrive - National University of Ireland, Galway\\Study\\NUIG\\CT102 Algorithms & SQL\\ass3\\file1.txt", "r");
	if (fptr != NULL) {
		int size = 0;
		int prevsize = 0;
		prevsize = size;

		printf("     Sort       N     Time  Comprasions   Data moves\n");
		for (int i = 1; i < 10; i++) {
			printf("\n");
			prevsize = size;
			size = 1000 * i;

			fillArray(prevsize, size);

			bubble(size, i);
			bubbleT(size, i);
			printf("Buble        %d    %.3lf    %9d    %9d\n", size, r[i][0].time, r[i][0].comprassion, r[i][0].swaps);

			selection(size, i);
			selectionT(size, i);
			printf("Selection    %d    %.3lf    %9d    %9d\n", size, r[i][1].time, r[i][1].comprassion, r[i][1].swaps);

			insertion(size, i);
			insertionT(size, i);
			printf("Insertion    %d    %.3lf    %9d    %9d\n", size, r[i][2].time, r[i][2].comprassion, r[i][2].swaps);

			count(size, i);
			countT(size, i);
			printf("Count        %d    %.3lf    %9d    %9d\n", size, r[i][3].time, r[i][3].comprassion, r[i][3].swaps);


			//fillTestArray(size);
			//merge(i, 0, size - 1);
			//chek(size);
		}
		fclose;
	}
	else
	{
		printf("File don't found");
	}
}


void fillArray(int begsec, int endsec) {
	for (int i = begsec; i < endsec; i++) {
		fscanf_s(fptr, "%d", &arrA[i]);
	}
}

void fillTestArray(int size) {
	for (int i = 0; i < size; i++) {
		testArr[i] = arrA[i];
	}
}

void bubble(int size, int a) {
	fillTestArray(size);

	int temp;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < (size - 1); j++) {
			if (testArr[j] > testArr[j + 1]) {//comp size*(size-1) times
				temp = testArr[j];//swap x times
				testArr[j] = testArr[j + 1];//swap x times
				testArr[j+1] = temp;//swap x times
				r[a][0].swaps += 3;
			}
		}
	}

	r[a][0].comprassion += size*(size-1);

	chek(size);
}

void bubbleT(int size, int a) {
	fillTestArray(size);

	clock_t start = clock(), end;

	int temp;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < (size - 1); j++) {
			if (testArr[j] > testArr[j + 1]) {
				temp = testArr[j];
				testArr[j] = testArr[j + 1];
				testArr[j + 1] = temp;
			}
		}
	}

	end = clock();
	r[a][0].time = (double)(end - start) / CLOCKS_PER_SEC;

	chek(size);
}

void selection(int size, int a) {
	fillTestArray(size);

	int smallest;
	int temp;

	for (int i = 0; i < size; i++) {
		smallest = i;
		for (int j = smallest+1; j < (size); j++) {
			if (testArr[smallest] > testArr[j]) {//comp x times
				smallest = j;
			}
			r[a][1].comprassion++;
		}
		temp = testArr[i];//swap size times
		testArr[i] = testArr[smallest];//swap size times
		testArr[smallest] = temp;//swap size times
	}

	r[a][1].swaps += 3*size;

	chek(size);
}

void selectionT(int size, int a) {
	fillTestArray(size);

	clock_t start = clock(), end;

	int smallest;
	int temp;

	for (int i = 0; i < size; i++) {
		smallest = i;
		for (int j = smallest + 1; j < (size); j++) {
			if (testArr[smallest] > testArr[j]) {
				smallest = j;
			}
		}
		temp = testArr[i];
		testArr[i] = testArr[smallest];
		testArr[smallest] = temp;
	}

	end = clock();
	r[a][1].time = (double)(end - start) / CLOCKS_PER_SEC;

	chek(size);
}

void insertion(int size, int a) {
	fillTestArray(size);

	int temp, j;

	for (int i = 1; i < size; i++) {
		temp = testArr[i];//swap size-1 times
		for (j = i - 1; j >= 0 && testArr[j] > temp; j--) {//comp (size - 1) + x times
			testArr[j + 1] = testArr[j];//swap x times
			r[a][2].comprassion++;
			r[a][2].swaps++;
		}
		if (testArr[j + 1] != temp) {//comp size-1 times
			testArr[j + 1] = temp;//swap x times
			r[a][2].swaps++;
		}
	}

	r[a][2].comprassion += 2*(size-1);
	r[a][2].swaps += size-1;

	chek(size);
}

void insertionT(int size, int a) {
	fillTestArray(size);

	clock_t start = clock(), end;

	int temp, j;

	for (int i = 1; i < size; i++) {
		temp = testArr[i];
		for (j = i - 1; j >= 0 && testArr[j] > temp; j--) {
			testArr[j + 1] = testArr[j];
		}
		if (testArr[j + 1] != temp) {
			testArr[j + 1] = temp;
		}
	}

	end = clock();
	r[a][2].time = (double)(end - start) / CLOCKS_PER_SEC;

	chek(size);
}

void count(int size, int a) {
	fillTestArray(size);

	int min = testArr[0];//swap 1 time
	for (int i = 1; i < size; i++) {
		if (testArr[i] < min) {//comp size-1 times
			min = testArr[i];//swap x times
			r[a][3].swaps++;
		}
	}

	if (min < 0) {
		for (int i = 0; i < size; i++)
		{
			testArr[i] -= min;//swap size times if min < 0
		}
		r[a][3].swaps += size;
	}

	int max = testArr[0];//swap 1 time
	for (int i = 1; i < size; i++) {
		if (testArr[i] > max) {//comp size-1 times
			max = testArr[i];//swap x times
			r[a][3].swaps++;
		}
	}

	int* freq = (int*)calloc((max + 1), sizeof(int));
	int* arrB = (int*)calloc(size, sizeof(int));

	if (!freq || !arrB) {
		return;
	}
	else {
		for (int i = 0; i < size; i++) {
			freq[testArr[i]]++;//swap size times
		}

		for (int i = 0; i < (max); i++) {
			freq[i + 1] += freq[i];//swap x times
			r[a][3].swaps++;
		}

		for (int i = 0; i < size; i++) {
			arrB[freq[testArr[i]]-1] = testArr[i];//swap size times
			freq[testArr[i]]--;//swap size times
		}

		for (int i = 0; i < size; i++) {
			testArr[i] = arrB[i];//swap  size times
		}
	}

	if (min < 0) {
		for (int i = 0; i < size; i++)
		{
			testArr[i] += min;//swap size times if min < 0
		}
		r[a][3].swaps += size;
	}
	free(arrB);
	free(freq);

	r[a][3].comprassion += 2*(size-1);
	r[a][3].swaps += (4*size)+2;

	chek(size);
}

void countT(int size, int a) {
	fillTestArray(size);

	clock_t start = clock(), end;

	int min = testArr[0];
	for (int i = 1; i < size; i++) {
		if (testArr[i] < min) {
			min = testArr[i];
		}
	}

	if (min < 0) {
		for (int i = 0; i < size; i++)
		{
			testArr[i] -= min;
		}
	}

	int max = testArr[0];
	for (int i = 1; i < size; i++) {
		if (testArr[i] > max) {
			max = testArr[i];
		}
	}

	int* freq = (int*)calloc((max + 1), sizeof(int));
	int* arrB = (int*)calloc(size, sizeof(int));

	if (!freq || !arrB) {
		return;
	}
	else {
		for (int i = 0; i < size; i++) {
			freq[testArr[i]]++;
		}

		for (int i = 0; i < (max); i++) {
			freq[i + 1] += freq[i];
		}

		for (int i = 0; i < size; i++) {
			arrB[freq[testArr[i]] - 1] = testArr[i];
			freq[testArr[i]]--;
		}

		for (int i = 0; i < size; i++) {
			testArr[i] = arrB[i];
		}
	}

	if (min < 0) {
		for (int i = 0; i < size; i++)
		{
			testArr[i] += min;
		}
	}
	free(arrB);
	free(freq);

	end = clock();
	r[a][3].time += (double)(end - start) / CLOCKS_PER_SEC;

	chek(size);
}

/*void merge(int a, int lb, int ub) {
	if(lb < ub){

		int mid = (int)(lb + ub) / 2;
		merge(a, lb, mid);
		merge(a, mid + 1, ub);
		merg(a, lb, mid, ub);

		
	}
}

void merg(int a, int lb, int mid, int ub) {
	int i, j, k;
	int size = ub-lb;
	int* arrC = (int*)calloc(size, sizeof(int));

	for (i = lb, j = mid + 1, k = 0; i <= mid && j <= ub; k++) {
		if (arrA[i] <= arrA[j]) {
			arrC[k] = arrA[i++]
		}
		else {
			arrC[k] = arrA[j++]
		}
	}

	while (i <= mid) {
		arrC[k++] = arrA[i++]
	}
	while (j <= ub) {
		arrC[k++] = arrA[j++]
	}
	for (int i = lb, k = 0; i < ub; i++, k++) {
		arrA[i] = arrC[k];
	}
}*/

void chek(int size) {
	int checked = 1;

	for (int i = 0; i < size - 1 && checked == 1; i++) {

		if (testArr[i] > testArr[i + 1]) {
			checked = 0;
		}

	}

	if (checked != 1) {
		puts("Array isn't sorted in ascending order");
	}
}