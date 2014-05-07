#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int epfd;
    struct epoll_event ev;
    struct sockaddr_in saddr;
    int port = 80;
    struct hostent *ht;
    char host[256]="www.google.com";

    if (argc > 1){
        strcpy(host,argv[1]);
    }

    if(argc == 3){
        port=atoi(argv[2]);
    }

    ht = gethostbyname(host);

    if(ht == NULL){
        herror("gethostbyname");
        exit(-1);
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    //saddr.sin_addr.s_addr = inet_addr("114.112.95.18");
    memcpy(&saddr.sin_addr, ht->h_addr, ht->h_length);


    epfd = epoll_create(3);
    if (epfd < 0) {
        perror("epoll_create");
        exit(-1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(-1);
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        perror("fcntl getfl");
        exit(-1);
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("fcntl setFL");
        exit(-1);
    }
    ev.data.fd = sockfd;
    ev.events = EPOLLOUT | EPOLLHUP;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
        perror("epoll_ctl");
        exit(-1);
    }
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        if (errno != EAGAIN && errno != EINPROGRESS) {
            perror("connect");
            exit(-1);
        }
    }
    int nr_events;
    while (1) {
        nr_events = epoll_wait(epfd, &ev, 1, 2000);
        if (nr_events < 0) {
            perror("epoll_wait");
            exit(-1);
        }
        if(nr_events == 0){
            printf("timeout\n");
            exit(-1);
        }
        if (ev.events & EPOLLOUT) {
            int error = 0;
            socklen_t len = sizeof(error);
            int nsend;
            if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
                perror("getsockopt");
                exit(-1);
            }
            if (error != 0) {
                printf("connect failed\n");
                exit(-1);
            }
            char p[256];

            sprintf(p, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\nUser-Agent: libcurl/1.8.1\r\n\r\n", host);
            nsend = send(sockfd, p, strlen(p), 0);
            if (nsend < 0) {
                if (errno != EAGAIN && errno != EINTR) {
                    perror("send");
                    exit(-1);
                }
            }
            struct epoll_event ev1;
            ev1.data.fd = sockfd;
            ev1.events = EPOLLIN | EPOLLHUP;
            if (epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev1) < 0) {
                perror("epoll_ctl 2");
                exit(-1);
            }
        } else if (ev.events & EPOLLIN) {
            char buf[1024];
            int nrecv;
            if ((nrecv = recv(sockfd, buf, 1024, 0)) < 0) {
                perror("recv");
                exit(-1);
            }
            if (nrecv == 0) {
                printf("closed\n");
                exit(-1);
            }
            printf("%.*s", nrecv, buf);
        } else if (ev.events & EPOLLHUP) {
            printf("connection closed\n");
            exit(-1);
        }
    }
    close(sockfd);
    return 0;
}
