/***
*eh.h - User include file for exception handling.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       User include file for exception handling.
*
*       [Public]
*
*Revision History:
*       10-12-93  BSC   Module created.
*       11-04-93  CFW   Converted to CRT format.
*       11-03-94  GJF   Ensure 8 byte alignment. Also, changed nested include
*                       macro to match our naming convention.
*       12-15-94  XY    merged with mac header
*       02-11-95  CFW   Add _CRTBLD to avoid users getting wrong headers.
*       02-14-95  CFW   Clean up Mac merge.
*       12-14-95  JWM   Add "#pragma once".
*       02-20-97  GJF   Cleaned out obsolete support for _CRTAPI* and _NTSDK.
*                       Replaced !defined(_M_MPPC) && !defined(_M_M68K) with
*                       !defined(_MAC). Also, detab-ed.
*       09-30-97  JWM   Restored not-so-obsolete _CRTAPI1 support.
*       10-07-97  RDL   Added IA64.
*       05-13-99  PML   Remove _CRTAPI1
*       05-17-99  PML   Remove all Macintosh support.
*       12-10-99  GB    Added __uncaught_exception().
*       09-22-04  AGH   Guard header with #ifndef RC_INVOKED, so RC ignores it
*       10-01-04  SJ    Added function _is_exception_typeof
*       10-10-04  ESC   Use _CRT_PACKING
*       10-20-04  MAL   Declare terminate() as __declspec(noreturn) for prefast
*       11-07-04  MSL   Allow get terminate and unexpected
*       11-18-04  ATC   SAL Annotations for CRT Headers
*
****/

#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#include <crtdefs.h>

#ifndef _INC_EH
#define _INC_EH
#ifndef RC_INVOKED

#if 0
#ifndef _CRTBLD
/* This version of the header files is NOT for user programs.
 * It is intended for use when building the C runtimes ONLY.
 * The version intended for public use will not have this message.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */
#endif

#ifdef  _MSC_VER
/* Currently, all MS C compilers for Win32 platforms default to 8 byte 
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#ifndef __cplusplus
#error "eh.h is only for C++!"
#endif

typedef void (__cdecl *terminate_function)();
typedef void (__cdecl *unexpected_function)();
typedef void (__cdecl *terminate_handler)();
typedef void (__cdecl *unexpected_handler)();

struct _EXCEPTION_POINTERS;
typedef void (__cdecl *_se_translator_function)(unsigned int, struct _EXCEPTION_POINTERS*);
_CRTIMP __declspec(noreturn) void __cdecl terminate(void);
_CRTIMP void __cdecl unexpected(void);

_CRTIMP int __cdecl _is_exception_typeof(__in const type_info &_P(_Type), __in struct _EXCEPTION_POINTERS * _P(_ExceptionPtr));

_CRTIMP terminate_function __cdecl set_terminate(__in_opt terminate_function _P(_NewPtFunc));
extern "C" _CRTIMP terminate_function __cdecl _get_terminate(void);
_CRTIMP unexpected_function __cdecl set_unexpected(__in_opt unexpected_function _P(_NewPtFunc));
extern "C" _CRTIMP unexpected_function __cdecl _get_unexpected(void);
_CRTIMP _se_translator_function __cdecl _set_se_translator(__in_opt _se_translator_function _P(_NewPtFunc));
_CRTIMP bool __cdecl __uncaught_exception();

/*
 * These overload helps in resolving NULL
 */
_CRTIMP terminate_function __cdecl set_terminate(__in_opt int _P(_Zero));
_CRTIMP unexpected_function __cdecl set_unexpected(__in_opt int _P(_Zero));
_CRTIMP _se_translator_function __cdecl _set_se_translator(__in_opt int _P(_Zero));

#if _MSC_VER >= 1400 && defined(__cplusplus) && defined(_M_CEE) /*IFSTRIP=IGN*/
typedef void (__clrcall *__terminate_function_m)();
typedef void (__clrcall *__unexpected_function_m)();
typedef void (__clrcall *__terminate_handler_m)();

_MRTIMP __terminate_function_m __cdecl set_terminate(__in_opt __terminate_function_m _P(_NewPtFunc));
_MRTIMP __unexpected_function_m __cdecl set_unexpected(__in_opt __unexpected_function_m _P(_NewPtFunc));
#endif

#ifndef _INTERNAL_IFSTRIP_
#if defined(CRTDLL) && !defined(_SYSCRT)
/*
 * All these function pointer are used for creating global state of CRT
 * functions. Either all of them will be set or all of them will be NULL
 */
typedef terminate_function (__cdecl *_set_terminate_function)(terminate_function);
typedef terminate_function (__cdecl *_get_terminate_function)(void);
typedef unexpected_function (__cdecl *_set_unexpected_function)(unexpected_function);
typedef unexpected_function (__cdecl *_get_unexpected_function)(void);
extern _set_terminate_function _set_terminate_server;
extern _get_terminate_function _get_terminate_server;
extern _set_unexpected_function _set_unexpected_server;
extern _get_unexpected_function _get_unexpected_server;
extern terminate_function _terminate_server;
extern unexpected_function _unexpected_server;
#endif
#endif  /* _INTERNAL_IFSTRIP_ */
#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */
#endif /* RC_INVOKED */
#endif  /* _INC_EH */
