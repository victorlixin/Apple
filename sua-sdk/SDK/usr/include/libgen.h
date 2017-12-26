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
 * RCSid = $Header: /E/interix/include/libgen.h,v 1.2 1998/07/22 22:22:36 SSI_DEV+mark Exp $
 */

#ifndef _LIBGEN_H_
#define _LIBGEN_H_

#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_ALL_SOURCE) \
	|| (defined(_XOPEN_SOURCE)&&(_XOPEN_SOURCE_EXTENDED==1)) \
        || (__STDC__ - 0 == 0 && !defined(_POSIX_C_SOURCE))
/*
 * prototypes from XPG4v2 - UNIX extensions
 */
extern char * __cdecl basename(char *);
extern char * __cdecl dirname(char *);

#endif /* defined(_ALL_SOURCE) ... */


#ifdef __cplusplus
}
#endif

#endif /* _LIBGEN_H_*/
