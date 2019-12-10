#include "unistd.h"
#include <stdio.h>

int main(void)
{
	pid_t pid;
	int count = 0;
    printf("start\n");
    pid = fork();
    if (pid < 0)
    {
		return 0;
    }
    else if (pid == 0)
    {
		printf("this is a son\n");
        printf("the pid is %d\n", getpid());
        printf("the uid is %d\n", getuid());
        printf("the gid is %d\n", getgid());
    }
    else
    {
        sleep(1);
		printf("this is a father\n");
        printf("the pid is %d\n", getpid());
        printf("the uid is %d\n", getuid());
        printf("the gid is %d\n", getgid());
    }

    printf("end\n");

}
