#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1){
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if(pid < 0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execlp("ls", "ls", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        dup2(fd[0], STDIN_FILENO);

        close(fd[1]);
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }
    return 0;
}
