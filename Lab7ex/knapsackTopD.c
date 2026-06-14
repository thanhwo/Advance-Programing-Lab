#include <stdio.h>

// Hàm đệ quy (Chạy tiến: i đi từ 0 đến n-1)
// W_rem là trọng lượng CÒN LẠI của túi
int knapsackTopDownHelper(int W_rem, int n, int weights[], int value[], int i, int W_max, int *memo) {
    // Trường hợp cơ sở: Hết đồ vật hoặc túi hết chỗ
    if (i == n || W_rem == 0) {
        return 0;
    }
    
    // Tính chỉ số index cho mảng 1 chiều
    int index = i * (W_max + 1) + W_rem;
    if (memo[index] != -1) {
        return memo[index];
    }
    
    int include = 0;
    // Nếu trọng lượng đồ vật <= sức chứa còn lại -> Thử LẤY đồ vật
    if (weights[i] <= W_rem) {
        include = value[i] + knapsackTopDownHelper(W_rem - weights[i], n, weights, value, i + 1, W_max, memo);
    }
    
    // KHÔNG LẤY đồ vật
    int exclude = knapsackTopDownHelper(W_rem, n, weights, value, i + 1, W_max, memo);
    
    // Ghi nhớ và trả về giá trị max
    memo[index] = (include > exclude) ? include : exclude;
    return memo[index];
}

void knapsackTopDown(int W, int n, int weights[], int value[]) {
    int total_size = (n + 1) * (W + 1);
    int memo[total_size];
    
    for (int i = 0; i < total_size; i++) {
        memo[i] = -1;
    }

    // Gọi hàm đệ quy với trọng lượng còn lại ban đầu là W
    int max_value = knapsackTopDownHelper(W, n, weights, value, 0, W, memo);
    printf("Gia tri lon nhat: %d\n", max_value);

    // --- Truy vết kết quả (Truy tiến cùng chiều với đệ quy) ---
    int res = max_value;
    int w = W;
    int selected_items[n];
    int count = 0;

    for (int i = 0; i < n && res > 0; i++) {
        int next_value = 0;
        
        // Lấy giá trị của nhánh "Không chọn đồ vật i" (tức là đi thẳng tới i+1 với cùng mức trọng lượng)
        if (i + 1 < n) {
            int next_index = (i + 1) * (W + 1) + w;
            next_value = (memo[next_index] == -1) ? 0 : memo[next_index];
        }

        // Nếu tổng hiện tại KHÁC với nhánh "Không chọn", có nghĩa là đồ vật i đã ĐƯỢC CHỌN
        if (res != next_value) {
            selected_items[count++] = i;
            res -= value[i];
            w -= weights[i];
        }
    }

    printf("Selected items: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", selected_items[i]);
    }
    printf("\n");
}

int main() {
    int W = 50;
    int weights[] = {10, 20, 30};
    int value[] = {60, 100, 120};
    
    // Tự động tính n dựa trên mảng để tránh lỗi out-of-bounds
    int n = sizeof(weights) / sizeof(weights[0]); 

    knapsackTopDown(W, n, weights, value);
    return 0;
}
