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

#ifndef _SCHED_H_
#define _SCHED_H_

#include <time.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _PID_T_DEFINED
#define _PID_T_DEFINED
typedef		int32_t pid_t;
#endif /* _PID_T_DEFINED*/

/* sched_param structure  contains the scheduling parameters required for 
 * implementation of each supported scheduling policy. 
 */
struct sched_param {
    int     sched_priority;	/* process execution scheduling priority */
    int     sched_nicelim;	/* nice value limit for SCHED_OTHER policy */
    int     sched_nice;		/* nice value for SCHED_OTHER policy */
    
     /* 
      * 'sched_pad' element here is used for padding.  The main purpose is to 
      * maintain the same structure size, even if we add new elements to this 
      * structure in future, so that it is backward compatible.  So the 
      * padding needs to be changed accordingly if any new elements are added 
      * to this structure 
      */
    int     sched_pad[6];	
};

/*
 *	scheduling policies
 */
#define SCHED_FIFO	1	/* run to completion */
#define SCHED_RR	2	/* round-robin */
#define SCHED_OTHER	3

/*
 *	function prototypes
 */
int __cdecl	sched_yield(void);
int __cdecl	sched_get_priority_max(int);
int __cdecl	sched_get_priority_min(int);

#ifdef  __cplusplus
}
#endif

#endif /* _SCHED_H_ */
