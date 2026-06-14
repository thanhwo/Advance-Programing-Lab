#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Thêm tham số total_cols để giữ nguyên chiều rộng của mảng 2 chiều mô phỏng
int lcsTopDownHelper(char *X, char *Y, int i, int j, int total_cols, int *memo) {
    if (i == 0 || j == 0) {
        return 0;
    }

    // Tính index chuẩn: hàng hiện tại * tổng số cột cố định + cột hiện tại
    int index = i * total_cols + j; 

    if (memo[index] != -1) {
        return memo[index];
    }

    if (X[i - 1] == Y[j - 1]) {
        memo[index] = 1 + lcsTopDownHelper(X, Y, i - 1, j - 1, total_cols, memo);
    } else {
        memo[index] = max(lcsTopDownHelper(X, Y, i - 1, j, total_cols, memo),
                          lcsTopDownHelper(X, Y, i, j - 1, total_cols, memo));
    }

    return memo[index];
}

void lcs_top_down(char *X, char *Y, int m, int n) {
    int total_cols = n + 1; // Lưu lại tổng số cột cố định
    int total_size = (m + 1) * total_cols;
    int memo[total_size];

    for (int i = 0; i < total_size; i++) {
        memo[i] = -1;
    }

    // Truyền total_cols vào hàm đệ quy
    int max_length = lcsTopDownHelper(X, Y, m, n, total_cols, memo);
    
    int len = max_length;
    char lcs[len + 1];
    lcs[len] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[--len] = X[i - 1]; // Cách viết gộp --len của bạn rất gọn gàng!
            i--;
            j--;
        } 
        // Sử dụng total_cols để đồng bộ cách tính index ở vòng lặp truy vết
        else if (memo[i * total_cols + (j - 1)] > memo[(i - 1) * total_cols + j]) {
            j--;
        } else {
            i--;
        }
    }
    
    printf("Length of LCS is %d\n", max_length);
    printf("LCS is %s\n", lcs);
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);

    lcs_top_down(X, Y, m, n);

    return 0;
}
