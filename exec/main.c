#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char buf[80];
    getcwd(buf,sizeof(buf));
    char * argv[]={"123","456",(char *)0};
    char * envp[]={"it's doesn't matter",0};
    printf("current working directory: %s\n", buf);
    strcat(buf, "/exectest");
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
        printf("now the path  = %s\n", buf);
        execve(buf, argv, envp);
    }


    return 0;

}
