/*
 * sprayd.c - RPC spray server
 * Coypright 1994 Olaf Kirch, <okir@monad.swb.de>
 *
 * This software is covered by the GNU General Public License, version 2.
 * It is provied in the hope that it will be useful. However, the author
 * disclaims ALL WARRANTIES, express or implied. See the GPL for details.
 */
#include <stdio.h>
#include <arpa/inet.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <syslog.h>
#include "spray.h"
#include "spraystat.h"

#ifdef __OPENNT
#include <unistd.h>
#include <errno.h>
#endif

static void sprayprog_1_svc(struct svc_req *rqstp, SVCXPRT *transp);
static char* sprayproc_clear_1(struct svc_req *rqstp);
static char* sprayproc_spray_1(struct svc_req *rqstp);
static char* sprayproc_get_1(struct svc_req *rqstp);

int	logging = 0;
int	daemon = 1;

/*
 * main - parse args, register with portmapper, and enter dispatch loop.
 */
int
main(int argc, char **argv)
{
    SVCXPRT     *transp;
    int     	ch, usage = 0;
    char    	opt;

    while((opt = getopt(argc, argv, "hln")) > 0) {
        switch( opt ) {
        case 'l':
            logging = 1;
            break;
        case 'n':
            daemon = 0;
            break;
        case 'h':
        default:
            usage = 1;
        }
    }
    if (usage || argc < optind) {
    	fprintf( stderr, "usage: rpc.sprayd [-l] [-n]\n" );
    	exit(2);
    }

    if (logging) {
    	openlog( "sprayd", LOG_DAEMON, LOG_PID | (daemon? 0 : LOG_PERROR) );
    }

    /* Initialize stat list module, setting idle time to 5 minutes */
    init_stat(5*60);

    /* unregister whichever spray server is registered with the
     * portmapper right now
     */
    (void)pmap_unset(SPRAYPROG, SPRAYVERS);

    /* Create UDP service, and register with the portmapper.
     */
    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "cannot create udp service.\n");
        exit(1);
    }
    if (!svc_register(transp, SPRAYPROG, SPRAYVERS,
                    sprayprog_1_svc, IPPROTO_UDP)) {
        fprintf(stderr, "unable to register (SPRAYPROG, SPRAYVERS, udp).\n");
        exit(1);
    }

    if (daemon) {
        /* become a daemon */
        if ((ch = fork()) > 0) {
            exit (0);
        }
        if (ch < 0) {
            fprintf( stderr, "sprayd: cannot fork: %s\n", strerror(errno) );
            return 1;
        }
        close (0); close (1); close (2);
        setsid();
    }

    /* Run the dispatcher
     */
    svc_run();
    exit(1);
}

/*
 * Service dispatch routine.
 */
static void
sprayprog_1_svc(struct svc_req *rqstp, SVCXPRT *transp)
{
    bool_t  (*xdr_result)();
    char    *result;

    switch (rqstp->rq_proc) {
    case NULLPROC:
        svc_sendreply(transp, xdr_void, (char *)NULL);
        return;

    case SPRAYPROC_SPRAY:
        /*
         * simply discard the data. We don't even bother with
         * decoding it.
         */
        result = sprayproc_spray_1(rqstp);
        return;

    case SPRAYPROC_GET:
        /*
         * Get cumulative spray results.
         */
        xdr_result = xdr_spraycumul;
        result = sprayproc_get_1(rqstp);
        break;

    case SPRAYPROC_CLEAR:
        /*
         * Reset counter and timer.
         */
        xdr_result = xdr_void;
        result = sprayproc_clear_1(rqstp);
        break;

    default:
        svcerr_noproc(transp);
        return;
    }
    if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
        svcerr_systemerr(transp);
    }
}

static char*
sprayproc_clear_1(struct svc_req *rqstp)
{
    spray_stat		*stat;
    struct sockaddr_in	*in;
    static char		result;

    in = &rqstp->rq_xprt->xp_raddr;
    if ((stat = get_stat(in)) != NULL) {
    	/* clean up after some unconsiderate client */
    	remove_stat(stat);
    }
    if ((stat = alloc_stat(in)) == NULL) {
    	/* nothing we can do about it -- we're out of memory */
    	if (logging) {
    	    syslog(LOG_ERR, "out of memory: %m");
    	}
    	return NULL;
    }
    stat->s_count = 0;
    gettimeofday(&stat->s_clear, NULL);
    return &result;
}

/*
 * Receive packet. We don't bother with decoding it, but rather
 * throw it away directly:-)
 */
static char *
sprayproc_spray_1(struct svc_req *rqstp)
{
    spray_stat	*stat;

    if ((stat = get_stat(&rqstp->rq_xprt->xp_raddr)) == NULL) {
    	return NULL;
    }
    if ((stat->s_count++) % 1000 == 0) {
        tick_stat(stat);
    }
    return NULL;
}

static char *
sprayproc_get_1(struct svc_req *rqstp)
{
    struct timeval	tv;
    static spraycumul	cumul;
    spray_stat		*stat;

    if ((stat = get_stat(&rqstp->rq_xprt->xp_raddr)) == NULL) {
    	/*
    	 * I don't know you. Go away.
    	 */
    	if (logging) {
    	    syslog(LOG_INFO, "get() request from non-client at %s",
    				inet_ntoa(rqstp->rq_xprt->xp_raddr.sin_addr) );
    	}
    	cumul.counter = cumul.clock.sec = cumul.clock.usec = 0;
    	return (char*)&cumul;
    }

    /*
     * compute time elapsed, and return stats.
     */
    gettimeofday(&tv, NULL);
    cumul.clock.sec  = tv.tv_sec - stat->s_clear.tv_sec;
    if (tv.tv_usec >= stat->s_clear.tv_usec) {
        cumul.clock.usec = tv.tv_usec - stat->s_clear.tv_usec;
    } else {
        cumul.clock.usec = 1000000 + tv.tv_usec - stat->s_clear.tv_usec;
    	cumul.clock.sec -= 1;
    }
    cumul.counter = stat->s_count;
    remove_stat(stat);
    if (cumul.counter && logging) {
        syslog(LOG_INFO, "get() request from %s: %d pkts in %0.2f sec",
    				inet_ntoa(rqstp->rq_xprt->xp_raddr.sin_addr),
    				cumul.counter,
    				cumul.clock.sec + cumul.clock.usec*1e-6 );
    }
    return (char*)&cumul;
}
