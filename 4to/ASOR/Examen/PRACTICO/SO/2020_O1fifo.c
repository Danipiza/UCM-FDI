#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char** argv){
    int fd1, fd2, fd_max, s_fd;
    fd_set set;
    char buf[BUF_SIZE];
    size_t bytes_read;
    
    fd1=open("tub1", O_RDWR);
    fd2=open("tub2", O_RDWR);
    if(fd1==-1 || fd2==-1){ perror("open()"); exit(EXIT_FAILURE); }
    fd_max=(fd1>=fd2?fd1:fd2)+1;

    while(1){
        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        s_fd=select(fd_max, &set, NULL, NULL, NULL);
        if(s_fd==-1) { perror("select()"); exit(EXIT_FAILURE); }

        if(FD_ISSET(fd1, &set)){
            bytes_read=read(fd1, buf, BUF_SIZE);
            if(bytes_read==-1) { perror("tub1, read()"); exit(EXIT_FAILURE); }
            else if(bytes_read==0){
                if(close(fd1)==-1) { perror("tub1, close()"); exit(EXIT_FAILURE); }
                if(open("tub1", O_RDWR)==-1) { perror("tub1, open()"); exit(EXIT_FAILURE); }
            }
            else {
                buf[bytes_read-1]='\0';
                printf("Tuberia 1: %s\n", buf);
            }
        }
        if(FD_ISSET(fd2, &set)){
            bytes_read=read(fd2, buf, BUF_SIZE);
            if(bytes_read==-1) { perror("tub2, read()"); exit(EXIT_FAILURE); }
            else if(bytes_read==0){
                if(close(fd2)==-1) { perror("tub2, close()"); exit(EXIT_FAILURE); }
                if(open("tub2", O_RDWR)==-1) { perror("tub2, open()"); exit(EXIT_FAILURE); }
            }
            else {
                buf[bytes_read-1]='\0';
                printf("Tuberia 2: %s\n", buf);
            }
        }

    }



    return 0;
}