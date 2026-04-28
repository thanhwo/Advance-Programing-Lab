#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s <directory_path\n", argv[0]);
        return 1;
    }
    int status;
    pid_t childPid = fork();
    if(childPid == 0){
        DIR *dir = opendir(argv[1]);
        if (dir == NULL){
            perror("Cannot open directory");
            return 1;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL){
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
        return 0;
	}
	else{
		wait(&status);
	} 
}
