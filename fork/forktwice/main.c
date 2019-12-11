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
            exit(0); //��һ���ӽ����˳�,��ʱ�ڶ���������init���̴���
        }

        sleep(1);
        printf("second child, parent pid = %d\n", getppid()); //��ʱ�ڶ������̾���1s�󣬻�ȡ�丸���̿��Է�����1 Ҳ����init����
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)        /* wait for first child */
    printf("waitpid error\n");
	exit(0);
}
