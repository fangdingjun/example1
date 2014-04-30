#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int num = 40532;

    //int i,j,index;
    unsigned char buf[16];
    //unsigned char buf1[16];

    unsigned char *p;

    if (argc == 2) {
        num = atoi(argv[1]);
    }
    printf("%d\n", num);
    memset(buf, 0, sizeof(buf));
    //memset(buf1, 0, sizeof(buf1));


    p = &buf[0];
    if (num < 0) {
        *p++ = '-';
        num *= -1;
    }

    int i = num;
    while (i) {
        i = i / 10;
        p++;
    }

    do {
        *--p = num % 10 + '0';
        num = num / 10;
    } while (num);

    printf("%s\n", buf);
    //printf("%s\n", buf1);
}
