#include <stdio.h>
#include <pthread.h>

pthread_barrier_t b;

void pthread_fun1(char *ch)
{
	printf("%s", ch);
	pthread_barrier_wait(&b);
}

void pthread_fun2(char *ch)
{
	printf("%s", ch);
	pthread_barrier_wait(&b);
}



int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    pthread_barrier_init(&b, NULL, 3);
	pthread_create(&tid1, NULL, pthread_fun1, "TestPhreadBarrier1\n");
    pthread_create(&tid2, NULL, pthread_fun2, "TestPhreadBarrier2\n");
    sleep(2);
    pthread_barrier_wait(&b);
    pthread_barrier_destroy(&b);
    return 0;

}
