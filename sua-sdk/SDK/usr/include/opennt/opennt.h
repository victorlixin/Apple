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

#ifndef _OPENNT_OPENNT_H
#define _OPENNT_OPENNT_H 1

#include <features.h>
#include <sys/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* NOTE: Apr, 2001
 *
 * ntpath2posix() and _ntpath2posix() have been removed 
 * from the Interix 3.0 release.
 * These interfaces were no longer usable with the new features
 * in Interix.  Namely 
 *   a) the /dev/fs/ directory now contains the 
 *      pointers to the Windows drive letters.
 *      The old Interix convention was /X  which is no longer implemented.
 *      Thus, it was no longer to call ntpath2posix(ptr, NULL, 0)
 *      since the result could be longer then the original path (ptr)
 *      and doing the conversion using the same buffer was dangerous.
 *   b) ntpath2posix() did lexical conversions only.
 *      The newer winpath2unix() may do more accurate job of converting
 *      Windows pathnames because it will follow windows reparse points.
 *
 * See winpath2unix(2) [ interix/interix.h ]
 * or  path_convert(3) [ interix/path_convert.h ]
 * for replacements.
 */

#if defined(__cplusplus)
}
#endif

#endif /* _OPENNT_OPENNT_H */
