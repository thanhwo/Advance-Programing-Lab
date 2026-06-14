#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int sharedVar = 5;

int main() {
    int status;
    pid_t pid = fork();
    if (pid == 0) { 
        sharedVar++;
        printf("Child Process: sharedVar = %d\n", sharedVar);
        exit(0);
    } else {
      wait(&status);
        printf("Parent Process: sharedVar = %d\n", sharedVar); 
    }

    return 0;
}

