#include "errno.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));//其作用是格式化输出到一个流文件(stderr)中
    printf("%s", strerror(EACCES)); //这行不输出，说明只能将该字符串与对应终端的屏幕stderr组合使用
    errno = ENOENT;
    perror(argv[0]);//此时的错误码errno = ENOENT,表示文件不存在，那么此时输出应该是 ./a.out: No such file or directory
	errno = EACCES;
    perror(argv[0]);
    exit(0);
    return 0;
}
