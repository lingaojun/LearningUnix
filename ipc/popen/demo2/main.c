#include <stdio.h>
#include <unistd.h>

FILE* my_popen(const char *cmd, const char *type)
{
	int fd[2];
    FILE *fp;
    int pid;
    if ((*type != 'r' && *type != 'w') || strlen(type) > 1) {
		printf("error type\n");
        exit(0);
    }

	pipe(fd);
    execl("/bin/sh", "sh", "-c", "ls *.c", NULL);
	if (*type == 'r') {
        dup2(fd[1],  STDOUT_FILENO); //将写端与终端输出绑定，即终端输出什么，写端就写入什么

    } else if (*type == 'w') {
		dup2(fd[0], STDIN_FILENO);
    }

    fp = fdopen(fd[0], type);
    if (*type == 'r') {
        printf("2\n");
		close(fd[1]);
        fp = fdopen(fd[0], type);
    } else if (*type == 'w') {
		close(fd[1]);
        fp = fdopen(fd[0], type);
    }

    return fp;
}

void my_pclose(FILE *fp)
{
	fp = NULL;
}

int main(void)
{
    char *buf = malloc(259);
	FILE *file = my_popen("ls *.c", "r");
    fread(buf, sizeof(char), 256, file);
    printf("buf is %s\n", buf);
    my_pclose(file);
    return 0;
}
