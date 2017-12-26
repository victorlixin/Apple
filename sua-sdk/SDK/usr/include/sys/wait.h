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
 *
 * RCSID = $Header: /E/interix/include/sys/wait.h,v 1.5 1999/05/17 18:51:05 SSI_DEV+mark Exp $
 */ 

#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#include <features.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * wait options
 */

#define WNOHANG   0x1	/* don't block in wait() */
#define WUNTRACED 0x2	/* report stopped and untraced children */

/*
 * Structure of wait status value
 *
 *   bits 0-7 :
 *              if zero then process exited (see bits 8-15 for exit code)
 *              if 0x7f then process is stopped (see bits 8-15 for stop sig#)
 *		if anything else then bits 0-6 contains the signal number
 *		   (because process died due to this signal number)
 *
 *    bits 8-15  
 *		- exit status (only valid when bits 0-7 == 0)
 *		- stopped signal number (only valid when bits 0-7 == 0x7f)
 *
 *    [ signal number:
 *           bits 0-6: the signal number
 *           bit  7  : set if a core image file was created
 *    ]
 *            
 */

#define _W_STOPPED  0x7f	/* special value used to indicate process
				 * has been stopped - due to a signal
				 */
#define _W_SIGMASK  0x7f	/* signal# in bits 0-6, bit 7 is core flag */


/*
 * WIFEXITED() - true if child terminated normally (via _exit())
 * WEXITSTATUS - return exit status of process (value passed via _exit())
 * WIFSIGNALLED - true if child exited due to an uncaught signal
 * WTERMSIG     - returns signal number that terminated child
 * WIFSTOPPED   - true if child is currently stopped
 * WSTOPSIG     - returns signal number that stopped the child process
 */ 

#define WIFEXITED(stat_loc)	(((stat_loc) & 0xff) == 0)
#define WEXITSTATUS(stat_loc)	(((stat_loc) & 0xff00) >> 8)
#define WIFSIGNALED(stat_loc)	(!WIFSTOPPED(stat_loc) && !WIFEXITED(stat_loc))
#define WTERMSIG(stat_loc)	((stat_loc) & _W_SIGMASK)
#define WIFSTOPPED(stat_loc)	(((stat_loc) & 0xff) == _W_STOPPED)
#define WSTOPSIG(stat_loc)	(((stat_loc) & 0xff00) >> 8)

#if defined (_ALL_SOURCE) \
        || (!defined(_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE))
#define WCOREFLG		0x80
#define WCOREDUMP(stat_loc)	((stat_loc) & WCOREFLG)
#endif /* defined (_ALL_SOURCE) ... */

#ifndef _PID_T_DEFINED
#define _PID_T_DEFINED
typedef		int32_t pid_t;
#endif /* _PID_T_DEFINED*/

extern pid_t __cdecl wait(int *);
extern pid_t __cdecl waitpid(pid_t, int *, int );

#ifdef __cplusplus
}
#endif

#endif /* _SYS_WAIT_H */
