#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <mtcr.h>

/*
hermon - 
rq_num_rnr = 1FDB8
sq_num_rnr = 1FDBC

sinai,arbel memfree, arbel artavor
rq_num_rnr =82294
sq_num_rnr = 82298
*/

/* Entry 0 is for rcv. 1 for snd */
static unsigned ihst_rnr_addr[] = {0x82294, 0x82298};
static unsigned cntx_rnr_addr[] = {0x1FDB8, 0x1FDBC};

#define CRA_RNR 0x8200

int main(int argc, char* argv[]) 
{

	mfile* mf;
	u_int32_t rnr;
	u_int32_t devid;
	u_int32_t ctraddr;
	u_int32_t* addr_array;
	
	if (argc != 3) {
		printf("  Usage: %s <bus:dev.fn> <snd|rcv>\n", argv[0]);
		printf("  Prints current number of RNRs for send or receive side.\n");
		return 1;
	}

	if (getuid()) {
		printf("-E- Only root can run this program\n", argv[0]);
		return 1;
	}

	mf = mopen(argv[1]);

	if (!mf) {
		printf("-E- Failed to open device %s: %s\n", argv[1], strerror(errno));
		return 1;
	}
	
	if (mread4(mf, 0xf0014, &rnr) != 4) {
		printf("-E- Failed to read device id: %s\n", strerror(errno));
	}
	
	devid &= 0xffff;

	if (devid == 0x190) {
		addr_array = cntx_rnr_addr;
	} else {
		addr_array = ihst_rnr_addr;
	}
	
	if (!strncmp("snd", argv[2], strlen(argv[2]))) {
		ctraddr = addr_array[1];
	} else if (!strncmp("rcv", argv[2], strlen(argv[2]))) {
		ctraddr = addr_array[0];
	} else {
		printf("-E- Bad parameter. Expected \"snd\" or \"rcv\". Got \"%s\"\n", argv[2]);
		return 1;
	}

		
    if (mread4(mf, ctraddr, &rnr) != 4) {
		printf("-E- Failed to read rnr: %s\n", strerror(errno));
		return 1;
 	}
	
	printf("%s RNR = %d\n", argv[2] ,rnr);

	mclose(mf);

	return 0;
}
