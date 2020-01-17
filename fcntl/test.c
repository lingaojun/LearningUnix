#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char *ch = "test\n";
    /*首先打开文件*/
    fd = open("hello", O_RDWR | O_APPEND, 0666);
    if (fd < 0){
        perror("open");
        exit(1);
    }
    /*给文件上写入锁*/
    write(fd, ch, strlen(ch));
    //getchar();
    /*给文件解锁*/
    //lock_set(fd, F_UNLCK);
    close(fd);
    exit(0);
}

