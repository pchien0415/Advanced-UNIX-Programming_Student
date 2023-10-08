#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <string.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[]){

    int inputFd, outputFd, openFlags;
    char buf[BUF_SIZE];
    ssize_t numRead;
    if (argc != 3 ) {
        printf("%s old_file new_file\n", argv[0]);
        return 0 ;
    }
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        printf("Can't opening file %s", argv[1]);
    outputFd = open(argv[2], O_RDWR);
    if (outputFd == -1)
        printf("Can't opening file %s", argv[2]);

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
         write(outputFd, buf, numRead);
    }

    return 0;
}