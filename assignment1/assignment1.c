#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main(){
    int fd = open("sample.txt", O_RDWR);
    char buffer[256] = {"\0"};
    lseek(fd, 14, SEEK_SET);
    read(fd, buffer, sizeof(buffer));
    printf("%s\n",buffer);
    lseek(fd, 14, SEEK_SET);
    write(fd, "NTHU student.", 13);
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, sizeof(buffer));
    printf("%s",buffer);
}