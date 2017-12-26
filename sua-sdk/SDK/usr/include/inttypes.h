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
 * RCSID = $Header: /E/interix/include/sys/inttypes.h $
 *
 */

#ifndef _SYS_INTTYPES_
#define _SYS_INTTYPES_

#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

/* types for compat. with various BSD and other library sources */
typedef signed char      int8_t;
typedef unsigned char  u_int8_t;
typedef short            int16_t;
typedef unsigned short u_int16_t;
typedef int              int32_t;
typedef unsigned int   u_int32_t;

/* types for compat. with Solaris 7 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

/*
 * 64bit type for BSD compatability
 */
#ifdef __GNUC__
typedef long long int 		  quad_t;
typedef unsigned long long int	u_quad_t;
typedef long long int             int64_t;
typedef unsigned long long int  u_int64_t;
#elif _MSC_VER
typedef __int64 		  quad_t;
typedef unsigned __int64 	u_quad_t;
typedef __int64 		  int64_t;
typedef unsigned __int64 	u_int64_t;
#endif /*__GNUC__*/

/* define the implementation dependent size types */

#ifndef _SIZE_T_DEFINED
#if (defined(lp64) || defined(_WIN64))
typedef unsigned __int64    size_t;
#else
typedef unsigned int  size_t;
#endif/*(defined(lp64) || defined(_WIN64))*/
#define _SIZE_T_DEFINED
#endif/*_SIZE_T_DEFINED*/

#ifndef _SSIZE_T_DEFINED
#if (defined(lp64) || defined(_WIN64))
typedef __int64    ssize_t;
#else
typedef int  ssize_t;
#endif/*(defined(lp64) || defined(_WIN64))*/
#define _SSIZE_T_DEFINED
#endif/*_SSIZE_T_DEFINED*/

#ifndef _INTPTR_T_DEFINED
typedef ssize_t intptr_t;
#define _INTPTR_T_DEFINED
#endif/*_INTPTR_T_DEFINED*/

#ifndef _UINTPTR_T_DEFINED
typedef size_t   uintptr_t;
#define _UINTPTR_T_DEFINED
#endif/*_UINTPTR_T_DEFINED*/

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif /*_SYS_INTTYPES_*/
