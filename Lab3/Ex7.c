#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handle_sigint(int sig) {
    printf("\nProgram is terminated by user\n");
    exit(0);
}

void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("Files in directory: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;
        stat(entry->d_name, &file_stat);

        printf("- %s (size: %ld bytes)\n",
               entry->d_name,
               file_stat.st_size);
    }

    closedir(dir);
    printf("-----------------------------\n");
}

int main(int argc, char *argv[]) {
    const char *path = "."; 

    if (argc > 1) {
        path = argv[1];
    }

    signal(SIGINT, handle_sigint);

    while (1) {
        list_files(path);
        sleep(60);
    }

    return 0;
}
