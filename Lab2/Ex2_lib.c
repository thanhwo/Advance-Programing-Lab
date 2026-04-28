#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main() {
    int choice;
    char filename[100];
    char buffer[BUF_SIZE];

    printf("Enter new file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }

    printf("Select option:\n");
    printf("1. Enter content from keyboard\n");
    printf("2. Copy from another file\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter text (Ctrl+D to end):\n");
        while (fgets(buffer, BUF_SIZE, stdin)) {
            fputs(buffer, fp);
        }
    }
    else if (choice == 2) {
        char srcfile[100];
        printf("Enter source file name: ");
        scanf("%s", srcfile);

        FILE *src = fopen(srcfile, "r");
        if (src == NULL) {
            perror("Error opening source file");
            fclose(fp);
            return 1;
        }

        size_t n;
        while ((n = fread(buffer, 1, BUF_SIZE, src)) > 0) {
            fwrite(buffer, 1, n, fp);
        }

        fclose(src);
    }

    fclose(fp);
    printf("Done!\n");
    return 0;
}
