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
 * RCSid = $Header: /E/interix/include/ftw.h,v 1.4 1998/07/10 14:09:52 SSI_DEV+mark Exp $
 */ 

#ifndef	_FTW_H_
#define	_FTW_H_

#if defined(__cplusplus)
extern "C" {
#endif


#include <features.h>
#include <sys/stat.h>

/*c
 * Constants indicating the file-object-type.
 * (2nd argument of ftw() and nftw()) 
 */
#define	FTW_D		1		/* preorder directory */
#define	FTW_DP	2		/* postorder directory */
#define	FTW_DNR	3		/* unreadable directory */
#define	FTW_F		4		/* regular file */
#define	FTW_NS	5		/* stat() failed */

#if defined (_ALL_SOURCE) \
	|| !defined(_XOPEN_SOURCE) \
	|| (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED))
#define	FTW_SL	6		/* symbolic link */
#define	FTW_SLN	7		/* symbolic link without target */
#endif /*defined (_ALL_SOURCE) || (defined(_XOPEN_SOURCE) .. */


int ftw(const char *, int (*) (const char *, const struct stat *, int), int);

#if defined (_ALL_SOURCE) \
	|| !defined(_XOPEN_SOURCE) \
	|| (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED))
/*f
 * Flags controlling the functioning of nftw(). (4th argument to nftw())
 */
#define	FTW_CHDIR	0x001		/* change directories during the walk */
#define	FTW_DEPTH	0x002		/* report dir last */
#define	FTW_MOUNT	0x004		/* only walk the indicated filesystem */
#define	FTW_PHYS	0x008		/* do a physical walk */

/*t
 * A structure to supply supplementary information in the 
 * user callback function from ntfw().
 */
struct FTW {
	int base;	/* offset of the filename in supplied pathname */
	int level;	/* depth below root of the walk */
};

int nftw(const char *path,
	   int (*func) (const char *, const struct stat *, int, struct FTW *),
	   int depth, int flags);
#endif /* defined (_ALL_SOURCE) || (defined(_XOPEN_SOURCE) .. */


#if defined(__cplusplus)
}
#endif

#endif /* !_FTW_H_ */
