#include <stdio.h>
#include <pthread.h>

pthread_key_t key;
pthread_once_t int_done = PTHREAD_ONCE_INIT;
struct str {
	char *ch;
    int flag;
};

void *ExitKeyMode()
{
	printf("%s\n", __FUNCTION__);
}

void *OnceFun(void)
{
    printf("%s\n", __FUNCTION__);
	pthread_key_create(&key, ExitKeyMode);
}

void pthread_fun1(struct str *str)
{
	printf("%s", str->ch);
    const void *ptr;
    pthread_once(&int_done, OnceFun);
    if ((ptr = pthread_getspecific(key)) == NULL) {
		ptr = malloc(5);
	    if (strstr(str->ch, "1") != NULL) {
			printf("Thread1 success\n");
            strcpy((char *)ptr, "tid1");
	    } else if (strstr(str->ch, "2") != NULL) {
			printf("Thread2 success\n");
            strcpy((char *)ptr, "tid2");
	    }
        pthread_setspecific(key, ptr); //将键与数据关联起来
	} else {
		printf("the Key be called\n");
    }


    while(1) {
        const void *res = pthread_getspecific(key);
        printf("res = %s\n", (char *)res);
		sleep(1);
        free(ptr);
        pthread_exit((void *) str->flag);
    }

}

int main(void)
{
	pthread_t tid1;
    pthread_t tid2;
	void *res1;
    void *res2;
	struct str str1 = {"Test Key_1\n", 1};
	struct str str2 = {"Test Key_2\n", 2};

    pthread_create(&tid1, NULL, pthread_fun1, &str1);
    pthread_create(&tid2, NULL, pthread_fun1, &str2);

	pthread_join(tid1, &res1);
    pthread_join(tid2, &res2);
    pthread_key_delete(key);
    printf("res1 = %d\nres2 = %d\n", (int *)res1, (int *)res2);
	return 0;
}

