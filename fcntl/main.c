#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


/*lock_set����*/
void lock_set(int fd, int type)
{
    struct flock lock;
    lock.l_whence = SEEK_SET;//��ֵlock�ṹ��
    lock.l_start = 0;
    lock.l_len = 0;
    while (1){
        lock.l_type = type;
        /*���ݲ�ͬ��typeֵ���ļ����������*/
        if ((fcntl(fd, F_SETLK, &lock)) == 0){
            if (lock.l_type == F_RDLCK)
                printf("read lock set by %d\n", getpid());
            else if (lock.l_type == F_WRLCK)
                printf("write lock set by %d\n", getpid());
            else if (lock.l_type == F_UNLCK)
                printf("release lock by %d\n", getpid());
            return;
        }
        /*�ж��ļ��Ƿ��������*/
        fcntl(fd, F_GETLK, &lock);
        /*�ж��ļ�����������ԭ��*/
        if (lock.l_type != F_UNLCK){
            /*/���ļ�����д����*/
            if (lock.l_type == F_RDLCK)
                printf("read lock already set by %d\n", lock.l_pid);
            /*���ļ����ж�ȡ��*/
            else if (lock.l_type == F_WRLCK)
                printf("write lock already set by %d\n", lock.l_pid);
            getchar();
        }
    }
}

int main(void)
{
    int fd;
    char *ch = "hello world\n";
    /*���ȴ��ļ�*/
    fd = open("hello", O_RDWR| O_APPEND, 0666);
    if (fd < 0){
        perror("open");
        exit(1);
    }
    /*���ļ���д����*/
    lock_set(fd, F_WRLCK);
    write(fd, ch, strlen(ch));
    sleep(10);
    /*���ļ�����*/
    //lock_set(fd, F_UNLCK);
    close(fd);
    exit(0);
}

