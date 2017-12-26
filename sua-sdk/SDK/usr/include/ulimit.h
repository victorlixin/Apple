/*
Copyright (c) 2000  Microsoft Corporation. All rights reserved.
*/

/*
 * Rcsid = $Header$;
 */

#ifndef _ULIMIT_H
#define _ULIMIT_H

#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UL_GETFSIZE	1
#define UL_SETFSIZE	2

/* svr4/solaris compatibilty -not implemented yet */
// #define UL_GMEMLIM	3	/* get maximum possible brk() size */
#define UL_GDESLIM	4	/* get maximum file descriptor limit */


extern long int ulimit(int cmd, ...);


#ifdef __cplusplus
}
#endif

#endif /* _ULIMIT_H */
