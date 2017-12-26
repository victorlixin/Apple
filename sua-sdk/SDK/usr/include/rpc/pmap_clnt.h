/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is derived from software that is included 
 * in the Sun RPC release which is copyrighted by Sun Microsystems Inc.
 * The Sun copyright appears elsewhere in this source module.
 * 
 * Modifications made to this Software Source are copyrighted by
 * Microsoft Corporation., and are the unpublished, valuable, confidential
 * property of Microsoft Corporation.  Use is therefore authorised only 
 * under the terms and conditions set out in the source code licence 
 * agreement protecting this Software Source.  Any unauthorised use or 
 * disclosure of this Software Source is prohibited.
 *
 * THESE SOFTWARE MODIFICATIONS ARE PROVIDED ``AS IS'' BY MICROSOFT CORP.
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */


/* @(#)pmap_clnt.h	2.1 88/07/29 4.0 RPCSRC; from 1.11 88/02/08 SMI */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */

/*
 * pmap_clnt.h
 * Supplies C routines to get to portmap services.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */
#ifndef _RPC_PMAPCLNT_H
#define _RPC_PMAPCLNT_H

#include <rpc/xdr.h>
#ifdef __cplusplus 
extern "C" { 
#endif 

/*
 * Usage:
 *	success = pmap_set(program, version, protocol, port);
 *	success = pmap_unset(program, version);
 *	port = pmap_getport(address, program, version, protocol);
 *	head = pmap_getmaps(address);
 *	clnt_stat = pmap_rmtcall(address, program, version, procedure,
 *		xdrargs, argsp, xdrres, resp, tout, port_ptr)
 *		(works for udp only.) 
 * 	clnt_stat = clnt_broadcast(program, version, procedure,
 *		xdrargs, argsp,	xdrres, resp, eachresult)
 *		(like pmap_rmtcall, except the call is broadcasted to all
 *		locally connected nets.  For each valid response received,
 *		the procedure eachresult is called.  Its form is:
 *	done = eachresult(resp, raddr)
 *		bool_t done;
 *		caddr_t resp;
 *		struct sockaddr_in raddr;
 *		where resp points to the results of the call and raddr is the
 *		address if the responder to the broadcast.
 */

#if (__STDC__ - 0  == 1) || defined(__cplusplus) || defined(__USE_PROTOTYPES)

extern bool_t		pmap_set(u_long, u_long, int, u_short);
extern bool_t		pmap_unset(u_long, u_long);
extern struct pmaplist* pmap_getmaps(struct sockaddr_in *);
extern enum clnt_stat	pmap_rmtcall(struct sockaddr_in *,
					u_long, u_long, u_long,
					xdrproc_t, caddr_t,
					xdrproc_t, caddr_t,
					struct timeval, u_long *);
extern enum clnt_stat	clnt_broadcast (u_long, u_long, u_long,
					xdrproc_t, char *,
					xdrproc_t, char *,
					resultproc_t);
extern u_short		pmap_getport (struct sockaddr_in *,
					 u_long, u_long, u_int);
#else

extern bool_t		pmap_set();
extern bool_t		pmap_unset();
extern struct pmaplist	*pmap_getmaps();
enum clnt_stat		pmap_rmtcall();
enum clnt_stat		clnt_broadcast();
extern u_short		pmap_getport();

#endif /* __STDC__ */
#ifdef __cplusplus 
}
#endif 

#endif /* !_RPC_PMAPCLNT_H */


