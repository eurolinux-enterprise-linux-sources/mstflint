/*
 *
 *  mtserver.c - Mellanox Software tools (mst) server (remote mtcr calls)
 *
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "mtcr.h"
#include "tcp.h"

/*
 * Constants
 */
#define DEF_PORT 23108
#define BUF_LEN  256
#define DEV_LEN  2048

int sdebug = 0;
int port = DEF_PORT;    /* Default port */

/* ////////////////////////////////////////////////////////////////////// */
void usage(const char *s)
{
    printf("Usage:\n\t%s [switches]\n\n", s);
    printf("Switches may be:\n");
    printf("\t-p[ort] <port> - Listen to specify port (default is %d).\n", port);
    printf("\t-d[ebug]       - Print all socket traffic (for debuging only).\n");
    printf("\t-dev <dev>     - Use this device for remote access\n");
    printf("\t-h[elp]        - Print help message.\n");
    exit (1);
}

/* ////////////////////////////////////////////////////////////////////// */
static void writes_deb(int con, char *s)
{
    writes(con, s);
    if (sdebug)
        printf("-> %s\n", s);
}

/* ////////////////////////////////////////////////////////////////////// */
void write_err(int con)
{
    writen(con, "E ", 2);
    writes(con, strerror(errno));
    if (sdebug)
        printf("-> E %s\n", strerror(errno));
}

/* ////////////////////////////////////////////////////////////////////// */
void write_ok(int con)
{
    writes_deb(con, "O");
}

/* ////////////////////////////////////////////////////////////////////// */
void mySignal()
{
    exit(0);
}

/* ////////////////////////////////////////////////////////////////////// */
#define CHK(f)    do { if ((f) < 0) { perror(""); exit(1); } } while(0)
#define CHK2(f,m) do { if ((f) < 0) { perror(m); exit(1); } } while(0)
int main (int ac, char *av[])
{
    char *end;
    char  buf[BUF_LEN], dev_buf[DEV_LEN];
    int   i, con, rc;
    char* local_dev = NULL;
    mfile *mf = 0;

    /* Command line parsing. */
    for (i=1; i<ac; i++)
    {
        switch (*av[i])
        {
        case '-':
            ++av[i];
            if (!strcmp(av[i], "p")  ||  !strcmp(av[i], "port"))
            {
                if (++i >= ac)
                {
                    printf("After switch \"%s\" port number is expected.\n",av[--i]);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                port = (int)strtol(av[i], &end, 0);
                if (*end)
                {
                    printf("Invalid port: \"%s\" -- ?\n", end);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
            }
            else if (!strcmp(av[i], "dev"))
            {
                if (++i >= ac)
                {
                    printf("After switch \"%s\" a device is expected.\n",av[--i]);
                    printf("Type \"%s -h\" for help.\n", av[0]);
                    exit(1);
                }
                local_dev = av[i];
            }
            else if (!strcmp(av[i], "d")  ||  !strcmp(av[i], "debug"))
            {
                sdebug = 1;
            }
            else if (!strcmp(av[i], "h")  ||  !strcmp(av[i], "help"))
            {
                usage(av[0]);
            }
            else
            {
                printf("Invalid switch \"%s\".\n", av[i]);
                printf("Type \"%s -h\" for help.\n", av[0]);
                exit(1);
            }
            break;
        case '?':
            usage(av[0]);
            break;
        default:
            printf("Invalid parameter \"%s\".\n", av[i]);
            printf("Type \"%s -h\" for help.\n", av[0]);
            exit(1);
        }
    }

#ifdef MST_UL
    if (local_dev == NULL) {
        printf("When accessing via user level mst, -dev <bus:dev.fun> flag must be provided\n");
        exit(1);
    }

#endif

    signal(SIGPIPE, mySignal);

    /* Now open and start work */
    logset(1);
    con = open_serv_connection(port);
    CHK2(con, "Open connection (server side)");
    for (;;)
    {
        memset(buf, 0, BUF_LEN);
        rc = reads(con, buf, BUF_LEN);
        CHK(rc);
        if (!rc)
            break;   /*  EOF */
        if (sdebug)
            printf("<- %s\n", buf);
        switch(*buf)
        {
        case 'O':   /*  Open mfile */
            if (mf)
                writes_deb(con, "E Already opened");
            else
            {

#ifndef MST_UL
                if (*end != ' ')
                    /*  Old style (O DEV_NAME) */
                    mf = mopen(buf+2);
                else {
                    /*  New style (O FLAG DEV_NAME) */
                    DType dtype = strtoul (buf+2, &end, 0);
                    mf = mopend (end+1, dtype);
                }

#else
                mf = mopen(local_dev);
#endif
                if (mf)
                    write_ok(con);
                else
                    write_err(con);
            }
            break;
        case 'C':  /*  Close mfile */
            if (!mf)
                writes_deb(con, "E Not opened");
            else
            {
                if (mclose(mf) < 0)
                    write_err(con);
                else
                {
                    write_ok(con);
                    mf = 0;
                }
            }
            break;
        case 'L':   /*  Get devices list */
            if (local_dev == NULL)
                #ifndef MST_UL
                rc = mdevices(dev_buf, DEV_LEN, MDEVS_ALL)
                #endif
		;
            else {

                strcpy(dev_buf, "/dev/mst/mt25204_pci_cr0");
                //strcpy(dev_buf, local_dev);
                printf("-D- local_dev=%s dev_buf=%s\n", local_dev, dev_buf);
                rc = 1;
            }            

            if (rc < 0)
                write_err(con);
            else
            {
                char *p = &dev_buf[0], vbuf[16];
                sprintf(vbuf, "O %d", rc);
                writes_deb(con, vbuf);
                for (i = 0; i < rc; i++, p += strlen(p)+1)
                    writes_deb(con, p);
            }
            break;
        case 'R':   /*  Read word */
            if (!mf)
                writes_deb(con, "E Not opened");
            else
            {
                unsigned int offset;
                u_int32_t    value;
                offset = strtoul(buf+2, &end, 0);
                if (*end)
                    writes_deb(con, "E Invalid offset");
                else
                {
                    if (mread4(mf, offset, &value) < 4)
                        write_err(con);
                    else
                    {
                        char vbuf[16];
                        sprintf(vbuf, "O 0x%08x", value);
                        writes_deb(con, vbuf);
                    }
                }
            }
            break;
        case 'W':   /*  Write word */
            if (!mf)
                writes_deb(con, "E Not opened");
            else
            {
                unsigned int offset;
                u_int32_t    value;
                char *p = strchr(buf+2, ' ');
                if (!p)
                    writes_deb(con, "E Invalid format (should be OFFS DATA)");
                else
                {
                    *p = '\0';
                    p++;
                    offset = strtoul(buf+2, &end, 0);
                    if (*end)
                        writes_deb(con, "E Invalid offset");
                    else
                    {
                        value = strtoul(p, &end, 0);
                        if (*end)
                            writes_deb(con, "E Invalid data");
                        else
                        {
                            if (mwrite4(mf, offset, value) < 4)
                                write_err(con);
                            else
                                write_ok(con);
                        }
                    }
                }
            }
            break;
        default:
            writes(con, "E Invalid command");
            if (sdebug)
                printf("-> E Invalid command (len:%d cmd:\"%s\")\n",
                       (int)strlen(buf), buf);
            break;
        }
    }

    return 0;
}
