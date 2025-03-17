#include <stdio.h>

int knapsack(int W, int wt[], int val[], int n) {
    int dp[n+1][W+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i-1] <= w) {
                dp[i][w] = (val[i-1] + dp[i-1][w-wt[i-1]] > dp[i-1][w]) 
                            ? val[i-1] + dp[i-1][w-wt[i-1]] 
                            : dp[i-1][w];
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    
    printf("Enter the number of items: ");  
    scanf("%d", &n);

    printf("Enter the maximum weight capacity of the knapsack: ");
    scanf("%d", &W);

    int val[n], wt[n];

    printf("Enter the values of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter the weights of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Maximum value in Knapsack = %d\n", knapsack(W, wt, val, n));
    
    return 0;
}
