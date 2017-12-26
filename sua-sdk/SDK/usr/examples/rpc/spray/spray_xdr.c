#include <rpc/rpc.h>
#include "spray.h"


bool_t
xdr_spraytimeval(xdrs, objp)
	XDR *xdrs;
	spraytimeval *objp;
{
	if (!xdr_u_int(xdrs, &objp->sec)) {
		return (FALSE);
	}
	if (!xdr_u_int(xdrs, &objp->usec)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_spraycumul(xdrs, objp)
	XDR *xdrs;
	spraycumul *objp;
{
	if (!xdr_u_int(xdrs, &objp->counter)) {
		return (FALSE);
	}
	if (!xdr_spraytimeval(xdrs, &objp->clock)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_sprayarr(xdrs, objp)
	XDR *xdrs;
	sprayarr *objp;
{
	if (!xdr_bytes(xdrs, (char **)&objp->sprayarr_val, (u_int *)&objp->sprayarr_len, SPRAYMAX)) {
		return (FALSE);
	}
	return (TRUE);
}


