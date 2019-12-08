#include <stdio.h>
#include "string.h"

int main(void)
{
    FILE *fp;
    char *str = "hello world";
    int getc;
    fp  = fopen("test.txt", "wb+");
    printf("strlen is %d\n", strlen(str));
    fwrite(str, sizeof(char), strlen(str), fp);
    fseek(fp, 0, SEEK_END);
    int lSize = ftell (fp);
    printf("size is %d\n", lSize);
    rewind(fp);
    char *buffer = (char*)malloc(sizeof(char)*lSize);
    int res = fread(buffer, sizeof(char), strlen(str), fp);
    fseek(fp, 0, SEEK_SET);
    getc = getc(fp);
    printf("%c\n", getc);
    getc = getc(fp); // µØÖ·Æ«ÒÆ
    printf("%c\n", getc);
    printf("buffer is %s\n", buffer);
    fclose(fp);
    free(buffer);
    return 0;
}
