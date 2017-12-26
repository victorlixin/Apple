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
 * RCSid = $Header: /E/interix/include/stdlib.h,v 1.18 1999/04/13 19:09:19 rodney Exp $
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_
 
#include <features.h>

#include <stddef.h>     /* for NULL and size_t and wchar_t  */
#include <sys/types.h>	/* for quad_t */

#ifdef __cplusplus
extern "C" {
#endif

/* Definition of the argument values for the exit() function */

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


/* Data structure definitions for div and ldiv runtimes. */

#ifndef _DIV_T_DEFINED
#define _DIV_T_DEFINED
typedef struct {
        int quot;	/* quotient */
        int rem;	/* remainder */
} div_t;

typedef struct {
        long quot;	/* quotient */
        long rem;	/* remainder */
} ldiv_t;

#if  defined(_ALL_SOURCE) \
     || ( !defined(_XOPEN_SOURCE) && (__STDC__ - 0 == 0) \
				  && !defined(_POSIX_C_SOURCE) )
typedef struct {
        quad_t quot;	/* quotient */
        quad_t rem;	/* remainder */
} qdiv_t;

#endif /*_ALL_SOURCE*/

#endif /*DIV_T_DEFINED*/

extern int daemon (int nochdir, int noclose);
extern char * getbsize(int *headerlenp, long *blocksizep);

/* Maximum value that can be returned by the rand() function. */
#define RAND_MAX 0x7fffffff

/*
 * Maximum number of bytes in multi-byte character in the current locale
 */
#if defined(_SVR_I18N)
extern unsigned char  __ctype[];
#define MB_CUR_MAX     ((int)__ctype[520])
#else
#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern  int __mb_cur_max;
#else
#include <globalexport.h>
#define __mb_cur_max (*((int*)libc_global(G_MB_CUR_MAX)))
#endif
#define MB_CUR_MAX      __mb_cur_max
#endif

/* function prototypes */
extern void   __cdecl abort(void);
extern int    __cdecl abs(int);
extern int    __cdecl atexit(void (__cdecl *)(void));
extern double __cdecl atof(const char *);
extern int    __cdecl atoi(const char *);
extern long   __cdecl atol(const char *);
extern void * __cdecl bsearch (const void *, const void *, size_t, size_t,
				int (__cdecl*)(const void *, const void *));
extern void * __cdecl calloc(size_t, size_t);
extern div_t  __cdecl div(int, int);
extern void   __cdecl exit(int);
extern void   __cdecl free(void *);
extern char * __cdecl getenv(const char *);
#if (defined(_WIN64) ||defined(lp64))
extern long   __cdecl labscore(long);
#else
extern long   __cdecl labs(long);
#endif
extern ldiv_t __cdecl ldiv(long, long);
extern void * __cdecl malloc(size_t);
extern int    __cdecl mblen(const char *, size_t);
extern size_t __cdecl mbstowcs(   wchar_t *pwcs, const char *src, size_t len );
extern int    __cdecl mbtowc(  wchar_t *pwc, const char *src, size_t len );
extern void   __cdecl qsort( void *, size_t, size_t,
			    int (__cdecl *)(const void *, const void *));
extern int    __cdecl rand(void);
extern void * __cdecl realloc(void *, size_t);
extern void   __cdecl srand(unsigned int);
extern double __cdecl strtod(const char *,  char **);
extern float __cdecl strtof(const char *,  char **);
extern long   __cdecl strtol(const char *,  char **, int);
extern unsigned long __cdecl strtoul(const char *,  char **, int);
extern quad_t __cdecl strtoq(const char *,  char **, int);
extern u_quad_t __cdecl strtouq(const char *,  char **, int);
extern int    __cdecl system(const char *);
extern size_t __cdecl wcstombs(  char *s, const wchar_t *pwcs, size_t len );
extern int    __cdecl wctomb(  /*MB_LEN_MAX*/ char *result, wchar_t src );

extern size_t __cdecl _wcstombs_forced(  char *dst, const wchar_t *pwcs, size_t len );
extern int    __cdecl _wctomb_forced( char *dst, wchar_t wc);
extern size_t __cdecl _wcstombs_ansi( char *dst, const wchar_t *pwcs, size_t len);
extern size_t __cdecl _mbstowcs_ansi(  wchar_t *, const char*, size_t len);

#if (defined(_WIN64) || defined(lp64))
#define labs labscore
#define llabs labscore
#else
#ifdef __GNUC__
extern long long llabs(long long);
#else
extern __int64 llabs(__int64);
#endif
#endif

#if defined(_SVR_I18N)
extern size_t __cdecl ucstombs(  char *s, const wchar_t *pucs, size_t len );
extern size_t __cdecl mbstoucs( wchar_t *, const char*, size_t);
#endif

#if  defined(_ALL_SOURCE)
extern size_t __cdecl wcsntombs( char*,  const wchar_t *, size_t dstlen, size_t srclen );
extern size_t __cdecl mbsntowcs( wchar_t *, const char*, size_t n, size_t m);

/* 
 * arc4 related header definitions
 */
u_int32_t arc4random(void);
void    arc4random_stir(void);
void    arc4random_addrandom(u_char *, int);

#endif /* defined(_ALL_SOURCE) */

#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
extern int    __cdecl rand_r(unsigned int *seed);
extern int    __cdecl  ptsname_r(int,  char*buf, int len );
#endif

#if  defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) \
			  || (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE))

#include <sys/wait.h>	/* for WNOHANG, WIFEXITED ... macros */

/*
 * additional prototypes from XPG4
 */
extern char *	__cdecl mktemp( char *);
extern int	__cdecl mkstemp( char *);
extern int	__cdecl putenv( char *);
extern char * 	__cdecl ptsname(int);
extern int	__cdecl grantpt(int);
extern int	__cdecl unlockpt(int);
extern int	__cdecl ttyslot(void);

extern int 	setkey(const char *);

/* 
 * BSD random number routines (now in XPG4)
 */
extern char * __cdecl initstate(unsigned int,  char *, size_t);
extern char * __cdecl setstate(const char *);
extern long   __cdecl random(void);
extern void   __cdecl srandom(unsigned int);

extern double           __cdecl drand48(void);
extern double           __cdecl erand48(unsigned short []);
extern long             __cdecl jrand48(unsigned short []);
extern void             __cdecl lcong48(unsigned short []);
extern long             __cdecl lrand48(void);
extern long             __cdecl mrand48(void);
extern long             __cdecl nrand48(unsigned short []);
extern unsigned short * __cdecl seed48(unsigned short []);
extern void             __cdecl srand48(long);

#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) ... */

#if defined(_ALL_SOURCE) \
	|| (defined(_XOPEN_SOURCE)&&(_XOPEN_SOURCE_EXTENDED==1)) \
        || (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE))
/*
 * additional prototypes from XPG4v2 - UNIX extensions
 */
extern long   __cdecl a64l(const char *);
extern char * __cdecl l64a(long);
extern char * __cdecl ecvt(double, int,  int*,  int*);
extern char * __cdecl fcvt(double, int,  int*,  int*);
extern char * __cdecl gcvt(double, int,  char *);
extern char * __cdecl realpath(const char *,  char *);
extern int    __cdecl getsubopt( char **,  char * const *,  char **);

#if defined(_ALL_SOURCE)
#if !defined(_IMPORT_LIBCDLL_GLOBALS)
extern char *suboptarg;	/* pointer to currently processed sub-option argument */
#else
#include <globalexport.h>
#define suboptarg (*((int*)libc_global(G_SUBOPTARG)))
#endif
#endif /*_ALL_SOURCE */

#endif /* defined(_ALL_SOURCE) ... */


#if  defined(_ALL_SOURCE) \
     || ( !defined(_XOPEN_SOURCE) && (__STDC__ - 0 == 0) \
				  && !defined(_POSIX_C_SOURCE) )
/*
 * additional prototypes from BSD4.4
 */
extern int    __cdecl setenv(const char *, const char *, int);
extern qdiv_t __cdecl qdiv(quad_t, quad_t);
extern quad_t __cdecl qabs(quad_t);

#endif /*defined(_ALL_SOURCE).. */


extern int daemon (int nochdir, int noclose);
extern char * getbsize(int *headerlenp, long *blocksizep);
extern int unsetenv (const char *name);


#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H_*/
