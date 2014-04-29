#include <stdio.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>
//#include <linux/if_arp.h>
//#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
unsigned char my_mac[] = { 0x08, 0x00, 0x27, 0x22, 0x55, 0xd9 };
unsigned char my_ip[] = { 192, 168, 1, 252 };
char brd[] = { 192, 168, 1, 255 };

struct arp_msg {
    struct ethhdr eth_hdr;
    struct ether_arp eth_bdy;
};

int main(int argc, char *argv[])
{
    int j;
    struct arp_msg arp;
    int sock;
    unsigned char dst_ip[4] = { 192, 168, 1, 200 };
    struct sockaddr_ll dst;

    if (argc == 2) {
        int ip = inet_addr(argv[1]);
        memcpy(dst_ip, &ip, 4);
    }
    printf("get ");
    for (j = 0; j < 4; j++) {
        printf("%d", dst_ip[j]);
        if (j < 3)
            printf(".");
    }
    printf("\n");

    memset(&arp, 0, sizeof(arp));
    memset(&arp.eth_hdr.h_dest, 0xFF, sizeof(arp)); // ethernet dst
    memcpy(arp.eth_hdr.h_source, my_mac, ETH_ALEN); // ethernet src
    arp.eth_hdr.h_proto = htons(ETH_P_ARP);  // ethernet type
    arp.eth_bdy.ea_hdr.ar_hrd = htons(ARPHRD_ETHER); // hardware type
    arp.eth_bdy.ea_hdr.ar_pro = htons(ETH_P_IP);  // protocol
    arp.eth_bdy.ea_hdr.ar_op = htons(ARPOP_REQUEST);  // arp request
    arp.eth_bdy.ea_hdr.ar_hln = ETH_ALEN; // hardware address length
    arp.eth_bdy.ea_hdr.ar_pln = 4; // protocol length
    memcpy(arp.eth_bdy.arp_sha, my_mac, ETH_ALEN); // arp source

    memcpy(arp.eth_bdy.arp_tpa, dst_ip, 4);  // ip dst
    //arp.eth_bdy.arp_tha={0xff,0xff,0xff,0xff,0xff,0xff};
    memset(arp.eth_bdy.arp_tha, 0xFF, ETH_ALEN); //arp dst 
    memcpy(arp.eth_bdy.arp_spa, my_ip, 4); // source ip

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) {
        perror("socket");
        exit(0);
    }
    dst.sll_family = AF_PACKET;
    dst.sll_protocol = htons(ETH_P_ARP);
    dst.sll_hatype = htons(ARPHRD_ETHER);
    dst.sll_halen = ETH_ALEN;
    dst.sll_ifindex = 4;
    dst.sll_pkttype = 1;
    memset(dst.sll_addr, 0xFF, ETH_ALEN);
    struct arp_msg res;

    memset(&res, 0, sizeof(res));
    int ll;
    while (1) {
        //printf("send %d bytes\n", sizeof(arp));
        if ((ll =
             sendto(sock, &arp, sizeof(arp), 0, (struct sockaddr *) &dst,
                    sizeof(dst))) < 0) {
            perror("sendto");
            close(sock);
            exit(0);
        }
        if ((ll = recvfrom(sock, &res, sizeof(res), 0, NULL, NULL)) < 0) {
            perror("recvfrom");
            close(sock);
            exit(0);
        }
        //printf("receive %d bytes\n", ll);
        if (res.eth_bdy.ea_hdr.ar_op != htons(ARPOP_REPLY)) {
            continue;
        }

        int i;
        printf("from:");
        for (i = 0; i < 6; i++) {
            printf("%02x", res.eth_hdr.h_source[i]);
            if (i < 5)
                printf(":");
        }
        printf(" ");
        printf("to:");
        for (i = 0; i < 6; i++) {
            printf("%02x", res.eth_hdr.h_dest[i]);
            if (i < 5)
                printf(":");
        }
        printf(" tpa: ");
        for (i = 0; i < 4; i++) {
            printf("%d", res.eth_bdy.arp_tpa[i]);
            if (i < 3)
                printf(".");
        }
        printf("  spa:");
        for (i = 0; i < 4; i++) {
            printf("%d", res.eth_bdy.arp_spa[i]);
            if (i < 3)
                printf(".");
        }
        printf("\n");
        break;

    }
    close(sock);
    return 0;
}
