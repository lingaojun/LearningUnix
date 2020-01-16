#include <stdio.h>
#include <pthread.h>
#include <signal.h>

int quitflag;
sigset_t mask;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitcond = PTHREAD_COND_INITIALIZER;

void pthread_fun1(char *ch)
{
    printf("%s", ch);
    int err, signo;
    while(1)
    {
		err = sigwait(&mask, &signo);
        if (err != 0)
            pthread_exit((void *) -1);
        switch (signo) {
			case SIGINT:
                printf("\ninterrupt\n");
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&waitcond);
                pthread_exit((void *) 1);
            default:
                printf("unexpected signal %d\n", signo);
                pthread_exit((void*) 0);
        }
    }
}

int main(void)
{
    int err;
    void *ret;
    sigset_t oldmask;
    pthread_t tid;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
	pthread_sigmask(SIG_BLOCK, &mask, &oldmask);

    pthread_create(&tid, NULL, pthread_fun1, "Test PthreadSig\n");

    pthread_mutex_lock(&lock);
    while(quitflag == 0) {
		pthread_cond_wait(&waitcond, &lock);
    }

	pthread_mutex_unlock(&lock);

    quitflag = 0;

    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    pthread_join(tid, &ret);
    printf("ret = %d\n", (int *)ret);
	return 0;
}
