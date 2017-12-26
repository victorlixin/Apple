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

#ifndef _INTERIX_PATH_CONVERT_H
#define _INTERIX_PATH_CONVERT_H 1


#if defined(__cplusplus)
extern "C" {
#endif

#ifdef _WIN32_
/* error code required in path_convert().
 * But its not defined in Windows errno.h
 * so we just arbitrarily define it here
 */
#include <errno.h>

#ifndef E2SMALL
#define E2SMALL  100
#endif /*E2SMALL*/

#endif /*_WIN32_*/


/* 
 * Interix 3.0 lexical pathname conversion routine.
 * This is a library routine that just does conversions
 * based on lexical analysis. 
 */

// pathinfo_t - struct containing information for path_convert()
//
struct pathinfo_t {
        char *src;
        char *dst;
        long dstsize;
        int flags;
	int reserved[12];
        };

// value for info-> flags
//
#define PATHCONV_CASESENSITIVE  0x01

// values for path_convert() 'type' argument
//
#define PATHCONV_WIN2UNIX       1
#define PATHCONV_UNIX2WIN       2


extern int   __cdecl path_convert(int /*type*/, struct pathinfo_t * /*info*/);
extern char* __cdecl path_casesensitive(char* /*buf*/);


#if defined(__cplusplus)
}
#endif

#endif /* _INTERIX_PATH_CONVERT_H */
