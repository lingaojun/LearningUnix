#include <setjmp.h>
#include "test.h"

jmp_buf buf;
int flag = 0;

void fun()
{
    printf("%s\n", __FUNCTION__);
    flag = 1;
    longjmp(buf, 0);
    printf("123\n");
    return;
}

