#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
    pid_t pid;
    char buf[11];
    int file;
    int writefd;
    int readfd;

    if (pipe(fd) < 0) {
		printf("pipe error\n");
    }

    if ((pid = fork()) == 0) {
		close(fd[1]); //close write
        printf("read ret %d\n", read(fd[0], buf, 11));
        write(STDOUT_FILENO, buf, 11); //Êä³öÖÁÖÕ¶Ë
    } else if ((pid = fork()) > 0) {
		close(fd[0]); //close read
		printf("write ret %d\n", write(fd[1], "helloworld", 11));
        //waitpid(pid, NULL, 0);
    }

	return 0;
}
