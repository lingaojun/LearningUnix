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
        c = fgetc(fp); //��fp�ж����ַ�
        if (c == 'l') {
	        ungetc('p', fp); //��������������p����ѹ��fp��
	        continue;
        }
        if (c != -1)
        fputc(c, stdout);
    }

    fclose(fp);
    return 0;
}
