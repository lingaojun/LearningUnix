#include <stdio.h>
#include <pthread.h>

void clean(char *ch)
{
	printf("clean starting\nthe param is %s", ch);
}

void pthreadfun_1(char *argv)
{
	printf("%s", argv);
	pthread_cleanup_push(clean, "hello pthreadfun_1 first cleanfun\n");
 	pthread_cleanup_push(clean, "hello pthreadfun_1 second cleanfun\n");
    if (argv)
        return;
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit(1);
}

void pthreadfun_2(char *argv)
{
	printf("%s", argv);
	pthread_cleanup_push(clean, "hello pthreadfun_2 first cleanfun\n");
 	pthread_cleanup_push(clean, "hello pthreadfun_2 second cleanfun\n");
    if (argv)
        pthread_exit(1);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit(1);
}

void pthreadfun_3(char *argv)
{
	printf("%s", argv);
	pthread_cleanup_push(clean, "hello pthreadfun_3 first cleanfun\n");
 	pthread_cleanup_push(clean, "hello pthreadfun_3 second cleanfun\n");
    pthread_cleanup_pop(1); // !0 删除上一次添加的清理函数
    pthread_cleanup_pop(0);
    pthread_exit(1);
}


int main(void)
{
    void *flag;
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    pthread_create(&tid1, NULL, pthreadfun_1, "PthreadCleanTest1\n");
    pthread_join(tid1, flag);

    pthread_create(&tid2, NULL, pthreadfun_2, "PthreadCleanTest2\n");
    pthread_join(tid2, flag);

    pthread_create(&tid3, NULL, pthreadfun_3, "PthreadCleanTest3\n");
    pthread_join(tid3, flag);

	return 0;
}
