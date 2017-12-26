#include <rpc/rpc.h>
#include "spray.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

void *
sprayproc_spray_1(argp, clnt)
	sprayarr *argp;
	CLIENT *clnt;
{
	static char res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, SPRAYPROC_SPRAY, xdr_sprayarr, argp, xdr_void, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&res);
}


spraycumul *
sprayproc_get_1(argp, clnt)
	sprayarr *argp;
	CLIENT *clnt;
{
	static spraycumul res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, SPRAYPROC_GET, xdr_sprayarr, argp, xdr_spraycumul, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


void *
sprayproc_clear_1(argp, clnt)
	sprayarr *argp;
	CLIENT *clnt;
{
	static char res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, SPRAYPROC_CLEAR, xdr_sprayarr, argp, xdr_void, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&res);
}

