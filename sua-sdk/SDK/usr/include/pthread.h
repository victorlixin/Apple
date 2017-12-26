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

#ifndef _PTHREAD_H_
#define _PTHREAD_H_


#include <sys/types.h>
#include <sched.h>
#include <time.h>



#ifdef __cplusplus
extern "C" {
#endif

#define PTHREAD_CANCEL_ENABLE           1
#define PTHREAD_CANCEL_DISABLE          2
#define PTHREAD_CANCEL_DEFERRED         3
#define PTHREAD_CANCEL_ASYNCHRONOUS     4
#define PTHREAD_MUTEX_NORMAL 1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_RECURSIVE 3
#define PTHREAD_MUTEX_DEFAULT PTHREAD_MUTEX_NORMAL

#define PTHREAD_CREATE_DETACHED         0x40
#define PTHREAD_CREATE_JOINABLE         0
#define PTHREAD_SCOPE_SYSTEM            0x01
#define PTHREAD_SCOPE_PROCESS           2
#define PTHREAD_INHERIT_SCHED           1
#define PTHREAD_EXPLICIT_SCHED          2
#define PTHREAD_PROCESS_SHARED          1       /* = USYNC_PROCESS */
#define PTHREAD_PROCESS_PRIVATE         2       /* = USYNC_THREAD */
#define DEFAULT_TYPE                    PTHREAD_PROCESS_PRIVATE

#define PTHREAD_CANCELED                ((void *)-19)
    
#define PTHREAD_PRIO_PROTECT 1
#define PTHREAD_PRIO_INHERIT 2
#define PTHREAD_PRIO_NONE 3

#define PTHREAD_P_DEFAULT_PRIOCEILING 0

#define PTHREAD_P_INVALID_PTHREADID -1

#define PTHREAD_MUTEX_INITIALIZER (pthread_mutex_t)-1
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER (pthread_mutex_t)-2

#define PTHREAD_COND_INITIALIZER (pthread_cond_t)-1
#define PTHREAD_RWLOCK_INITIALIZER (pthread_rwlock_t)-1

#define PTHREAD_ONCE_NOTDONE		1
#define PTHREAD_ONCE_DONE		2
#define PTHREAD_ONCE_INIT 	{(void*)PTHREAD_ONCE_NOTDONE,  \
    PTHREAD_RECURSIVE_MUTEX_INITIALIZER}

typedef struct timespec pthread_timespec;

typedef void* pthread_p_create_init_func (void *);
 int __cdecl pthread_atfork(void (*)(void), void (*)(void), void (*)(void));


int __cdecl	pthread_create(pthread_t*, const pthread_attr_t*, void* (*) (void *), void *);
int __cdecl	pthread_join(pthread_t, void **);
void __cdecl	pthread_exit(void *);
int __cdecl	pthread_detach(pthread_t);
pthread_t __cdecl	pthread_self(void);
int __cdecl	pthread_equal(pthread_t, pthread_t);
int __cdecl	pthread_cancel(pthread_t);
int __cdecl	pthread_setcanceltype(int, int *);
int __cdecl	pthread_setcancelstate(int, int *);
void __cdecl	pthread_testcancel(void);
int __cdecl 	pthread_once(pthread_once_t * once_control, void (*init_routine) (void));

int __cdecl	pthread_attr_init(pthread_attr_t *);
int __cdecl	pthread_attr_destroy(pthread_attr_t *);
int __cdecl 	pthread_attr_setdetachstate (pthread_attr_t * attr, int detachstate);
int __cdecl 	pthread_attr_getdetachstate (const pthread_attr_t * attr, int *detachstate);
int __cdecl 	pthread_attr_setschedparam (pthread_attr_t *attr, const struct sched_param *param);
int __cdecl 	pthread_attr_getschedparam (const pthread_attr_t *attr, struct sched_param *param);
int __cdecl 	pthread_attr_getstackaddr (const pthread_attr_t * attr, void **stackaddr);
int __cdecl 	pthread_attr_getstacksize (const pthread_attr_t * attr, size_t * stacksize);
int __cdecl 	pthread_attr_setstackaddr (pthread_attr_t * attr, void *stackaddr);
int __cdecl 	pthread_attr_setstacksize (pthread_attr_t * attr, size_t stacksize);
int __cdecl 	pthread_attr_setstack(pthread_attr_t * attr, void *stackaddr, size_t stacksize);
int __cdecl 	pthread_attr_getstack(const pthread_attr_t * attr, void **stackaddr, size_t* stacksize);
int __cdecl     pthread_attr_setguardsize(pthread_attr_t * attrp, size_t guardsize);
int __cdecl     pthread_attr_getguardsize (const pthread_attr_t * attrp, size_t * guardsize);
int __cdecl 	pthread_attr_setschedpolicy (pthread_attr_t *, int);
int __cdecl 	pthread_attr_getschedpolicy (const pthread_attr_t *, int *);
int  __cdecl 	pthread_attr_setinheritsched(pthread_attr_t * attr, int inheritsched);
int __cdecl 	pthread_attr_getinheritsched(const pthread_attr_t * attr, int * inheritsched);
int __cdecl 	pthread_attr_setscope (pthread_attr_t *, int scope);
int __cdecl 	pthread_attr_getscope (const pthread_attr_t *, int *);

int __cdecl pthread_getschedparam (pthread_t thread, int *policy, struct sched_param *param);	
int __cdecl pthread_setschedparam (pthread_t thread, int policy,const struct sched_param *param); 
int __cdecl pthread_setschedprio(pthread_t thread, int prio);
int __cdecl pthread_setconcurrency (int);
int __cdecl pthread_getconcurrency (void);


int __cdecl  pthread_mutex_init(pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
int __cdecl  pthread_mutex_destroy(pthread_mutex_t * mutex);
int __cdecl  pthread_mutex_lock(pthread_mutex_t * mutex);
int __cdecl  pthread_mutex_timedlock(pthread_mutex_t *mutext, pthread_timespec *abstime);
int __cdecl  pthread_mutex_trylock(pthread_mutex_t* mutex);
int __cdecl  pthread_mutex_unlock(pthread_mutex_t * mutex);
int __cdecl pthread_mutexattr_init (pthread_mutexattr_t * attr);
int __cdecl pthread_mutexattr_destroy (pthread_mutexattr_t * attr);
int __cdecl pthread_mutexattr_getpshared (const pthread_mutexattr_t * attr, int *pshared);
int __cdecl pthread_mutexattr_setpshared (pthread_mutexattr_t * attr, int  pshared);
int __cdecl pthread_mutexattr_settype (pthread_mutexattr_t * attr, int kind);
int __cdecl pthread_mutexattr_gettype (const pthread_mutexattr_t * attr, int *kind);
int __cdecl   pthread_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr);
int __cdecl   pthread_cond_destroy(pthread_cond_t * cond);
int __cdecl   pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex);
int __cdecl   pthread_cond_timedwait(pthread_cond_t * cond, pthread_mutex_t * mutex, const pthread_timespec *abstime);
int __cdecl   pthread_cond_signal(pthread_cond_t * cond);
int __cdecl   pthread_cond_broadcast(pthread_cond_t * cond);
int __cdecl pthread_condattr_init (pthread_condattr_t * attr);
int __cdecl pthread_condattr_destroy (pthread_condattr_t * attr);
int __cdecl pthread_condattr_getpshared (const pthread_condattr_t * attr,  int *pshared);
int __cdecl  pthread_condattr_setpshared (pthread_condattr_t * attr, int pshared);

int __cdecl pthread_key_create(pthread_key_t *, void (*)(void *));
int __cdecl pthread_key_delete(pthread_key_t);
void * __cdecl pthread_getspecific(pthread_key_t);
int __cdecl pthread_setspecific(pthread_key_t, const void *);
void __cdecl __pthread_cleanup_push(void (__cdecl *)(void *), void *);
void __cdecl __pthread_cleanup_pop(int);


int __cdecl pthread_rwlockattr_init (pthread_rwlockattr_t * attr);
int __cdecl pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr);
int __cdecl pthread_rwlockattr_getpshared (const pthread_rwlockattr_t * attr, int *pshared);
int __cdecl pthread_rwlockattr_setpshared (pthread_rwlockattr_t * attr, int pshared);
int __cdecl pthread_rwlock_init(pthread_rwlock_t *lock, const pthread_rwlockattr_t *attr);
int __cdecl pthread_rwlock_destroy(pthread_rwlock_t *lock);
int __cdecl pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int __cdecl pthread_rwlock_trywrlock(pthread_rwlock_t *);
int __cdecl pthread_rwlock_rdlock(pthread_rwlock_t *lock);
int __cdecl pthread_rwlock_timedrdlock(pthread_rwlock_t *lock, const struct timespec *abstime);
int __cdecl pthread_rwlock_wrlock(pthread_rwlock_t *lock);
int __cdecl pthread_rwlock_timedwrlock(pthread_rwlock_t *lock,  const struct timespec *abstime);
int __cdecl pthread_rwlock_unlock(pthread_rwlock_t *lock);

int __cdecl pthread_spin_init (pthread_spinlock_t * lock, int pshared);
int __cdecl pthread_spin_destroy (pthread_spinlock_t * lock);
int __cdecl pthread_spin_lock (pthread_spinlock_t * lock);
int __cdecl pthread_spin_trylock (pthread_spinlock_t * lock);
int __cdecl pthread_spin_unlock (pthread_spinlock_t * lock);

#define pthread_cleanup_push(routine, arg) { \
    __pthread_cleanup_push((void (__cdecl *)(void *))routine, (void *)arg);

#define pthread_cleanup_pop(execute) __pthread_cleanup_pop(execute); \
    }

#ifdef __cplusplus
}
#endif

#endif


