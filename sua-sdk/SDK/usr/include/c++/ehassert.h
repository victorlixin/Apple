/***
*ehassert.h - our own little versions of the assert macros.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Versions of the assert macros for exception handling.
*
*       [Internal]
*
*Revision History:
*       09-02-94  SKS   This header file added.
*       12-15-94  XY    merged with mac header
*       02-14-95  CFW   Clean up Mac merge.
*       03-29-95  CFW   Add error message to internal headers.
*       04-13-95  DAK   Add NT Kernel EH support
*       12-14-95  JWM   Add "#pragma once".
*       02-24-97  GJF   Detab-ed.
*       05-17-99  PML   Remove all Macintosh support.
*       10-22-99  PML   Add EHTRACE support
*       10-12-04  JL    Export EHTRACE support
*       11-18-04  ATC   SAL Annotations for CRT Headers
*       01-14-05  AC    Fix SAL annotations (using prefast espx plug-in)
*
****/



#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#ifndef _INC_EHASSERT
#define _INC_EHASSERT

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#if !defined(_MS_SUA_)
#include <windows.h>
#else /* !_MS_SUA_ */
#include <nowin.h>
#endif /* !_MS_SUA_ */

#ifdef  DEBUG

#include <stdio.h>
#include <stdlib.h>

int __cdecl dprintf( __in_z __format_string  char * _P(_Format), ... );

#ifdef  _NTSUBSET_

#define DASSERT(c)  ((c)?0: \
                      (DbgPrint("Runtime internal error (%s, line %d)", __FILE__, __LINE__),\
                      terminate()))

#define DEXPECT(c)      ((c)?0: \
                      DbgPrint("Runtime internal error suspected (%s, line %d)", __FILE__, __LINE__))

#else   /* _NTSUBSET_ */

#define DASSERT(c)  ((c)?0: \
                      (printf("Runtime internal error (%s, line %d)", __FILE__, __LINE__),\
                      terminate()))

#define DEXPECT(c)  ((c)?0: \
                      printf("Runtime internal error suspected (%s, line %d)", __FILE__, __LINE__))

#endif  /* _NTSUBSET_ */

#else

// Disable dprintf output
#define dprintf

#define DASSERT(c)  ((c)?0:_inconsistency())
#define DEXPECT(c)  (c)

#endif

#define CHECKPTR(p) (_ValidateRead((p),sizeof(typeof(*(p))))
#define CHECKCODE(p) (_ValidateExecute( (FARPROC)(p) )

_CRTIMP __checkReturn BOOL __cdecl _ValidateRead( __in_opt const void *_P(_Data), __in UINT _P(_Size) = sizeof(char) );
_CRTIMP __checkReturn BOOL __cdecl _ValidateWrite( __in_opt void *_P(_Data), UINT _P(_Size) = sizeof(char) );
_CRTIMP __checkReturn BOOL __cdecl _ValidateExecute( __in_opt FARPROC _P(_Code) );

#if     defined(ENABLE_EHTRACE) && (_MSC_VER >= 1300)

// Warning: EH tracing can only be used in a single thread because this tracing
// level global is not per-thread.
extern int __ehtrace_level;

_CRTIMP void __cdecl         EHTraceOutput(__in __format_string const char *_P(_Format), ...);
_CRTIMP const char * __cdecl EHTraceIndent(__in int _P(_Level));
_CRTIMP const char * __cdecl EHTraceFunc(__in const char *_P(_Func));
_CRTIMP void __cdecl         EHTracePushLevel(__in int _P(_New_level));
_CRTIMP void __cdecl         EHTracePopLevel(__in bool _P(_Restore));
_CRTIMP int  __cdecl         EHTraceExceptFilter(__in const char *_P(_Func), __in int _P(_Expr));
_CRTIMP void __cdecl         EHTraceHandlerReturn(__in const char *_P(_Func), __in int _P(_Level), __in EXCEPTION_DISPOSITION result);

#define EHTRACE_INIT              int __ehtrace_local_level; __ehtrace_local_level = ++__ehtrace_level
#define EHTRACE_RESET             __ehtrace_level = 0
#define EHTRACE_SAVE_LEVEL        EHTracePushLevel(__ehtrace_local_level)
#define EHTRACE_RESTORE_LEVEL(x)  EHTracePopLevel(x)
#define EHTRACE_ENTER             EHTRACE_INIT; \
                                  EHTraceOutput( "Enter: %s%s\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__) )
#define EHTRACE_ENTER_MSG(x)      EHTRACE_INIT; \
                                  EHTraceOutput( "Enter: %s%s: %s\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__), x )
#define EHTRACE_ENTER_FMT1(x,y)   EHTRACE_INIT; \
                                  EHTraceOutput( "Enter: %s%s: " x "\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__), y )
#define EHTRACE_ENTER_FMT2(x,y,z) EHTRACE_INIT; \
                                  EHTraceOutput( "Enter: %s%s: " x "\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__), y, z )
#define EHTRACE_MSG(x)            EHTraceOutput( "In   : %s%s: %s\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__), x )
#define EHTRACE_FMT1(x,y)         EHTraceOutput( "In   : %s%s: " x "\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__), y )
#define EHTRACE_FMT2(x,y,z)       EHTraceOutput( "In   : %s%s: " x "\n", EHTraceIndent(__ehtrace_local_level), EHTraceFunc(__FUNCTION__), y, z )
#define EHTRACE_EXCEPT(x)         EHTRACE_SAVE_LEVEL, EHTraceExceptFilter( __FUNCTION__, x )
#define EHTRACE_EXIT              --__ehtrace_level
#define EHTRACE_HANDLER_EXIT(x)   EHTraceHandlerReturn( __FUNCTION__, __ehtrace_local_level, x); \
                                  EHTRACE_EXIT

#else

#define EHTRACE_RESET
#define EHTRACE_SAVE_LEVEL
#define EHTRACE_RESTORE_LEVEL(x)
#define EHTRACE_ENTER
#define EHTRACE_ENTER_MSG(x)
#define EHTRACE_ENTER_FMT1(x,y)
#define EHTRACE_ENTER_FMT2(x,y,z)
#define EHTRACE_MSG(x)
#define EHTRACE_FMT1(x,y)
#define EHTRACE_FMT2(x,y,z)
#define EHTRACE_EXCEPT(x)       (x)
#define EHTRACE_EXIT
#define EHTRACE_HANDLER_EXIT(x)

#endif  /* ENABLE_EHTRACE */

#endif  /* _INC_EHASSERT */
