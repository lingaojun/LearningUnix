#include <stdio.h>

#include "test.h"


int main(void)
{
    int jmp = setjmp(buf);
    printf("jmp = %d\n", jmp);
    printf("flag = %d\n", flag);
    if(!jmp)
    {
        fun();
    }

    return 0;
}
