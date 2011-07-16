#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <linux/if_arp.h>
#include <sys/ioctl.h>
#include <string.h>

struct arpheader {
    unsigned char h_dest[ETH_ALEN];
    unsigned char h_source[ETH_ALEN];
    __be16 h_proto;
    __be16 ar_hrd;
    __be16 ar_pro;
    unsigned char ar_hln;
    unsigned char ar_pln;
    __be16 ar_op;
    unsigned char ar_sha[ETH_ALEN];
    unsigned char ar_sip[4];
    unsigned char ar_tha[ETH_ALEN];
    unsigned char ar_tip[4];
} __attribute__ ((packed));
