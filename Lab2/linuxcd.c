#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("chdir failed");
        return 1;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Changed directory to: %s\n", cwd);
    }

    return 0;
}
