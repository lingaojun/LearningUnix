#include <stdio.h>
#include <sys/select.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    fd_set readfds, writefds;//读, 写文件描述符
    int ready, nfds, fd;
    struct timeval timeout;//超时
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    for (int i = 0; i < 3; i++) { // 4改为3即只测试前三个系统fd即可select正确返回，第4个fd未进行具体赋值，所以select出错。
		fd = i;
		printf("the fd is %d\n", fd);
		nfds = i+1;
		//FD_SET(fd, &readfds);
		FD_SET(fd, &writefds);
    }

    fd  = open("test.txt", O_RDWR | O_CREAT, 0777);
    printf("fd = %d\n", fd);
    int tmp = fd;
    FD_SET(fd, &writefds);
    FD_SET(fd, &readfds);
    nfds  = fd + 1;

    ready = select(nfds, &readfds, &writefds, NULL, &timeout);
    printf("errno is %d\n", errno);
    printf("ready = %d\n", ready);
    for (fd = 0; fd < nfds; fd++)
        printf("%d: %s%s\n", fd, FD_ISSET(fd, &readfds) ? "r" : "",
                FD_ISSET(fd, &writefds) ? "w" : "");

    close(tmp);
}

