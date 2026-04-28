#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <string> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "%s\n", argv[1]);

    fclose(fp);
    printf("Written to file successfully.\n");

    return 0;
}
