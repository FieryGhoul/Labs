#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function for top-down heapify
void topDownHeapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child index
    int right = 2 * i + 2; // Right child index

    // Check if left child exists and is greater than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child exists and is greater than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If the largest is not the root, swap and recursively heapify the affected subtree
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        topDownHeapify(arr, n, largest);
    }
}

// Function to build a max-heap using a top-down approach
void buildMaxHeap(int arr[], int n) {
    // Start heapifying from the last non-leaf node up to the root node
    for (int i = (n / 2) - 1; i >= 0; i--) {
        topDownHeapify(arr, n, i);
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {4, 18, 17, 10, 19, 20, 14, 8, 3, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array:\n");
    printArray(arr, n);

    buildMaxHeap(arr, n);

    printf("Max-Heap Array:\n");
    printArray(arr, n);

    return 0;
}
