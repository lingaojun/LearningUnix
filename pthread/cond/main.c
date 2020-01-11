#include <stdio.h>
#include <pthread.h>

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

int ch[20] = {1};

struct msg {
	struct msg *next;
};

struct msg *workq;

void pthread_fun1(char *argv)
{
    printf("%s", argv);
    struct msg *mp;
    while(1)
    {
        pthread_mutex_lock(&qlock);
        printf("get the mutex\n");
	    while(workq == NULL)
	    {
	        //printf("get the mutex\n");
			pthread_cond_wait(&qready, &qlock);
			mp = workq;
            workq = mp->next; //遍历任务队列workq mp为临时变量
	        printf("after cond wait\n");
	        pthread_mutex_unlock(&qlock);

	    }
    }
    pthread_exit((void*) 1);
}

void pthread_fun2(struct msg *mp)
{
    printf("Hello Thread2\n");
    sleep(1);
    pthread_mutex_lock(&qlock);
	mp->next = workq;
	workq = mp;
    if (workq != NULL) {
        printf("workq is not NULL now\n");
    }
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
    //pthread_exit((void *)2);
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;
    void *res;
    struct msg Msg;
    Msg.next = NULL;
	pthread_create(&tid1, NULL, pthread_fun1, "cond1 testing\n");
    pthread_create(&tid2, NULL, pthread_fun2, &Msg);

    pthread_join(tid1, &res);
    pthread_join(tid2, &res);
    return 0;
}
