/*
 *
 *  test_cr.c - CR Space access test - checks orderring and performance
 *  To compile : gcc -o test_cr test_cr.c -I/usr/mst/include -L/usr/mst/lib -lmtcr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mtcr.h>

void usage(const char *n)
{
    printf("%s <device> <addr> [times]\n", n);
    printf(" Write and Reads X times from the given addr\n");
    exit(1);
}

int main(int ac, char *av[])
{
    char          *endp;
    int           rc=0;
    unsigned int  addr, val;
    mfile         *mf;
    //DType         dtype = MST_TAVOR;
    unsigned int times = 1000000;
    int i;

    if (ac < 3)
        usage(av[0]);
    addr = strtoul(av[2], &endp, 0);
    if (*endp)
        usage(av[0]);
    
    mf = mopen(av[1]);
    if (!mf)
    {
        perror("mopen");
        return 1;
    }

    if (ac >= 4)
        times =  strtoul(av[3],0,0);


    for (i=0; i< times; i++) {
       unsigned int val;
       if (mwrite4(mf, addr, i) != 4) return 1;
       if (mread4( mf, addr, &val) != 4) return 1;

       if (val != i) {
           printf("-E- Orderring error on %d write out of %d\n", i, times);
           return 1;
       }

    }

    mclose(mf);
    return rc;
}

