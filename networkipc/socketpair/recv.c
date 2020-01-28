#include <stdio.h>
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>

struct threadinfo {
	int qid; //消息队列ID
    int fd; //文件描述符ID
};

struct mymesg {
	int type;
    char buf[128];
};

void thread_fun(void *arg)
{
	int n;
    struct mymesg m;
    struct threadinfo *tip = arg;
    while(1) {
		memset(&m, 0, sizeof(m));
        if ((n = msgrcv(tip->qid, &m, 128, 0, MSG_NOERROR)) < 0)
        	printf("msgrcv error, n = %d\n", n);
        if (write(tip->fd, m.buf, n) < 0) {
			printf("write error\n");
        }
    }

}

int main(void)
{
    struct pollfd pfd[3];
    struct threadinfo ti[3];
    int qid[3];
    int fd[2];
    pthread_t tid[3];
    char buf[128];
	for (int i = 0; i < 3; i++) {
		qid[i] = msgget((0x123 + i), IPC_CREAT | 0666); //创建消息队列，特征值是0x123+i
		printf("queue ID %d is %d\n", i, qid[i]);
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0) { //将fd与socket绑定
			printf("socketpair error\n");
        }

        pfd[i].fd = fd[0]; //read
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1]; //write
        pthread_create(&tid[i], NULL, thread_fun, &ti[i]);
    }

    while(1) {
		if (poll(pfd, 3, 0) < 0) {
			printf("poll error\n");
        }
        for (int i = 0; i < 3; i++) {
			if (pfd[i].revents & POLLIN) {
                int n;
				if ((n = read(pfd[i].fd, buf, sizeof(buf))) < 0) {
					printf("read error\n");
                }

                buf[n] = 0;
                printf("queue id is %d, the buf is %s\n", qid[i], buf);
            }
        }
    }
	return 0;
}
