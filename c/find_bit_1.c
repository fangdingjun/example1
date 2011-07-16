#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_one(unsigned int data)
{
    int count = 0;

    while (data) {
        data &= (data - 1);
        count++;
    }

    return count;
}

int main(int argc, char *argv[])
{
    char buf[128];

    while (fgets(buf, 128, stdin) != NULL) {
        buf[strlen(buf) - 1] = '\0';
        int a = atoi(buf);
        printf("%d %d\n", a, find_one(a));
    }
    return 0;
}
