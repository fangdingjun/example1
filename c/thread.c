#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

int sock;
void *thread_read()
{
    int l;
    char buf[1024];
    //int s=*(int *)sock;
    int s = sock;
    while (1) {
        l = recv(s, &buf, 1024, 0);
        if (l == -1) {
            perror("recv");
            pthread_exit("recv error");
        } else if (l == 0) {
            printf("recv:connect closed\n");
            exit(0);
            //break;
        }
        buf[l] = '\0';
        printf("%s", buf);
    }
    return NULL;
}

int main(int argc, char **argv)
{

    if ( argc != 3 ){
        fprintf(stderr,"%s hostname port\n",argv[0]);
        exit(1);
    }
    //int sock;
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = ntohs(atoi(argv[2]));
    struct hostent *host;
    host = gethostbyname(argv[1]);
    if (host == NULL) {
        herror("gethostbyname");
        return -1;
    }

    memcpy(&sin.sin_addr, host->h_addr, host->h_length);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return -1;
    }

    //printf("%s\n", inet_ntoa(sin.sin_addr));
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
        perror("connect");
        return -1;
    }

    pthread_t id;
    pthread_create(&id, NULL, &thread_read, NULL);
    int l;
    char buf[1024];
    while (1) {
        memset(&buf, 0, sizeof(buf));
        fgets(buf, 1024, stdin);
        l=strlen(buf);
        buf[l-1]='\0';
        strcat(buf,"\r\n");
        l = send(sock, buf, strlen(buf), 0);
        //printf("send size:%d\n",l);
        if (l == -1) {
            perror("send");
            return -1;
        } else if (l == 0) {
            printf("send:connect closed\n");
            break;
        }
    }
    close(sock);
    exit(0);
}
