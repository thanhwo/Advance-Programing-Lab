#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

int main() {
    int choice;
    char filename[100];
    char buffer[BUF_SIZE];

    printf("Enter new file name: ");
    scanf("%s", filename);

    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error creating file");
        return 1;
    }

    printf("Select option:\n");
    printf("1. Enter content from keyboard\n");
    printf("2. Copy from another file\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    getchar(); // remove newline

    if (choice == 1) {
        printf("Enter text (Ctrl+D to end):\n");
        while (fgets(buffer, BUF_SIZE, stdin)) {
            write(fd, buffer, strlen(buffer));
        }
    } 
    else if (choice == 2) {
        char srcfile[100];
        printf("Enter source file name: ");
        scanf("%s", srcfile);

        int fd_src = open(srcfile, O_RDONLY);
        if (fd_src < 0) {
            perror("Error opening source file");
            close(fd);
            return 1;
        }

        int n;
        while ((n = read(fd_src, buffer, BUF_SIZE)) > 0) {
            write(fd, buffer, n);
        }

        close(fd_src);
    }

    close(fd);
    printf("Done!\n");
    return 0;
}
