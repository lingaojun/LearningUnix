#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct {
    char name[7];
    int age;
}human;

int main(void)
{
	int fd = open("test.txt", O_RDWR | O_CREAT, 0777);
    human *test;
    write(fd,"", 7);
    test = (human *)mmap(NULL, sizeof(human), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (test == MAP_FAILED) {
		printf("mmap error\n");
    }

    strcpy(test->name, "lingj\n");
    test->age = 20;

    if (vfork() == 0) {
		human *out;
        out = (human *)mmap(NULL, sizeof(human), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        printf("out->name is %sout->age is %d\n", out->name, out->age);
        exit(0);
        munmap(out,sizeof(human));
    }

    close(fd);
    munmap(test,sizeof(human));

	return 0;
}
