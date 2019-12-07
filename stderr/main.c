#include "errno.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    printf(strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]); //将错误码的意义作为argv[0]的后缀，例如当错误码errno = ENOENT时，表示的意思是找不到该文件，那么就会显示，./a.out: No such file or directory.
    exit(0);
    return 0;
}
