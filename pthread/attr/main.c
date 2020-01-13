#include <stdio.h>
#include <pthread.h>

int a = 0;

void pthread_fun1(char *ch)
{

	printf("%s", ch);
	while(1)
   	{
		sleep(1);
        a++;
        printf("a = %d\n", a);
	}
}


int main(void)
{
	pthread_t tid1;
    pthread_t tid2;
    pthread_attr_t attr;
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&tid1, &attr, pthread_fun1, "Test Attr\n");

	pthread_attr_destroy(&attr);
    while(!(a == 10)) {
		printf("wait a to 10\n");
        sleep(1);
    }
	return 0;
 }
