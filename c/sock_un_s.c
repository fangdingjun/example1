#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <signal.h>

#define SOCK_PATH "/tmp/sock.listen"
void sighandler(int num){
    printf("get signal %d, exit..\n", num);
    unlink(SOCK_PATH);
    exit(0);
}

int main(int argc, char **argv)
{
    int fd;
    int i;
    struct sockaddr_un addr;
    int new_fd;
    fd_set fds;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    unlink(SOCK_PATH);

    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        close(fd);
        exit(-1);
    }

    if (listen(fd, 10) < 0) {
        perror("listen");
        close(fd);
        exit(-1);
    }

    struct sockaddr_un addr_c;
    socklen_t l;
    char buf[1024];
    int socks[100];
    int msg_len;
    memset(socks, 0, sizeof(socks));
    FD_ZERO(&fds);
    fd_set efds;
    FD_ZERO(&efds);
    int max_fd = 0;
    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);

    while (1) {
        FD_ZERO(&fds);
        FD_ZERO(&efds);
        FD_SET(fd, &fds);
        FD_SET(fd, &efds);
        max_fd = fd;
        for (i = 0; i < 100; i++) {
            if (socks[i] != 0) {
                if (socks[i] > max_fd) {
                    max_fd = socks[i];
                }
                FD_SET(socks[i], &fds);
                FD_SET(socks[i], &efds);
            }
        }
        if(select(max_fd + 1, &fds, NULL, &efds, NULL) < 0){
            perror("select");
            close(fd);
            exit(-1);
        }
        if (FD_ISSET(fd, &efds)) {
            printf("error on listen socket\n");
            close(fd);
            for (i = 0; i < 100; i++) {
                if (socks[i] != 0) {
                    close(socks[i]);
                }
            }
            exit(-1);
        }

        if (FD_ISSET(fd, &fds)) {
            memset(&addr_c, 0, sizeof(addr_c));
            l = sizeof(addr_c);
            new_fd = accept(fd, (struct sockaddr *) &addr_c, &l);
            if (new_fd < 0) {
                perror("accept");
                close(fd);
                exit(-1);
            }

            printf("connect from %s %d\n", addr_c.sun_path, new_fd);
            for (i = 0; i < 100; i++) {
                if (socks[i] == 0) {
                    socks[i] = new_fd;
                    break;
                }
            }
            if (i == 100) {
                printf("out of queue\n");
                close(new_fd);
            }
        }
        for (i = 0; i < 100; i++) {
            if (socks[i] == 0) {
                continue;
            }
                if (FD_ISSET(socks[i], &efds)) {
                    printf("close %d\n", socks[i]);
                    close(socks[i]);
                    socks[i] = 0;
                    continue;
                }
        
                if (FD_ISSET(socks[i], &fds)) {
                    msg_len = recv(socks[i], buf, 1024, 0);
                    if (msg_len < 0) {
                        perror("recv");
                        close(socks[i]);
                        socks[i] = 0;
                        continue;
                    }
                    if (msg_len == 0) {
                        printf("connection closed %d\n", socks[i]);
                        close(socks[i]);
                        socks[i] = 0;
                        continue;
                    }
                    printf("recv %.*s\n", msg_len, buf);
                    if (send(socks[i], buf, msg_len, 0) < 0) {
                        perror("send");
                        close(socks[i]);
                        socks[i] = 0;
                    }
                }               //if FD_ISSET

        }                       //for
    }                           //while
    close(fd);
    return 0;

}
