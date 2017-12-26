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

/*M+
 * NAME
 *  	strings.h - Single UNIX Spec <strings.h>
 *
 * SYNOPSIS
 *	#include <strings.h>
 *
 * DESCRIPTION
 *	The <strings.h> header provides prototypes for various library
 *      routines. 
 * 
 * SEE ALSO
 *	...
 *
 * CHANGE HISTORY
 * Stephen R. Walli	19-Sep-1995	Initial revision.
 *
 *M-
 */
#ifndef _STRINGS_H_
#define	_STRINGS_H_

#include <features.h>

#if defined(_ALL_SOURCE) \
	 || (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE_EXTENDED==1)

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


/*Pointer precission data types*/
#ifndef _SIZE_T_DEFINED
#if (defined(lp64) || defined(_WIN64))
typedef unsigned __int64    size_t;
#else
typedef unsigned int  size_t;
#endif/*(defined(lp64) || defined(_WIN64))*/
#define _SIZE_T_DEFINED
#define _SIZE_T
#endif/*_SIZE_T_DEFINED*/

#ifndef _SSIZE_T_DEFINED
#if (defined(lp64) || defined(_WIN64))
typedef  __int64    ssize_t;
#else
typedef int  ssize_t;
#endif/*#if (defined(lp64) || defined(_WIN64))*/
#define _SSIZE_T_DEFINED
#endif/*_SSIZE_T_DEFINED*/

extern int	 __cdecl bcmp (const void *, const void *, size_t);
extern void	 __cdecl bcopy (const void *, void *, size_t);
extern void	 __cdecl bzero (void *, size_t);
extern int	 __cdecl ffs (int);
extern char *	 __cdecl index (const char *, int);
extern char *	 __cdecl rindex (const char *, int);
extern int	 __cdecl strcasecmp (const char *, const char *);
extern int	 __cdecl strncasecmp (const char *, const char *, size_t);

#if defined(_ALL_SOURCE)
extern char * __cdecl strsep (char **, const char *);
extern char * __cdecl strcasestr (const char *, const char *);
#endif

#if (defined(_PSX_KERNEL) && !defined(_PSX_DLL))
extern int     __cdecl _strcmpi(const char *, const char *);
extern int     __cdecl _stricmp(const char *, const char *);
extern int     __cdecl _stricoll(const char *, const char *);
extern int     __cdecl _strncoll(const char *, const char *, size_t);
extern int     __cdecl _strnicoll(const char *, const char *, size_t);
extern char *  __cdecl _strdup(const char *);
extern char *  __cdecl _strerror(const char *);
extern char *  __cdecl _strlwr(char *);
extern int     __cdecl _strnicmp(const char *, const char *, size_t);
extern char *  __cdecl _strnset(char *, int, size_t);
extern char *  __cdecl _strrev(char *);
extern char *  __cdecl _strupr(char *);
#endif /*defined(_PSX_KERNEL) && !defined(_PSX_DLL)*/

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) */

#endif /* _STRINGS_H_ */
