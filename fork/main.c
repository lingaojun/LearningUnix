#include "unistd.h"
#include <stdio.h>

int main(void)
{
	pid_t pid;
	int count = 0;
    pid = fork();
    if (pid < 0)
    {
		return 0;
    }
    else if (pid == 0)
    {
		printf("this is a son\n");
        printf("the pid is %d\n", getpid());
        return 0;
    }
    else
    {
		printf("this is a father\n");
        printf("the pid is %d\n", getpid());
        return 0;
    }



}
