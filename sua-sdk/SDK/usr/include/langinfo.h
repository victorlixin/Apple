/*C+
 * Copyright 1998 by Softway Systems, Inc.  All rights reserved.
 * 
 * This Software Source is the unpublished, valuable, confidential property
 * of Softway Systems, Inc.  Use is authorised only under the terms and
 * conditions set out in the source code licence agreement protecting this
 * Software Source.  Any unauthorised use or disclosure of this Software 
 * Source is prohibited.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' BY SOFTWAY SYSTEMS, INC. AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL SOFTWAY SYSTEMS, INC. BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */ 

/* $Id: langinfo.h,v 1.1 1999/06/29 17:44:39 jeff Exp $ */

#ifndef _LANGINFO_INTERIX_H
#define _LANGINFO_INTERIX_H

#include <nl_types.h>


/* list of constants from XSH, langinfo() page */
#define CODESET		1
#define D_T_FMT		2
#define D_FMT		3
#define T_FMT		4
#define T_FMT_AMPM	5
#define AM_STR		6
#define PM_STR		7

#define ERA		8
#define ERA_D_FMT	9
#define ERA_T_FMT	10
#define ERA_D_T_FMT	11
#define ALT_DIGITS	12

#define RADIXCHAR	13
#define THOUSEP		14

#define CRNCYSTR	15

#define YESEXPR		16
#define NOEXPR		17
#define YESSTR		18
#define NOSTR		19

#define DAY_1		20
#define DAY_2		(DAY_1+1)
#define DAY_3		(DAY_1+2)
#define DAY_4		(DAY_1+3)
#define DAY_5		(DAY_1+4)
#define DAY_6		(DAY_1+5)
#define DAY_7		(DAY_1+6)
 
#define ABDAY_1		30
#define ABDAY_2		(ABDAY_1+1)
#define ABDAY_3		(ABDAY_1+2)
#define ABDAY_4		(ABDAY_1+3)
#define ABDAY_5		(ABDAY_1+4)
#define ABDAY_6		(ABDAY_1+5)
#define ABDAY_7		(ABDAY_1+6)

#define MON_1		40
#define MON_2		(MON_1+1)
#define MON_3		(MON_1+2)
#define MON_4		(MON_1+3)
#define MON_5		(MON_1+4)
#define MON_6		(MON_1+5)
#define MON_7		(MON_1+6)
#define MON_8		(MON_1+7)
#define MON_9		(MON_1+8)
#define MON_10		(MON_1+9)
#define MON_11		(MON_1+10)
#define MON_12		(MON_1+11)

#define ABMON_1		60
#define ABMON_2		(ABMON_1+1)
#define ABMON_3		(ABMON_1+2)
#define ABMON_4		(ABMON_1+3)
#define ABMON_5		(ABMON_1+4)
#define ABMON_6		(ABMON_1+5)
#define ABMON_7		(ABMON_1+6)
#define ABMON_8		(ABMON_1+7)
#define ABMON_9		(ABMON_1+8)
#define ABMON_10	(ABMON_1+9)
#define ABMON_11	(ABMON_1+10)
#define ABMON_12	(ABMON_1+11)


/* prototype for required function */
#ifdef __cplusplus 
extern "C" { 
#endif 
extern char * __cdecl nl_langinfo(nl_item);
#ifdef __cplusplus 
} 
#endif 

#endif
