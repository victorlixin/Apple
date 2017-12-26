/*
 * spraystat.h
 * Coypright 1994 Olaf Kirch, <okir@monad.swb.de>
 *
 * This software is covered by the GNU General Public License, version 2.
 * It is provied in the hope that it will be useful. However, the author
 * disclaims ALL WARRANTIES, express or implied. See the GPL for details.
 */

#ifndef __SPRAYSTAT_H__
#define __SPRAYSTAT_H__

#include <netinet/in.h>
#include <sys/time.h>

/*
 * Spray stats are collected in this struct. Right now,
 * it's only a linked list. It seems to make little sense to make
 * this a hash table, unless we were sprayed by several clients at
 * once over an ATM link :)
 */
typedef struct spray_stat {
	struct spray_stat	*s_next;
	struct sockaddr_in	s_clnt;
	unsigned int		s_count;
	struct timeval		s_clear;
} spray_stat;

void		init_stat(int secs);
spray_stat*	alloc_stat(struct sockaddr_in* in);
spray_stat*	get_stat(struct sockaddr_in* in);
void		remove_stat(spray_stat *stat);
void		tick_stat(spray_stat *stat);

#endif /* __SPRAYSTAT_H__ */
