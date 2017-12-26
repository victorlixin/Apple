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

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/types.h>
#include <fcntl.h>
#include <sys/time_impl.h> /* For struct timespec */

#ifdef __cplusplus
extern "C" {
#endif

typedef void*  sem_t;

#define SEM_FAILED ((sem_t *)(-1))

sem_t* __cdecl sem_open(const char *, int, ...);
int __cdecl sem_close (sem_t *);
int __cdecl sem_unlink(const char *);
int __cdecl sem_init(sem_t *, int, unsigned int);
int __cdecl sem_destroy(sem_t *);
int __cdecl sem_post(sem_t *);
int __cdecl sem_getvalue(sem_t *, int *);
int __cdecl sem_timedwait(sem_t *, const struct timespec *);
int __cdecl sem_trywait(sem_t *);
int __cdecl sem_wait(sem_t *);

#ifdef __cplusplus
}
#endif

#endif /* _SEMAPHORE_H_ */
