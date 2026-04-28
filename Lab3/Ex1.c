#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd = fork();
    int status;
    if(fd){
	wait(&status);
        printf("I am the parent\n");
    }
    else{
        printf("This is the child\n");
    }
    return 0;
}
