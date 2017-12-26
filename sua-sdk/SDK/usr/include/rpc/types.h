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

/* @(#)types.h	2.3 88/08/15 4.0 RPCSRC */
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
/*      @(#)types.h 1.18 87/07/24 SMI      */

/*
 * Rpc additions to <sys/types.h>
 */
#ifndef __TYPES_RPC_HEADER__
#define __TYPES_RPC_HEADER__
#ifdef __cplusplus 
extern "C" { 
#endif 

#ifndef boot_t
#define	bool_t	int
#endif

#ifndef enum_t
#define	enum_t	int
#endif

#ifndef FALSE
#define	FALSE	(0)
#define	TRUE	(1)
#endif

#define __dontcare__	-1
#ifndef NULL
#	define NULL 0
#endif

#ifdef __INTERIX
#include <stdlib.h>	/* for malloc() prototype */
#else
extern char *malloc();
#endif
#define mem_alloc(bsize)	malloc(bsize)
#define mem_free(ptr, bsize)	free(ptr)

#ifndef makedev /* ie, we haven't already included it */
#include <sys/types.h>
#endif
#include <sys/time.h>

#ifndef linux
#ifndef INADDR_LOOPBACK
#define       INADDR_LOOPBACK         (u_long)0x7F000001
#endif
#endif
#ifndef MAXHOSTNAMELEN
#define        MAXHOSTNAMELEN  64
#endif
#ifdef __cplusplus 
}
#endif 

#endif /* ndef __TYPES_RPC_HEADER__ */
