#include <stdio.h>
#define max 1024
typedef struct{   
    int size;
    int f[max + 1];
    int e[max + 1];
} factor;

void FindFactors(int x, factor* factor){
    int i, c = 0, k = 1, n = x;
    factor->f[0] = 1;
    factor->e[0] = 1;

    for (i = 2; i <= n; i++) {
        c = 0;
        while (n % i == 0) {
            c++;
            n = n / i;
        }
        if (c > 0) {
            factor->e[k] = c;
            factor->f[k] = i;
            k++;
        }
    }
    factor->size = k - 1;
}
int gcd(int m, int n,int *count){
    factor mF, nF;
    int i = 1, j = 1, x = 1, min;
    FindFactors(m, &mF);
    FindFactors(n, &nF);
    while (i <= mF.size && j <= nF.size) {
        (*count)++;
        if (mF.f[i] < nF.f[j])
            i++;
        else if (nF.f[j] < mF.f[i])
            j++;
        else 
        {
            min = mF.e[i]<nF.e[j] ? mF.e[i]:nF.e[j];
            x = x * mF.f[i]*min;
            i++;
            j++;
        }
    }
    return x;
}
int main(){
    int m,n;
    int count=0;
    printf("Enter 2 numbers : ");
    scanf("%d%d",&m,&n);
    int x = gcd(m,n,&count);
    printf("GCD : %d \n",x);
    printf("Count : %d \n",count);
}
