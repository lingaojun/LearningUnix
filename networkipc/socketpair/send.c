#include <stdio.h>
#include <sys/msg.h>

struct mymesg {
	int type;
    char buf[128];
};

int main(int argc, char *argv[])
{
	key_t key;
    long qid;
    struct mymesg m;
    for (int i = 0;i < 3; i++) {
	    key = strtol("0x123", NULL, 0);
	    qid = msgget(key+i, 0);
	    printf("qid is %ld", qid);
	    memset(&m, 0, sizeof(m));
	    strncpy(m.buf, "hello world", 128-1);
	    int cnt = strlen(m.buf);
	    m.type = 1;
	    if (msgsnd(qid, &m, cnt, 0) < 0) {
			printf("msgsnd error\n");
	    }
    }
	return 0;
}
