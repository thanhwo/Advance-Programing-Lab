#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
        int fd;
        char buffer[100];
        int n;
        fd = open("Hello.txt", O_RDONLY);
        if(fd < 0){
                perror("Error!");
                return 1;
        }
        lseek(fd, 6, SEEK_SET);
        n = read(fd, buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';
        printf("%s\n", buffer);

        close(fd);
        return 0;
}
