#include<stdlib.h>
#include<stdio.h>

void merge(int arr[], int left, int mid, int right) {
    int n1=mid-left+1;
    int n2=right-mid;

    int leftArr[n1], rightArr[n2];
    //partition
    for (int i=0;i<n1;i++) {
        leftArr[i] = arr[left+i];
    }
    for (int j=0;j<n2;j++) {
        rightArr[j] = arr[mid+1+j];
    }
    //merge
    int i=0,j=0,k=left;
    while (i<n1&&j<n2){
        if (leftArr[i]<=rightArr[j]) {
            arr[k]=leftArr[i];
            i++;

            c++''
        } else {
            arr[k]=rightArr[j];
            j++;
        }
        k++;
    }
    while (i<n1) {
        arr[k]=leftArr[i];
        i++;
        k++;
    }
    while (j <n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left<right) {
        int mid=left+(right-left)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}

int main(){
	int n;
	printf("Enter the number of elements : ");
	scanf("%d",&n);
	int a[n];
	printf("Enter the elements for array : ");
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);	
	}
 	mergeSort(a,0,n);
	printf("Sorted array : ");
	for(int i=0;i<n;i++){
		printf("%d \t",a[i]);
	}
	printf("\n");
}
