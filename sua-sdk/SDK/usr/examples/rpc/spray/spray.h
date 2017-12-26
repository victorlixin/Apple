/*
 * spray.h - RPC spray declarations
 *
 * Automatically generated using rpcgen, with a little manual editing.
 */

#ifndef __SPRAYSVC_H__
#define __SPRAYSVC_H__

#include <sys/types.h>

#define SPRAYPROG ((u_long)100012)
#define SPRAYVERS ((u_long)1)
#define SPRAYPROC_SPRAY ((u_long)1)
#define SPRAYPROC_GET ((u_long)2)
#define SPRAYPROC_CLEAR ((u_long)3)


#define SPRAYMAX 8845

typedef struct spraytimeval {
	u_int sec;
	u_int usec;
} spraytimeval;

typedef struct spraycumul {
	u_int counter;
	spraytimeval clock;
} spraycumul;

typedef struct {
	u_int sprayarr_len;
	char *sprayarr_val;
} sprayarr;


bool_t xdr_spraytimeval(XDR *xdrs, spraytimeval *objp);
bool_t xdr_spraycumul(XDR *xdrs, spraycumul *objp);
bool_t xdr_sprayarr(XDR *xdrs, sprayarr *objp);


#endif /* __SPRAYSVC_H__ */
