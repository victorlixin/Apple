/*C+
 *
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *
 * Rcsid = $Id:$
 */

/* defines prototypes and constants for the user/group name caching APIs.
 * These Apis are from BSD4.4
 */

#ifndef _PWCACHE_H_
#define _PWCACHE_H_  1

#include <features.h>
#include <sys/types.h>	/* for gid_t and uid_t */

#ifdef __cplusplus
extern "C" {
#endif


/*
 * pwcache_enable   :  set to 0 to turn off usr/grp name caching (default = 1)
 * group_from_gid() :  get group name using a groupID. Values are cached.
 * user_from_uid()  :  get user name using a userID. Values are cached.
 */
#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern int        pwcache_enable;
#else
#include <globalexport.h>
#define pwcache_enable (*((int*)libc_global(G_PWCACHE_ENABLE)))
#endif

extern char *  group_from_gid(gid_t, int);
extern char * user_from_uid(uid_t, int);


/* flags for 2nd arg of group_from_gid()  and user_from_uid() 
 */
#define PWCACHE_FULLNAME  1	/* return user/group fully qualified name */


#ifdef __cplusplus
}
#endif

#endif	/* _PWCACHE_H_ */
