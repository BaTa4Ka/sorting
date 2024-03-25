#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Structure to store sorting results
typedef struct {
	double time;
	int swaps, comprassion, rCalls, nrCalls;
} result;

// Global arrays and result matrix
int arrA[10000];
int testArr[10000];
result r[10][4];;//[max amount of n][max amount of technique]
FILE* fptr;

// Function prototypes
void fillArray(int begsec, int endsec);
void fillTestArray(int endsec);
void merge(int a, int lb, int ub);
void merg(int a, int lb, int mid, int ub);
void mergeT(int lb, int ub);
void mergT(int lb, int mid, int ub);
void qSort(int a, int lb, int ub);
int partition(int a, int lb, int ub);
void qSortT(int lb, int ub);
int partitionT(int lb, int ub);
void chek(int size);
void swap(int* a, int* b);

void main() {
	fopen_s(&fptr, "C:\\Users\\aufme\\OneDrive - National University of Ireland, Galway\\Study\\NUIG\\CT102 Algorithms & SQL\\ass4\\file1.txt", "r");
	if (fptr != NULL) {
		int size = 0;
		int prevsize = 0;
		prevsize = size;
		clock_t start, end;

		// Printing header
		printf("     Sort       N     Time  Comprasions   Data moves   RCalls NRCalls\n");
		for (int i = 1; i < 10; i++) {
			printf("\n");
			prevsize = size;
			size = 1000 * i;

			// Fill array from file
			fillArray(prevsize, size);

            // Merge sort with stats
			fillTestArray(size);
			merge(i, 0, size - 1);
			chek(size);

            // Merge sort without stats for time count
			fillTestArray(size);
			start = clock();
			mergeT(0, size - 1);
			end = clock();
			r[i][0].time = (double)(end - start) / CLOCKS_PER_SEC;
			chek(size);

            // Quick sort with stats
			fillTestArray(size);
			qSort(i, 0, size - 1);
			chek(size);

            // Quick sort without stats for time count
			fillTestArray(size);
			start = clock();
			qSortT(0, size - 1);
			end = clock();
			r[i][1].time = (double)(end - start) / CLOCKS_PER_SEC;
			chek(size);

            // Display results
            printf("Merge        %d    %.3lf    %9d    %9d   %6d  %6d\n", size, r[i][0].time, r[i][0].comprassion, r[i][0].swaps, r[i][0].rCalls, r[i][0].nrCalls);
			printf("QSort        %d    %.3lf    %9d    %9d   %6d  %6d\n", size, r[i][1].time, r[i][1].comprassion, r[i][1].swaps, r[i][1].rCalls, r[i][1].nrCalls);
		}
		fclose;
	}
	else
	{
		printf("File don't found");
	}
}

// Function to fill array from file
void fillArray(int begsec, int endsec) {
	for (int i = begsec; i < endsec; i++) {
		fscanf_s(fptr, "%d", &arrA[i]);
	}
}

// Function to fill test array
void fillTestArray(int size) {
	for (int i = 0; i < size; i++) {
		testArr[i] = arrA[i];
	}
}

// Function to merge subarrays
void merge(int a, int lb, int ub) {
    if (lb < ub) {
        // Calculate middle index
        int mid = (int)(lb + ub) / 2;

        // Recursively call merge on left and right halves
        merge(a, lb, mid);
        merge(a, mid + 1, ub);

        // Increment recursive calls count
        r[a][0].rCalls += 2;

        // Merge the subarrays
        merg(a, lb, mid, ub);

        // Increment non-recursive calls count
        r[a][0].nrCalls++;
    }
}

// Actual merging of subarrays
void merg(int a, int lb, int mid, int ub) {
    int i, j, k;
    int size = ub - lb + 1;
    int* arrC = (int*)calloc(size, sizeof(int));

    // Merge sorted subarrays
    for (i = lb, j = mid + 1, k = 0; i <= mid && j <= ub; k++) {
        if (testArr[i] <= testArr[j]) {
            arrC[k] = testArr[i++];
        }
        else {
            arrC[k] = testArr[j++];
        }
        // Increment comparison and swap counts
        r[a][0].comprassion++;
        r[a][0].swaps++;
    }

    // Copy remaining elements from left subarray
    while (i <= mid) {
        arrC[k++] = testArr[i++];
        r[a][0].swaps++;
    }

    // Copy remaining elements from right subarray
    while (j <= ub) {
        arrC[k++] = testArr[j++];
        r[a][0].swaps++;
    }

    // Copy merged array back to original array
    for (int i = lb, k = 0; i <= ub; i++, k++) {
        testArr[i] = arrC[k];
        r[a][0].swaps++;
    }

    // Free dynamically allocated memory
    free(arrC);
}

// Function to perform merge sort recursively
void mergeT(int lb, int ub) {
    if (lb < ub) {
        int mid = (int)(lb + ub) / 2;
        mergeT(lb, mid);
        mergeT(mid + 1, ub);
        mergT(lb, mid, ub);
    }
}

// Actual merging of subarrays for non-recursive merge sort
void mergT(int lb, int mid, int ub) {
    int i, j, k;
    int size = ub - lb + 1;
    int* arrC = (int*)calloc(size, sizeof(int));

    // Merge sorted subarrays
    for (i = lb, j = mid + 1, k = 0; i <= mid && j <= ub; k++) {
        if (testArr[i] <= testArr[j]) {
            arrC[k] = testArr[i++];
        }
        else {
            arrC[k] = testArr[j++];
        }
    }

    // Copy remaining elements from left subarray
    while (i <= mid) {
        arrC[k++] = testArr[i++];
    }

    // Copy remaining elements from right subarray
    while (j <= ub) {
        arrC[k++] = testArr[j++];
    }

    // Copy merged array back to original array
    for (int i = lb, k = 0; i <= ub; i++, k++) {
        testArr[i] = arrC[k];
    }

    // Free dynamically allocated memory
    free(arrC);
}

// Function to perform quick sort recursively
void qSort(int a, int lb, int ub) {
    if (lb < ub) {
        int k = partition(a, lb, ub);
        r[a][1].nrCalls++;
        qSort(a, lb, k - 1);
        qSort(a, k + 1, ub);
        r[a][1].rCalls += 2;
    }
}

// Partition function for quick sort
int partition(int a, int lb, int ub) {
    int i = lb + 1;
    int k = ub;
    int pivot = testArr[lb];
    r[a][1].swaps++;

    while (k >= i) {
        while (testArr[i] <= pivot && i <= k) {
            r[a][1].comprassion++;
            i++;
        }
        while (testArr[k] > pivot && k >= i) {
            r[a][1].comprassion++;
            k--;
        }
        if (k > i) {
            // Swap values at k and i
            swap(&testArr[i], &testArr[k]);
            r[a][1].swaps += 3;
        }
        r[a][1].comprassion += 2;
    }

    // Swap pivot with element at position k
    swap(&testArr[lb], &testArr[k]);
    r[a][1].swaps += 3;
    return (k);
}

// Function to perform quick sort without recursion
void qSortT(int lb, int ub) {
    if (lb < ub) {
        int k = partitionT(lb, ub);
        qSortT(lb, k - 1);
        qSortT(k + 1, ub);
    }
}

// Partition function for non-recursive quick sort
int partitionT(int lb, int ub) {
    int i = lb + 1;
    int k = ub;
    int pivot = testArr[lb];

    while (k >= i) {
        while (testArr[i] <= pivot && i <= k) {
            i++;
        }
        while (testArr[k] > pivot && k >= i) {
            k--;
        }
        if (k > i) {
            // Swap values at k and i
            swap(&testArr[i], &testArr[k]);
        }
    }

    // Swap pivot with element at position k
    swap(&testArr[lb], &testArr[k]);
    return (k);
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to check if array is sorted
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
