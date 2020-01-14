#include <stdio.h>
#include <pthread.h>

pthread_t tid1;
pthread_t tid2;

void pthread_fun1(char *ch)
{
	printf("%s", ch);
	while(1)
    {
        //printf("Now The Thread1 Is Running\n");
    }

    pthread_exit((void *)1);
}

void pthread_fun2(char *ch)
{
	printf("%s", ch);
    int a = 0;
	while(!(a == 3))
    {
		sleep(1);
        a++;
    }
    pthread_cancel(tid1);
    printf("Now The Thread2 Notify The Thread1\n");
    pthread_exit((void *) 2);

}


int main(void)
{
	void *res1;
    void *res2;

    pthread_create(&tid1, NULL, &pthread_fun1, "TestThreadCancel_1\n");
    pthread_create(&tid2, NULL, &pthread_fun2, "TestThreadCancel_2\n");

    pthread_join(tid1, &res1);
    pthread_join(tid2, &res2);

    printf("Now The Main Thread Is Exit\n");
    printf("The Thread1 Res Is %d\n", (int)res1);
    printf("The Thread2 Res Is %d\n", (int)res2);

	return 0;
}
