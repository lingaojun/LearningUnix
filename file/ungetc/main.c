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
        int c = getc(fp); //��fp�ж����ַ�
        if (c == 'l') {
        ungetc('p', fp); //��������������p����ѹ��fp��
        continue;
        }
        fputc(c, stdout);
        buffer[i++] = c;
        /*else
        ungetc(c, fp);  //��������������ѹ��fp�У���֤fp�������ԡ�
        //fgets(buffer, sizeof(buffer), fp); //�����������ζ�����
        fgets(buffer, sizeof(buffer), fp);
        fputs(buffer, stdout);
        */
    }
    printf("%s\n", buffer);
    fclose(fp);
    return 0;
}
