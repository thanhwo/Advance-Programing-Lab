#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CMDSIZ 1024
#define MAXARGS 64  

void process_command(char* cmdbuf);

int main(int argc, char *argv[]) {
    int logout = 0;
    char cmdbuf[CMDSIZ];

    while (!logout) {
        printf("myshell> ");
        fflush(stdout); 

        if (fgets(cmdbuf, CMDSIZ, stdin) == NULL) {
            printf("\n");
            break; 
        }

        cmdbuf[strcspn(cmdbuf, "\n")] = '\0';
        if (strlen(cmdbuf) == 0) {
            continue;
        }

        if (strcmp("logout", cmdbuf) == 0 || strcmp("exit", cmdbuf) == 0) {
            logout = 1;
        } else {
            process_command(cmdbuf);
        }
    }
    return 0;
}

void process_command(char* cmdbuf) {
    pid_t pid;
    int status;
    char *args[MAXARGS];
    int i = 0;

    char *token = strtok(cmdbuf, " ");
    while (token != NULL && i < MAXARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; 

    pid = fork();

    if (pid < 0) {
        perror("tao tien trinh con that bai");
        return;
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("Thuc thi that bai");
            exit(1);
        }
    } else {
        waitpid(pid, &status, 0);
    }
}
