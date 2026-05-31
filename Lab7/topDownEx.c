#include <stdio.h>
#include <limits.h>
 // Top-down memoized cut rod function
int memoized_cut_rod_aux(int p[], int n, int r[], int s[]) {
    int q;
    if (r[n] >= 0) return r[n];
    if (n == 0) q = 0;
    else q = -1;
    for (int i = 1; i <= n; i++) {
        int temp = p[i] + memoized_cut_rod_aux(p, n - i, r, s);
        if (temp > q) {
            q = temp;
            s[n] = i; // Store optimal first cut
        }
    }
    r[n] = q;
    return q;
}
 // Function to print rod cutting solution
void print_cut_rod_solution(int s[], int n) {
    while (n > 0) {
    printf("%d ", s[n]);
    n -= s[n];
    }
}
int main() {
    int price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 10; // Rod length
    int r[n + 1], s[n + 1];
    for (int i = 0; i <= n; i++)
        r[i] = -1; // Initialize revenues to -1 to mark “unkown”
    int max_revenue = memoized_cut_rod_aux(price, n, r, s);

    printf("Optimal revenue: %d\n", max_revenue);
    printf("Cuts: ");
    print_cut_rod_solution(s, n);
    printf("\n");
    return 0;
}
