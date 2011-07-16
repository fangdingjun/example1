#include <stdio.h>
//#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char buf[8192];
    char *p;
    char *p1;
    char *delim = "\r\n";
    char a[]="aaaaa\r\nbbbbb\nccccc\rp\ndddddd\n";
    //while (fgets(buf, 8192, stdin) != NULL) {
        p1 = a;
        p = strtok(p1, delim);
        if (p) {
            printf("get:%s'\n", p);
        }//else { continue;}

        while ((p = strtok(NULL, delim)) != NULL) {
            printf("get:%s'\n", p);
        }
    //}
    return 0;
}
