#include <stdio.h>

int main(void)
{
	FILE *fd = popen("ls", "r");
    char *buf = malloc(sizeof(char) * 256);
    fread(buf, sizeof(char), 256, fd);
    printf("buf is %s", buf);
    pclose(fd);
    return 0;
}
