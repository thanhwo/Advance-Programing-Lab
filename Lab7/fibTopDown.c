#include <stdio.h>

int memo[1000];
int fib(int n){
    if(n <= 1) return n;
    if(memo[n] != -1) return memo[n];
    return memo[n] = fib(n-1) + fib(n-2);
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) memo[i] = -1;
    printf("Fibonacci of %d is %d\n", n, fib(n));
    return 0;
}
