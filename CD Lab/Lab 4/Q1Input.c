#include<stdio.h>
#include<stdlib.h>
int main(){
    int a, b;
    printf("Enter the numbers A and B...");
    scanf("%d",&a,&b);
    if(a>b){
        printf("%d",a);
        return a;
    }else{
        printf("%d",b);
        return b;
    }
}