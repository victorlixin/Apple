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

#ifndef _INTERIX_INTERIX_H
#define _INTERIX_INTERIX_H 1

#include <features.h>
#include <sys/types.h>

#if defined(__cplusplus)
extern "C" {
#endif


#include <wchar.h>
typedef const wchar_t * PCWSTR;
#define ENABLE_REDIRECTION  1
#define DISABLE_REDIRECTION 0

#define ENABLE 1
#define DISABLE 0

//
// 'type' values returned by getreg().
//
// WIN_REG_NONE             	No value type
// WIN_REG_SZ               	Unicode nul terminated string
// WIN_REG_EXPAND_SZ        	Unicode nul terminated string
// 				(with environment variable references)
// WIN_REG_BINARY           	Free form binary
// WIN_REG_DWORD            	 32-bit number
// WIN_REG_DWORD_LITTLE_ENDIAN       32-bit number (same as WIN_REG_DWORD)
// WIN_REG_DWORD_BIG_ENDIAN          32-bit number
// WIN_REG_LINK                      Symbolic Link (unicode)
// WIN_REG_MULTI_SZ                  Multiple Unicode strings
// WIN_REG_RESOURCE_LIST             Resource list in the resource map
// WIN_REG_FULL_RESOURCE_DESCRIPTOR  Resource list in the hardware description
// WIN_REG_RESOURCE_REQUIREMENTS_LIST 
// 
#define WIN_REG_NONE           		(0)   
#define WIN_REG_SZ             		(1)  
#define WIN_REG_EXPAND_SZ      		(2) 
#define WIN_REG_BINARY         		(3)
#define WIN_REG_DWORD          		(4)
#define WIN_REG_DWORD_LITTLE_ENDIAN     	(4)
#define WIN_REG_DWORD_BIG_ENDIAN        	(5)
#define WIN_REG_LINK                    	(6)
#define WIN_REG_MULTI_SZ                	(7)
#define WIN_REG_RESOURCE_LIST           	(8)
#define WIN_REG_FULL_RESOURCE_DESCRIPTOR 	(9)
#define WIN_REG_RESOURCE_REQUIREMENTS_LIST 	(10)



/* 
 * routines to get info from the registry 
 */
/*
 * getreg()
 *  OUT data  - buffer to contain contents of registry entry 
 *  OUT type  - type of data returned in 'data'
 *  IN  path  - single byte string containing full registry pathname 
 *               (Key and Value)
 *  INT size  - max size of bytes of 'data' buffer
 */
extern int __cdecl getreg( char * /*path*/, int *    /*type*/, 
			   void * /*data*/, size_t * /*size*/);

/* getreg_strvalue()
 *  Return the ansi string from a registry entry.
 *   IN  keystr    - name of registry key        (wide char string)
 *   IN  valuestr  - name of registry value      (wide char string)
 *   OUT buf       - buffer to store the result in   (ansi string)
 *   IN  bufsize   - size of the buffer (in bytes)
 *
 * Return 0 on success, 1 on failure
 */
extern int __cdecl getreg_strvalue( PCWSTR keystr,
			             PCWSTR valuestr,
				     char * buf,
				    int    bufsize);

/* getreg_wstrvalue()
 *  Return the wide char (UNICODE) string from a registry entry.
 *   IN  keystr    - name of registry key        (wide char string)
 *   IN  valuestr  - name of registry value      (wide char string)
 *   OUT buf       - buffer to store the result in   (wide char string)
 *   IN  bufsize   - size of the buffer (in bytes)
 *
 * Return 0 on success, 1 on failure
 */
extern int __cdecl getreg_wstrvalue(PCWSTR   /*keystr*/,
			            PCWSTR   /*valuestr*/,
				     wchar_t* /*buf*/,
				    int      /*size of buf (in wchars) */);

/*
 * Interix 3.0 pathname conversion routines.
 */
#define PATH_SYMLINK	1
#define PATH_NONSTRICT	2
extern int __cdecl winpath2unix(const char * path, int  flags, 
				       char * buf, size_t buflen);
extern int __cdecl unixpath2win(const char * path, int  flags, 
			 	       char * buf, size_t buflen);

/*
 * gettzenv() - return a string containing "TZ=tzinfo"
 *              where tzinfo is the system default time zone
 * getpdomain(char *buf, size_t bufsize);
 *              - return principal domain name in buf
 * chpass(char *fullyqualifiedusername, char *oldpasswd, char *newpasswd);
 *              - change a user's password
 */
extern char*  __cdecl gettzenv();
extern int    __cdecl getpdomain( char * buf, size_t bufsize);
extern int    __cdecl chpass( char *,  char *,  char *);

extern char* __cdecl _getInstallPath(void);
extern char* __cdecl _prefixInstallPath(const char *,  char *, int);
extern char* __cdecl _getInstallPath_Win(void);
extern char* __cdecl _prefixInstallPath_Win(const char *,  char *, int);

int __cdecl pdxWow64EnableFSRedirection(int);
int __cdecl accessMisAlignedData(int);

extern void SqmLogSUAFeature(int, int);

#if defined(__cplusplus)
}
#endif

/*
 * This is the chunk size by which TEB pointer array gets expanded.
 */
#define PTHREAD_CHUNK_SIZE	32
#define PTHREAD_CHUNK_NUM_BITS  5     /* 2 power 5 = 32 */
#define PTHREAD_CHUNK_BINARY    0x1F  /* binary representation of 31 */

#endif /* _INTERIX_INTERIX_H */
