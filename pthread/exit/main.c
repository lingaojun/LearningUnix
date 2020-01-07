#include <stdio.h>
#include <pthread.h>

void pthreadfun_1(char * argv)
{
	printf("%s", argv);
    pthread_exit((void *)1314);
}

int main(void)
{
    int err;
    int res;
    pthread_t tid;
    err = pthread_create(&tid, NULL, pthreadfun_1, "Testing Pthread Exit\n");
    pthread_join(tid, &res);
    printf("the pthread ret = %d\n", res);
	return 0;
}
