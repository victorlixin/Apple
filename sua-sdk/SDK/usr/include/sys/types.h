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
 *
 * RCSID = $Header: /E/interix/include/sys/types.h,v 1.18 2000/03/15 20:23:30 NORTHAMERICA+markfunk Exp $
 *
 */


#ifndef _SYS_TYPES_
#define _SYS_TYPES_

#include <features.h>

#include <sys/endian.h>
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/
#if defined(_SVR_I18N)
/*compatibility with SVR*/
typedef unsigned long      off64_t;
typedef unsigned int       off32_t;
typedef unsigned long       ino64_t;
typedef unsigned long       blkcnt64_t;
typedef unsigned long       lid_t;
typedef long level_t;
#endif /*_SVR_I18N*/

/* types for compat. with various BSD and other library sources */
typedef signed char      int8_t;
typedef unsigned char  u_int8_t;
typedef short            int16_t;
typedef unsigned short u_int16_t;
typedef int              int32_t;
typedef unsigned int   u_int32_t;

/* types for compat. with Solaris 7 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

/*
 * 64bit type for BSD compatability
 */
#ifdef __GNUC__
typedef long long int 		  quad_t;
typedef unsigned long long int	u_quad_t;
typedef long long int             int64_t;
typedef unsigned long long int  u_int64_t;
#elif _MSC_VER
typedef __int64 		  quad_t;
typedef unsigned __int64 	u_quad_t;
typedef __int64 		  int64_t;
typedef unsigned __int64 	u_int64_t;
#endif /*__GNUC__*/

#if defined(_ALL_SOURCE) \
     || (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) \
     || (__STDC__ -0 == 0)


/*
 * Additional types for sockets and streams
 */
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned short	ushort;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

typedef unsigned int    uint;
typedef unsigned long   ulong;
typedef unsigned char   unchar;

#endif	/* _ALL_SOURCE */

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
#endif/* (defined(lp64) || defined(_WIN64))*/
#define _SSIZE_T_DEFINED
#endif/*_SSIZE_T_DEFINED*/

/*
 *   POSIX data types
 */

#ifndef _MODE_T_DEFINED
#define _MODE_T_DEFINED
typedef u_int32_t mode_t;
#endif  /*_MODE_T_DEFINED*/

#ifndef _NLINK_T_DEFINED
#define _NLINK_T_DEFINED
typedef u_int32_t nlink_t;
#endif /* _NLINK_T_DEFINED*/

#ifndef _PID_T_DEFINED
#define _PID_T_DEFINED
typedef		int32_t pid_t;
#endif /* _PID_T_DEFINED*/

#ifndef _UID_T_DEFINED
#define _UID_T_DEFINED
typedef u_int32_t uid_t;
#endif /* _UID_T_DEFINED*/

#ifndef _GID_T_DEFINED
#define _GID_T_DEFINED
typedef uid_t gid_t;
#endif /* _GID_T_DEFINED*/

#ifndef _SUSECONDS_T_DEFINED
#define _SUSECONDS_T_DEFINED
typedef int32_t suseconds_t;
#endif /*_SUSECONDS_T_DEFINED*/

#if (defined(_PSX_KERNEL) && defined(_WIN64))
#define ulong size_t
#define long ssize_t
#else
#define ulong unsigned long
#endif/*(defined(_PSX_KERNEL) && defined(_WIN64))*/

#ifndef _OFF_T_DEFINED
typedef 	 long off_t;
#define _OFF_T_DEFINED
#endif/*_OFF_T_DEFINED*/

#ifndef _N_OFF_T_DEFINED
typedef         long n_off_t;
#define _N_OFF_T_DEFINED
#endif /*_N_OFF_DEFINED*/


#ifndef _INO_T_DEFINED
typedef ulong ino_t;
#define _INO_T_DEFINED
#endif/*_INO_T_DEFINED*/

#ifndef _BLKSIZE_T_DEFINED
typedef long blksize_t;
#define _BLKSIZE_T_DEFINED
#endif/*_BLKSIZE_T_DEFINED*/

#ifndef _BLKCNT_T_DEFINED
typedef long blkcnt_t;
#define _BLKCNT_T_DEFINED
#endif/*_BLKCNT_T_DEFINED*/

#ifndef _FSBLKCNT_T_DEFINED
typedef ulong fsblkcnt_t;
#define _FSBLKCNT_T_DEFINED
#endif/*_FSBLKCNT_T_DEFINED*/

#ifndef _FSFILCNT_T_DEFINED
typedef ulong fsfilcnt_t;
#define _FSFILCNT_T_DEFINED
#endif/*_FSFILCNT_T_DEFINED*/

#undef ulong
#if (defined(_PSX_KERNEL) && defined(_WIN64))
#undef long
#endif/*(defined(_PSX_KERNEL) && defined(_WIN64))*/

#ifndef _DEV_T_DEFINED
typedef u_int32_t dev_t;
#define _DEV_T_DEFINED
#endif/*_DEV_T_DEFINED*/

#ifndef _TIME_T_DEFINED
typedef int32_t time_t;
#define _TIME_T_DEFINED
#endif/*_TIME_T_DEFINED*/




#if defined(_SVR_I18N) && !defined(_PSX_LIB)
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef int 	wchar_t;
#endif
#else
#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
typedef unsigned short 	wchar_t;
#endif
#endif


#ifndef _WCTYPE_T_DEFINED
#define _WCTYPE_T_DEFINED
typedef wchar_t wctype_t;

#ifndef _WINT_T
#define _WINT_T
typedef int wint_t;
#endif /*_WINT_T*/
#endif /* _WCTYPE_T_DEFINED */


#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef unsigned short  sa_family_t;
#endif /* !_SA_FAMILY_T */

/*
 * additional symbols not defined in POSIX.1 but are permitted
 */

/*
 * symbols in XPG4
 */
#ifndef _CLOCK_T_DEFINED
typedef int32_t clock_t;
#define _CLOCK_T_DEFINED
#endif/*_CLOCK_T_DEFINED*/

#ifndef _USECONDS_T_DEFINED
typedef u_int32_t useconds_t;
#define _USECONDS_T_DEFINED
#endif/*_USECONDS_T_DEFINED*/

#ifndef _ID_T_DEFINED
typedef u_int32_t id_t;
#define _ID_T_DEFINED
#endif /* _ID_T_DEFINED */

/* types for Networking headers */
typedef char            *caddr_t;

/* types for IPC */
typedef int32_t key_t;

/* types from SVR4 */
typedef unsigned char uchar_t;
typedef unsigned int uint_t;
typedef unsigned short ushort_t;
typedef unsigned long ulong_t;

typedef struct {
        void *_current_table;
        long _state;
        long _fill[7];
        long _policy;
} __mbstate_t;


/*
 * pthread definitions
 */
#ifndef _THREAD_T_DEFINED
#define _THREAD_T_DEFINED
typedef id_t	thread_t;		/* thread id type	*/
#endif/*_THREAD_T_DEFINED*/

#ifndef _PTHREAD_T_DEFINED
#define _PTHREAD_T_DEFINED
typedef thread_t	pthread_t;	/* pthread id type	*/
#endif/*_PTHREAD_T_DEFINED*/

/*
 * attributes for threads, dynamically allocated by library
 */
typedef  void* pthread_attr_t;

/*
 * mutex, cond variables and their attributes
 */
typedef void*   pthread_mutex_t;
typedef void*   pthread_cond_t;
typedef void*   pthread_mutexattr_t;
typedef void*   pthread_condattr_t;

/*
 * pthread once, keys
 */
typedef struct {
    void* _once_value ;
    pthread_mutex_t _once_mutex ;
    int _reserved[6];
} pthread_once_t ;

typedef u_int32_t pthread_key_t;

/*
 * spinlock, rwlock and attributes for rwlock
 */
typedef void*   pthread_spinlock_t;
typedef void*   pthread_rwlock_t;
typedef void*   pthread_rwlockattr_t;

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif  /* _SYS_TYPES_ */
