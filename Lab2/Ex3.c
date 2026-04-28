#include <stdio.h>
#include <sys/stat.h>

int main(){
	char filename[100];
	struct stat fileStat;
	printf("Enter file: ");
	scanf("%s",filename);

	if (stat(filename, &fileStat) == -1){
		perror("Error");
		return 1;
	}
	printf("File size: %ld bytes\n", fileStat.st_size);
	printf("Access permissions: \n");
	printf("Owner: ");
    
	printf((fileStat.st_mode & S_IRUSR) ? "Read " : "");
   	printf((fileStat.st_mode & S_IWUSR) ? "Write " : "");
    	printf((fileStat.st_mode & S_IXUSR) ? "Execute " : "");
   	printf("\n");

    	printf("Group: ");
   	printf((fileStat.st_mode & S_IRGRP) ? "Read " : "");
    	printf((fileStat.st_mode & S_IWGRP) ? "Write " : "");
    	printf((fileStat.st_mode & S_IXGRP) ? "Execute " : "");
    	printf("\n");

    	printf("Others: ");
    	printf((fileStat.st_mode & S_IROTH) ? "Read " : "");
    	printf((fileStat.st_mode & S_IWOTH) ? "Write " : "");
	printf((fileStat.st_mode & S_IXOTH) ? "Execute " : "");
    	printf("\n");

    	return 0;
}
