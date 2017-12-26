/***
*process.h - definition and declarations for process control functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines the modeflag values for spawnxx calls.
*       Also contains the function argument declarations for all
*       process control related routines.
*
*       [Public]
*
*Revision History:
*       08/24/87  JCR   Added P_NOWAITO
*       10/20/87  JCR   Removed "MSC40_ONLY" entries and "MSSDK_ONLY" comments
*       12-11-87  JCR   Added "_loadds" functionality
*       12-18-87  JCR   Added _FAR_ to declarations
*       01-11-88  JCR   Added _beginthread/_endthread
*       01-15-88  JCR   Got rid of _p_overlay for MTRHEAD/DLL
*       02-10-88  JCR   Cleaned up white space
*       05-08-88  SKS   Removed bogus comment about "DOS 4"; Added "P_DETACH"
*       08-22-88  GJF   Modified to also work for the 386 (small model only)
*       09-14-88  JCR   Added _cexit and _c_exit declarations
*       05-03-89  JCR   Added _INTERNAL_IFSTRIP for relinc usage
*       06-08-89  JCR   386 _beginthread does NOT take a stackpointer arg
*       08-01-89  GJF   Cleanup, now specific to OS/2 2.0 (i.e., 386 flat model)
*       10-30-89  GJF   Fixed copyright
*       11-02-89  JCR   Changed "DLL" to "_DLL"
*       11-17-89  GJF   Added const attribute to appropriate arg types
*       03-01-90  GJF   Added #ifndef _INC_PROCESS and #include <cruntime.h>
*                       stuff. Also, removed some (now) useless preprocessor
*                       directives.
*       03-21-90  GJF   Replaced _cdecl with _CALLTYPE1 or _CALLTYPE2 in
*                       prototypes.
*       04-10-90  GJF   Replaced remaining instances of _cdecl (with _CALLTYPE1
*                       or _VARTYPE1, as appropriate).
*       10-12-90  GJF   Changed return type of _beginthread() to unsigned long.
*       01-17-91  GJF   ANSI naming.
*       08-20-91  JCR   C++ and ANSI naming
*       08-26-91  BWM   Added prototypes for _loaddll, unloaddll, and
*                       _getdllprocaddr.
*       09-28-91  JCR   ANSI names: DOSX32=prototypes, WIN32=#defines for now
*       07-22-92  GJF   Deleted references to _wait for Win32.
*       08-05-92  GJF   Function calling type and variable type macros.
*       08-28-92  GJF   #ifdef-ed out for POSIX.
*       09-03-92  GJF   Merged two changes above.
*       01-21-93  GJF   Removed support for C6-386's _cdecl.
*       03-20-93  SKS   Remove obsolete _loaddll, unloaddll, _getdllprocaddr.
*       04-07-93  SKS   Add _CRTIMP keyword for CRT DLL model
*                       Use link-time aliases for old names, not #define's
*       10-11-93  GJF   Merged NT and Cuda versions.
*       12-06-93  CFW   Add wCRT_INIT.
*       12-07-93  CFW   Add wide exec/spawn protos.
*       02-16-94  SKS   Add _beginthreadex(), _endthreadex()
*       12-28-94  JCF   Merged with mac header
*       02-11-95  CFW   Add _CRTBLD to avoid users getting wrong headers.
*       02-13-95  CFW   Fixed Mac merge.
*       02-14-95  CFW   Clean up Mac merge.
*       05-24-95  CFW   "spawn" not a mac oldames.
*       12-14-95  JWM   Add "#pragma once".
*       02-20-97  GJF   Cleaned out obsolete support for _CRTAPI* and _NTSDK.
*                       Also, detab-ed.
*       09-30-97  JWM   Restored not-so-obsolete _CRTAPI1 support.
*       10-07-97  RDL   Added IA64.
*       02-06-98  GJF   Changes for Win64: changed return and argument types to
*                       to intptr_t and uintptr_t where appropriate.
*       02-10-98  GJF   Changes for Win64: fixed a couple of prototypes
*       05-13-99  PML   Remove _CRTAPI1
*       05-17-99  PML   Remove all Macintosh support.
*       06-05-99  PML   Win64: int -> intptr_t for !__STDC__ variants.
*       10-06-99  PML   Add _W64 modifier to types which are 32 bits in Win32,
*                       64 bits in Win64.
*       10-25-02  SJ    Fixed /clr /W4 Warnings VSWhidbey-2445
*       10-28-02  PK    Marked _loaddll, _unloaddll and _getdllprocaddr as 
*                       #pragma deprecated.
*       02-16-04  SJ    VSW#243523 - moved the lines preventing deprecation from
*                       the header to the sources.
*       04-07-04  GB    Added support for beginthread et. al. for /clr:pure.
*       11-08-04  JL    Added _CRT_NONSTDC_DEPRECATE to deprecate non-ANSI functions
*       11-18-04  ATC   SAL Annotations for CRT Headers
*       01-14-05  AC    Fix SAL annotations (using prefast espx plug-in)
*
****/

#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#ifndef _INC_PROCESS
#define _INC_PROCESS

#include <crtdefs.h>

#ifndef _POSIX_

#ifdef __cplusplus
extern "C" {
#endif

/* modeflag values for _spawnxx routines */

#define _P_WAIT         0
#define _P_NOWAIT       1
#define _OLD_P_OVERLAY  2
#define _P_NOWAITO      3
#define _P_DETACH       4

#ifdef  _MT
#define _P_OVERLAY      2
#else
extern int _p_overlay;
#define _P_OVERLAY      _p_overlay
#endif  /* _MT */

/* Action codes for _cwait(). The action code argument to _cwait is ignored
   on Win32 though it is accepted for compatibilty with old MS CRT libs */
#define _WAIT_CHILD      0
#define _WAIT_GRANDCHILD 1


/* function prototypes */

#ifdef  _MT
_CRTIMP uintptr_t __cdecl _beginthread (__in void (__cdecl * _P(_StartAddress)) (void *),
        __in unsigned _P(_StackSize), __in_opt void * _P(_ArgList));
_CRTIMP void __cdecl _endthread(void);
_CRTIMP uintptr_t __cdecl _beginthreadex(__in_opt void * _P(_Security), __in unsigned _P(_StackSize),
        __in unsigned (__stdcall * _P(_StartAddress)) (void *), __in_opt void * _P(_ArgList), 
        __in unsigned _P(_InitFlag), __in_opt unsigned * _P(_ThrdAddr));
_CRTIMP void __cdecl _endthreadex(__in unsigned _P(_Retval));

#if defined(__cplusplus) && defined(_M_CEE)
extern "C++"
{
_MCRTIMP uintptr_t __cdecl _beginthread (__in void (__clrcall * _P(_StartAddress)) (void *),
         __in unsigned _P(_StackSize), __in_opt void * _P(_ArgList));
_MCRTIMP uintptr_t __cdecl _beginthreadex(__in_opt void * _P(_Security), __in unsigned _P(_StackSize),
        __in unsigned (__clrcall * _P(_StartAddress)) (void *), __in_opt void * _P(_ArgList), 
        __in unsigned _P(_InitFlag), __out_opt unsigned * _P(_ThrdAddr));
}
#endif

#endif

#if     _MSC_VER >= 1200 /*IFSTRIP=IGN*/
_CRTIMP __declspec(noreturn) void __cdecl exit(__in int _P(_Code));
_CRTIMP __declspec(noreturn) void __cdecl _exit(__in int _P(_Code));
#else
_CRTIMP void __cdecl exit(__in int _P(_Code));
_CRTIMP void __cdecl _exit(__in int _P(_Code));
#endif
_CRTIMP void __cdecl abort(void);
_CRTIMP void __cdecl _cexit(void);
_CRTIMP void __cdecl _c_exit(void);
_CRTIMP int __cdecl _getpid(void);

_CRTIMP intptr_t __cdecl _cwait(__out_opt int * _P(_TermStat), __in intptr_t _P(_ProcHandle), __in int _P(_Action));
_CRTIMP intptr_t __cdecl _execl(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _execle(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _execlp(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _execlpe(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _execv(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _execve(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList), __in_z_opt const char * const * _P(_Env));
_CRTIMP intptr_t __cdecl _execvp(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _execvpe(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList), __in_z_opt const char * const * _P(_Env));
_CRTIMP intptr_t __cdecl _spawnl(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _spawnle(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _spawnlp(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _spawnlpe(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _spawnv(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _spawnve(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList),
        __in_z_opt const char * const * _P(_Env));
_CRTIMP intptr_t __cdecl _spawnvp(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _spawnvpe(__in int _P(_Mode), __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList),
        __in_z_opt const char * const * _P(_Env));
_CRTIMP int __cdecl system(__in_z_opt const char * _P(_Command));

#ifndef _WPROCESS_DEFINED
/* wide function prototypes, also declared in wchar.h  */
_CRTIMP intptr_t __cdecl _wexecl(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wexecle(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wexeclp(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wexeclpe(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wexecv(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _wexecve(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList),
        __in_z_opt const wchar_t * const * _P(_Env));
_CRTIMP intptr_t __cdecl _wexecvp(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _wexecvpe(__in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList), 
        __in_z_opt const wchar_t * const * _P(_Env));
_CRTIMP intptr_t __cdecl _wspawnl(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wspawnle(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wspawnlp(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wspawnlpe(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * _P(_ArgList), ...);
_CRTIMP intptr_t __cdecl _wspawnv(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _wspawnve(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList),
        __in_z_opt const wchar_t * const * _P(_Env));
_CRTIMP intptr_t __cdecl _wspawnvp(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList));
_CRTIMP intptr_t __cdecl _wspawnvpe(__in int _P(_Mode), __in_z const wchar_t * _P(_Filename), __in_z const wchar_t * const * _P(_ArgList),
        __in_z_opt const wchar_t * const * _P(_Env));
_CRTIMP int __cdecl _wsystem(__in_z_opt const wchar_t * _P(_Command));

#define _WPROCESS_DEFINED
#endif

/* --------- The following functions are OBSOLETE --------- */
/*
 * The Win32 API LoadLibrary, FreeLibrary and GetProcAddress should be used
 * instead.
 */

#if defined(_CRT_ENABLE_OBSOLETE_LOADLIBRARY_FUNCTIONS)
#define _DEPRECATED_CRT_FUNCTION
#else
#define _DEPRECATED_CRT_FUNCTION __declspec(deprecated)
#endif

_DEPRECATED_CRT_FUNCTION intptr_t __cdecl _loaddll(__in_z char * _P(_Filename));
_DEPRECATED_CRT_FUNCTION int __cdecl _unloaddll(__in intptr_t _P(_Handle));
_DEPRECATED_CRT_FUNCTION int (__cdecl * __cdecl _getdllprocaddr(__in intptr_t _P(_Handle), __in_z_opt char * _P(_ProcedureName), __in intptr_t _P(_Ordinal)))(void);

/* --------- The preceding functions are OBSOLETE --------- */


#ifdef  _DECL_DLLMAIN
/*
 * Declare DLL notification (initialization/termination) routines
 *      The preferred method is for the user to provide DllMain() which will
 *      be called automatically by the DLL entry point defined by the C run-
 *      time library code.  If the user wants to define the DLL entry point
 *      routine, the user's entry point must call _CRT_INIT on all types of
 *      notifications, as the very first thing on attach notifications and
 *      as the very last thing on detach notifications.
 */
#ifdef  _WINDOWS_       /* Use types from WINDOWS.H */
#if defined (MRTDLL)
BOOL __clrcall DllMain(__in HANDLE _P(_HDllHandle), __in DWORD _P(_Reason), __in_opt LPVOID _P(_Reserved));
#else
BOOL WINAPI DllMain(__in HANDLE _P(_HDllHandle), __in DWORD _P(_Reason), __in_opt LPVOID _P(_Reserved));
#endif
#if defined (MRTDLL)
BOOL _CRT_INIT(__in HANDLE _P(_HDllHandle), __in DWORD _P(_Reason), __in_opt LPVOID _P(_Reserved));
#else
BOOL WINAPI _CRT_INIT(__in HANDLE _P(_HDllHandle), __in DWORD _P(_Reason), __in_opt LPVOID _P(_Reserved));
#endif
BOOL WINAPI _wCRT_INIT(__in HANDLE _P(_HDllHandle), __in DWORD _P(_Reason), __in_opt LPVOID _P(_Reserved));
extern BOOL (WINAPI *_pRawDllMain)(HANDLE, DWORD, LPVOID);
#else
int __stdcall DllMain(__in void * _P(_HDllHandle), __in unsigned _P(_Reason), __in_opt void * _P(_Reserved));
int __stdcall _CRT_INIT(__in void * _P(_HDllHandle), __in unsigned _P(_Reason), __in_opt void * _P(_Reserved));
int __stdcall _wCRT_INIT(__in void * _P(_HDllHandle), __in unsigned _P(_Reason), __in_opt void * _P(_Reserved));
extern int (__stdcall *_pRawDllMain)(void *, unsigned, void *);
#endif  /* _WINDOWS_ */
#endif

#if     !__STDC__

/* Non-ANSI names for compatibility */

#define P_WAIT          _P_WAIT
#define P_NOWAIT        _P_NOWAIT
#define P_OVERLAY       _P_OVERLAY
#define OLD_P_OVERLAY   _OLD_P_OVERLAY
#define P_NOWAITO       _P_NOWAITO
#define P_DETACH        _P_DETACH
#define WAIT_CHILD      _WAIT_CHILD
#define WAIT_GRANDCHILD _WAIT_GRANDCHILD

/* current declarations */
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl cwait(__out_opt int * _P(_TermStat), __in intptr_t _P(_ProcHandle), __in int _P(_Action));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execl(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execle(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execlp(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execlpe(__in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execv(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execve(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList), __in_z_opt const char * const * _P(_Env));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execvp(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl execvpe(__in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList), __in_z_opt const char * const * _P(_Env));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnl(__in int, __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnle(__in int, __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnlp(__in int, __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnlpe(__in int, __in_z const char * _P(_Filename), __in_z const char * _P(_ArgList), ...);
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnv(__in int, __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnve(__in int, __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList),
        __in_z_opt const char * const * _P(_Env));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnvp(__in int, __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList));
_CRT_NONSTDC_DEPRECATE _CRTIMP intptr_t __cdecl spawnvpe(__in int, __in_z const char * _P(_Filename), __in_z const char * const * _P(_ArgList),
        __in_z_opt const char * const * _P(_Env));

_CRT_NONSTDC_DEPRECATE _CRTIMP int __cdecl getpid(void);

#endif  /* __STDC__ */

#ifdef  __cplusplus
}
#endif

#endif  /* _POSIX_ */

#endif  /* _INC_PROCESS */
