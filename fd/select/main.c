#include <stdio.h>
#include <sys/select.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    fd_set readfds, writefds;//��, д�ļ�������
    int ready, nfds, fd;
    struct timeval timeout;//��ʱ
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    for (int i = 0; i < 4; i++) { // 4��Ϊ3��ֻ����ǰ����ϵͳfd����select��ȷ���أ���4��fdδ���о��帳ֵ������select����
		fd = i;
		printf("the fd is %d\n", fd);
		nfds = i+1;
		//FD_SET(fd, &readfds);
		FD_SET(fd, &writefds);
    }


    ready = select(nfds, &readfds, &writefds, NULL, &timeout);
    printf("errno is %d\n", errno);
    printf("ready = %d\n", ready);
    for (fd = 0; fd < nfds; fd++)
        printf("%d: %s%s\n", fd, FD_ISSET(fd, &readfds) ? "r" : "",
                FD_ISSET(fd, &writefds) ? "w" : "");

}

