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

/*
 * Implementation-private.  This header should not be included
 * directly by an application.  The application should instead
 * include <time.h> which includes this header.
 */

#ifndef _SYS_TIME_IMPL_H
#define _SYS_TIME_IMPL_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
typedef int time_t;            /* from <sys/types.h> */
#endif

#if defined(_ALL_SOURCE) \
	|| ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) )
	
#ifdef _PSX_KERNEL
#define long ssize_t
#endif //_PSX_KERNEL

struct timespec {
        time_t  tv_sec;         /* seconds */
	long    tv_nsec;        /* nanoseconds */
};

#ifdef _PSX_KERNEL
#undef long
#endif //_PSX_KERNEL

#endif // defined(_ALL_SOURCE) || ( ..  && (_POSIX_C_SOURCE >= 19309L) )

#ifdef __cplusplus
}
#endif

#endif /* _SYS_TIME_IMPL_H */
