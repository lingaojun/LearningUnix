#include "errno.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    printf(strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]); //���������������Ϊargv[0]�ĺ�׺�����統������errno = ENOENTʱ����ʾ����˼���Ҳ������ļ�����ô�ͻ���ʾ��./a.out: No such file or directory.
    exit(0);
    return 0;
}
