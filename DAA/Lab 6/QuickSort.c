#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function using the first element as pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[low]; // Choosing the first element as pivot
    int i = low + 1;      // Start from the second element
    int j = high;

    while (i <= j) {
        // Find an element larger than the pivot on the left side
        while (i <= j && arr[i] <= pivot)
            i++;

        // Find an element smaller than the pivot on the right side
        while (i <= j && arr[j] > pivot)
            j--;

        // Swap elements if i is still less than j
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    // Place the pivot in its correct position by swapping it with arr[j]
    swap(&arr[low], &arr[j]);
    return j; // Return the new index of the pivot
}

// QuickSort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function to test Quick Sort
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}



// #include <stdio.h>

// void swap(int* a, int* b) {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// int partition(int arr[], int low, int high) {
//     int pivot = arr[high];
//     int i = (low - 1);

//     for (int j = low; j < high; j++) {
//         if (arr[j] <= pivot) {
//             i++;
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[i + 1], &arr[high]);
//     return (i + 1);
// }

// void quickSort(int arr[], int low, int high) {
//     if (low < high) {
//         int pi = partition(arr, low, high);
//         quickSort(arr, low, pi - 1);
//         quickSort(arr, pi + 1, high);
//     }
// }

// int main(){
//     int n;
//     printf("Enter the number of elements : ");
//     scanf("%d",&n);
//     int a[n];
//     printf("Enter the elements for array : ");
//     for(int i=0;i<n;i++){
//         scanf("%d",&a[i]);  
//     }
//     quickSort(a,0,n);
//     printf("Sorted array : ");
//     for(int i=0;i<n;i++){
//         printf("%d \t",a[i]);
//     }
//     printf("\n");
// }
