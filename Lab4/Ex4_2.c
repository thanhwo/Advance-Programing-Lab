#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int sharedVar = 5;  // Separate copy for each process

int main() {
//Write code to create child process here
    int status;
    pid_t pid = fork();
    if (pid == 0) { // Child process
     //Write code change value of global variable here
        sharedVar++;
        printf("Child Process: sharedVar = %d\n", sharedVar);
        exit(0);
    } else {
      //Write code to wait for child process to terminate here
      wait(&status);
        printf("Parent Process: sharedVar = %d\n", sharedVar); 
    }

    return 0;
}

