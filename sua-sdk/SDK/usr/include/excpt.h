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


#ifndef _EXCPT_H_
#define _EXCPT_H_

#include <features.h>


/***
*excpt.h - defines exception values, types and routines
*
*       Copyright (c) 1990-1995, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the definitions and prototypes for the compiler-
*       dependent intrinsics, support functions and keywords which implement
*       the structured exception handling extensions.
*
*       [Public]
*
****/



#ifdef  _MSC_VER	/* MSVC compiler exception handling */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_PSX_KERNEL) && !defined(_PSX_LIB) && !defined(_PSX_DLL) && !(_CRTBLD)
typedef unsigned int DWORD;
typedef void * PVOID;
#endif
   
/*
 * Exception disposition return values.
 */
typedef enum _EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

#ifndef _CRTIMP
#ifdef _DLL
#define _CRTIMP __declspec(dllimport)
#else /*_DLL not defined*/
#define _CRTIMP
#endif /* _DLL */
#endif /* _CRTIMP */

/*
 * Prototype for SEH support function.
 */

/*
 * Declarations to keep compiler happy
 */
struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _DISPATCHER_CONTEXT;
typedef struct _EXCEPTION_POINTERS *Exception_info_ptr;

#ifdef _M_IX86

EXCEPTION_DISPOSITION __cdecl _except_handler (
    struct _EXCEPTION_RECORD *ExceptionRecord,
    void * EstablisherFrame,
    struct _CONTEXT *ContextRecord,
    void * DispatcherContext
    );

#elif defined(_M_IA64)

_CRTIMP EXCEPTION_DISPOSITION __C_specific_handler (
    struct _EXCEPTION_RECORD *ExceptionRecord,
    unsigned __int64 MemoryStackFp,
    unsigned __int64 BackingStoreFp,
    struct _CONTEXT *ContextRecord,
    struct _DISPATCHER_CONTEXT *DispatcherContext,
    unsigned __int64 GlobalPointer
    );

#elif   defined(_M_AMD64)

_CRTIMP EXCEPTION_DISPOSITION __C_specific_handler (
    struct _EXCEPTION_RECORD *ExceptionRecord,
    void *EstablisherFrame,
    struct _CONTEXT *ContextRecord,
    struct _DISPATCHER_CONTEXT *DispatcherContext
    );

#elif   defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC)

extern EXCEPTION_DISPOSITION __C_specific_handler (
    struct _EXCEPTION_RECORD *ExceptionRecord,
    void *EstablisherFrame,
    struct _CONTEXT *ContextRecord,
    struct _DISPATCHER_CONTEXT *DispatcherContext
    );

#endif


/*
 * Keywords and intrinsics for SEH
 */
#if defined(_NTSDK) && !defined(__cplusplus)
#define try                       __try
#define except                    __except
#define finally                   __finally
#define leave                     __leave
#endif  /* _NTSDK */


#define GetExceptionCode          _exception_code
#define exception_code            _exception_code
#define GetExceptionInformation   (struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info            (struct _EXCEPTION_POINTERS *)_exception_info
#define AbnormalTermination         _abnormal_termination
#define abnormal_termination        _abnormal_termination

#pragma warning(push)
#pragma warning(disable:4391)
unsigned int __cdecl _exception_code(void);
#pragma warning(pop)

void *        __cdecl _exception_info(void);
int           __cdecl _abnormal_termination(void);


/*
 * Legal values for expression in except().
 */

#define EXCEPTION_EXECUTE_HANDLER       1
#define EXCEPTION_CONTINUE_SEARCH       0
#define EXCEPTION_CONTINUE_EXECUTION    -1

#if !defined(_PSX_KERNEL) && !defined(_PSX_LIB)
/* 
 ***  Additional INFO obtained from <winnt.h>
 */
#define EXCEPTION_NONCONTINUABLE 0x1    // Noncontinuable exception
#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum exception parameters

#ifdef _WIN64

#define DWORD64 __int64

typedef struct _EXCEPTION_RECORD {
    DWORD    ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD * ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    DWORD __unusedAlignment;
    DWORD64 ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD, *PEXCEPTION_RECORD;
#else /* _WIN64 */

typedef struct _EXCEPTION_RECORD {
    /*lint -e18 */  // Don't complain about different definitions
    DWORD    ExceptionCode;
    /*lint +e18 */  // Resume checking for different definitions
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    DWORD ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
    } EXCEPTION_RECORD;
#endif /* _WIN64 */

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

//
// Typedef for pointer returned by exception_info()
//

typedef struct _CONTEXT *PCONTEXT;

typedef struct _EXCEPTION_POINTERS {
    PEXCEPTION_RECORD ExceptionRecord;
    PCONTEXT ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

/* 
 ***  END - Additional INFO obtained from <winnt.h>
 */
#endif /*_PSX_KERNEL*/


#ifdef __cplusplus
}
#endif

#endif /* _MSC_VER */

#endif	/* _EXCPT_H_ */
