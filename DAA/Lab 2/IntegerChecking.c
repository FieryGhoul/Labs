#include <stdio.h>
int gcd(int m, int n, int *x) {
    for (int i=(m<n)?m:n; i>0; i--) {
        (*x)++;
        if (m%i==0 && n%i==0) {
            return i;
        }
    }
    return 1;
}

int main() {
    int a, b;
    int count = 0;
    printf("Enter two numbers: ");
    scanf("%d%d", &a, &b);
    
    int result = gcd(a, b, &count);
    
    printf("Result (GCD) = %d\n", result);
    printf("Operational count = %d\n", count);
}
