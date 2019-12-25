#include <stdio.h>
#include <setjmp.h>
#include <time.h>
#include <signal.h>

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main(void)
{
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
        printf("SIGUSR1 error\n");
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        printf("SIGALRM error\n");

	printf("starting main\n");

    if (sigsetjmp(jmpbuf, 1))
    {
		printf("end main\n");
        return 0;
    }
    canjump = 1;

    for(;;)
        pause();
}

static void sig_usr1(int signo)
{
	time_t starttime;
    if (canjump == 0)
    {
		return;
    }

	printf("start sig_usr1\n");
    alarm(3);
	starttime = time(NULL);

    for (;;)
        if (time(NULL) > starttime + 5)
            break;

    printf("end sig_usr1\n");

    canjump = 0;
    siglongjmp(jmpbuf, 1);
}

static void sig_alrm(int signo)
{
    printf("now in sig_alrm\n");
}
