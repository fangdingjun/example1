#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>

#define SOCK_PATH "/tmp/sock.listen"
#define LOCAL_PATH "/tmp/sock.go"

int main(int argc, char **argv){
    int fd;
    struct sockaddr_un addr;
    //int new_fd;
    char p[128];

    if (argc == 2){
        strcpy(p,argv[1]);
    }else{
        strcpy(p,LOCAL_PATH);
    }
    fd=socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0){
        perror("socket");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, p);

    unlink(p);

    if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        close(fd);
        unlink(p);
        exit(-1);
    }

    struct sockaddr_un addr_c;
    //socklen_t l;
    //char buf[1024];
    int msg_len;
    memset(&addr_c, 0, sizeof(addr_c));
    addr_c.sun_family = AF_UNIX;
    strcpy(addr_c.sun_path, SOCK_PATH);

    if(connect(fd, (struct sockaddr *)&addr_c, sizeof(addr_c)) < 0){
        perror("connect");
        close(fd);
        unlink(p);
        exit(-1);
    }
    char tty_in[1024];
    char s_in[1024];
    fd_set fds;
    fd_set efds;
    FD_ZERO(&fds);
    FD_ZERO(&efds);
    char *p1;

    while(1){
        FD_SET(fileno(stdin),&fds);
        FD_SET(fd,&fds);
        FD_SET(fd,&efds);
        select(fd+1, &fds,NULL,&efds,NULL);
        if(FD_ISSET(fileno(stdin),&fds)){
            p1=fgets(tty_in, 1024, stdin);
            if(p1 == NULL){
                printf("NULL or EOF\n");
                break;
            }
            printf("send\n");
            if(send(fd, tty_in, strlen(tty_in), 0) < 0){
                perror("send");
                break;
            }
        }
        if(FD_ISSET(fd,&efds)){
            printf("exit\n");
            break;
        }

        if(FD_ISSET(fd,&fds)){
            printf("recv\n");
            if((msg_len = recv(fd, s_in, 1024, 0)) < 0){
                perror("recv");
                break;
            }
            if(msg_len == 0){
                printf("connection closed\n");
                break;
            }
            printf("recv: %.*s\n", msg_len, s_in);
        }
    }
    close(fd);
    unlink(p);
    return 0;

}
