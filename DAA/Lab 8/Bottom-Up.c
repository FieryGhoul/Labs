#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function for bottom-up heapify
void bottomUpHeapify(int arr[], int n, int i) {
    int parent = i; // Start at the current node
    int leftChild = 2 * parent + 1; // Left child index
    int rightChild = 2 * parent + 2; // Right child index

    while (leftChild < n) {
        int largest = parent;

        // Check if left child exists and is greater than parent
        if (arr[leftChild] > arr[largest])
            largest = leftChild;

        // Check if right child exists and is greater than the largest so far
        if (rightChild < n && arr[rightChild] > arr[largest])
            largest = rightChild;

        // If parent is already larger than its children, break out of the loop
        if (largest == parent)
            break;

        // Swap parent with the larger child
        swap(&arr[parent], &arr[largest]);

        // Move down to the next level
        parent = largest;
        leftChild = 2 * parent + 1;
        rightChild = 2 * parent + 2;
    }
}

// Function to build a max-heap using a bottom-up approach
void buildMaxHeapBottomUp(int arr[], int n) {
    // Start heapifying from the last non-leaf node up to the root node
    for (int i = (n / 2) - 1; i >= 0; i--) {
        bottomUpHeapify(arr, n, i);
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

    buildMaxHeapBottomUp(arr, n);

    printf("Max-Heap Array:\n");
    printArray(arr, n);

    return 0;
}
