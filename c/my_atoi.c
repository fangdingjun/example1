#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int my_atoi(const char *p)
{
    int r1[50];
    int r2 = 0;
    char *p1;
    int pos = 0;
    int i;
    p1 = (char *) p;
    while (*p1 != '\0') {
        // number is between 0x30 and 0x39
        // '0' = 0x30 '9' = 0x39
        if (*p1 < 0x30 || *p1 > 0x39) {
            break;
        }
        r1[pos] = (*p1 - 0x30);
        p1++;
        pos++;
    }
    for (i = 0; i < pos; i++) {
        r2 += r1[i] * pow(10, pos - i - 1);
    }
    return r2;
}

int main(int argc, char **argv)
{
    printf("%d\n", my_atoi(argv[1]));
    printf("%d\n", atoi(argv[1]));
    return 0;
}
