#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;
static void sig_alarm(int signo)
{
 	longjmp(env_alrm, 1);
}

unsigned int my_sleep(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        return seconds;
    if (setjmp(env_alrm) == 0) {
		alarm(seconds);
        pause();
    }
    return (alarm(0));
}

static void sig_init(int signo)
{
	int i,j;
    volatile k;
    printf("\nsig_init starting\n");
    for(int i = 0; i < 6; i++)
    {
		sleep(1);
        printf("sleep once\n");
    }
    printf("sig_init end\n");
}
void fun(void)
{
	alarm(5);
    sleep(2);
    printf("alarm return is %d", alarm(2)); //二次调用alarm时，会返回第一次的余留值作为二次调用的返回值
}

int main(void)
{
	//fun();
	unsigned int unslept;
    if (signal(SIGINT, sig_init) == SIG_ERR)
        printf("SIG ERR\n");
    unslept = my_sleep(5);
    printf("my_sleep returned : %u\n", unslept);
	return 0;
}
