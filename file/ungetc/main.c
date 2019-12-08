#include <stdio.h>
#include "string.h"

int main(void)
{
    FILE *fp;
    char *str = "hello world";
    char *buffer;
    int i = 0;
    fp  = fopen("test.txt", "wb+");
    printf("strlen is %d\n", strlen(str));
    fwrite(str, sizeof(char), strlen(str), fp);
    fseek(fp, 0, SEEK_SET);
    rewind(fp);
    while(!feof(fp))
    {
        int c = getc(fp); //从fp中读出字符
        if (c == 'l') {
        ungetc('p', fp); //若满足条件，则将p重新压进fp中
        continue;
        }
        fputc(c, stdout);
        buffer[i++] = c;
        /*else
        ungetc(c, fp);  //若不满足则重新压进fp中，保证fp的完整性。
        //fgets(buffer, sizeof(buffer), fp); //把流内容依次读出来
        fgets(buffer, sizeof(buffer), fp);
        fputs(buffer, stdout);
        */
    }
    printf("%s\n", buffer);
    fclose(fp);
    return 0;
}
