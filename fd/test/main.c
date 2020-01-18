#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
const char *buf = "Hello World\n";
char stream[1024];
int main(void)
{
    int fd;
    if ((fd = open("test.txt", O_RDWR | O_CREAT, 0777)) < 0)
    {
        printf("open file error\n");
        return -1;
    }

    if (write(fd, buf, strlen(buf)) != strlen(buf))
    {
		printf("write failed\n");
        return -1;
    }

    if (write(fd, buf, strlen(buf)) != strlen(buf))
    {
		printf("write again failed\n");
        return -1;
    }

	if (lseek(fd, 0, SEEK_SET) == -1)
    {
        printf("seek error\n");
    }

  	int size = read(fd, stream, sizeof(stream));

    printf("size is %d\n the buffer is %s", size, stream);
    close(fd);
    return 0;
}
