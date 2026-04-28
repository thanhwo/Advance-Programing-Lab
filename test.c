#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    if (fork()) {
	wait(NULL);
        printf("I am parent\n");
    } else {
	char* argv[] = {"ls","-l",NULL};
	char* envp[] = {NULL};
	execve("/bin/ls", argv,envp);
        printf("I am child\n");
    }
    return 0;
}
