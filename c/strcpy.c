#include <stdio.h>
#include <string.h>

int main()
{
    char str2[10],str1[10];
    int i;

    for (i=0; i<10; i++)
    {
        str2[i]='a';
    }

    char *p;
    p=str1;
    //strcpy(str1,p);
    memcpy(str1,str2,10);
    printf("%s\n%s\n",str1,str2);

    return 0;
}
