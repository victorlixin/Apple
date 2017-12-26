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
 *      sys/msg.h -- message queue structure
 *
 * DESCRIPTION
 *      Definitions for the constants and structures for message queue facility
 *
 * SEE ALSO
 *      msgctl(), msgget(), msgrcv(), msgsnd(), <sys/types.h>
 *
 * CHANGE HISTORY
 * 
 *      Created on 04-Dec-96 by yan@softway.com
 *
 *M_
 */

#ifndef _SYS_MSG_H_
#define _SYS_MSG_H_

#if defined(__cplusplus)
extern "C" {
#endif


#include <features.h>

#include <sys/types.h>		/* for pid_t, time_t, key_t */
#include <sys/ipc.h>		/* for struct ipc_perm */

#define MSG_NOERROR 1<<12

typedef unsigned int msgqnum_t;
typedef size_t msglen_t;

struct msqid_ds {
    struct ipc_perm msg_perm;
    msglen_t        msg_cbytes;
    msgqnum_t       msg_qnum;
    msglen_t        msg_qbytes;
    pid_t           msg_lspid;
    pid_t           msg_lrpid;
    time_t          msg_stime;
    time_t          msg_rtime;
    time_t          msg_ctime;
};


int __cdecl msgctl ( int msqid, int cmd, struct msqid_ds *buf );
int __cdecl msgget ( key_t key, int msgflg );
int __cdecl msgsnd ( int msqid, const void *msgp, size_t msgsz, int msgflg );

#ifdef _PSX_KERNEL
#define long ssize_t
#endif //_PSX_KERNEL

ssize_t __cdecl msgrcv ( int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg );

#ifdef _PSX_KERNEL
#undef long
#endif //_PSX_KERNEL


#if defined(__cplusplus)
}
#endif

#endif  /* _SYS_MSG_H_ */
