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
 * RCSID = $Header: /E/interix/include/search.h,v 1.5 1997/10/20 19:06:38 SSI_DEV+jamesp Exp $
 */ 

#ifndef	_SEARCH_H_
#define	_SEARCH_H_

#include <features.h>

#include <sys/types.h>	/* for size_t */

/* Note that the bsearch() prototype is in <stdlib.h>.  */

/*
 * A type to contain the information needed by the hsearch() API.
 */
typedef struct entry {
	char * key;		/* string to key the assoiciated datum upon */
	void * data;	/* the datum to be stored */
} ENTRY;

/*
 * An enumerated type to indicate the type of visit twalk() has called
 * it's 'action()' argument for.
 */
typedef enum __visit { preorder, postorder, endorder, leaf } VISIT;

/*
 * An enumerated type to control the behaviour of hsearch() and hsearch_r().
 */
typedef enum __action { FIND, ENTER, REMOVE } ACTION;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Hash table API prototypes.
 */
int    hcreate(size_t);
void   hdestroy(void);
ENTRY *hsearch(ENTRY, ACTION);


/*
 * lsearch() APIs prototypes.
 */
void *lsearch(const void *, void *, size_t *, size_t,
	      int (*) (const void *, const void *));

void *lfind(const void *, const void *, size_t *, size_t,
	    int (*) (const void *, const void *));


/*
 * tsearch() API protoypes.
 */
void *tdelete(const void*, void**,int (*)(const void*, const void*));
void *tfind(const void*, void* const*,int (*)(const void*, const void*));
void *tsearch(const void*, void**,int (*)(const void*, const void*));
void  twalk(const void *, void (*)(const void*, VISIT, int));


#ifdef _ALL_SOURCE
/*
 * Re-entrant Hash table API prototypes.
 */
void   *hcreate_r(size_t);
void	  hdestroy_r(void *);
ENTRY  *hsearch_r(void *, ENTRY, ACTION);
#endif /* (_ALL_SOURCE) */

#ifdef __cplusplus
}
#endif

#endif /* _SEARCH_H_ */
