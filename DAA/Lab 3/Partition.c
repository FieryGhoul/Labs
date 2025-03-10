#include <stdio.h>
#include <stdlib.h>

void generatePowerSet(int arr[], int n) {
    int opcount = 0;
    int total = 1 << n;
    for (int i = 1; i<total-1; i++) {
        int sum1 = 0, sum2 = 0;
        for (int j = 0; j < n; j++) {
            opcount++;  
            if (i & (1 << j)) {
                sum1 += arr[j];
            } else {
                sum2 += arr[j];
            }
        }
        if (sum1 == sum2) {
            printf("Subset 1: ");
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    printf("%d ", arr[j]);
                }
            }
            printf("\nSubset 2: ");
            for (int j = 0; j < n; j++) {
                if (!(i & (1 << j))) {
                    printf("%d ", arr[j]);
                }
            }
            printf("\n");
            printf("Operation count: %d\n", opcount);
            return;
        }
    }
    printf("No partition \n");
    printf("Operation count: %d\n", opcount);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    generatePowerSet(arr, n);
}
