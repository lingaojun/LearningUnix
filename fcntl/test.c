#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char *ch = "test\n";
    /*���ȴ��ļ�*/
    fd = open("hello", O_RDWR | O_APPEND, 0666);
    if (fd < 0){
        perror("open");
        exit(1);
    }
    /*���ļ���д����*/
    write(fd, ch, strlen(ch));
    //getchar();
    /*���ļ�����*/
    //lock_set(fd, F_UNLCK);
    close(fd);
    exit(0);
}

