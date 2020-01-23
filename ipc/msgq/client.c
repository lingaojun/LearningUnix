#include <stdio.h>
#include <sys/ipc.h>
#include <signal.h>

struct msgstru {
	int msgtype;
    char msgbuf[2048];
};

void exitfun()
{
    printf("exitfun\n");
    msgctl(999,IPC_RMID,0); //删除消息队列
    exit(0);
}

int main(void)
{
    signal(SIGINT, exitfun);
    struct msgstru msg1;
    struct msgstru msg2;
	int res = msgget(999, IPC_EXCL);
    if (res < 0) {
		res = msgget(999, IPC_CREAT|0666);
    }

    pid_t fok;
    if ((fok = fork()) != 0) {
    while(1) {
			msg1.msgtype = 100;
	        strcpy(msg1.msgbuf, "the type is 100\n");
	        res = msgsnd(res, &msg1, sizeof(struct msgstru), IPC_NOWAIT);
        }
    } else if (fok == 0) {
    	while(1) {
			msg2.msgtype = 101;
	        strcpy(msg2.msgbuf, "the type is 101\n");
	        res = msgsnd(res, &msg2, sizeof(struct msgstru), IPC_NOWAIT);
	        }
        }

}

