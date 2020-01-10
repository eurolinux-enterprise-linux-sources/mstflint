/*
 *
 *  tcp.c - simple socket library routines
 *
 */

#ifndef INSIDE_MTCR
#define INSIDE_MTCR

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifdef linux
#include <sys/ioctl.h>
#else
#include <sys/filio.h>
#endif

#include "tcp.h"

#endif

/* ----------------------------------------------------- */
/* ------------------------------ Log all socket traffic */
/* ----------------------------------------------------- */
/* ////////////////////////////////////////////////////////////////////// */
static int log_ena=0;
INSIDE_MTCR void logset(const int ena) { log_ena = ena; }
INSIDE_MTCR int  plog(const char *fmt, ...)
{
    va_list ap;
    int     rc=0;

    if (log_ena)
    {
        va_start (ap, fmt);
        rc = vprintf (fmt, ap);
        va_end (ap);
    }
    return rc;
}

/* --------------------------------------------------- */
/* ------------------------------ Base socket routines */
/* --------------------------------------------------- */

/* ////////////////////////////////////////////////////////////////////// */
/*
** readn - read n bytes from the socket "fd"
**
** Attempt to read "nbytes" bytes from socket "fd" into "ptr".
** Returns number of bytes read, or -1 if an error occurs.
** Will read less than the specified count *only* if the peer sends
** EOF
*/
INSIDE_MTCR int readn(int fd, void *vptr, int nbytes)
{
    int     nleft, nread;
    char    *ptr = (char *)vptr;

    nleft = nbytes;
    while (nleft > 0)
    {
        do
            nread = read(fd, ptr, nleft);
        while (nread < 0 && errno == EINTR);

        if (nread < 0)
            return -1;              /*  error, return -1 */
        else if (nread == 0)
            break;                  /*  EOF */

        nleft -= nread;
        ptr   += nread;
    }
    return(nbytes - nleft);         /*  return >= 0 */
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** reads - reads string (till \0)  from the socket "fd"
*/
INSIDE_MTCR int reads(int fd, char *ptr, int maxlen)
{
    int     n, done=0, rc;
    char    c;

    for (n = 0; n <= maxlen && !done; n++)
    {
        do
            rc = read(fd, &c, 1);
	while (rc < 0 && errno == EINTR);

        switch(rc)
        {
        case 1:
            *ptr++ = c;
            if (c == '\0')
                done=1;
            break;
        case 0:
            done=1;
            break;
        default:
            return -1;     /*  error */
        }
    }
    return n-1;
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** readnl - reads till till newline  from the socket "fd"
*/
INSIDE_MTCR int readnl(int fd, char *ptr, int maxlen)
{
    int     n, done=0, rc;
    char    c;

    for (n = 0; n <= maxlen-1 && !done; n++)
    {
        do
        {
            rc = read(fd, &c, 1);
        }
	while (rc < 0 && errno == EINTR);

        switch(rc)
        {
        case 1:
            *ptr++ = c;
            if (c == '\n')
            {
                *ptr = '\0';
                done=1;
            }
            break;
        case 0:
            done=1;
            break;
        default:
            return -1;     /*  error */
        }
    }
    return n-1;
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** writen - write n bytes to the socket "fd"
**
** Attempt to write "nbytes" bytes to socket "fd" from "ptr".
** Returns number of bytes written, or -1 if an error occurs.
** Return value will always be either -1 or "nbytes"
*/
INSIDE_MTCR int writen(int fd, void *vptr, int nbytes)
{
    int     nleft, nwritten;
    char    *ptr = (char *)vptr;

    nleft = nbytes;
    while (nleft > 0)
    {
        do
            nwritten = write(fd, ptr, nleft);
        while (nwritten < 0 && errno == EINTR);

        if (nwritten < 0)
            return -1;

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(nbytes - nleft);
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** writes - write string (null ternminated buffer) to the socket "fd"
*/
INSIDE_MTCR int writes(int fd, char *ptr)
{
    return writen(fd, ptr, strlen(ptr)+1);
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** writenl - write newline ternminated buffer to the socket "fd"
*/
INSIDE_MTCR int writenl(int fd, char *ptr)
{
    char *last = strchr(ptr, '\n');
    if (last)
        return writen(fd, ptr, last - ptr + 1);
    return 0;
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** open_cli_connection - open client TCP connection and return socket fd
*/
INSIDE_MTCR int open_cli_connection(const char *host, const int port)
{
    int                 SockFD;
    struct sockaddr_in  serv_addr;
    struct hostent      *hent;

    plog("open_connection(%s, %d)\n", host, port);

    /*  Try to determinate server IP address */
    if ((hent = gethostbyname(host)) == NULL)
        return -1;

    /*
     * Fill in the structure "serv_addr" with the address of the
     * server that we want to connect with.
     */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    memcpy(&serv_addr.sin_addr, (*(hent->h_addr_list)), sizeof(struct in_addr));
    serv_addr.sin_port        = htons(port);

    /*  Open a TCP socket (an Internet stream socket). */
    if ( (SockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    /*
     * Connect to the server.
     */
    if (connect(SockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        return -1;

    /*  All OK */
    return SockFD;
}

/* ////////////////////////////////////////////////////////////////////// */
/*
** open_serv_connection - open server TCP connection and return socket fd
*/
INSIDE_MTCR int open_serv_connection(const int port)
{
    struct hostent     *hent;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_inet_addr;
    int                SockFD, newsockfd;
    int                clilen = sizeof(cli_inet_addr);
    int                childpid;

    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
        return -1;
    if ((SockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    /*  Bind our local address so that the client can send to us. */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(port);
    if (bind(SockFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        close(SockFD);
        return -1;
    }

    /*  Get ready to accept connection */
    if (listen(SockFD, 1) < 0)
    {
        close(SockFD);
        return -1;
    }

    /*  Accept connection */
    for (;;)
    {
        plog("Waiting for connection on port %d\n", port);

        while ((newsockfd = accept(SockFD, (struct sockaddr *)&cli_inet_addr,
                                   (socklen_t *)&clilen)) < 0)
        {
            if (errno != EINTR)
            {
                close(SockFD);
                return -1;
            }
        }
        if ((childpid = fork()) < 0)
            return -1;
        if (childpid)
        {
            /*  We are parent */
            close(newsockfd);
            /*   ... and try accept next connection */
        }
        else
        {
            /*  We are child */
            close(SockFD);

            /*  Determine the client host name */
            hent = gethostbyaddr((char *)&cli_inet_addr.sin_addr,
                                 sizeof(cli_inet_addr.sin_addr), AF_INET);
            plog("Accepted connection from host \"%s\" ", 
                hent ? hent->h_name : "????");

            /*  Determine the client host address */
            plog(" (%s)", inet_ntoa(cli_inet_addr.sin_addr));

            plog(", port %d\n", port);
            return newsockfd;
        }
    }
}
