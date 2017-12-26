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
 * RCSid = $Header: /E/interix/include/string.h,v 1.10 1999/02/03 16:27:34 SSI_DEV+mark Exp $
 */

#ifndef _STRING_H_
#define _STRING_H_
 
#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SIZE_T_DEFINED
#if defined (lp64) || defined(_WIN64)
typedef unsigned __int64    size_t;
#else
typedef unsigned int  size_t;
#endif/*(defined(lp64) || defined(_WIN64))*/
#define _SIZE_T_DEFINED
#define _SIZE_T
#endif/*_SIZE_T_DEFINED*/

#ifndef NULL
# ifdef __cplusplus
#    define NULL        0
# else
#    define NULL        ((void *)0)
# endif /*__cplusplus*/
#endif /*NULL*/

/* Function prototypes */
extern void *  __cdecl memchr(const void *, int, size_t);
extern int     __cdecl memcmp(const void *, const void *, size_t);
extern void *  __cdecl memcpy(void *, const void *, size_t);
extern void *  __cdecl memmove(void *, const void *, size_t);
extern void *  __cdecl memset(void *, int, size_t);
extern char *  __cdecl strcat(  char *, const char *);
extern char *  __cdecl strchr(const char *, int);
extern int     __cdecl strcmp(const char *, const char *);
extern int     __cdecl strcoll(const char *, const char *);
extern char *  __cdecl strcpy(  char *, const char *);
extern size_t  __cdecl strcspn(const char *, const char *);
extern char *  __cdecl strerror(int);
extern size_t  __cdecl strlen(const char *);
extern char *  __cdecl strncat( char *, const char *, size_t);
extern int     __cdecl strncmp(const char *, const char *, size_t);
extern char *  __cdecl strncpy( char *dst, const char *src, size_t count);
extern char *  __cdecl strpbrk(const char *, const char *);
extern char *  __cdecl strrchr(const char *, int);
extern size_t  __cdecl strspn(const char *, const char *);
extern char *  __cdecl strstr(const char *, const char *);
extern char *  __cdecl strtok( char *, const char *);
extern size_t  __cdecl strxfrm ( char *, const char *, size_t);
#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
extern int     __cdecl strerror_r(int,  char *, size_t);
extern char *  __cdecl strtok_r( char *, const char *,  char**);
#endif

#if defined(_ALL_SOURCE) 
extern char *  __cdecl mbsrchr(const char *, char);
#endif

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) \
	    || (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE)) 
extern void* __cdecl memccpy(void *, const void *, int, size_t);
#endif /* defined(_ALL_SOURCE) ... */


#if defined(_ALL_SOURCE)  \
	    || (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED==1)) \
	    || (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE)) 
extern char* __cdecl strdup(const char *);
#endif /* defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED == 1) */


#if defined(_ALL_SOURCE)
#include <strings.h>		/* include other BSD definitions */

extern char *strsignal(int);	/* Linux/Solaris compatibility */
extern char *strsigname(int);

/* strncat(), strncpy() replacements from OpenBSD/FreeBsd */
extern size_t strlcpy( char *dst, const char *src, size_t maxlen);
extern size_t strlcat( char *dst, const char *src, size_t maxlen);

#endif /* defined(_ALL_SOURCE) */


#ifdef __cplusplus
}
#endif

#endif	/* _STRING_H_ */
