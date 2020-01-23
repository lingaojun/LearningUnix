#include <stdio.h>
#include <sys/ipc.h>

struct msgstru {
	int msgtype;
    char msgbuf[2048];
};

void msgrecv(int i)
{
	int msgid;
    struct msgstru msg;
	while(1) {
		msgid = msgget(999, IPC_EXCL);
        printf("msgid is %d\n", msgid);
        if (msgid == -1 ) {
			sleep(1);
            continue;
        }
        msgrcv(msgid, &msg, sizeof(msg), 101, IPC_NOWAIT);
        //msgrcv(msgid, &msg, sizeof(msg), 0, IPC_NOWAIT);
		printf("the chile-%d buf'type is %d, buf is %s\n", i, msg.msgtype, msg.msgbuf);
    }

}

int main(void)
{
	msgrecv(1);
}


