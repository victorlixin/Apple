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

/*M+
 * $Id: monetary.h,v 1.5 1999/05/05 14:43:28 jeff Exp $
 * NAME
 *  	monetary.h - ...
 *
 * SYNOPSIS
 *	#include <monetary.h>
 *
 * DESCRIPTION
 *	The <monetary.h> header provides definitions for strfmon().
 * 
 * SEE ALSO
 *	strfmon(3).
 *
 * CHANGE HISTORY
 * Jeffrey Copeland	03 May 1999	Initial revision.
 *
 *M-
 */
#ifndef _MONETARY_H
#define	_MONETARY_H

#include <features.h>
#include <stddef.h>	/* size_t */
#include <sys/types.h>	/* ssize_t */

#ifdef __cplusplus
extern "C" {
#endif

extern ssize_t  _CRTAPI1 strfmon(char *, size_t, const char *, ...);

#ifdef __cplusplus
}
#endif

#endif
