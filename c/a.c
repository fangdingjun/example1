#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("%s ipaddr netmask\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in sin, sin_mask;

    memset(&sin, 0, sizeof(struct sockaddr_in));
    memset(&sin_mask, 0, sizeof(struct sockaddr_in));

    if (!(inet_aton(argv[1], &sin.sin_addr))) {
        perror("inet_aton");
        exit(1);
    }

    if (!(inet_aton(argv[2], &sin_mask.sin_addr))) {
        perror("inet_aton");
        exit(1);
    }

    in_addr_t net;
    net = sin.sin_addr.s_addr & sin_mask.sin_addr.s_addr;

    sin.sin_addr.s_addr = net;
    printf("%s\n", inet_ntoa(sin.sin_addr));
    return 0;
}
