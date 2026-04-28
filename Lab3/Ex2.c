include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static int idata = 1000;

int main(){
	int istack = 150;
	int status;
	int fd = open("Hello.txt", O_RDONLY);
	pid_t childPid = fork();

    if(childPid == 0){
		idata += 200;
		istack += 50;
		printf("idata= %d, istack = %d\n", idata, istack);
		lseek(fd, 7, SEEK_SET);
	}
	else{
		wait(&status);
		printf("idata= %d, istack = %d\n", idata, istack);
		char buffer[1000];
		int n = read(fd, buffer, sizeof(buffer) -1);
		buffer[n] = '\0';
	printf("Hello.txt: %s\n", buffer);	
	}
}
