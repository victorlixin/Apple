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
#ifndef _SYS_UTSNAME_H_
#define _SYS_UTSNAME_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _UTS_BUFSIZE	257

struct utsname {
    char sysname [_UTS_BUFSIZE];
    char nodename[_UTS_BUFSIZE];
    char release [_UTS_BUFSIZE];
    char version [_UTS_BUFSIZE];

    /* note: for backwards compat with Interix2.2, 
     *       these last 4 members must use only 257 bytes
     */

    /* generic machine/architecture type - x86, alpha, ... */
    char machine[16];	

    /* info from host OS (Windows NT info) */
    char sysname_host[20];	/* Windows NT */
    char release_host[10];	/* 4.0 */
    char version_host[10];	/* SP5 */

    /* more specific processor type - Pentium_I, Alpha_22064, */
    char processor [50];

    /* reserved space */
    char padding[257-16-40-50];
};

extern int __cdecl uname(struct utsname *name);

#ifdef __cplusplus
}
#endif

#endif /*_SYS_UTSNAME_H_*/
