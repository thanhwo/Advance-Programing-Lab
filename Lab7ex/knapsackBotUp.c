#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(int W, int n, int weights[], int values[]) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int res = dp[n][W];
    int w = W;

    int selectedItems[n];
    int count = 0;

    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {
            selectedItems[count++] = i - 1;
            res -= values[i - 1];
            w -= weights[i - 1];
        }
    }
    printf("Maximum value in Knapsack = %d\n", dp[n][W]);
    printf("Selected items: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", selectedItems[i]);
    }
    printf("\n");
}

int main(){
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(values) / sizeof(values[0]);

    knapsack(W, n, weights, values);
    return 0;
}
