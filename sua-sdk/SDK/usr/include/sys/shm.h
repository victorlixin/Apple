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
 *      sys/shm.h -- shared memory facility
 *
 * SYNOPSIS
 *      #include <sys/shm.h>
 *
 * DESCRIPTION
 *      Definitions for the constants and structures for shared memory facility
 *
 * SEE ALSO
 *      shmat(), shmctl(), shmdt(), shmget(), <sys/types.h>
 *
 * CHANGE HISTORY
 *      ...
 *
 *M_
 */

#ifndef _SYS_SHM_H_
#define _SYS_SHM_H_


#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define SHM_RDONLY 1<<12
#define SHM_RND    1<<13

#define SHMLBA     0x00400000

typedef unsigned int shmatt_t;

struct shmid_ds {
    struct ipc_perm shm_perm;
    size_t          shm_segsz;
    pid_t           shm_lpid;
    pid_t           shm_cpid;
    shmatt_t        shm_nattch;
    time_t          shm_atime;
    time_t          shm_dtime;
    time_t          shm_ctime;
};

void * __cdecl shmat(int shmid, const void *shmaddr, int shmflg );
int    __cdecl shmctl(int shmid, int cmd, struct shmid_ds *buf );
int    __cdecl shmdt(const void *shmaddr );
int    __cdecl shmget(key_t key, size_t size, int shmflg );


#if defined(__cplusplus)
}
#endif

#endif  /* _SYS_SHM_H_ */
