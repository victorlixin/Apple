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
 * C-
 */

#ifndef _SECURITY_H
#define _SECURITY_H


#if defined(__cplusplus)
extern "C" {
#endif
  
#include <features.h> 
#include <sys/types.h> 

/* 
 * Constants for 'logontype'.
 * Must be 0 for now
 */
#define PSX_LOGON_INTERACTIVE 0
#define PSX_LOGON_NETWORK 1
#define PSX_LOGON_BATCH 2
#define PSX_LOGON_SERVICE 3

/* 
 * Constants for 'logonprovider'.
 * Must be 0 for now.
 */
#define PSX_LOGON_PROVIDER_DEFAULT 0
#define PSX_LOGON_PROVIDER_WINNT35 1
#define PSX_LOGON_PROVIDER_WINNT40 2

/*
 * Flags for setuser API.
 */
#define SU_COMPLETE	(0x0000)	/* apply to real + eff id's */
#define SU_CHECK	(0x0001)	/* check only; take no action */
#define SU_SET_SAVED	(0x0002)	/* apply to saved uid + gid too */
#define SU_USE_SAVED	(0x0004)	/* use saved to set real and eff id's */
#define SU_MAXFLAG	(0x0007)	/* for validity checks */

struct usersec {
    char *user;
    char *domain;
    char *password;
    int  logontype;      /* Must be 0 */
    int  logonprovider;  /* Must be 0 */
};

extern char *stripdomainprefix(const char *fullname, const char *domain, 
                               const int casesensitive );

extern char*  _CRTAPI1 uidtontsid(uid_t uid);

extern int _CRTAPI1 getsecret( char * /*keyname*/,  void* /*data*/, 
						  int /*datalen*/);
extern int _CRTAPI1 setsecret( char * /*keyname*/,  void* /*data*/, 
						  int /*datalen*/);

#if defined (_ALL_SOURCE)

extern int _CRTAPI1 uidtontsid_r(uid_t uid,  char *buf, int bufsize);

#endif // defined (_ALL_SOURCE)


#if (!defined(_PSX_KERNEL) || defined(_PSX_DLL))

extern int _CRTAPI1 setuser(const char *aname, const char *apass,
				const int flags);
extern int _CRTAPI1 authenticateuser(const struct usersec userdata);
extern int _CRTAPI1 execl_asuser(const struct usersec userdata, 
				 const char *, const char *, ...);
extern int _CRTAPI1 execv_asuser(const struct usersec userdata, 
				  const char *,  char * const []);
extern int _CRTAPI1 execle_asuser(const struct usersec userdata, 
				  const char *, const char *arg, ...);
extern int _CRTAPI1 execve_asuser(const struct usersec userdata, 
				   const char *,  char * const [],
				   char * const []);
extern int _CRTAPI1 execlp_asuser(const struct usersec userdata, 
				  const char *, const char *, ...);
extern int _CRTAPI1 execvp_asuser(const struct usersec userdata, 
				   const char *,  char * const []);

#endif /* (!defined(_PSX_KERNEL) || defined(_PSX_DLL)) */



#if defined(__cplusplus)
}
#endif

#endif /* _SECURITY_H */
