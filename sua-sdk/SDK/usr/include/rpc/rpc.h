/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *
 * This Software Source is derived from software that is included
 * in the 4.4BSD-Lite release which is copyrighted by The Regents
 * of the University of California.  The Berkeley copyright appears
 * elsewhere in this source module.
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

/* @(#)rpc.h	2.3 88/08/10 4.0 RPCSRC; from 1.9 88/02/08 SMI */
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
 * rpc.h, Just includes the billions of rpc header files necessary to
 * do remote procedure calling.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */
#ifndef _RPC_RPC_H
#define _RPC_RPC_H
#ifdef __cplusplus 
extern "C" { 
#endif 

#if defined(linux) || defined(__INTERIX)
#include <sys/time.h>
#endif

#include <rpc/types.h>		/* some typedefs */
#include <netinet/in.h>

/* external data representation interfaces */
#include <rpc/xdr.h>		/* generic (de)serializer */

/* Client side only authentication */
#include <rpc/auth.h>		/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#include <rpc/clnt.h>		/* generic rpc stuff */

/* semi-private protocol headers */
#include <rpc/rpc_msg.h>	/* protocol for rpc messages */
#include <rpc/auth_unix.h>	/* protocol for unix style cred */
/*
 *  Uncomment-out the next line if you are building the rpc library with    
 *  DES Authentication (see the README file in the secure_rpc/ directory).
 */
#if 0
#include <rpc/auth_des.h>	/* protocol for des style cred */
#endif

/* Server side only remote procedure callee */
#include <rpc/svc.h>		/* service manager and multiplexer */
#include <rpc/svc_auth.h>	/* service side authenticator */

/*
 * SET THE FOLLOWING SECTION TO #if 0 IF THE TARGET SYSTEM HAS THE
 * THE CONDITIONALIZED DECLARATIONS IN in the system <netdb.h>
 */
#if 1
/* routines for parsing /etc/rpc */
struct rpcent {
      char    *r_name;        /* name of server for this rpc program */
      char    **r_aliases;    /* alias list */
      int     r_number;       /* rpc program number */
};

#ifdef __INTERIX
struct rpcent *getrpcbyname(const char *), *getrpcbynumber(), *getrpcent();
#else
struct rpcent *getrpcbyname(), *getrpcbynumber(), *getrpcent();
#endif

#endif
#ifdef __cplusplus 
}
#endif 

#endif
/* !  _RPC_RPC_H */
