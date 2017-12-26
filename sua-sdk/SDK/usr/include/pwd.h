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
  * Rcsid = $Header: /E/interix/include/pwd.h,v 1.9 1998/11/19 22:33:23 rodney Exp $
  */

#ifndef _PWD_H_
#define _PWD_H_
 
#include <features.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct passwd {
	char *pw_name;				/* users login name	*/
	uid_t pw_uid;				/* user id number	*/
	gid_t pw_gid;				/* group id number	*/
	char *pw_dir;				/* home directory	*/
	char *pw_shell;				/* shell		*/
	char *pw_passwd;			/* password. Always "*" */
	char *pw_gecos;				/* login info */
	time_t pw_change;			/* password change time */
	time_t pw_expire;			/* account expiration   */
	long  reserved[20];
};

struct passwd * _CRTAPI1 getpwuid(uid_t);
struct passwd * _CRTAPI1 getpwnam(const char *);

#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
int _CRTAPI1 getpwuid_r(uid_t uid, struct passwd *pwd,  char *buffer,
        size_t bufsize, struct passwd **result);
int _CRTAPI1 getpwnam_r(const char *name, struct passwd *pwd,  char *buffer,
        size_t bufsize, struct passwd **result);
#endif

#if defined(_ALL_SOURCE)  \
	    || (defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED==1)) \
	    || (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE)) 

struct passwd * _CRTAPI1 getpwent(void);
void _CRTAPI1 setpwent(void);
void _CRTAPI1 endpwent(void);

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
/* flags for 2nd arg of getpwuid_ex() */
#define PW_FULLNAME 0x1

struct passwd * _CRTAPI1 getpwuid_ex(uid_t, unsigned long);

#if defined(_REENTRANT)
int _CRTAPI1 getpwuid_ex_r(uid_t uid, unsigned long flags, struct passwd *pwd,  char *buffer,
        size_t bufsize, struct passwd **result);
#endif /* defined (_REENTRANT) */

#endif /* defined(_ALL_SOURCE) */

#ifdef __cplusplus
}
#endif

#endif /* _PWD_H_ */
