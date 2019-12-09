#include <stdio.h>
#include "string.h"

int main(void)
{
    FILE *fp;
    char *str = "hello world\n";
    char *buffer;
    int c = 0;
    fp  = fopen("test.txt", "wb+");
    printf("strlen is %d\n", strlen(str));
    fwrite(str, sizeof(char), strlen(str), fp);
    fseek(fp, 0, SEEK_SET);
    rewind(fp);
    while(!feof(fp))
    {
        c = fgetc(fp); //从fp中读出字符
        if (c == 'l') {
	        ungetc('p', fp); //若满足条件，则将p重新压进fp中
	        continue;
        }
        if (c != -1)
        fputc(c, stdout);
    }

    fclose(fp);
    return 0;
}
