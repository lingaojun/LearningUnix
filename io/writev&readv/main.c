#include <stdio.h>
#include <sys/uio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	struct iovec writevio[2];
    struct iovec readvio[2];
    char *ch1 = "hello";
    char *ch2 = "world\n";
    writevio[0].iov_base = ch1;
    writevio[0].iov_len = strlen(ch1) + 1;
    printf("len is %d\n", writevio[0].iov_len);
    writevio[1].iov_base = ch2;
    writevio[1].iov_len = strlen(ch2) + 1;
    int nwritten = writev(STDOUT_FILENO, writevio, 2);
    printf("%ld bytes written.\n", nwritten);
    //int fd = fopen("test.txt", "a+");
    int fd=open("test.txt", O_WRONLY | O_CREAT, 0777);
    writev(fd, writevio, 0);
    close(fd);

	readvio[0].iov_base = malloc(writevio[0].iov_len);
    readvio[0].iov_len = writevio[0].iov_len;
    readvio[1].iov_base =  malloc(writevio[1].iov_len);
    readvio[1].iov_len = writevio[1].iov_len;
    fd=open("test.txt", O_RDONLY);
    readv(fd, readvio, 2);
    printf("%s\n%s", readvio[0].iov_base, readvio[1].iov_base);
    close(fd);

	return 0;
}

