#include "errno.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));//�������Ǹ�ʽ�������һ�����ļ�(stderr)��
    printf("%s", strerror(EACCES)); //���в������˵��ֻ�ܽ����ַ������Ӧ�ն˵���Ļstderr���ʹ��
    errno = ENOENT;
    perror(argv[0]);//��ʱ�Ĵ�����errno = ENOENT,��ʾ�ļ������ڣ���ô��ʱ���Ӧ���� ./a.out: No such file or directory
	errno = EACCES;
    perror(argv[0]);
    exit(0);
    return 0;
}
