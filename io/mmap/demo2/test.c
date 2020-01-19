#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct {
    char name[7];
    int age;
}human;


int main(void)
{
	int fd = open("test.txt", O_RDWR, 0777);
    human *out = (human *)mmap(NULL, sizeof(human), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (out == MAP_FAILED) {
		printf("mmap error\n");
    }
    printf("out.name = %sout.age = %d\n", out->name, out->age);
    munmap(out, sizeof(human));

	return 0;
}
