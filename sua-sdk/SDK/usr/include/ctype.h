/*
 * Copyright (c)  Microsoft Corporation. All rights reserved.
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
 *
 * Id = $Id$
 */ 

#ifndef _CTYPE_INTERIX_H_
#define _CTYPE_INTERIX_H_

#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * character classification function prototypes
 */
extern int __cdecl isalnum(int);
extern int __cdecl isalpha(int);
extern int __cdecl iscntrl(int);
extern int __cdecl isdigit(int);
extern int __cdecl isgraph(int);
extern int __cdecl islower(int);
extern int __cdecl isprint(int);
extern int __cdecl ispunct(int);
extern int __cdecl isspace(int);
extern int __cdecl isupper(int);
extern int __cdecl isxdigit(int);
extern int __cdecl toupper(int);
extern int __cdecl tolower(int);

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) || (__STDC__ - 0 == 0)
/* XPG4 extensions */
extern int __cdecl _tolower(int);
extern int __cdecl _toupper(int);
extern int __cdecl isascii(int);
extern int __cdecl toascii(int);
#endif /* defined(_ALL_SOURCE) ... */


#if defined(_ALL_SOURCE) || (__STDC__ - 0 == 0)
extern int __cdecl isblank(int c);
#endif /*defined(_ALL_SOURCE) || (__STDC__ - 0 == 0)*/

/* set bit masks for the possible character types */
	/* I18N: see notes below.... */

#define _UPPER		0x0001	/* upper case letter */
#define _LOWER		0x0002	/* lower case letter */
#define _DIGIT		0x0004	/* digit[0-9] */
#define _SPACE		0x0008	/* tab, carriage return, newline, */
				/* vertical tab or form feed */
#define _PUNCT		0x0010	/* punctuation character */
#define _CONTROL	0x0020	/* control character */
#define _CNTRL		0x0020
#define _BLANK		0x0040	/* space char */
#define _HEX		0x0080	/* hexadecimal digit */
#define _XDIGIT		0x0080
#define _ALPHA		0x0100  /* alphabetic character */
#define _PRINT		0x0200	/* printing character */
#define _GRAPH		0x0400	/* graphic character */
#define _ALNUM		0x0800	/* alphanumeric character */

	/* For the I18N version, these masks are different from the stock
	    version.  Each XPG4 locale character class has its own bit,
	    even though some of them can be combined.  To conform this
	    to the stock version, we'd have to combine bits -- ALNUM ==
	    ALPHA | DIGIT, for example -- but we'd also have new bits,
	    such as _PRINT, which isn't necessarily _PUNCT | _ALNUM, 
	    like in the C locale. */

#define _EOF (-1)

#ifndef _CTYPE_DISABLE_MACROS
/*
 * Macro definitions to do direct lookup via the _ctype database
 *
 */

/* note: the implementation of __ctypetest() has changed.
 *       It uses the _ictype[] data pointer.
 *       Which is different from the 2.2 and 3.0 Interix releases.
 */
#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern unsigned short *_ictype;
#else
#include <globalexport.h>
#define _ictype ((unsigned short*)libc_global(G_ICTYPE))
#endif

#define __ctypetest(_c, _flags) \
			(_ictype[(unsigned int)(_c)] & (_flags))

#define isalpha(_c)	__ctypetest(_c, _ALPHA)
#define isupper(_c)	__ctypetest(_c, _UPPER)
#define islower(_c)	__ctypetest(_c, _LOWER)
#define isdigit(_c)	__ctypetest(_c, _DIGIT)
#define isxdigit(_c)	__ctypetest(_c, _HEX)
#define isspace(_c)	__ctypetest(_c, _SPACE)
#define ispunct(_c)	__ctypetest(_c, _PUNCT)
#define isalnum(_c)	__ctypetest(_c, _ALNUM)
#define isprint(_c)	__ctypetest(_c, _PRINT)
#define isgraph(_c)	__ctypetest(_c, _GRAPH)
#define iscntrl(_c)	__ctypetest(_c, _CONTROL)

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) || (__STDC__ - 0 == 0)
/* _to*() must be macros */
#define _tolower(_c)	( (_c)-'A'+'a' )
#define _toupper(_c)	( (_c)-'a'+'A' )

#define isascii(_c)	( (unsigned)(_c) < 0x80 )
#define toascii(_c)	( (_c) & 0x7f )
#endif /* defined(_ALL_SOURCE) .. */


#endif /*_CTYPE_DISABLE_MACROS*/


#ifdef _PSX_LIB
/* Interix DLL requires definitions from wchar.h in order 
 * to avoid definition problems from other NT headers
 */
#include <wchar.h>
#endif

#ifdef __cplusplus
}
#endif

#endif	/* _CTYPE_INTERIX_H_ */
