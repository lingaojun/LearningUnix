#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    system("gcc -o exectest main2.c");
    if ((pid = fork()) < 0)
    {
        printf("fork error\n");
        return 0;
    }
    else if (pid == 0)
    {
        printf("start son\n");
        execve("./exectest", "hello new one", NULL);
    }


    return 0;

}
