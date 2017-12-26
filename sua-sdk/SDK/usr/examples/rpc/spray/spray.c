/*
 * spray.c - RPC spray client.
 * Coypright 1994 Olaf Kirch, <okir@monad.swb.de>
 *
 * This software is covered by the GNU General Public License, version 2.
 * It is provided in the hope that it will be useful. However, the author
 * disclaims ALL WARRANTIES, express or implied. See the GPL for details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <unistd.h>
#include <netdb.h>
#include "spray.h"

#ifdef __OPENNT
#include <sys/socket.h>
#endif

/* PACKET_CRUD is the total amount of additional baggage each
 * RPC packet carries around. It's made up of the IP header (20 bytes),
 * UDP header (8), RPC call header (20), RPC proc no. (4), RPC
 * auth_none info (12), 4 spurious bytes I can't explain, plus
 * the length count of the spray data (another 4 bytes).
 */
#define PACKET_CRUD	72
#define SPRAYMIN	PACKET_CRUD


/* Function Prototypes.
 */
void *	     sprayproc_clear_1(CLIENT *clnt);
spraycumul * sprayproc_get_1(CLIENT *clnt);
void	     usage(void);
int	     eat_args(int argc, char **argv);
CLIENT*	     connect_server(char *host);
int          blast_server(CLIENT *clnt);

/* Global variables.
 */
int		pkt_len;		/* length of packets */
int		pkt_snd;		/* number of packets to send */
int		pkt_rcv;		/* packets received by the server */
long		pkt_dly;		/* delay between packets */
int		drop_snd;		/* packets dropped locally */
int		drop_rcv;		/* packets dropped en route */
double		time_snd;		/* total sending time */
double		time_rcv;		/* total receive time */
double		time_rpc;		/* RPC round-trip time */
char		*host;			/* target host */
int		nocompress = 0;		/* send non-compressible data */
int		verbose = 0;		/* verbosity */
int		retry_calls = 0;	/* # of times to retry an RPC call */


/* Default timeout for RPC calls. Better not make this value too small,
 * because our shooting spree may have tied up all buffers in any of the
 * involved hosts or routing equipment, or wreaked other kinds of havoc
 * on the network.
 */
static struct timeval TIMEOUT = { 25, 0 };

/* TIME_DELTA computes the difference in seconds between two timeval's.
 */
#define TIME_DELTA(now, then)\
	(((long)now.tv_sec -(long)then.tv_sec) +\
	 ((long)now.tv_usec-(long)then.tv_usec) * uSec)
#define uSec		(1.0E-6)
#define mSec		(1.0E-3)



int
main(int argc, char **argv)
{
    CLIENT		*clnt;

    if (!eat_args(argc, argv)) {
    	fprintf( stderr, "usage: spray [-l length] [-c count] "
    			 "[-d delay] [-r retries] [-n] host\n" );
    	return 2;
    }

    clnt = connect_server(host);
    if (clnt == NULL) {
    	fprintf( stderr, "spray: couldn't bind to spray server\n" );
    	return 2;
    }

    /* Okay, here we go. Print the header, and start firing away.
     */
    printf( "sending %d packets of length %d to %s...\n",
    			pkt_snd, pkt_len, host );

    if (!blast_server(clnt)) {
    	fprintf( stderr, "spray: terminating.\n" );
    	return 2;
    }

    printf( "        in %0.2f seconds elapsed time,\n", time_snd );
    if (verbose) {
    	printf( "\t%d packets rcvd by %s in %0.2f seconds,\n",
            		 pkt_rcv, host, time_rcv );
    }
    printf( "        %d packets (%0.2f%%) dropped",
            		 pkt_snd - pkt_rcv,
            		 100.0 * (pkt_snd - pkt_rcv) / pkt_snd );
    if (verbose) {
    	printf( " (%d locally, %d en route).\n", drop_snd, drop_rcv );
    } else {
    	printf( ".\n" );
    }
    printf( "Sent:   %d packets/sec, %0.1f KBytes/sec\n"
            "Recvd:  %d packets/sec, %0.1f KBytes/sec\n",
    		    (int)(pkt_snd/time_snd), pkt_snd*pkt_len / time_snd / 1000,
    		    (int)(pkt_rcv/time_rcv), pkt_rcv*pkt_len / time_rcv / 1000 );
    if (verbose) {
    	printf( "RPC:    %0.2f ms RPC round-trip time\n", time_rpc*1000.0 );
    }

    clnt_destroy(clnt);
    return 0;
}

/* Parse command line arguments.
 */
int
eat_args(int argc, char **argv)
{
    char opt_c, opt_l, opt;

    /* set defaults: */
    opt_c = opt_l = 0;
    pkt_snd = 1162;
    pkt_len = 86;
    pkt_dly = 0;

    /* parse arguments */
    while ((opt = getopt(argc, argv, "c:d:l:nr:v")) > 0) {
    	switch(opt) {
    	case 'c':
    	    pkt_snd = atoi(optarg); opt_c = 1;
    	    break;
    	case 'd':
    	    pkt_dly = atoi(optarg) / mSec;
    	    break;
    	case 'l':
    	    pkt_len = atoi(optarg); opt_l = 1;
    	    break;
    	case 'n':
    	    nocompress = 1;
    	    break;
    	case 'r':
    	    if ((retry_calls = atoi(optarg)) < 0) {
    	    	retry_calls = INT_MAX;
    	    }
    	    break;
    	case 'v':
    	    verbose = 1;
    	    break;
    	case '?':
    	    return 0;
    	}
    }
    if (argc - optind != 1)
    	return 0;

    host = argv[optind];

    if (pkt_len < SPRAYMIN || pkt_len >= SPRAYMAX) {
    	fprintf( stderr, "spray: packet length must be at least %d"
    			 " and less than %d\n",
    				SPRAYMIN,
    				SPRAYMAX );
        return 0;
    }
    if (pkt_snd <= 0) {
    	fprintf( stderr, "spray: packet count must be positive.\n" );
    	return 0;
    }
    if (opt_c && !opt_l) {
    	if ((pkt_len = 100000 / pkt_snd) < SPRAYMIN)
    	    pkt_len = SPRAYMIN;
    }
    if (opt_l && !opt_c) {
    	if ((pkt_snd = 100000 / pkt_len) == 0)
    	    pkt_snd = 1;
    }

    return 1;
}

/* Find the spray server and create an RPC client. Check the comment
 * preceding blast_server() for an explanation of why we don't
 * use the more convenient clnt_create() function here.
 */
CLIENT*
connect_server(char *host)
{
    struct timeval	WAIT = { 5, 0 };
    struct sockaddr_in	sin;
    struct hostent	*h;
    CLIENT		*clnt;
    static int		clntsock;

    h = gethostbyname(host);
    if (h == NULL || h->h_addrtype != AF_INET) {
    	perror("spray:");
    	return NULL;
    }
    sin.sin_family = h->h_addrtype;
    sin.sin_port = 0;
    clntsock = -1;
    bcopy(h->h_addr, (char*)&sin.sin_addr, h->h_length);
    clnt = clntudp_create(&sin, SPRAYPROG, SPRAYVERS, WAIT, &clntsock);

    if (clnt == NULL) {
    	perror("spray:");
    }
    return clnt;
}

/* This is the main loop for firing packets at the server.
 * When sending a packet, we ignore any errors; they're likely
 * to occur anyway..
 *
 * Note that we pass a timeout of 0 to clnt_call here, so that it
 * returns immediately after sending the UDP datagram and doesn't
 * wait for the server's response. Also note that this code will only
 * work if *no* default timeout has been set with clnt_control().
 * Unfortunately, clnt_create does just this, which is why we use
 * clntudp_create above.
 *
 * One little problem is that of synchronization - what happens
 * if the spray_get() RPC request is dropped by some router because of
 * the after-effects of our spraying? We avoid this by sleeping for
 * a few milliseconds after sending the last packet. This sleep
 * interval is then subtracted from the whole elapsed time before
 * computing any data rates etc.
 */
int
blast_server(CLIENT *clnt)
{
    struct timeval NORETRY = { 0, 0 };
    double		skew = 0.0, rmt_rtt;
    struct timeval	t0, t1;
    spraycumul		*cumul;
    sprayarr		array;
    int			ct, res, rtr;

    array.sprayarr_len = pkt_len - PACKET_CRUD;
    array.sprayarr_val = calloc(1, pkt_len - PACKET_CRUD);

    /* If the -n option was given, try to generate data that's
     * hard to compress. We use a pattern of FF 01 FE 02 FD ...
     */
    if (nocompress) {
        unsigned char *sp;
        int	      len, i;

        sp = (unsigned char *) array.sprayarr_val;
        len = pkt_len - PACKET_CRUD;
        for (i=1; i+1 < len; i+=2) {
            sp[i]   = (unsigned char)i;
            sp[i+1] = (unsigned char)(0xFF-i);
        }
        while (i < len) {
            sp[i++] = (unsigned char)i;
        }
    }

    /* Make sure the link (e.g. dial-up ISDN link) is activated.
     */
    if (sprayproc_clear_1(clnt) == NULL || sprayproc_get_1(clnt) == NULL) {
    	clnt_perror(clnt, "spray");
    	return 0;
    }

    /* Get some idea of the RPC round-trip time. The global rtt is
     * stored in time_rpc. We also compute the average delay between
     * a clear/get operation the server sees. Usually, this should
     * be half the global rtt.
     */
    time_rpc = 0; rmt_rtt = 0;
    for (ct=3; ct--;) {
        gettimeofday(&t0, NULL);
        if (sprayproc_clear_1(clnt) == NULL
         || (cumul = sprayproc_get_1(clnt)) == NULL) {
    	    clnt_perror(clnt, "spray");
    	    return 0;
        }
        gettimeofday(&t1, NULL);
        time_rpc += TIME_DELTA(t1, t0);
        rmt_rtt += cumul->clock.sec + cumul->clock.usec * uSec;
    }
    time_rpc /= 3.0;
    rmt_rtt /= 3;

    /* Store the current time, and clear the server's counter.
     */
    gettimeofday(&t0, NULL);
    if (sprayproc_clear_1(clnt) == NULL) {
    	clnt_perror(clnt, "spray");
    	return 0;
    }

    drop_snd = 0;
    for (ct = pkt_snd; ct--;) {
	rtr = retry_calls;
	while (clnt_call(clnt, SPRAYPROC_SPRAY,
			xdr_sprayarr, &array,
			xdr_void, &res, NORETRY) == RPC_CANTSEND && rtr--) {
    	    usleep(500); /* wait for 0.5 milliseconds */
    	}
    	if (rtr < 0) {
    	    drop_snd++;
    	}
    	if (pkt_dly)
    	    usleep(pkt_dly);
    }
    skew += pkt_dly * pkt_snd * uSec;

    /* Get the server's statistics, and the local time elapsed.
     */
    cumul = sprayproc_get_1(clnt);
    if (cumul == 0) {
    	clnt_perror( clnt, "spray" );
    	return 0;
    }
    gettimeofday(&t1, NULL);

    pkt_rcv = cumul->counter;
    drop_rcv = pkt_snd - drop_snd - pkt_rcv;
    time_snd = TIME_DELTA(t1, t0) - skew - time_rpc;
    time_rcv = cumul->clock.sec + cumul->clock.usec * uSec
    			        - skew - rmt_rtt;
    /*
    fprintf( stderr, "\ttsend %f; trecv = %f\n", time_snd, time_rcv );
    */
    if (time_rcv < 0) {
    	fprintf( stderr, "Warning: inexact result - please increase packet count\n" );
    	time_rcv = 1;
    }
    return 1;
}

void *
sprayproc_clear_1(CLIENT *clnt)
{
	static char res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, SPRAYPROC_CLEAR,
			xdr_void, NULL,
			xdr_void, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&res);
}

/* Get the spray statistics from the server.
 */
spraycumul *
sprayproc_get_1(CLIENT *clnt)
{
	static spraycumul res;
	int	status, retries = 50;
	unsigned long	backoff = 1000;

	bzero((char *)&res, sizeof(res));
	do {
		status = clnt_call(clnt, SPRAYPROC_GET,
					 xdr_void, NULL,
					 xdr_spraycumul, &res, TIMEOUT);
		switch (status) {
		case RPC_SUCCESS:
			return &res;
		case RPC_CANTRECV: /* uh-ok.. we really broke something */
		case RPC_CANTSEND:
			fprintf( stderr, "*" );
			usleep(backoff);
			if (backoff <= 16000)
				backoff <<= 1;
			break;
		default:
			return NULL;
		}
	} while (retries--);
	return NULL;
}

