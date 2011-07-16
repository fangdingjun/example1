#include <stdio.h>
#include <math.h>

int num(int number)
{
    int i = 1;
    while ((number = number / 10) > 0) {
        i++;
    }
    return i;
}

int rs(int m, int n)
{
    int i;
    int total = 0;
    int temp = m;
    do {
        i = temp % 10;
        //printf("temp %d\n",temp);
        //printf("i %d\n",i);
        total += (int) (pow(i, n));
        temp = temp / 10;
        //printf("total %d\n",total);
    } while (temp);

    if (total == m) {
        printf("%d ", m);
    }
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    for (i = 11; i <= 99999; i++) {
        rs(i, num(i));
    }

    return 0;
}
