#include <stdio.h>
#include <pthread.h>

pthread_t ntid;

void pthreadfun(char *argv)
{
	printf("argv = %s", argv);
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
	printf("pthread pid is %lu, tid is %lu (0x%lx)\n", pid, (unsigned long)tid);
    return;
}


int main(void)
{
    int err;
    err = pthread_create(&ntid, NULL, pthreadfun, "hello thread\n");
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
	printf("main pid is %lu, tid is %lu (0x%lx)\n", pid, (unsigned long)tid);
    sleep(1);
    //pthread_join(ntid);
    return 0;

}
