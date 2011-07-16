#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct hostent *ht;
    if (argc < 2) {
        fprintf(stderr, "%s domainname\n", argv[0]);
        exit(1);
    }

    ht = gethostbyname(argv[1]);
    if (ht == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    printf("%s\n", inet_ntoa(*((struct in_addr *) ht->h_addr)));
    return 0;
}
