//#include "../include/apue.h"
#include <stdio.h> // fputs, stdout, stderr, etc..
#include <stdlib.h> // exit
#include <unistd.h> // STDOUT_FILENO, STDIN_FILENO, STDERR_FILENO
#include <string.h> // strlen, strcat ...
#include <stdarg.h> // va_list, va_start, va_end
#include <errno.h> // errno

#define BUFFSIZE    4096
#define MAXLINE     1024

static void err_doit(int errnoflag, int error, const char *fmt, va_list ap) {
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE, fmt, ap);
    if (errnoflag) {
        snprintf(buf + strlen(buf), MAXLINE-strlen(buf), ": %s", 
                strerror(error));
    }
    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}

void err_sys(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

int main(int argc, const char *argv[])
{
    int     n;
    char    buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    return 0;
}



