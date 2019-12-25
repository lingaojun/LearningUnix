#include <stdio.h>
#include <signal.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
	if (signo == SIGINT)
        printf("\ninterrupt\n");
    else if (signo == SIGQUIT)
    {
        quitflag = 1;
        printf("signo is SIGQUIT\n");
    }
}

int main(void)
{
	sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        printf("SIGINT error\n");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
        printf("SIGQUIT error\n");

	sigemptyset(&zeromask); //�����ڳ�ʼ���źż�����
    sigemptyset(&newmask);//�����ڳ�ʼ���źż�����
    sigaddset(&newmask, SIGQUIT); //���˳��źż���Ŀ���źż�

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) //�������źż������źŲ�������
        printf("sigprocmask error\n");

	while (quitflag == 0)
    {
        sigsuspend(&zeromask); //�������ֱ���źŴ���
        printf("sigsuspend is running\n");
	}
    //quitflag = 0; //????

	printf("now back to main\n");
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("sigprocmask error\n");

	return 0;
}
