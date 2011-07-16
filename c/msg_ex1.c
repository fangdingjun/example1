#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct msgbuf {
    int mtype;
    char mtext[10];
};

int main(int argc, char **argv)
{
    key_t key;
    struct msgbuf mbuf;
    //struct msqid_ds msg_ginfo, msg_sinfo;
    int gflags, sflags, rflags;
    gflags = IPC_CREAT | IPC_EXCL;
    int msgid;
    key = ftok("/etc/fstab", 'a');

    msgid = msgget(key, gflags | 00666);
    if (msgid == -1) {
        perror("msg create error");
        exit(1);
    }

    sflags = IPC_NOWAIT;
    mbuf.mtype = 1;
    strcpy(mbuf.mtext, "hello!");
    int reval;

    reval = msgsnd(msgid, &mbuf, sizeof(mbuf.mtext), sflags);
    if (reval == -1) {
        perror("msg send error");
        exit(1);
    }

    rflags = IPC_NOWAIT | MSG_NOERROR;
    memset(&mbuf, 0, sizeof(mbuf));
    reval = msgrcv(msgid, &mbuf, sizeof(mbuf),0, rflags);
    if (reval == -1) {
        perror("recv msg error");
        exit(1);
    }

    printf("type %d,content %s\n", mbuf.mtype, mbuf.mtext);

    reval = msgctl(msgid, IPC_RMID, NULL);
    if (reval == -1) {
        perror("rm msg error");
        exit(1);
    }

    return 0;
}
