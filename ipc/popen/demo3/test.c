#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char buf[256];
    FILE *fp;
    system("gcc main.c -o main");
    fp = popen("./main", "r");
    while (1) {
	    fputs("prompt > ", stdout);
	    fflush(stdout);
	    fgets(buf, 256, fp);
	    fputs(buf, stdout);
    }
    pclose(fp);
	return 0;
}
