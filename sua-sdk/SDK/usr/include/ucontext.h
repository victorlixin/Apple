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
 * Rcsid = $Header: /E/interix/include/ucontext.h,v 1.6 1998/09/17 19:37:01 SSI_DEV+mark Exp $
 *
 */ 

#ifndef _UCONTEXT_H
#define _UCONTEXT_H


#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>

#include <signal.h>    /* for defn of sigset_t and stack_t */

#include <sys/reg.h>	/* get register definitions for regset.h */
#include <sys/regset.h> /* get defn for mcontext_t */

typedef struct ucontext ucontext_t;
struct ucontext {
    ucontext_t *uc_link;
    sigset_t	uc_sigmask;
    stack_t	uc_stack;
    mcontext_t	uc_mcontext;
};

#if defined(__cplusplus)
}
#endif


#endif /* _UCONTEXT_H */
