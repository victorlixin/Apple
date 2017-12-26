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

#ifndef _SYS_TIMEB_H_
#define	_SYS_TIMEB_H_

#include <features.h>

#if (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) \
      || !defined(_XOPEN_SOURCE) || defined(_ALL_SOURCE)

#include <sys/types.h>	/* to get definition of time_t  (XPG4 requirement) */

struct timeb {
        time_t time;
        unsigned short millitm;
        short timezone;
        short dstflag;
};


#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

int __cdecl ftime(struct timeb*);

#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif /*(defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED)) ...*/

#endif /*_SYS_TIMEB_H_*/
