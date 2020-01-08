#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int a = 0;

void pthreadfun_1(char * argv)
{
	printf("%s", argv);
	pthread_mutex_lock(&mutex);
	printf("tid1 get the mutex\n");
	a++;
	printf("in tid1 a = %d\n", a);
	pthread_mutex_unlock(&mutex);
    //sleep(2);
}


void pthreadfun_2(char * argv)
{
	printf("%s", argv);
	int flag = pthread_mutex_lock(&mutex);
	//int flag = pthread_mutex_trylock(&mutex);
	printf("%d\n", flag);
	printf("tid2 get the mutex\n");
	a--;
	printf("in tid2 a = %d\n", a);
	pthread_mutex_unlock(&mutex);
	//sleep(1);
}


int main(void)
{
	pthread_t tid1;
    pthread_t tid2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, pthreadfun_1, "Test Mutex And PthreadFun1\n");
    pthread_create(&tid2, NULL, pthreadfun_2, "Test Mutes And PthreadFun2\n");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);


	return 0;
}
