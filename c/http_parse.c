#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *msg = "HTTP/1.1 404 Not found  \r\n "
    "Server: bws/1.0\r\n "
    "Content-Type: text/html; charset=utf-8 \r\n "
    "Content-Encoding: gzip \r\n "
    "Content-Length: 26 \r\n"
    "\r\n"
    "\r\naaasdfasdfasa" "aasdfasdfasdf\r\n";

/*
 * move to end, 
 * return a pointer to '\r', '\n' or '\0'
 * 
 */
char *move_to_end(char *p)
{
    char *p1;
    p1 = p;
    while (*p1 != '\r' && *p1 != '\n' && *p1 != '\0')
        p1++;
    return p1;
}

/*
 * move back
 * return a pointer to first whitespace
 */
char *move_back_skip_space(char *p)
{
    char *p1;
    p1 = p;
    while (isspace(*p1))
        p1--;
    p1++;
    return p1;
}

/*
 * skip the space at begin
 * return a pointer at first non-space
 */
char *skip_space(char *p)
{
    char *p1;
    p1 = p;
    while (isspace(*p1))
        p1++;
    return p1;
}

char *skip_space_and(char *p, char a)
{
    char *p1;
    p1 = p;
    while (isspace(*p1) || *p1 == a)
        p1++;
    return p1;
}

char *skip_nonspace(char *p)
{
    char *p1;
    p1 = p;
    while (!isspace(*p1))
        p1++;
    return p1;
}

char *skip_nonspace_except(char *p, char except)
{
    char *p1;
    p1 = p;
    while (!isspace(*p1) && *p1 != except)
        p1++;
    return p1;
}

/* 
 * read a line from buffer to dst
 * return the ponter to next line
 * the dst contain the '\0'
 *
 */
char *buffer_readline(char *src, char *dst, size_t size)
{
    char *p1, *p2;
    p1 = src;
    p2 = dst;
    while (1) {
        if ((p1 - src) >= (size - 1)) {
            *p2 = '\0';
            break;
        }
        if (*p1 == '\0') {
            *p2 = '\0';
            break;
        }
        if (*p1 == '\n') {
            *p2 = *p1;
            p1++;
            p2++;
            *p2 = '\0';
            break;
        }
        *p2 = *p1;
        p1++;
        p2++;
    }
    return p1;
}

char *buffer_read(char *src, char *dst, size_t size)
{
    char *p1, *p2;
    p1 = src;
    p2 = dst;
    while (1) {
        if ((p1 - src) >= (size - 1)) {
            *p2 = '\0';
            break;
        }
        if (*p1 == '\0') {
            *p2 = '\0';
            break;
        }
        *p2 = *p1;
        p1++;
        p2++;
    }
    return p1;
}

int main(int argc, char **argv)
{
    char *p;
    char *p1;
    char *p2;
    char buf[512];

    p = buffer_readline(msg, buf, 512);
    p1 = buf;
    p1 = skip_space(p1);
    if (strncasecmp(p1, "HTTP/", 5) == 0) {
        printf("message is response\n");
    }

    p1 = skip_nonspace(p1);
    p2 = p1;
    p2 = skip_nonspace(p2);
    printf("code: %.*s\n", p2 - p1, p1);

    p2 = skip_space(p2);
    p1 = p2;
    p2 = move_to_end(p2);
    p2 = move_back_skip_space(p2);

    printf("reason: %.*s\n", p2 - p1, p1);
    while (1) {
        p = buffer_readline(p, buf, 512);
        if (buf[0] == '\0')
            break;
        p1 = buf;
        p1 = skip_space(p1);
        if (*p1 == '\0') {
            if (*p == '\0')
                break;
            while (1) {
                p = buffer_read(p, buf, 512);
                if (buf[0] == '\0')
                    break;
                printf("body:\n|%s|\n", buf);
                if (*p == '\0')
                    break;
            }

            break;
        }
        p2 = skip_nonspace_except(p1, ':');

        printf("header: |%.*s|,", p2 - p1, p1);
        p1 = skip_space_and(p2, ':');
        p2 = move_to_end(p1);
        p2 = move_back_skip_space(p2);
        printf(" value: |%.*s|\n", p2 - p1, p1);
        if (*p == '\0')
            break;
    }
    return 0;
}
