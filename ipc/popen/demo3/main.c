#include <stdio.h>

int main(void)
{
	int c;
    while ((c = getchar()) != EOF) {
		if (isupper(c))
            c = tolower(c);
        if (putchar(c) == EOF) {
			printf("putchar error\n");
        }
        if (c == '\n') {
			fflush(stdout);
        }
    }
	return 0;
}
