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
  * rcsid = $Header: /E/interix/include/nl_types.h,v 1.2 1999/02/25 19:21:10 SSI_DEV+mark Exp $
  */
#ifndef _NL_TYPES_INTERIX_H_
#define _NL_TYPES_INTERIX_H_  1

#define	NL_SETD		1
#define NL_CAT_LOCALE   1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _nl_catd {
	void	*__data;
	int	__size;
} *nl_catd;

typedef unsigned int	nl_item;

extern nl_catd  __cdecl catopen(const char *, int);
extern char *   __cdecl catgets(nl_catd, int, int, const char *);
extern int	__cdecl catclose(nl_catd);

#ifdef __cplusplus
}
#endif

#endif	/* _NL_TYPES_INTERIX_H_ */
