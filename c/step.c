#include <stdio.h>
#include <stdlib.h>

int count(int n)
{
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else {
        return count(n - 1) + count(n - 2);
    }
}

int main(int argc, char **argv)
{
    int n;
    if (argc < 2) {
        printf("input a number:");
        scanf("%d", &n);
    } else {
        n = atoi(argv[1]);
    }

    printf("%d\n", count(n));
    return 0;
}
