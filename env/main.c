#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *ch;
    char *bak;
    ch = getenv("PATH");
    system("echo $PATH");
    bak = malloc(sizeof(char) * strlen(ch) + 20); //�ڽ���strcpy֮ǰ��������ڴ�����
    printf("%s\n", ch);
    strcpy(bak, "PATH=");
    strcat(bak, ch);
    strcat(bak, ":/usr/");
    printf("%s\n",bak);
    putenv(bak);
    system("echo $PATH");
    return 0;
}
