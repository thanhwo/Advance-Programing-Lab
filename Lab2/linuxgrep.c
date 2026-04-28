#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("Word not found\n");
    }

    fclose(fp);
    return 0;
}
