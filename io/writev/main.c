#include <stdio.h>
#include <sys/uio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	struct iovec io[2];
    char *ch1 = "hello";
    char *ch2 = "world\n";
    io[0].iov_base = ch1;
    io[0].iov_len = strlen(ch1) + 1;
    printf("len is %d\n", io[0].iov_len);
    io[1].iov_base = ch2;
    io[1].iov_len = strlen(ch2) + 1;
    int nwritten = writev(STDOUT_FILENO, io, 2);
    printf("%ld bytes written.\n", nwritten);
    //int fd = fopen("test.txt", "a+");
    int fd=open("test.txt", O_WRONLY | O_CREAT, 0777);
    writev(fd, io, 2);
    close(fd);
	return 0;
}

