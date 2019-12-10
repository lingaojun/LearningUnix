#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int i;
    if((pid = vfork()) < 0)
    {
        printf("vfork error\n");
        return 0;
    }

    if (pid == 0)
    {
        printf("start son\n");
        i++;
        printf("son 's i = %d\n", i);
        exit(0);
    }
    printf("start father\n");
    printf("father 's i = %d\n", i);
    exit(0);
    return 0;
}
