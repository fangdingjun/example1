#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toten(char *argv, char **rs)
{
    const char *delim = " \t\r\n";
    char *toten;

    toten = strtok(argv, delim);
    rs[0] = toten;

    int i = 1;

    while ((toten = strtok(NULL, delim)) != NULL) {
        rs[i] = toten;
        i++;
    }
    rs[i] = NULL;

    return 0;
}

int main(int argc, char *argv[])
{
    char buf[8192];

    while (fgets(buf, 8192, stdin) != NULL) {
        //buf[strlen(buf) - 1] = '\0';        /* delete '\n' */
        //printf("%s\n", buf);
        char *a[128];
        toten(buf, a);

        int i = 0;

        while (a[i] != NULL) {
            printf("get:%s'\n", a[i]);
            i++;
        }
    }
    return 0;
}
