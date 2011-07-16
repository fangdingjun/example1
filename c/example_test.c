#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#define SECONDS_PER_YEAR (60*60*24*365UL)
#define MIN(x,y) (x > y ? y:x)
#define MAX(x,y) (x>y ? x:y)

int a = 3;
int b = 5;

int main(int argc, char *argv[])
{
    printf("%ld\n", SECONDS_PER_YEAR);
    int a = 5, b = 3;
    printf("a:%d, b:%d\n", a, b);
    //printf("a:%d, b:%d\n",a,b);
    printf("min(%d,%d) is %d\n", a, b, MIN(a, b));
    printf("max(%d,%d) is %d\n", a, b, MAX(a, b));

    unsigned int c = 6;
    int d = -20;
    (c + d > 6) ? puts(">6") : puts("<=6");

    unsigned int e = 0;
    printf("%#X\n", ~e);
    printf("%u\n", (0x1 << 2));

    char str1[] = "abcdefg123456789";
    int len = strlen(str1);
    int i;

    for (i = 0; i < len / 2; i++) {
        char temp;
        temp = str1[i];
        str1[i] = str1[len - i - 1];
        str1[len - i - 1] = temp;
    }

    printf("str1 :%s\n", str1);
    char *n = "CC342f";
    len = strlen(n);
    int num, count = 0;
    for (i = 0; i < len; i++) {
        switch (tolower(n[i])) {
        case 'a':
            num = 10;
            break;
        case 'b':
            num = 11;
            break;
        case 'c':
            num = 12;
            break;
        case 'd':
            num = 13;
            break;
        case 'e':
            num = 14;
            break;
        case 'f':
            num = 15;
            break;
        default:
            num = n[i] - 48;    /* 2 = '2'-48 3='3'-48 ..... */
        }
        printf("num %d\n", num);
        count += (num * pow(16, len - i - 1));  /*convert hex to decimal */
    }

    printf("%#x %d\n", count, count);

    printf("%d %d\n", '4' - 4, 'a' - 'A');

    return 0;
}
