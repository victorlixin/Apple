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
 *  time.h 
 *
 *  RCSid = $Header: /E/interix/include/time.h,v 1.15 1999/04/23 02:38:02 SSI_DEV+mark Exp $
 *
 */

#ifndef _TIME_H
#define _TIME_H
 
#include <features.h>
#include <sys/time_impl.h> /* for struct timespec and time_t */
#include<sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

/* Define the implementation defined time type */

#ifndef _CLOCK_T_DEFINED
#define _CLOCK_T_DEFINED
typedef int32_t clock_t;		/* from <sys/types.h> */
#endif/*_CLOCK_T_DEFINED*/

/*Pointer precission data types*/
#ifndef _SIZE_T_DEFINED
#if (defined(lp64) || defined(_WIN64))
typedef unsigned __int64    size_t;
#else
typedef unsigned int  size_t;
#endif/*#if (defined(lp64) || defined(_WIN64))*/
#define _SIZE_T_DEFINED
#define _SIZE_T
#endif/*_SIZE_T_DEFINED*/


/* Define NULL pointer value */

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif/*__cplusplus*/
#endif/*NULL*/

/* Clock ticks macro - ANSI version */
#define CLOCKS_PER_SEC  1000
#define CLK_TCK  	CLOCKS_PER_SEC

#ifndef _TM_DEFINED
#define _TM_DEFINED
struct tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
        };
#endif/*_TM_DEFINED*/

/* Function prototypes */

extern char *	   __cdecl asctime(const struct tm *);
extern char *	   __cdecl ctime(const time_t *);
extern clock_t	   __cdecl clock(void);
extern double	   __cdecl difftime(time_t, time_t);
extern struct tm*  __cdecl gmtime(const time_t *);
extern struct tm*  __cdecl localtime(const time_t *);
extern time_t	   __cdecl mktime(struct tm *);
extern size_t	   __cdecl strftime( char *, size_t, const char *,
				    const struct tm *);
extern time_t	   __cdecl time(time_t *);
extern void	   __cdecl tzset(void);

/* Re-entrant functions prototypes.*/
#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
extern char *       __cdecl asctime_r(const struct tm *,  char *);
extern char *       __cdecl ctime_r(const time_t *,  char *);
extern struct tm* __cdecl gmtime_r(const time_t *, struct tm*);
extern struct tm* __cdecl localtime_r(const time_t *, struct tm*);
#endif

/* standard/daylight savings time zone names */
#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern char* tzname[2];
#else
#include <globalexport.h>
#define tzname ((char**)libc_global(G_TZNAME))
#endif


#if defined(_ALL_SOURCE)  || defined(_XOPEN_SOURCE) \
	|| (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE))

extern char * __cdecl strptime(const char *, const char *, struct tm *);

#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern long int timezone;    /* diff. in seconds between UTC and local time*/
extern int daylight;	     /* non-zero if daylight savings time active */
#else
#include <globalexport.h>
#define timezone (*(long int*)libc_global(G_TIMEZONE)
#define daylight (*(int*)libc_global(G_DAYLIGHT)
#endif

#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) */

#if defined(_ALL_SOURCE)  \
	|| (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED==1)) \
	|| (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE))
extern struct tm*  getdate(const char *);
#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern int getdate_err;     		/* errors for getdate() */
#else
#include <globalexport.h>
#define getdate_err (*((int*)libc_global(G_GETDATE_ERR)))
#endif
#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) */

#if (__STDC__ - 0 == 0) && !defined(_XOPEN_SOURCE) \
    && !defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
extern long	altzone;
extern int	cftime( char *, const char *, const time_t *);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TIME_H_ */
