#include <stdio.h>
#include <stdlib.h>

void swap(int*a,int*b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int calculate_cost(int jobs[][4],int n,int assign[]){
    int total_cost=0;
    for(int i=0;i<n;i++){
        total_cost+=jobs[i][assign[i]];
    }
	
}

void permute(int jobs[][4],int n,int assign[],int l,int r,int* min_cost,int best_assign[],int* opcount){
    if(l==r){
        int current_cost=calculate_cost(jobs,n,assign);
        (*opcount)++;
        if(current_cost<*min_cost){
            *min_cost=current_cost;
            for(int i=0;i<n;i++){
                best_assign[i]=assign[i];
            }
        }
    }else{
        for(int i=l;i<=r;i++){
            swap(&assign[l],&assign[i]);
            permute(jobs,n,assign,l+1,r,min_cost,best_assign,opcount);
            swap(&assign[l],&assign[i]);
        }
    }
}

int main(){
    int n,i,j;
    printf("Enter the number of jobs: ");
    scanf("%d",&n);
    
    int jobs[n][n];
    int assign[n];
    int best_assign[n];
    int min_cost=123456;
    int opcount=0;
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("Enter the cost for Job %d for Person %d: ",j+1,i+1);
            scanf("%d",&jobs[i][j]);
        }
    }

    for(i=0;i<n;i++){
        assign[i]=i;
    }

    permute(jobs,n,assign,0,n-1,&min_cost,best_assign,&opcount);
    
    for(i=0;i<n;i++){
        printf("Person %d is assigned Job %d with cost %d\n",i+1,best_assign[i]+1,jobs[i][best_assign[i]]);
    }
    printf("Minimum total cost: %d\n",min_cost);
    printf("Op count: %d\n",opcount);
}


/*
try for 
9  2  7  8
6  4  3  7
5  8  1  8		
7  6  9  4
*/
