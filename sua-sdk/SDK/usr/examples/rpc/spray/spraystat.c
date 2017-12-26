/*
 * spraystat.c
 * Coypright 1994 Olaf Kirch, <okir@monad.swb.de>
 *
 * This software is covered by the GNU General Public License, version 2.
 * It is provied in the hope that it will be useful. However, the author
 * disclaims ALL WARRANTIES, express or implied. See the GPL for details.
 *
 *
 * This module records statistics for several clients simultaneously.
 * We do a little alarm() wrestling to make sure our memory doesn't
 * fill up with leftover rubbish from clients that have gone long ago.
 */
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "spraystat.h"

static void purge_stat(int sig);

static spray_stat	*stat_list = NULL;
static time_t		interval = 300;

/*
 * Initialize stat list. The alarm handler will be executed after a few
 * minutes of inactivity, and removes all clients from the queue.
 */
void
init_stat(int secs)
{
    struct sigaction	sa;

    sa.sa_handler = purge_stat;
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    interval = secs;
}

/*
 * Allocate a stat list entry, and set the alarm clock for
 * five minutes.
 */
spray_stat*
alloc_stat(struct sockaddr_in* in)
{
    long	mask;
    spray_stat	*stat;

    stat = malloc(sizeof(*stat));
    if (!stat) {
        return stat;
    }
    bcopy(in, &stat->s_clnt, sizeof(stat->s_clnt));
    mask = sigblock(sigmask(SIGALRM));
    stat->s_next = stat_list;
    stat_list = stat;
    sigsetmask(mask);

    alarm(interval);
    return stat;
}

/*
 * find the current client in the stat list
 */
spray_stat*
get_stat(struct sockaddr_in* in)
{
    spray_stat	*stat;

    /* in = rqstp->rq_xprt->xp_raddr; */
    for (stat = stat_list; stat; stat=stat->s_next) {
    	if (stat->s_clnt.sin_addr.s_addr == in->sin_addr.s_addr
    	 && stat->s_clnt.sin_port == in->sin_port)
    	    break;
    }
    return stat;
}

/*
 * remove a client from the list of stat structs. If the
 * list is empty afterwards, reset the alarm timer to 0, so
 * we won't be signalled until a new clients requests a clear().
 */
void
remove_stat(spray_stat *stat)
{
    long	mask;
    spray_stat *prev;

    mask = sigblock(sigmask(SIGALRM));
    if (stat == stat_list) {
        stat_list = stat->s_next;
        if (stat_list == NULL) {
    	    alarm(0); /* no more clients - go to bed again */
        }
    } else {
        for (prev = stat_list; prev != NULL; prev = prev->s_next) {
    	    if (prev->s_next == stat)
    	        break;
        }
        if (prev) {
            prev->s_next = stat->s_next;
        } else {
    	    /* all those bogus pointers, where do they all come from? */
        }
    }
    free(stat);
    sigsetmask(mask);
}

/*
 * Remove all clients from the stat list. This function is called
 * after a few minutes of inactivity. In this way, we make sure
 * we don't start hogging memory.
 */
static void
purge_stat(int sig)
{
    spray_stat	*stat, *next;

    for (stat = stat_list; stat; stat = next) {
    	next = stat->s_next;
    	free(stat);
    }
    stat_list = NULL;
}

/*
 * tick_stat - server tells us that the client is still alive.
 * We simple reset the timer.
 */
void
tick_stat(spray_stat *stat)
{
    alarm(interval);
}
