/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is the unpublished, valuable, confidential property
 * of Microsoft Corporation.  Use is authorised only under the terms and
 * conditions set out in the source code licence agreement protecting this
 * Software Source.  Any unauthorised use or disclosure of this Software 
 * Source is prohibited.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' BY MICROSOFT CORPORATION AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */ 

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)float.h	8.1 (Berkeley) 6/10/93
 *
 */

 /*
  *
  * RCSID = $Header: /E/interix/include/float.h,v 1.7 1999/06/07 14:03:49 mark Exp $
  */

#ifndef _FLOAT_H_
#define _FLOAT_H_

#include <features.h>

/* several definitions are also required in <limits.h> - XPG4 requirement
 * So <limits.h> includes this file when necessary
 * When it does, it enables __HIDE_CONSTS_FROM_LIMITS_H
 */
#ifndef FLT_DIG
   #define FLT_DIG		6		/* floor((p-1)*log10(b))+(b == 10) */
#endif /* FLT_DIG */
#ifndef FLT_MAX
   #define FLT_MAX		3.402823466E+38F/* (1-b**(-p))*b**emax */
#endif /* FLT_MAX */
#define FLT_MIN		1.17549435E-38F	/* b**(emin-1) */

#ifndef DBL_DIG
   #define DBL_DIG		15
#endif /* DBL_DIG */
#ifndef DBL_MAX
   #define DBL_MAX		1.7976931348623157E+308
#endif /* DBL_MAX */
#define DBL_MIN		2.2250738585072014E-308

#if !defined(__HIDE_CONSTS_FROM_LIMITS_H)  /* definitions not for <limits.h> */
#define FLT_RADIX	2		/* exponent radix (b) */
#define FLT_ROUNDS	1		/* FP addition rounds to nearest */

#define FLT_EPSILON	1.19209290E-07F	/* b**(1-p) */
#define FLT_MANT_DIG	24		/* p */
#define FLT_MAX_EXP	128		/* emax */
#define FLT_MAX_10_EXP	38		/* floor(log10((1-b**(-p))*b**emax)) */
#define FLT_MIN_EXP	(-125)		/* emin */
#define FLT_MIN_10_EXP	(-37)		/* ceil(log10(b**(emin-1))) */

#define DBL_MANT_DIG	53
#define DBL_EPSILON	2.2204460492503131E-16
#define DBL_MAX_EXP	1024
#define DBL_MAX_10_EXP	308
#define DBL_MIN_EXP	(-1021)
#define DBL_MIN_10_EXP	(-307)

#define LDBL_MANT_DIG	DBL_MANT_DIG
#define LDBL_EPSILON	DBL_EPSILON
#define LDBL_DIG	DBL_DIG
#define LDBL_MIN_EXP	DBL_MIN_EXP
#define LDBL_MIN	DBL_MIN
#define LDBL_MIN_10_EXP	DBL_MIN_10_EXP
#define LDBL_MAX_EXP	DBL_MAX_EXP
#define LDBL_MAX	DBL_MAX
#define LDBL_MAX_10_EXP	DBL_MAX_10_EXP
#endif /* __HIDE_CONSTS_FROM_LIMITS_H */


#endif /* _FLOAT_H_ */
