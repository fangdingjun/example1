#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct msgbuf {
    int mtype;
    char mtext[100];
};

int msend(int msgid, char *msg)
{
    int reval;
    struct msgbuf mbuf;
    mbuf.mtype = 10;
    strcpy(mbuf.mtext, msg);
    reval = msgsnd(msgid, &mbuf, sizeof(mbuf), IPC_NOWAIT);
    if (reval == -1) {
        perror("msg send error");
        return -1;
    }

    return 0;
}

int mrecv(int msgid)
{
    int reval;
    struct msgbuf mbuf;
    memset(&mbuf, 0, sizeof(mbuf));
    reval = msgrcv(msgid, &mbuf, sizeof(mbuf), 0, IPC_NOWAIT);
    if (reval == -1) {
        perror("msg rcv error");
        return -1;
    }

    printf("msg type: %d,msg text: %s\n", mbuf.mtype, mbuf.mtext);

    return 0;
}

void usage()
{
    fprintf(stderr,
            "Usage:\n"
            "\t%s send 'msg text'\n" "\t%s recv\n", "msg_do", "msg_do");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        usage();
        return -1;
    }

    int msgid;
    key_t key;
    key = ftok("/etc/", 'a');

    msgid = msgget(key, IPC_CREAT | 00666);
    if (msgid == -1) {
        perror("create msg error");
        return -1;
    }

    if (strcmp(argv[1], "send") == 0 || strcmp(argv[1], "recv") == 0) {
        if (!strcmp(argv[1], "send")) {
            if (argc != 3) {
                usage();
                return -1;
            }
           return  msend(msgid, argv[2]);
        } else {
            return mrecv(msgid);
        }
    } else {
        usage();
        return -1;
    }
}
