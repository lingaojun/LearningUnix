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

	sigemptyset(&zeromask); //类似于初始化信号集操作
    sigemptyset(&newmask);//类似于初始化信号集操作
    sigaddset(&newmask, SIGQUIT); //将退出信号加入目标信号集

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) //对两个信号集进行信号并集操作
        printf("sigprocmask error\n");

	while (quitflag == 0)
    {
        sigsuspend(&zeromask); //挂起进程直到信号触发
        printf("sigsuspend is running\n");
	}
    //quitflag = 0; //????

	printf("now back to main\n");
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("sigprocmask error\n");

	return 0;
}
