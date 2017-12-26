/*C+
 * Copyright (C) Microsoft Corporation.  All rights reserved.
 */

/* 
 *  Rcsid = $Header: /E/interix/include/errno.h,v 1.17 1999/01/14 21:06:03 SSI_DEV+dmoen Exp $
 */

#ifndef _ERRNO_H_
#define _ERRNO_H_

#if defined(__cplusplus)
extern "C" {
#endif

#if (!defined(_PSX_KERNEL) || defined(_PSX_DLL))
#include <features.h>
#endif /*(!defined(_PSX_KERNEL) || defined(_PSX_DLL))*/

#ifndef errno
#if defined(_REENTRANT) || (_POSIX_C_SOURCE - 0 >= 199506L) 
  extern int * __cdecl __errno();
  #define errno (*(__errno()))
#else
  extern int errno;
#endif  /* defined(_REENTRANT) ...) */
#endif

/*
 *  Interix error codes
 */
#define  EZERO		0	/* No error				*/
#define  EPERM		1	/* Operation not permitted		*/
#define  ENOENT		2	/* No such file or directory		*/
#define  ESRCH		3	/* No such process			*/
#define  EINTR		4	/* Interrupted function call		*/
#define  EIO		5	/* Input/output error			*/
#define  ENXIO		6	/* No such device or address		*/
#define  E2BIG		7	/* Arg list too long			*/
#define  ENOEXEC	8	/* Exec format error			*/
#define  EBADF		9	/* Bad file descriptor			*/
#define  ECHILD		10	/* No child processes			*/
#define  EAGAIN		11	/* Resource temporarily unavailable	*/
#define  EWOULDBLOCK	EAGAIN
#define  ENOMEM		12	/* Not enough space			*/
#define  EACCES		13	/* Permission denied			*/
#define  EFAULT		14	/* Bad address				*/
#define  ENOTBLK	15	/* Unknown error			*/
#define  EBUSY		16	/* Resource device			*/
#define  EEXIST		17	/* File exists				*/
#define  EXDEV		18	/* Improper link			*/
#define  ENODEV		19	/* No such device			*/
#define  ENOTDIR	20	/* Not a directory			*/
#define  EISDIR		21	/* Is a directory			*/
#define  EINVAL		22	/* Invalid argument			*/
#define  ENFILE		23	/* Too many open files in system	*/
#define  EMFILE		24	/* Too many open files			*/
#define  ENOTTY		25	/* Inappropriate I/O control operation	*/
#define  ETXTBSY	26	/* Text file busy			*/
#define  ETXTBUSY	ETXTBSY
#define  EFBIG		27	/* File too large			*/
#define  ENOSPC		28	/* No space left on device		*/
#define  ESPIPE		29	/* Invalid seek				*/
#define  EROFS		30	/* Read-only file system		*/
#define  EMLINK		31	/* Too many links			*/
#define  EPIPE		32	/* Broken pipe				*/
#define  EDOM		33	/* Domain error				*/
#define  ERANGE		34	/* Result too large			*/
#define  EIDRM		35	/* IPC object has been deleted          */
#define  EDEADLK	36	/* Resource deadlock avoided		*/
#define  EDEADLOCK	EDEADLK	
#define  EALREADY	37	/* Operation already in progress	*/
#define  ENAMETOOLONG	38	/* Filename too long			*/
#define  ENOLCK		39	/* No locks available			*/
#define  ENOSYS		40	/* Function not implemented		*/
#define  ENOTEMPTY	41	/* Directory not empty			*/
#define  EILSEQ		42      /* Invalid multi-byte character         */

#define EPROTONOSUPPORT	43	/* Protocol not supported		*/
#define ESOCKTNOSUPPORT	44	/* Socket type not supported		*/
#define EOPNOTSUPP	45	/* Operation not supported		*/
#define EPFNOSUPPORT	46	/* Protocol family not supported	*/
#define EAFNOSUPPORT	47	/* Address family not supported by protocol*/
#define EADDRINUSE	48	/* Address already in use		*/
#define EADDRNOTAVAIL	49	/* Can't assign requested address	*/
#define ENETDOWN	50	/* Network is down			*/
#define ENETUNREACH	51	/* Network is unreachable		*/
#define ENETRESET	52	/* Network dropped connection on reset	*/
#define ECONNABORTED	53	/* Software caused connection abort	*/
#define ECONNRESET	54	/* Connection reset by peer		*/
#define ENOBUFS		55	/* No buffer space available		*/
#define EISCONN		56	/* Socket is already connected		*/  
#define ENOTCONN	57	/* Socket is not connected		*/
#define ESHUTDOWN	58	/* Can't send after socket shutdown	*/
#define ETOOMANYREFS	59	/* Too many references: can't splice	*/
#define ETIMEDOUT	60	/* Operation timed out			*/
#define ECONNREFUSED	61	/* Connection refused			*/
#define ELOOP		62	/* Too many levels of symbolic links	*/
#define EBADENCRYPTDATA  63	/* Invalid encrypted data found */
#define EHOSTDOWN	64	/* Host is down				*/
#define EHOSTUNREACH	65	/* No route to host			*/
#define ENOSETUID       66	/* Cannot exec() - setuid/setgid not enabled*/

#define EPROCLIM	67	/* Too many processes			*/
#define EUSERS		68	/* Too many users			*/
#define EDQUOT		69	/* Disk quota exceeded			*/

/* NFS errors          70-78      -  not used yet			*/

#define EFTYPE		79	/* Inappropriate file type or format	*/

/* ipc/network software */
#define EINPROGRESS	80	/* Operation now in progress		*/
#define ENOTSOCK	81	/* Socket operation on non-socket	*/
#define EDESTADDRREQ	82	/* Destination address required		*/
#define EMSGSIZE	83	/* Message too long		`	*/
#define EPROTOTYPE	84	/* Protocol wrong type for socket	*/
#define ENOPROTOOPT	85	/* Protocol not available		*/
#define ENOMSG		86	/* No message of desired type		*/
			    /* note: was equal to ENOENT(2) in Interix 2.x */

#define EWINPATH	87	/* Can't map pathname to Windows namespace */
#define EOVERFLOW	88	/* Value too large for datatype */
#define E2SMALL	        89	/* user data buffer too small */


/* netdb errors (for h_errno) */
#define EHOSTNOTFOUND	90
#define ETRYAGAIN	91
#define ENORECOVERY	92
#define ENODATA		93

/* other errors */
#define ENOTSUP 	94
#define EPROTO          95      /* Protocol Error */

#if defined(_ALL_SOURCE)
#define MAX_ERRNO 	95
#endif /* defined(_ALL_SOURCE) */

#if defined(__cplusplus)
}
#endif

#endif /* _ERRNO_H_ */

