#include<stdio.h>
#include<stdlib.h>

int opcount = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i, int *opcount) {
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[large]) {
        large = left;
        (*opcount)++;
    }
    if (right < n && arr[right] > arr[large]) {
        large = right;
        (*opcount)++;
    }
    if (large != i) {
        swap(&arr[i], &arr[large]);
        (*opcount)++;
        heapify(arr, n, large, opcount);
    }
}

void buildHeap(int arr[], int n, int *opcount) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, opcount);
    }
}

int main() {
    int n;
    printf("Enter size of array : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    buildHeap(arr, n, &opcount);
    printf("Operation count: %d\n", opcount);
    return 0;
}
