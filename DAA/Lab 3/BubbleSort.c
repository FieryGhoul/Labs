#include <stdio.h>
#include <stdlib.h>

int main() {
    int a;
    int opcount = 0;

    printf("Enter number of elements: ");
    scanf("%d", &a);

    int arr[a];

    for (int i = 0; i < a; i++)
        arr[i] = rand() % (a + 1);

    // // Best case: sorted array
    // printf("Best case scenario (sorted array):\n");
    // for (int i = 0; i < a; i++) {
    //     arr[i] = i; // Sorted array
    // }

	// // Worst case: reverse sorted array
    // printf("Worst case scenario (reverse sorted array):\n");
    // for (int i = 0; i < a; i++) {
    //     arr[i] = a - 1 - i; // Reverse sorted array
    // }

    for(int i=0;i<a;i++){
    	printf("%d  ",arr[i]);
    }

	for (int i = 0; i < a - 1; i++) {
        for (int j = 0; j < a - i - 1; j++) {
        	opcount++;
            if (arr[j] > arr[j + 1]) {
            	
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    

    printf("Sorted array: ");
    for (int i = 0; i < a; i++)
        printf("%d\t", arr[i]);
    printf("\n");
    printf("Total number of operations (comparisons): %d\n", opcount);
}
