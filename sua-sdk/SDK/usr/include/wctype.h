//depot/interixR2/include/wctype.h#1 - branch change 12040 (text)
/*C+
 * Copyright 1999 by Softway Systems, Inc.  All rights reserved.
 * 
 * This Software Source is the unpublished, valuable, confidential property
 * of Softway Systems, Inc.  Use is authorised only under the terms and
 * conditions set out in the source code licence agreement protecting this
 * Software Source.  Any unauthorised use or disclosure of this Software 
 * Source is prohibited.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' BY SOFTWAY SYSTEMS, INC. AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL SOFTWAY SYSTEMS, INC. BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */ 
/* $Id: wctype.h,v 1.1 1999/06/29 17:44:39 jeff Exp $ */

#ifndef _WCTYPE_INTERIX_H_
#define _WCTYPE_INTERIX_H_

#include <features.h>

#include <wchar.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int __cdecl      iswblank(wint_t);

#ifdef __cplusplus
}
#endif

#endif	/* _WCTYPE_INTERIX_H_ */
