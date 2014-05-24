#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
//#include <unistd.h>
//#include <sys/stat.h>
//#include <fcntl.h>

int main(int argc, char **argv)
{
    char a[] = "function bind\r\ndevid 1233\r\nphoneid 45312\r\n";
    char buf[8192];
    char *delim = "\r\n";
    char *p;
    int c=0;
    printf("a %s\n", a);
    //char *p1;
    //while (fgets(buf, 8192, stdin) != NULL) {
        char *p1=a;
        while ((p = strsep(&p1, delim)) != NULL) {
            c++;
            printf("get line %d:%s'\n", c, p);
        }
    //}
    printf("a %s\n", a);

    return 0;
}
