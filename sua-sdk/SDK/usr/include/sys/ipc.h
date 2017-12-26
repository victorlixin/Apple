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

/*M+
 * NAME
 *      sys/ipc.h -- interprocess communication access structure
 *
 * SYNOPSIS
 *      #include <sys/ipc.h>
 *
 * DESCRIPTION
 *      Definitions for the common structure type ipc_perm and constants
 *      used by IPC mechanisms
 *
 * SEE ALSO
 *      <sys/types.h>
 *
 * CHANGE HISTORY
 *      ...
 *
 *M_
 */

#ifndef _SYS_IPC_H_
#define _SYS_IPC_H_


#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>
#include <sys/types.h> 	/* for uid_t, gid_t, mode_t */

#define IPC_CREAT  1<<9
#define IPC_EXCL   1<<10
#define IPC_NOWAIT 1<<11

#define IPC_RMID   0
#define IPC_SET    1
#define IPC_STAT   2

#define IPC_PRIVATE 0L

struct ipc_perm {
    uid_t   uid;
    gid_t   gid;
    uid_t   cuid;
    gid_t   cgid;
    mode_t  mode;
};


#if (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) \
      || !defined(_XOPEN_SOURCE) \
      || defined(_ALL_SOURCE)

extern key_t ftok(const char*, int);

#endif

#if defined(__cplusplus)
}
#endif


#endif  /* _SYS_IPC_H_ */
