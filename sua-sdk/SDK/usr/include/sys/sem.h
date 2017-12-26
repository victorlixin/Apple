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
 *      sys/sem.h -- semaphore facility
 *
 * SYNOPSIS
 *      #include <sys/sem.h>
 * 
 * DESCRIPTION
 *      Definitions for the constants and structures for semaphore facility
 *
 * SEE ALSO
 *      semctl(), semget(), semop(), <sys/types.h>
 *
 * CHANGE HISTORY
 *      ...
 *
 *M_ 
 */


#ifndef _SYS_SEM_H_
#define _SYS_SEM_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>

#include <sys/types.h>
#include <sys/ipc.h>

#define SEM_UNDO 1<<12

#define GETNCNT  3
#define GETPID   GETNCNT+1
#define GETVAL   GETNCNT+2
#define GETALL   GETNCNT+3
#define GETZCNT  GETNCNT+4
#define SETVAL   GETNCNT+5
#define SETALL   GETNCNT+6


struct semid_ds {
    struct ipc_perm    sem_perm;
    unsigned short int sem_nsems;
    time_t             sem_otime;
    time_t             sem_ctime;
};

struct sembuf {
    unsigned short int sem_num;
    short int          sem_op;
    short int          sem_flg;
};

struct sem {
    unsigned short int semval;
    pid_t              sempid;
    unsigned short int semncnt;
    unsigned short int semzcnt;
};

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int __cdecl semctl(int semid, int semnum, int cmd, ... ) ;
int __cdecl semget(key_t key, int nsems, int semflg );
int __cdecl semop(int semid, struct sembuf *sops, size_t nsops );


#if defined(__cplusplus)
}
#endif

#endif /* _SYS_SEM_H_ */
