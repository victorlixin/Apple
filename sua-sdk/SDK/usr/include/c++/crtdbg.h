/***
*crtdbg.h - Supports debugging features of the C runtime library.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Support CRT debugging features.
*
*       [Public]
*
*Revision History:
*       08-16-94  CFW   Module created.
*       11-28-94  CFW   Add DumpClient, more params for AllocHook.
*       12-08-94  CFW   Use non-win32 names.
*       01-09-95  CFW   Dump client needs size, add _CrtSetBreakAlloc,
*                       use const state pointers.
*       01-10-95  CFW   dbgint.h merge.
*       01-20-94  CFW   Change unsigned chars to chars.
*       01-24-94  CFW   Cleanup: remove unneeded funcs, add _CrtSetDbgFlag.
*       01-24-94  CFW   _CrtDbgReport now returns 1 for debug.
*       02-11-95  CFW   Add _CRTBLD to avoid users getting wrong headers.
*       02-14-95  CFW   Clean up Mac merge.
*       02-17-95  CFW   new() proto moved from dbgint.h.
*       02-27-95  CFW   Change debug break scheme.
*       03-21-95  CFW   Add _CRT_ASSERT & _delete_client, remove tracking.
*       03-23-95  JWM   Restored tracking.
*       03-28-95  CFW   Remove tracking, export _crtBreakAlloc.
*       04-06-95  CFW   Add malloc -> _malloc_dbg macros.
*       04-10-95  CFW   Define NULL.
*       03-21-95  CFW   Remove _delete_client.
*       03-30-95  CFW   Avoid _CRTDBG_xxx conflicts with MFC.
*       05-11-95  CFW   Move C++ code to its own section.
*       05-12-95  CFW   Use _CrtIsValidPointer & _CrtIsValidHeapPointer.
*       06-08-95  CFW   Add return value parameter to report hook.
*       06-27-95  CFW   Add win32s support for debug libs.
*       07-25-95  CFW   Add win32s support for user visible debug heap variables.
*       09-01-95  GJF   Moved a proto for new up slightly to avoid compiler
*                       error C2660 (Olympus 1015).
*       09-20-95  CFW   Change _RPT0, _RPTF0 to support messages with '%' in them.
*       12-14-95  JWM   Add "#pragma once".
*       01-23-97  GJF   Cleaned out obsolete support for Win32s.
*       04-21-97  JWM   Added 4-parameter operator delete(), required by 6.0 compiler.
*       04-29-97  JWM   Made 4-parameter operator delete() #if _MSC_VER >= 1200.
*       08-14-97  GJF   Strip __p_* prototypes from release version. Also,
*                       moved the constant and type definition out of the ifdef
*                       _DEBUG so they are always defined.
*       01-19-98  JWM   At request of DeanM, made debug prototypes of new & delete
*                       #ifndef _MFC_OVERRIDES_NEW
*       05-22-98  JWM   Added support for new[] & delete[], courtesy of KFrei's RTC work.
*       06-08-98  JWM   Minor cleanups.
*       12-01-98  GJF   More choices for calling _CrtCheckMemory than never or always.
*       12-15-98  GJF   Changes for 64-bit size_t.
*       05-17-99  PML   Remove all Macintosh support.
*       08-30-99  PML   Get rid of unprintable character in comment.
*       10-06-99  PML   Add _W64 modifier to types which are 32 bits in Win32,
*                       64 bits in Win64.
*       11-02-99  PML   Add extern "C++" around C++ definitions.
*       11-08-99  PML   Don't mark debug operator new _CRTIMP (vs7#16060).
*       11-16-99  PML   Forward-decl _CrtMemBlockHeader to work around vs7#63059
*       01-04-00  GB    Added support for debug version for _aligned routines
*       02-25-00  PML   _CrtDbgBreak should use __debugbreak if available.
*       05-31-00  PML   Add _CrtReportBlockType (VS7#55049).
*       09-26-00  PML   Fix _ASSERT*, _RPT* to compile /W4 clean (vs7#166894)
*       12-10-00  PML   Non-_DEBUG macro versions of _CrtSet* should not be
*                       typed as void (vs7#166572).
*       03-21-01  PML   Add _CrtSetReportHook2 (vs7#124998)
*       07-15-01  PML   Remove all ALPHA, MIPS, and PPC code
*       05-29-02  MSL   Allow _ASSERT, _ASSERTE to be overridden
*       02-04-03  EAN   Added _STATIC_ASSERT
*       08-28-03  SJ    Added _wassert, CrtSetReportHookW2,CrtDbgReportW, 
*                       & other helper functions. VSWhidbey#55308
*       12-12-03  SJ    Removed the temporary switch provided to revert to 
*                       the old ANSI Assert Behaviour VSW#172434
*       01-13-04  AC    Added _alloca_s and _freea_s
*       03-08-04  MSL   Added define of NULL in this file for back-compat
*                       VSW# 248613
*       04-07-04  MSL   CLR overloads for callbacks
*                       VSW# 242826
*                       VSW# 242827
*       07-20-04  AC    Moved _CRT_WIDE to crtdefs.h
*       09-08-04  AC    Removed bogus pragma warning 4507
*                       VSW#354837
*       09-24-04  MSL   Hook changes for mixed and pure, plus _ASSERT_EXPR
*       10-12-04  JL    Make _CrtDoForAllClientObjects work for mixed and pure
*       10-14-04  ESC   Protect against -Zp with pragma pack
*       11-04-04  JL    Make operator new and delete as a part of pure CRT
*       11-05-04  AGH   Call _Crt[S|G]etReportHook[W][2] from msvcm80d under 
*                       /clr:pure
*       11-07-04  MSL   Return native types from NULL set overloads
*       11-18-04  ATC   SAL Annotations for CRT Headers
*       12-21-04  AC    Added _CrtSetDebugFillThreshold
*                       VSW#425584
*       01-14-05  AC    Fix SAL annotations (using prefast espx plug-in)
*       02-02-05  AC    Added SAL annotation to operator new
*                       VSW#449209
*       02-02-05  AC    Added _malloca and _freea
*                       VSW#416634
*
****/

#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#include <crtdefs.h>

#ifndef _INC_CRTDBG
#define _INC_CRTDBG

#ifdef  _MSC_VER
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

/* Define NULL here since we depend on it and for back-compat
*/
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifdef  __cplusplus
extern "C" {
#endif  /* __cplusplus */

 /****************************************************************************
 *
 * Debug Reporting
 *
 ***************************************************************************/

typedef void *_HFILE; /* file handle pointer */

#define _CRT_WARN           0
#define _CRT_ERROR          1
#define _CRT_ASSERT         2
#define _CRT_ERRCNT         3

#define _CRTDBG_MODE_FILE      0x1
#define _CRTDBG_MODE_DEBUG     0x2
#define _CRTDBG_MODE_WNDW      0x4
#define _CRTDBG_REPORT_MODE    -1

#define _CRTDBG_INVALID_HFILE ((_HFILE)-1)
#define _CRTDBG_HFILE_ERROR   ((_HFILE)-2)
#define _CRTDBG_FILE_STDOUT   ((_HFILE)-4)
#define _CRTDBG_FILE_STDERR   ((_HFILE)-5)
#define _CRTDBG_REPORT_FILE   ((_HFILE)-6)

#if !defined(_M_CEE_PURE)
typedef int (__cdecl * _CRT_REPORT_HOOK)(int, char *, int *);
typedef int (__cdecl * _CRT_REPORT_HOOKW)(int, wchar_t *, int *);
#else
typedef int (__clrcall * _CRT_REPORT_HOOK)(int, char *, int *);
typedef int (__clrcall * _CRT_REPORT_HOOKW)(int, wchar_t *, int *);
#endif

#if defined(_M_CEE) 
typedef int (__clrcall *_CRT_REPORT_HOOK_M)(int, char *, int *);
typedef int (__clrcall *_CRT_REPORT_HOOKW_M)(int, wchar_t *, int *);
#endif

#define _CRT_RPTHOOK_INSTALL  0
#define _CRT_RPTHOOK_REMOVE   1

 /****************************************************************************
 *
 * Heap
 *
 ***************************************************************************/

 /****************************************************************************
 *
 * Client-defined allocation hook
 *
 ***************************************************************************/

#define _HOOK_ALLOC     1
#define _HOOK_REALLOC   2
#define _HOOK_FREE      3

#if !defined(_M_CEE_PURE)
typedef int (__cdecl * _CRT_ALLOC_HOOK)(int, void *, size_t, int, long, const unsigned char *, int);
#else
typedef int (__clrcall * _CRT_ALLOC_HOOK)(int, void *, size_t, int, long, const unsigned char *, int);
#endif
#if defined(_M_CEE) 
typedef int (__clrcall * _CRT_ALLOC_HOOK_M)(int, void *, size_t, int, long, const unsigned char *, int);
#endif

 /****************************************************************************
 *
 * Memory management
 *
 ***************************************************************************/

/*
 * Bit values for _crtDbgFlag flag:
 *
 * These bitflags control debug heap behavior.
 */

#define _CRTDBG_ALLOC_MEM_DF        0x01  /* Turn on debug allocation */
#define _CRTDBG_DELAY_FREE_MEM_DF   0x02  /* Don't actually free memory */
#define _CRTDBG_CHECK_ALWAYS_DF     0x04  /* Check heap every alloc/dealloc */
#define _CRTDBG_RESERVED_DF         0x08  /* Reserved - do not use */
#define _CRTDBG_CHECK_CRT_DF        0x10  /* Leak check/diff CRT blocks */
#define _CRTDBG_LEAK_CHECK_DF       0x20  /* Leak check at program exit */

/*
 * Some bit values for _crtDbgFlag which correspond to frequencies for checking
 * the the heap.
 */
#define _CRTDBG_CHECK_EVERY_16_DF   0x00100000  /* check heap every 16 heap ops */
#define _CRTDBG_CHECK_EVERY_128_DF  0x00800000  /* check heap every 128 heap ops */
#define _CRTDBG_CHECK_EVERY_1024_DF 0x04000000  /* check heap every 1024 heap ops */
/*
We do not check the heap by default at this point because the cost was too high
for some applications. You can still turn this feature on manually.
*/
#define _CRTDBG_CHECK_DEFAULT_DF    0           

#define _CRTDBG_REPORT_FLAG         -1    /* Query bitflag status */

#define _BLOCK_TYPE(block)          (block & 0xFFFF)
#define _BLOCK_SUBTYPE(block)       (block >> 16 & 0xFFFF)


 /****************************************************************************
 *
 * Memory state
 *
 ***************************************************************************/

/* Memory block identification */
#define _FREE_BLOCK      0
#define _NORMAL_BLOCK    1
#define _CRT_BLOCK       2
#define _IGNORE_BLOCK    3
#define _CLIENT_BLOCK    4
#define _MAX_BLOCKS      5

#if !defined(_M_CEE_PURE)
typedef void (__cdecl * _CRT_DUMP_CLIENT)(void *, size_t);
#else
typedef void (__clrcall * _CRT_DUMP_CLIENT)(void *, size_t);
#endif
#if defined(_M_CEE)
typedef void (__clrcall * _CRT_DUMP_CLIENT_M)(void *, size_t);
#endif

struct _CrtMemBlockHeader;
typedef struct _CrtMemState
{
        struct _CrtMemBlockHeader * pBlockHeader;
        size_t lCounts[_MAX_BLOCKS];
        size_t lSizes[_MAX_BLOCKS];
        size_t lHighWaterCount;
        size_t lTotalCount;
} _CrtMemState;


 /****************************************************************************
 *
 * Declarations, prototype and function-like macros
 *
 ***************************************************************************/

/* _STATIC_ASSERT is for enforcing boolean/integral conditions at compile time.
   Since it is purely a compile-time mechanism that generates no code, the check
   is left in even if _DEBUG is not defined. */

#ifndef _STATIC_ASSERT
#define _STATIC_ASSERT(expr) typedef char __static_assert_t[ (expr) ]
#endif

#ifndef _DEBUG

 /****************************************************************************
 *
 * Debug OFF
 * Debug OFF
 * Debug OFF
 *
 ***************************************************************************/

/*  We allow our basic _ASSERT macros to be overridden by pre-existing definitions. 
    This is not the ideal mechanism, but is helpful in some scenarios and helps avoid
    multiple definition problems */

#ifndef _ASSERT
#define _ASSERT(expr) ((void)0)
#endif 

#ifndef _ASSERTE
#define _ASSERTE(expr) ((void)0)
#endif

#ifndef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, expr_str) ((void)0)
#endif

#define _RPT0(rptno, msg)
#define _RPTW0(rptno, msg)

#define _RPT1(rptno, msg, arg1)
#define _RPTW1(rptno, msg, arg1)

#define _RPT2(rptno, msg, arg1, arg2)
#define _RPTW2(rptno, msg, arg1, arg2)

#define _RPT3(rptno, msg, arg1, arg2, arg3)
#define _RPTW3(rptno, msg, arg1, arg2, arg3)

#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4)
#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4)


#define _RPTF0(rptno, msg)
#define _RPTFW0(rptno, msg)

#define _RPTF1(rptno, msg, arg1)
#define _RPTFW1(rptno, msg, arg1)

#define _RPTF2(rptno, msg, arg1, arg2)
#define _RPTFW2(rptno, msg, arg1, arg2)

#define _RPTF3(rptno, msg, arg1, arg2, arg3)
#define _RPTFW3(rptno, msg, arg1, arg2, arg3)

#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4)
#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4)

#define _malloc_dbg(s, t, f, l)         malloc(s)
#define _calloc_dbg(c, s, t, f, l)      calloc(c, s)
#define _realloc_dbg(p, s, t, f, l)     realloc(p, s)
#define _expand_dbg(p, s, t, f, l)      _expand(p, s)
#define _free_dbg(p, t)                 free(p)
#define _msize_dbg(p, t)                _msize(p)

#define _aligned_malloc_dbg(s, a, f, l)     _aligned_malloc(s, a)
#define _aligned_realloc_dbg(p, s, a, f, l) _aligned_realloc(p, s, a)
#define _aligned_free_dbg(p)                _aligned_free(p)
#define _aligned_offset_malloc_dbg(s, a, o, f, l)       _aligned_offset_malloc(s, a, o)
#define _aligned_offset_realloc_dbg(p, s, a, o, f, l)   _aligned_offset_realloc(p, s, a, o)

#define _alloca_s_dbg(s, t, f, l)       _alloca_s(s)
#define _freea_s_dbg(p, t)              _freea_s(p)
#define _malloca_dbg(s, t, f, l)        _malloca(s)
#define _freea_dbg(p, t)                _freea(p)

#define _strdup_dbg(s, t, f, l)         _strdup(s)
#define _wcsdup_dbg(s, t, f, l)         _wcsdup(s)
#define _mbsdup_dbg(s, t, f, l)         _mbsdup(s)
#define _tempnam_dbg(s1, s2, t, f, l)   _tempnam(s1, s2)
#define _wtempnam_dbg(s1, s2, t, f, l)  _wtempnam(s1, s2)
#define _fullpath_dbg(s1, s2, le, t, f, l)  _fullpath(s1, s2, le)
#define _wfullpath_dbg(s1, s2, le, t, f, l) _wfullpath(s1, s2, le)
#define _getcwd_dbg(s, le, t, f, l)     _getcwd(s, le)
#define _wgetcwd_dbg(s, le, t, f, l)    _wgetcwd(s, le)
#define _getdcwd_dbg(d, s, le, t, f, l)     _getdcwd(d, s, le)
#define _wgetdcwd_dbg(d, s, le, t, f, l)    _wgetdcwd(d, s, le)
#define _getdcwd_lk_dbg(d, s, le, t, f, l)  _getdcwd_nolock(d, s, le)
#define _wgetdcwd_lk_dbg(d, s, le, t, f, l) _wgetdcwd_nolock(d, s, le)
#define _dupenv_s_dbg(ps1, size, s2, t, f, l)  _dupenv_s(ps1, size, s2)
#define _wdupenv_s_dbg(ps1, size, s2, t, f, l) _wdupenv_s(ps1, size, s2)

#define _CrtSetReportHook(f)                ((_CRT_REPORT_HOOK)0)
#define _CrtGetReportHook()                 ((_CRT_REPORT_HOOK)0)
#define _CrtSetReportHook2(t, f)            ((int)0)
#define _CrtSetReportHookW2(t, f)           ((int)0)
#define _CrtSetReportMode(t, f)             ((int)0)
#define _CrtSetReportFile(t, f)             ((_HFILE)0)

#define _CrtDbgBreak()                      ((void)0)

#define _CrtSetBreakAlloc(a)                ((long)0)

#define _CrtSetAllocHook(f)                 ((_CRT_ALLOC_HOOK)0)
#define _CrtGetAllocHook()                  ((_CRT_ALLOC_HOOK)0)

#define _CrtCheckMemory()                   ((int)1)
#define _CrtSetDbgFlag(f)                   ((int)0)
#define _CrtDoForAllClientObjects(f, c)     ((void)0)
#define _CrtIsValidPointer(p, n, r)         ((int)1)
#define _CrtIsValidHeapPointer(p)           ((int)1)
#define _CrtIsMemoryBlock(p, t, r, f, l)    ((int)1)
#define _CrtReportBlockType(p)              ((int)-1)

#define _CrtSetDumpClient(f)                ((_CRT_DUMP_CLIENT)0)
#define _CrtGetDumpClient()                 ((_CRT_DUMP_CLIENT)0)

#define _CrtMemCheckpoint(s)                ((void)0)
#define _CrtMemDifference(s1, s2, s3)       ((int)0)
#define _CrtMemDumpAllObjectsSince(s)       ((void)0)
#define _CrtMemDumpStatistics(s)            ((void)0)
#define _CrtDumpMemoryLeaks()               ((int)0)
#define _CrtSetDebugFillThreshold(t)        ((size_t)0)

#else   /* _DEBUG */


 /****************************************************************************
 *
 * Debug ON
 * Debug ON
 * Debug ON
 *
 ***************************************************************************/


/* Define _MRTIMP */

#ifndef _MRTIMP
#ifdef MRTDLL
#define _MRTIMP __declspec(dllexport)
#else   /* ndef MRTDLL */
#define _MRTIMP __declspec(dllimport)
#endif  /* MRTDLL */
#endif  /* _MRTIMP */

/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef  CRTDLL
#define _CRTIMP __declspec(dllexport)
#else   /* ndef CRTDLL */
#ifdef  _DLL
#define _CRTIMP __declspec(dllimport)
#else   /* ndef _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP */

 /****************************************************************************
 *
 * Debug Reporting
 *
 ***************************************************************************/

#ifndef _INTERNAL_IFSTRIP_
#if     defined(_DLL) && defined(_M_IX86)
/* Retained for compatibility with VC++ 5.0 and earlier versions */
_CRTIMP long * __cdecl __p__crtAssertBusy(void);
#endif
#endif  /* _INTERNAL_IFSTRIP_ */
#if !defined(_M_CEE_PURE)
_CRTIMP extern long _crtAssertBusy;
#endif /* !defined(_M_CEE_PURE) */

#if !defined(_M_CEE_PURE)
_CRTIMP _CRT_REPORT_HOOK __cdecl _CrtSetReportHook
(
    __in_opt _CRT_REPORT_HOOK _P(_PFnNewHook)
);

_CRTIMP _CRT_REPORT_HOOK __cdecl _CrtGetReportHook
(
    void
);

_CRTIMP int __cdecl _CrtSetReportHook2(
        __in int _P(_Mode),
        __in_opt _CRT_REPORT_HOOK _P(_PFnNewHook)
        );

_CRTIMP int __cdecl _CrtSetReportHookW2(
        __in int _P(_Mode),
        __in_opt _CRT_REPORT_HOOKW _P(_PFnNewHook)
        );
#endif

_CRTIMP int __cdecl _CrtSetReportMode(
        __in int _P(_ReportType),
        __in_opt int _P(_ReportMode) 
        );

_CRTIMP _HFILE __cdecl _CrtSetReportFile(
        __in int _P(_ReportType),
        __in_opt _HFILE _P(_ReportFile) 
        );

_CRTIMP int __cdecl _CrtDbgReport(
        __in int _P(_ReportType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_Linenumber),
        __in_z_opt const char * _P(_ModuleName),
        __in_z_opt const char * _P(_Format),
        ...);

_CRTIMP size_t __cdecl _CrtSetDebugFillThreshold(
        __in size_t _P(_NewDebugFillThreshold)
        );

#if !defined(_NATIVE_WCHAR_T_DEFINED) && defined(_M_CEE_PURE)
extern "C++"
#endif
_CRTIMP int __cdecl _CrtDbgReportW(
        __in int _P(_ReportType),
        __in_z_opt const wchar_t * _P(_Filename),
        __in int _P(_LineNumber),
        __in_z_opt const wchar_t * _P(_ModuleName),
        __in_z_opt const wchar_t * _P(_Format),
        ...);

#if defined(_M_CEE)
extern "C++"
{
_MRTIMP _CRT_REPORT_HOOK_M __cdecl _CrtSetReportHook(
        __in_opt _CRT_REPORT_HOOK_M _P(_PFnNewHook)
        );

/* 
This overload allows NULL to be passed unambiguously in the mixed case
*/
_MRTIMP _CRT_REPORT_HOOK __cdecl _CrtSetReportHook(
        __in int _P(_PFnNewHook)
        );

_MRTIMP int __cdecl _CrtSetReportHook2(
        __in int _P(_Mode),
        __in_opt _CRT_REPORT_HOOK_M _P(_PFnNewHook)
        );


_MRTIMP int __cdecl _CrtSetReportHookW2(
        __in int _P(_Mode),
        __in_opt _CRT_REPORT_HOOKW_M _P(_PFnNewHook)
        );
}
#endif

/* Asserts */

#if     _MSC_VER >= 1300 || !defined(_M_IX86) || defined(_CRT_PORTABLE) /*IFSTRIP=IGN*/
#define _ASSERT_EXPR(expr, msg) \
        (void) ((expr) || \
                (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
                (_CrtDbgBreak(), 0))
#else
#define _ASSERT_EXPR(expr, msg) \
        do { if (!(expr) && \
                (1 == _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg))) \
             _CrtDbgBreak(); } while (0)
#endif

#ifndef _ASSERT
#define _ASSERT(expr)   _ASSERT_EXPR((expr), NULL)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr)  _ASSERT_EXPR((expr), _CRT_WIDE(#expr))
#endif

/* Reports with no file/line info */

#if     _MSC_VER >= 1300 || !defined(_M_IX86) || defined(_CRT_PORTABLE) /*IFSTRIP=IGN*/
#define _RPT_BASE(args) \
        (void) ((1 != _CrtDbgReport args) || \
                (_CrtDbgBreak(), 0))

#define _RPT_BASE_W(args) \
        (void) ((1 != _CrtDbgReportW args) || \
                (_CrtDbgBreak(), 0))
#else
#define _RPT_BASE(args) \
        do { if ((1 == _CrtDbgReport args)) \
                _CrtDbgBreak(); } while (0)

#define _RPT_BASE_W(args) \
        do { if ((1 == _CrtDbgReportW args)) \
                _CrtDbgBreak(); } while (0)
#endif

#define _RPT0(rptno, msg) \
        _RPT_BASE((rptno, NULL, 0, NULL, "%s", msg))

#define _RPTW0(rptno, msg) \
        _RPT_BASE_W((rptno, NULL, 0, NULL, L"%s", msg))

#define _RPT1(rptno, msg, arg1) \
        _RPT_BASE((rptno, NULL, 0, NULL, msg, arg1))

#define _RPTW1(rptno, msg, arg1) \
        _RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1))

#define _RPT2(rptno, msg, arg1, arg2) \
        _RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2))

#define _RPTW2(rptno, msg, arg1, arg2) \
        _RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2))

#define _RPT3(rptno, msg, arg1, arg2, arg3) \
        _RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3))

#define _RPTW3(rptno, msg, arg1, arg2, arg3) \
        _RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3))

#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4) \
        _RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4))

#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4) \
        _RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4))

/* Reports with file/line info */

#define _RPTF0(rptno, msg) \
        _RPT_BASE((rptno, __FILE__, __LINE__, NULL, "%s", msg))

#define _RPTFW0(rptno, msg) \
        _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, L"%s", msg))

#define _RPTF1(rptno, msg, arg1) \
        _RPT_BASE((rptno, __FILE__, __LINE__, NULL, msg, arg1))

#define _RPTFW1(rptno, msg, arg1) \
        _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1))

#define _RPTF2(rptno, msg, arg1, arg2) \
        _RPT_BASE((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2))

#define _RPTFW2(rptno, msg, arg1, arg2) \
        _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2))

#define _RPTF3(rptno, msg, arg1, arg2, arg3) \
        _RPT_BASE((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2, arg3))

#define _RPTFW3(rptno, msg, arg1, arg2, arg3) \
        _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2, arg3))

#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4) \
        _RPT_BASE((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2, arg3, arg4))

#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4) \
        _RPT_BASE_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2, arg3, arg4))

#if     _MSC_VER >= 1300 && !defined(_CRT_PORTABLE) /*IFSTRIP=IGN*/
#define _CrtDbgBreak() __debugbreak()
#elif   defined(_M_IX86) && !defined(_CRT_PORTABLE)
#define _CrtDbgBreak() __asm { int 3 }
#elif   defined(_M_IA64) && !defined(_CRT_PORTABLE)
void __break(int);
#pragma intrinsic (__break)
#define _CrtDbgBreak() __break(0x80016)
#else
_CRTIMP void __cdecl _CrtDbgBreak(
        void
        );
#endif

 /****************************************************************************
 *
 * Heap routines
 *
 ***************************************************************************/

#ifdef  _CRTDBG_MAP_ALLOC

#define   malloc(s)         _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)      _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)     _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)     _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   free(p)           _free_dbg(p, _NORMAL_BLOCK)
#define   _msize(p)         _msize_dbg(p, _NORMAL_BLOCK)
#define   _aligned_malloc(s, a)                 _aligned_malloc_dbg(s, a, __FILE__, __LINE__)
#define   _aligned_realloc(p, s, a)             _aligned_realloc_dbg(p, s, a, __FILE__, __LINE__)
#define   _aligned_offset_malloc(s, a, o)       _aligned_offset_malloc_dbg(s, a, o, __FILE__, __LINE__)
#define   _aligned_offset_realloc(p, s, a, o)   _aligned_offset_realloc_dbg(p, s, a, o, __FILE__, __LINE__)
#define   _aligned_free(p)  _aligned_free_dbg(p)

#define   _alloca_s(s)       _alloca_s_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _freea_s(p)        _freea_s_dbg(p, _NORMAL_BLOCK)
#define   _malloca(s)        _malloca_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _freea(p)          _freea_dbg(p, _NORMAL_BLOCK)

#define   _strdup(s)         _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wcsdup(s)         _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _mbsdup(s)         _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _tempnam(s1, s2)   _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wtempnam(s1, s2)  _wtempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _fullpath(s1, s2, le)     _fullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wfullpath(s1, s2, le)    _wfullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _getcwd(s, le)      _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wgetcwd(s, le)     _wgetcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _getdcwd(d, s, le)  _getdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wgetdcwd(d, s, le) _wgetdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _getdcwd_nolock(d, s, le)     _getdcwd_lk_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wgetdcwd_nolock(d, s, le)    _wgetdcwd_lk_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _dupenv_s(ps1, size, s2)      _dupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _wdupenv_s(ps1, size, s2)     _wdupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)

#if     !__STDC__
#define   strdup(s)          _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   wcsdup(s)          _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   tempnam(s1, s2)    _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   getcwd(s, le)      _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#endif  /* _CRTDBG_MAP_ALLOC */

#ifndef _INTERNAL_IFSTRIP_
#if     defined(_DLL) && defined(_M_IX86)
/* Retained for compatibility with VC++ 5.0 and earlier versions */
_CRTIMP long * __cdecl __p__crtBreakAlloc(void);
#endif
#endif  /* _INTERNAL_IFSTRIP_ */
#if !defined(_M_CEE_PURE)
_CRTIMP extern long _crtBreakAlloc;      /* Break on this allocation */
#endif /* !defined(_M_CEE_PURE) */

_CRTIMP long __cdecl _CrtSetBreakAlloc(
        __in long _P(_BreakAlloc) 
        );

/*
 * Prototypes for malloc, free, realloc, etc are in malloc.h
 */

_CRTIMP __checkReturn __bcount_opt(_Size) void * __cdecl _malloc_dbg(
        __in size_t _P(_Size),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __bcount_opt(_NumOfElements*_SizeOfElements) void * __cdecl _calloc_dbg(
        __in size_t _P(_NumOfElements),
        __in size_t _P(_SizeOfElements),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __bcount_opt(_NewSize) void * __cdecl _realloc_dbg(
        __inout_opt void * _P(_Memory),
        __in size_t _P(_NewSize),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __bcount_opt(_NewSize) void * __cdecl _expand_dbg(
        __inout_opt void * _P(_Memory),
        __in size_t _P(_NewSize),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP void __cdecl _free_dbg(
        __inout_opt void * _P(_Memory),
        __in int _P(_BlockType)
        );

_CRTIMP size_t __cdecl _msize_dbg (
        __in void * _P(_Memory),
        __in int _P(_BlockType)
        );

_CRTIMP __checkReturn __bcount_opt(_Size) void * __cdecl _aligned_malloc_dbg(
        __in size_t _P(_Size),
        __in size_t _P(_Alignment),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __bcount_opt(_Size) void * __cdecl _aligned_realloc_dbg(
        __inout_opt void * _P(_Memory),
        __in size_t _P(_Size),
        __in size_t _P(_Alignment),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __bcount_opt(_Size) void * __cdecl _aligned_offset_malloc_dbg(
        __in size_t _P(_Size),
        __in size_t _P(_Alignment),
        __in size_t _P(_Offset),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __bcount_opt(_Size) void * __cdecl _aligned_offset_realloc_dbg(
        __inout_opt void * _P(_Memory),
        __in size_t _P(_Size),
        __in size_t _P(_Alignment),
        __in size_t _P(_Offset),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP void __cdecl _aligned_free_dbg(
        __inout_opt void * _P(_Memory)
        );

_CRTIMP __checkReturn __out_z_opt char * __cdecl _strdup_dbg(
        __in_z_opt const char * _P(_Str),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wcsdup_dbg(
        __in_z_opt const wchar_t * _P(_Str),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt char * __cdecl _tempnam_dbg(
        __in_z_opt const char * _P(_DirName),
        __in_z_opt const char * _P(_FilePrefix),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wtempnam_dbg(
        __in_z_opt const wchar_t * _P(_DirName),
        __in_z_opt const wchar_t * _P(_FilePrefix),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt char * __cdecl _fullpath_dbg(
        __out_ecount_z_opt(_SizeInBytes) char * _P(_FullPath), 
        __in_z const char * _P(_Path), 
        __in size_t _P(_SizeInBytes),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wfullpath_dbg(
        __out_ecount_z_opt(_SizeInWords) wchar_t * _P(_FullPath), 
        __in_z const wchar_t * _P(_Path), 
        __in size_t _P(_SizeInWords),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt char * __cdecl _getcwd_dbg(
        __out_ecount_z_opt(_SizeInBytes) char * _P(_DstBuf),
        __in int _P(_SizeInBytes),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wgetcwd_dbg(
        __out_ecount_z_opt(_SizeInWords) wchar_t * _P(_DstBuf),
        __in int _P(_SizeInWords),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt char * __cdecl _getdcwd_dbg(
        __in int _P(_Drive),
        __out_ecount_z_opt(_SizeInBytes) char * _P(_DstBuf),
        __in int _P(_SizeInBytes),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wgetdcwd_dbg(
        __in int _P(_Drive),
        __out_ecount_z_opt(_SizeInWords) wchar_t * _P(_DstBuf),
        __in int _P(_SizeInWords),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

__checkReturn __out_z_opt char * __cdecl _getdcwd_lk_dbg(
        __in int _P(_Drive),
        __out_ecount_z_opt(_SizeInBytes) char * _P(_DstBuf),
        __in int _P(_SizeInBytes),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

__checkReturn __out_z_opt wchar_t * __cdecl _wgetdcwd_lk_dbg(
        __in int _P(_Drive),
        __out_ecount_z_opt(_SizeInWords) wchar_t * _P(_DstBuf),
        __in int _P(_SizeInWords),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn_wat errno_t __cdecl _dupenv_s_dbg(
        __deref_out_ecount_z_opt(*_PBufferSizeInBytes) char ** _P(_PBuffer),
        __out_opt size_t * _P(_PBufferSizeInBytes),
        __in_z const char * _P(_VarName),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

_CRTIMP __checkReturn_wat errno_t __cdecl _wdupenv_s_dbg(
        __deref_out_ecount_z_opt(*_PBufferSizeInWords) wchar_t ** _P(_PBuffer),
        __out_opt size_t * _P(_PBufferSizeInWords),
        __in_z const wchar_t * _P(_VarName),
        __in int _P(_BlockType),
        __in_z_opt const char * _P(_Filename),
        __in int _P(_LineNumber)
        );

#define _alloca_s_dbg(s, t, f, l)   _malloc_dbg(s, t, f, l)
#define _freea_s_dbg(p, t)          _free_dbg(p, t)
#define _malloca_dbg(s, t, f, l)    _malloc_dbg(s, t, f, l)
#define _freea_dbg(p, t)            _free_dbg(p, t)

 /****************************************************************************
 *
 * Client-defined allocation hook
 *
 ***************************************************************************/

#if !defined(_M_CEE_PURE)
_CRTIMP _CRT_ALLOC_HOOK __cdecl _CrtSetAllocHook
(
    __in_opt _CRT_ALLOC_HOOK _P(_PfnNewHook)
);

_CRTIMP _CRT_ALLOC_HOOK __cdecl _CrtGetAllocHook
(
    void
);
#endif

#if defined (_M_CEE)
/* If we have both versions, then we need an int overload to disambiguate for the NULL case */
extern "C++" 
{
_MRTIMP _CRT_ALLOC_HOOK __cdecl _CrtSetAllocHook
(
    __in int _P(_PfnNewHook)
);
}

extern "C++"
{
_MRTIMP _CRT_ALLOC_HOOK_M __cdecl _CrtSetAllocHook
(
    __in_opt _CRT_ALLOC_HOOK_M _P(_PfnNewHook) 
);
}
#endif


 /****************************************************************************
 *
 * Memory management
 *
 ***************************************************************************/

/*
 * Bitfield flag that controls CRT heap behavior
 * Default setting is _CRTDBG_ALLOC_MEM_DF
 */

#ifndef _INTERNAL_IFSTRIP_
#if     defined(_DLL) && defined(_M_IX86)
/* Retained for compatibility with VC++ 5.0 and earlier versions */
_CRTIMP int * __cdecl __p__crtDbgFlag(void);
#endif
#endif  /* _INTERNAL_IFSTRIP_ */
#if !defined(_M_CEE_PURE)
_CRTIMP extern int _crtDbgFlag;
#endif /* !defined(_M_CEE_PURE) */

_CRTIMP int __cdecl _CrtCheckMemory(
        void
        );

_CRTIMP int __cdecl _CrtSetDbgFlag(
        __in int _P(_NewFlag)
        );

_CRTIMP void __cdecl _CrtDoForAllClientObjects(
        __in void (__cdecl *_P(_PFn))(void *, void *),
        void * _P(_Context)
        );

#if defined(_M_CEE)
extern "C++"
{
_MRTIMP void __cdecl _CrtDoForAllClientObjects(
        __in void (__clrcall * _P(_PFn))(void *, void *),
        void * _P(_Context)
        );
}
#endif

_CRTIMP __checkReturn int __cdecl _CrtIsValidPointer(
        __in_opt const void * _P(_Ptr),
        __in unsigned int _P(_Bytes),
        __in int _P(_ReadWrite)
        );

_CRTIMP __checkReturn int __cdecl _CrtIsValidHeapPointer(
        __in_opt const void * _P(_HeapPtr)
        );

_CRTIMP int __cdecl _CrtIsMemoryBlock(
        __in_opt const void * _P(_Memory),
        __in unsigned int _P(_Bytes),
        __out_opt long * _P(_RequestNumber),
        __out_opt char ** _P(_Filename),
        __out_opt int * _P(_LineNumber)
        );

_CRTIMP __checkReturn int __cdecl _CrtReportBlockType(
        __in_opt const void * _P(_Memory)
        );


 /****************************************************************************
 *
 * Memory state
 *
 ***************************************************************************/

#if !defined(_M_CEE_PURE)
_CRTIMP _CRT_DUMP_CLIENT __cdecl _CrtSetDumpClient
(
    __in_opt _CRT_DUMP_CLIENT _P(_PFnNewDump)
);

_CRTIMP _CRT_DUMP_CLIENT __cdecl _CrtGetDumpClient
(
    void
);
#endif

#if defined (_M_CEE)
/* If we have both versions, then we need an int overload to disambiguate for the NULL case */
extern "C++" 
{
_MRTIMP _CRT_DUMP_CLIENT __cdecl _CrtSetDumpClient
(
    __in_opt int _P(_PFnNewDump)
);
}

extern "C++" 
{
_MRTIMP _CRT_DUMP_CLIENT_M __cdecl _CrtSetDumpClient
(
    __in_opt _CRT_DUMP_CLIENT_M _P(_PFnNewDump)
);
}
#endif

_CRTIMP void __cdecl _CrtMemCheckpoint(
        __out _CrtMemState * _P(_State)
        );

_CRTIMP int __cdecl _CrtMemDifference(
        __out _CrtMemState * _P(_State),
        __in const _CrtMemState * _P(_OldState),
        __in const _CrtMemState * _P(_NewState)
        );

_CRTIMP void __cdecl _CrtMemDumpAllObjectsSince(
        __in_opt const _CrtMemState * _P(_State)
        );

_CRTIMP void __cdecl _CrtMemDumpStatistics(
        __in const _CrtMemState * _P(_State)
        );

_CRTIMP int __cdecl _CrtDumpMemoryLeaks(
        void
        );

#endif  /* _DEBUG */

#ifdef  __cplusplus
}

#ifndef _MFC_OVERRIDES_NEW

extern "C++" {

#ifndef _DEBUG

 /****************************************************************************
 *
 * Debug OFF
 * Debug OFF
 * Debug OFF
 *
 ***************************************************************************/

 
__bcount_opt(_Size) void * __CRTDECL operator new[](size_t _Size);

#if !defined(_M_CEE_PURE)
inline __bcount_opt(_Size) void * __CRTDECL operator new(size_t _Size, int, const char *, int)
        { return ::operator new(_Size); }

inline __bcount_opt(_Size) void* __CRTDECL operator new[](size_t _Size, int, const char *, int)
        { return ::operator new[](_Size); }

#if     _MSC_VER >= 1200 /*IFSTRIP=IGN*/


void __CRTDECL operator delete[](void *);

inline void __CRTDECL operator delete(void * _P, int, const char *, int)
        { ::operator delete(_P); }
inline void __CRTDECL operator delete[](void * _P, int, const char *, int)
        { ::operator delete[](_P); }
#endif
#endif
#else /* _DEBUG */

 /****************************************************************************
 *
 * Debug ON
 * Debug ON
 * Debug ON
 *
 ***************************************************************************/
 
__bcount_opt(_Size) void * __CRTDECL operator new[](size_t _Size);

__bcount_opt(_Size) void * __CRTDECL operator new(
        size_t _Size,
        int,
        const char *,
        int
        );

__bcount_opt(_Size) void * __CRTDECL operator new[](
        size_t _Size,
        int,
        const char *,
        int
        );

#if     _MSC_VER >= 1200 /*IFSTRIP=IGN*/
void __CRTDECL operator delete[](void *);

inline void __CRTDECL operator delete(void * _P, int, const char *, int)
        { ::operator delete(_P); }

inline void __CRTDECL operator delete[](void * _P, int, const char *, int)
        { ::operator delete[](_P); }
#endif

#ifdef _CRTDBG_MAP_ALLOC

inline __bcount_opt(_Size) void * __CRTDECL operator new(size_t _Size)
        { return ::operator new(_Size, _NORMAL_BLOCK, __FILE__, __LINE__); }

inline __bcount_opt(_Size) void* __CRTDECL operator new[](size_t _Size)
        { return ::operator new[](_Size, _NORMAL_BLOCK, __FILE__, __LINE__); }

#endif  /* _CRTDBG_MAP_ALLOC */

#endif  /* _DEBUG */

}

#endif  /* _MFC_OVERRIDES_NEW */

#endif  /* __cplusplus */

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_CRTDBG */
