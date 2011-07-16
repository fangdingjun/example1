#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"%s num\n",argv[0]);
        exit(1);
    }

    int count=0,num;
    num=atoi(argv[1]);

    do {
        if (num & 0x1)
        {
            count++;
        }

    }	while((num=(num>>1))>0);

    printf("%d\n",count);

    return 0;
}
