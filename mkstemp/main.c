#include <stdio.h>

void make_temp(char *ch)
{
    int fd;
    //struct stat sbuf;
    if (fd = mkstemp(ch) < 0)
        printf("mkstemp error\n");
    close(fd);
}

int main(void)
{
    char good_temp[] = "/tmp/dirXXXXXX";
    char *bad_temp = "/tmp/dirXXXXXX";
    //make_temp(bad_temp);
    make_temp(good_temp);

    return 0;
}
