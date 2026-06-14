#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Cần thiết để dùng malloc và free

int main() {
    // Mở file gốc bằng chế độ "w+" để vừa ghi vừa đọc được dữ liệu
    FILE *file = fopen("Data.txt", "w+");
    FILE *file_out = fopen("Data_reversed.txt", "w");

    if (file == NULL || file_out == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Khai báo mảng char để chứa chuỗi nhập vào thay vì dùng "stdin string"
    char data[256];
    printf("Enter a string: ");
    scanf("%255s", data); // %255s để giới hạn chống tràn bộ đệm
    
    // Ghi dữ liệu người dùng nhập vào file gốc
    fprintf(file, "%s", data);
    
    // Đẩy con trỏ file về cuối để lấy kích thước dữ liệu vừa ghi
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    
    // Cấp phát bộ nhớ động dựa trên kích thước thực tế
    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Đưa con trỏ file về đầu file gốc để chuẩn bị ĐỌC
    fseek(file, 0, SEEK_SET);
    
    // ĐỌC dữ liệu từ 'file' (chứ không phải file_out) vào bộ đệm buffer
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Thêm ký tự kết thúc chuỗi

    // Ghi ngược chuỗi từ bộ đệm vào file_out
    for (int i = file_size - 1; i >= 0; i--) {
        fprintf(file_out, "%c", buffer[i]);
    }

    // Giải phóng bộ nhớ và đóng ĐẦY ĐỦ các file
    free(buffer);
    fclose(file);
    fclose(file_out);

    printf("Done! Check Data.txt and Data_reversed.txt\n");
    return 0;
}
