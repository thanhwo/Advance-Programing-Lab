#include <stdio.h>
#include <limits.h>

int topDownCutRod(int price[], int n, int memo[], int cuts[]) {
    if (n == 0) {
        return 0;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    int maxV = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int current_profit = price[i - 1] + topDownCutRod(price, n - i, memo, cuts);
        if (current_profit > maxV) {
            maxV = current_profit;
            cuts[n] = i; // Store the cut length
        }
    }
    memo[n] = maxV;
    return maxV;
}

void printRod(int n, int max_profit, int cuts[]) {
    printf("Maximum profit: %d\n", max_profit);
    printf("Cuts: ");
    while (n > 0) {
        printf("%d ", cuts[n]);
        n -= cuts[n];
    }
    printf("\n");
}

int main(){
    int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30}; 
    int n;
    printf("Enter the length of the rod: ");
    scanf("%d", &n);

    int memo[n + 1], cuts[n + 1];
    for (int i = 0; i <= n; i++) {
        memo[i] = -1; 
        cuts[i] = -1; 
    }

    int max_profit = topDownCutRod(price, n, memo, cuts);
    printRod(n, max_profit, cuts);
    return 0;
}
