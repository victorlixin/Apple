/*C+
 *
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
 * Rcsid = $Header: /E/interix/include/grp.h,v 1.10 1999/03/23 05:53:20 rodney Exp $
 */

/*++
Copyright (c) 1992  Microsoft Corporation
Module Name:
	grp.h
Abstract:
	Defines data types and declares routines necessary for group database
	access, as required by 1003.1-88 (9.2.1).
--*/

#ifndef _GRP_H_
#define _GRP_H_
 
#include <features.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct group {
	char *gr_name;			/* the name of the group	*/
	gid_t gr_gid;			/* the numerical group ID	*/
	char **gr_mem;			/* null-terminated vector of pointers*/
					/*   to the individual member names*/
	char *gr_passwd;		/* group password; returns "*" always */
	long reserved[19];
};

struct group * _CRTAPI1 getgrgid(gid_t);
struct group * _CRTAPI1 getgrnam(const char *);

#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
int _CRTAPI1 getgrnam_r(const char *name, struct group *grp,  char *buffer,
        size_t bufsize, struct group **result);
int _CRTAPI1 getgrgid_r(gid_t gid, struct group *grp,  char *buffer,
        size_t bufsize, struct group **result);

#endif

#if defined(_ALL_SOURCE)  \
	|| (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE))  \
	|| (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED==1))

struct group * _CRTAPI1 getgrent(void);
void _CRTAPI1 setgrent(void);
void _CRTAPI1 endgrent(void);

#endif /* defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED == 1) */

#if  defined(_ALL_SOURCE) \
     || ( !defined(_XOPEN_SOURCE) && (__STDC__ - 0 == 0) \
                                  && !defined(_POSIX_C_SOURCE) )
/*
 * additional prototypes from BSD4.4
 */
#include <pwcache.h>

#endif /*defined(_ALL_SOURCE).. */

#if defined (_ALL_SOURCE)
/* flags for 2nd arg of getgrgid_ex() */
#define GR_NOMEMBERS 0x1
#define GR_FULLNAME  0x2

struct group * _CRTAPI1 getgrgid_ex(gid_t, unsigned int);
struct group * _CRTAPI1 getgrgid_nomembers(gid_t);
struct group * _CRTAPI1 getgrnam_nomembers(const char *);
struct group * _CRTAPI1 getgrent_nomembers(void);

#if defined(_REENTRANT)

int _CRTAPI1 getgrgid_ex_r(gid_t gid, unsigned int flags, struct group *grp,  char *buffer,
        size_t bufsize, struct group **result);
int _CRTAPI1 getgrgid_nomembers_r(gid_t gid, struct group *grp,  char *buffer,
        size_t bufsize, struct group **result);
int _CRTAPI1 getgrnam_nomembers_r(const char *name, struct group *grp,  char *buffer,
        size_t bufsize, struct group **result);

#endif /* defined (_REENTRANT) */

#endif /* defined(_ALL_SOURCE) */

#ifdef __cplusplus
}
#endif

#endif	/* _GRP_H_ */
