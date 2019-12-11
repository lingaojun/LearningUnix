#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(0);
    } else if (pid == 0) {
        if ((pid = fork()) < 0) {
            printf("fork twice error\n");
            exit(0);
        } else if (pid > 0) {
            exit(0); //第一个子进程退出,此时第二个进程由init进程处理。
        }

        sleep(1);
        printf("second child, parent pid = %d\n", getppid()); //此时第二个进程经过1s后，获取其父进程可以发现是1 也就是init进程
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)        /* wait for first child */
    printf("waitpid error\n");
	exit(0);
}
