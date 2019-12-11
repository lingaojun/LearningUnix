#include "unistd.h"
#include <stdio.h>
#include "test.h"

int main(void)
{
    test();
    printf("test fork\n");
    return 0;
}
