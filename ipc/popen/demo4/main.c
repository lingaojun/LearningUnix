#include <stdio.h>
#include <unistd.h>


int main(void)
{
    int n;
    int pid;
	int fd1[2], fd2[2];
    char buf[256];
    pipe(fd1);
    pipe(fd2);

    if ((pid = fork()) > 0 ) {  //parent 负责发送初始两个数字
		close(fd1[0]);
        close(fd2[1]);
        while (fgets(buf, 256, stdin) != NULL) {
            //printf("get buf\n");
			n = strlen(buf);
            write(fd1[1], buf, n);
            //printf("write to sdtin success\n");
            n = read(fd2[0], buf, 256);
            printf("read buf success\n");
            if (0 == n) {
				printf("child has error\n");
            }
            buf[n] = 0;
            fputs(buf, stdout);
        }


    } else if (pid == 0) {
        //printf("enter child\n");
		close(fd1[1]);
        close(fd2[0]);
        dup2(fd1[0], STDIN_FILENO);
        close(fd1[0]);
        dup2(fd2[1], STDOUT_FILENO);
        close(fd2[1]);
        //printf("start add\n");
        execl("./add", "add", 0);
        //printf("end add\n");
        exit(0);
    }
	return 0;
}
