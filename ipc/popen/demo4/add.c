#include <stdio.h>
#include <unistd.h>


int main(void)
{
    int n;
    int int1,int2;
	char buf[256];
    while(n = read(STDIN_FILENO, buf, 256) > 0) {
		if (sscanf(buf, "%d%d", &int1, &int2) == 2) {
			sprintf(buf, "the res is %d\n", int1 + int2);
            n = strlen(buf);
            write(STDOUT_FILENO, buf, n);
        } else {
			write(STDOUT_FILENO, "error argv", 11);
        }
    }

    return 0;
}
