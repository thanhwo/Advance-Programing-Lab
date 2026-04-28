#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CMDSIZ 32 

extern char **environ; 
void process_command(char* cmdbuf);
int main(int argc, char *argv[] ){
    int logout = 0, cmdsiz;
    char cmdbuf[CMDSIZ] ;
    while(!logout){
        write (1, "myshell> ", 9) ;
        cmdsiz = read(0, cmdbuf, CMDSIZ) ;
        cmdbuf[cmdsiz-1] = '\0' ;
        if (strcmp("logout", cmdbuf) == 0) ++logout ;
        else process_command(cmdbuf) ;
    }
}

void process_command(char* cmdbuf){
    pid_t pid;
    int status;
    pid = fork();

    if (pid < 0){
        perror("tao tien trinh con that bai");
        return;
    }
    else if( pid == 0 ){
        char *args[2];
        args[0] = cmdbuf;
        args[1] = NULL;
        
        if(execve(cmdbuf, args, environ) == -1){
            perror("Thuc thi that bai");
            exit(1);
        }
    }
    else{
        waitpid(pid, &status, 0);
    }
}
