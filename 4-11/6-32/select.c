#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

#define DEVFILE "/dev/devone0"

int main(void)
{
    int fd;
    fd_set rfds;
    struct timeval tv;
    int retval;
    unsigned char buf[64];
    ssize_t sz;
    int i;

    fd = open(DEVFILE, O_RDWR | O_NONBLOCK);
    if(fd == -1) {
        perror("open");
        exit(1);
    }

    do {
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        printf("select() ...\n");
        retval = select(fd + 1, &rfds, NULL, NULL, &tv);
        if(retval == -1){
            perror("select");
            break;
        }
        if(retval){
            break;
        }
    } while(retval == 0); /* time out */

    if(FD_ISSET(fd, &rfds)) {
        printf("read() ...\n");
        sz = read(fd, buf, sizeof(buf));
        printf("read() %d\n", sz);
        if(sz > 0) {
            for(i = 0; i < sz; i++){
                printf("%02x ", buf[i]);
            }
            printf("\n");
        }
        else {
            printf("errno %d\n", errno);
            perror("read");
        }
    } 
    
    close(fd);

    return 0;
}