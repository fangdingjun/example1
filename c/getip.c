#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>

int main()
{
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    struct ifconf ifc;
    struct ifreq *ifr;
    int len = 50 * (sizeof(struct ifreq));
    char buf[len];
    struct sockaddr_in *sin;

    ifc.ifc_len = len;
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
        perror("CGIFCONF");
        exit(1);
    }

    ifr = ifc.ifc_req;
    int i;
    //printf("len %d ifc_len %d\n",len,ifc.ifc_len);
    //printf("sizeof buf %d\n",(int)strlen(ifc.ifc_buf));
    len = ifc.ifc_len / (sizeof(struct ifreq));
    //printf("%d\n",len);
    for (i = 0; i < len; i++) {
        sin = (struct sockaddr_in *) &ifr->ifr_addr;
        //printf("%s\n",ifr->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, ifr) == -1) {
            perror("CGIFFLAGS");
            exit(1);
        }
        if (((ifr->ifr_flags & IFF_LOOPBACK) == 0)
            && (ifr->ifr_flags & IFF_UP)) {
            printf("%s ", ifr->ifr_name);
            printf("%s ", inet_ntoa(sin->sin_addr));
            if (ioctl(sock, SIOCGIFNETMASK, ifr) == -1) {
                perror("CGIFNETMASK");
                exit(1);
            }

            sin = (struct sockaddr_in *) &ifr->ifr_netmask;
            printf(" %s ", inet_ntoa(sin->sin_addr));

            if (ioctl(sock, SIOCGIFHWADDR, ifr) == -1) {
                perror("CGIFHWADDR");
                exit(1);
            }

            unsigned char mac[6];
            memcpy(mac, (ifr->ifr_hwaddr).sa_data, 6);
            printf(" %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0],
                   mac[1], mac[2], mac[3], mac[4], mac[5]);
        }
        ifr++;
    }
    /*
       struct arpreq arp;
       if (ioctl(sock,SIOCGARP,&arp) == -1)
       {
       perror("CGARP");
       exit(0);
       }

       unsigned char mac1[6];
       unsigned char ip[4];
       memcpy(mac1,arp.arp_ha.sa_data,6);
       memcpy(ip,arp.arp_pa.sa_data,4);
       printf("%02X:%02X:%02X:%02X:%02X:%02X ",mac1[0],mac1[1],mac1[2],mac1[3],mac1[4],mac1[5]);
       printf("%d.%d.%d.%d\n",ip[0],ip[1],ip[2],ip[3]);
     */
    return 0;
}
