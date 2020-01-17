#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


/*lock_set函数*/
void lock_set(int fd, int type)
{
    struct flock lock;
    lock.l_whence = SEEK_SET;//赋值lock结构体
    lock.l_start = 0;
    lock.l_len = 0;
    while (1){
        lock.l_type = type;
        /*根据不同的type值给文件上锁或解锁*/
        if ((fcntl(fd, F_SETLK, &lock)) == 0){
            if (lock.l_type == F_RDLCK)
                printf("read lock set by %d\n", getpid());
            else if (lock.l_type == F_WRLCK)
                printf("write lock set by %d\n", getpid());
            else if (lock.l_type == F_UNLCK)
                printf("release lock by %d\n", getpid());
            return;
        }
        /*判断文件是否可以上锁*/
        fcntl(fd, F_GETLK, &lock);
        /*判断文件不能上锁的原因*/
        if (lock.l_type != F_UNLCK){
            /*/该文件已有写入锁*/
            if (lock.l_type == F_RDLCK)
                printf("read lock already set by %d\n", lock.l_pid);
            /*该文件已有读取锁*/
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
    /*首先打开文件*/
    fd = open("hello", O_RDWR| O_APPEND, 0666);
    if (fd < 0){
        perror("open");
        exit(1);
    }
    /*给文件上写入锁*/
    lock_set(fd, F_WRLCK);
    write(fd, ch, strlen(ch));
    sleep(10);
    /*给文件解锁*/
    //lock_set(fd, F_UNLCK);
    close(fd);
    exit(0);
}

