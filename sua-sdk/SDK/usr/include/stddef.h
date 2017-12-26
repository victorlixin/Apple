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

#ifndef _STDDEF_H_
#define _STDDEF_H_
#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Define NULL pointer value and the offset() macro */

#ifndef NULL
# ifdef __cplusplus
#    define NULL	0
# else
#    define NULL	((void *)0)
# endif /*__cplusplus*/
#endif /*NULL*/


#define offsetof(type,member)	((size_t)&(((type *)0)->member))

#ifndef _SIZE_T_DEFINED
#if defined (lp64) || defined(_WIN64)
typedef unsigned __int64    size_t;
#else
typedef unsigned int  size_t;
#endif/*(defined(lp64) || defined(_WIN64))*/
#define _SIZE_T_DEFINED
#define _SIZE_T
#endif/*_SIZE_T_DEFINED*/

#ifndef _SSIZE_T_DEFINED
#if (defined(lp64) || defined(_WIN64))
typedef __int64    ssize_t;
#else
typedef int  ssize_t;
#endif/*#if (defined(lp64) || defined(_WIN64))*/
#define _SSIZE_T_DEFINED
#endif/*_SIZE_T_DEFINED*/




/* define the implementation dependent size types */

#ifndef _INTPTR_T_DEFINED
typedef ssize_t intptr_t;
#define _INTPTR_T_DEFINED
#endif/*_INTPTR_T_DEFINED*/

#ifndef _UINTPTR_T_DEFINED
typedef size_t   uintptr_t;
#define _UINTPTR_T_DEFINED
#endif/*_UINTPTR_T_DEFINED*/

#ifndef _PTRDIFF_T_DEFINED
typedef ssize_t ptrdiff_t;
#define _PTRDIFF_T_DEFINED
#endif/*_PTRDIFF_T_DEFINED*/



#if defined(_SVR_I18N) && !defined(_PSX_LIB)
#ifndef _WCHAR_T_DEFINED
typedef int  wchar_t;
#define _WCHAR_T_DEFINED
#endif/*_WCHAR_T_DEFINED*/
#else
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif/*_WCHAR_T_DEFINED*/
#endif


#ifdef __cplusplus
}
#endif

#endif	/* _STDDEF_H_ */
