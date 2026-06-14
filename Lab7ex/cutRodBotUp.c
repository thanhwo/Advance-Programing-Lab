#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void cutRod(int price[], int n, int r[], int s[]) {
    r[0] = 0;
    s[0] = 0;

    for (int j = 1; j <= n; j++) {
        int maxV = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (maxV < price[i - 1] + r[j - i]) {
                maxV = price[i - 1] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = maxV;
    }
}

void printRod(int n, int r[], int s[]) {
    printf("Maximum revenue: %d\n", r[n]);
    printf("Cuts: ");
    while (n > 0) {
        printf("%d ", s[n]);
        n -= s[n];
    }
    printf("\n");
}

int main(){
    int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20};
    int n;
    printf("Enter the length of the rod: ");
    scanf("%d", &n);

    if(n < 0 || n > 10){
        printf("Invalid input. Please enter a length between 0 and 10.\n");
        return 1;
    }

    int r[n + 1], s[n + 1];

    for (int i = 0; i <= n; i++) {
        r[i] = -1;
        s[i] = -1;
    }

    cutRod(price, n, r, s);
    printRod(n, r, s);
    return 0;
}

