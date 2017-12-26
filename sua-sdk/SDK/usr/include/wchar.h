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

#ifndef _WCHAR_INTERIX_H_
#define _WCHAR_INTERIX_H_
 
#include <features.h>

#if !defined(_PSX_LIB)
/* avoid including this headers when building Interix DLL */
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>	/* for FILE */
#include <stdarg.h>
#include <time.h>
#endif /*_PSX_LIB*/

#include <sys/types.h>	/* for __mbstate_t , wchar_t, wint_t, ... */

#ifndef EOF
#define EOF     (-1)
#endif /*EOF*/


#ifndef WEOF
#define WEOF (wint_t)(-1)
#endif

#define WCHAR_MAX  0xFFFF
#define WCHAR_MIN  0


typedef __mbstate_t mbstate_t;

#ifdef __cplusplus
extern "C" {
#endif


extern int __cdecl      iswalnum(wint_t);
extern int __cdecl      iswalpha(wint_t);
extern int __cdecl      iswcntrl(wint_t);
extern int __cdecl      iswdigit(wint_t);
extern int __cdecl      iswgraph(wint_t);
extern int __cdecl      iswlower(wint_t);
extern int __cdecl      iswprint(wint_t);
extern int __cdecl      iswpunct(wint_t);
extern int __cdecl      iswspace(wint_t);
extern int __cdecl      iswupper(wint_t);
extern int __cdecl      iswxdigit(wint_t);
extern int __cdecl      iswctype(wint_t, wctype_t);

#ifdef FOPEN_MAX	/* test to see if we've included <stdio.h> */
extern wint_t __cdecl  fgetwc(FILE *);
extern wchar_t* __cdecl fgetws( wchar_t *, int, FILE *);
extern wint_t   __cdecl fputwc(wchar_t, FILE *);
extern int __cdecl      fputws(const wchar_t *, FILE *);
extern wint_t   __cdecl getwc(FILE *);
extern wint_t   __cdecl putwc(wchar_t, FILE *);
extern wint_t   __cdecl ungetwc(wint_t, FILE *);
#endif /* FOPEN_MAX */

extern wint_t   __cdecl getwchar(void);
extern wint_t   __cdecl putwchar(wchar_t);
extern wint_t   __cdecl towlower(wint_t);
extern wint_t   __cdecl towupper(wint_t);
#if !defined(_PSX_LIB) && defined(_M_IA64)
#define wcscat _ia_wcscat
#else
extern wchar_t* __cdecl wcscat( wchar_t *, const wchar_t *);
#endif
extern wchar_t* __cdecl wcschr(const wchar_t *, wchar_t);
extern wchar_t* __cdecl wcsrchr(const wchar_t *, wchar_t);
#if !defined(_PSX_LIB) && defined(_M_IA64)
#define wcscmp _ia_wcscmp
#else
extern int __cdecl      wcscmp(const wchar_t *, const wchar_t *);
#endif
extern int __cdecl      wcscoll(const wchar_t *, const wchar_t *);
#if !defined(_PSX_LIB) && defined(_M_IA64)
#define wcscpy _ia_wcscpy
#else
extern wchar_t* __cdecl wcscpy( wchar_t *, const wchar_t *);
#endif
extern size_t   __cdecl wcscspn(const wchar_t *, const wchar_t *);
extern size_t   __cdecl wcsftime( wchar_t *, size_t, const wchar_t *, 
				 const struct tm *);
#if !defined(_PSX_LIB) && defined(_M_IA64)
#define wcslen _ia_wcslen
#else
extern size_t   __cdecl wcslen(const wchar_t* );
#endif
extern wchar_t* __cdecl wcsncat( wchar_t *, const wchar_t *, size_t);
extern int __cdecl      wcsncmp(const wchar_t *, const wchar_t *, size_t);
extern wchar_t* __cdecl wcsncpy( wchar_t *, const wchar_t *, size_t);
extern wchar_t* __cdecl wcspbrk(const wchar_t *, const wchar_t *);
extern size_t   __cdecl wcsspn(const wchar_t *, const wchar_t *);
extern wchar_t* __cdecl wcsstr(const wchar_t *, const wchar_t *);
extern double   __cdecl wcstod(const wchar_t *,  wchar_t **);
extern long int __cdecl wcstol(const wchar_t *,  wchar_t **, int);
extern unsigned long int __cdecl wcstoul(const wchar_t *,  wchar_t **, int);
extern wchar_t* __cdecl wcswcs(const wchar_t *, const wchar_t *);
extern int __cdecl      wcswidth(const wchar_t *, size_t);
extern size_t   __cdecl wcsxfrm( wchar_t *, const wchar_t *, size_t);
extern wctype_t __cdecl wctype(const char *);
extern int __cdecl      wcwidth(wchar_t);

#if !defined(_XPG4_UNIX)
extern wchar_t* __cdecl __wcstok_xpg5( wchar_t *wstr, const wchar_t *wsep, 
	 wchar_t **ptr);
#define wcstok __wcstok_xpg5
#else
extern wchar_t* __cdecl wcstok ( wchar_t *wstr, const wchar_t *wsep);
#endif   /* !definded(_XPG4_UNIX) */

#ifdef _ALL_SOURCE
extern int __cdecl       putws(const wchar_t *);
extern wchar_t* __cdecl  wcscasewcs(const wchar_t *, const wchar_t *);
extern int __cdecl	 wcscasecmp(const wchar_t *, const wchar_t *);
extern wchar_t * __cdecl wcsdup(const wchar_t *);
extern int __cdecl	 wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
extern size_t	 __cdecl wcslcat( wchar_t *, const wchar_t *, size_t);
extern size_t	 __cdecl wcslcpy( wchar_t *, const wchar_t *, size_t);
extern wchar_t* __cdecl  wcssep( wchar_t **, const wchar_t *);
#endif /*_ALL_SOURCE */


#ifdef __cplusplus
}
#endif

#endif	/* _WCHAR_INTERIX_H_ */
