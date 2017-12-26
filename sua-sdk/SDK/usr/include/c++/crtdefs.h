/***
*crtdefs.h - definitions/declarations common to all CRT
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file has mostly defines used by the entire CRT.
*
*       [Public]
*
*Revision History:
*       08-15-03  AC    Module created
*       10-28-03  SJ    Secure CRT - printf_s : positional args & validations
*       03-04-04  SJ    VSW#255684 - Temporary fix for fwcommon.h issue.
*       03-08-04  MSL   Moved definition of locale info here to allow inline usage in ctype.h
*       03-26-04  AC    Added SECURE_SCL workaround when _DLL is true
*       04-02-04  SJ    Renamed __MAX_POSITIONAL_PARAMETERS to _ARGMAX as per spec.
*       04-08-04  AC    Added __GOT_SECURE_LIB__ 
*       04-10-04  MSL   Added errno_t
*       04-02-04  AJS   va_list to System::ArgIterator.
*       04-16-04  SSM   Manifest related changes.
*       04-29-04  SJ    VSW#288429 - changes in yvals.h need to be duplicated
*                       in crtdefs.h also
*       05-11-04  AC    Added _CRT_INSECURE_DEPRECATE_MEMORY to optionally deprecate [w]mem[cpy|move]
*                       VSW#302444
*       05-12-04  AC    Added workaround when _DLL is true for _M_CEE and _HAS_ITERATOR_DEBUGGING
*       05-14-04  SJ    Changed to C-Style Comments
*       05-19-04  SJ    VSW#252827 - Manifest directive shouldn't be there for /Zl
*       06-15-04  AJS   VSW#316378 - __declspec(process) causes warning under /clr:oldSyntax; changed
*                       definition of _PGLOBAL so that it's a no-op under /clr:oldSyntax.
*       06-30-04  SJ    Changing #pragma to #error
*       08-05-04  AC    Added _CRTIMP_ALTERNATIVE.
*                       Added _TRUNCATE.
*       08-27-04  AC    Removed temporary workaround to solve alignment problems when _SECURE_SCL is set
*                       and we link to the dll.
*       09-14-04  AC    Defines _CRTIMP_ALTERNATIVE based on _CRTIMP
*                       VSW#366528
*       09-24-04  MSL   _CRT_OBSOLETE and parameter naming
*       10-08-04  ESC   Protect against -Zp with pragma pack
*       10-29-04  AGH   Define _CRT_OBSOLETE for users, not internally
*       11-02-04  AC    Add cpp overloads for secure functions.
*                       VSW#313364
*       11-06-04  AC    Add _SECURECRT_FILL_BUFFER_PATTERN
*                       VSW#2459
*                       Remove hack for _HAS_ITERATOR_DEBUGGING
*                       VSW#334470
*       11-08-04  JL    Added _CRT_NONSTDC_DEPRECATE to deprecate non-ANSI functions
*       11-18-04  ATC   SAL Annotations for CRT Headers
*       11-23-04  AC    Fix cpp overload for cgets family.
*                       VSW#408697
*                       Fixed typo.
*       11-30-04  AC    Added the _CRT_PACKING definition to vadefs.h as well
*       12-08-04  AC    Remove _STATIC_CPPLIB when compiling _M_CEE
*                       VSW#338034
*       01-20-05  AC    Added _CRT_INSECURE_DEPRECATE_GLOBALS
*                       VSW#438137
*       01-24-05  AC    Turn on _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES by default
*                       VSW#440460
*       01-25-05  GR    Define _CRT_JIT_INTRINSIC for JIT64 use
*       01-25-05  MSL   Add param names to overload macros
*       03-07-05  PAL   Add overload macro for _swprintf_l, etc.
*
****/

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

#ifndef _INC_CRTDEFS
#define _INC_CRTDEFS

#if 0
#ifndef _CRTBLD
/* This version of the header files is NOT for user programs.
 * It is intended for use when building the C runtimes ONLY.
 * The version intended for public use will not have this message.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */
#endif

#ifndef _INTERNAL_IFSTRIP_

/* Turn off cpp overloads internally */
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 0

#endif

#if     !defined(_WIN32) && !defined(_MS_SUA_)
#error ERROR: Only Win32 target supported!
#endif

#ifdef _CRTBLD
#ifndef _INTERNAL_IFSTRIP_
#define _IGNORE_VC_NO_DEFAULTLIB
#endif
#endif

#ifdef _INTERNAL_IFSTRIP_
#if !defined(_CRT_NOFORCE_MANIFEST) && defined(_VC_NODEFAULTLIB)
#define _CRT_NOFORCE_MANIFEST
#endif
#else
#if !defined(_CRT_NOFORCE_MANIFEST) && defined(_VC_NODEFAULTLIB) && !defined (_IGNORE_VC_NO_DEFAULTLIB)
#define _CRT_NOFORCE_MANIFEST
#endif
#endif

#include <sal.h>

#ifdef _DLL

#if !defined(_CRT_NOFORCE_MANIFEST)

#if _MSC_FULL_VER >= 140040130 /*IFSTRIP=IGN*/

#include <crtassem.h>

#ifdef _M_IX86

#ifdef _DEBUG
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' "         \
        "version='" _CRT_ASSEMBLY_VERSION "' "                          \
        "processorArchitecture='x86' "                                  \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
        "version='" _CRT_ASSEMBLY_VERSION "' "                          \
        "processorArchitecture='x86' "                                  \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif	/* _M_IX86 */

#ifdef _M_AMD64

#ifdef _DEBUG
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' "         \
        "version='" _CRT_ASSEMBLY_VERSION "' "                          \
        "processorArchitecture='amd64' "                                \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
        "version='" _CRT_ASSEMBLY_VERSION "' "                          \
        "processorArchitecture='amd64' "                                \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif	/* _M_AMD64 */

#ifdef _M_IA64

#ifdef _DEBUG
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' "         \
        "version='" _CRT_ASSEMBLY_VERSION "' "                          \
        "processorArchitecture='ia64' "                                 \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
        "version='" _CRT_ASSEMBLY_VERSION "' "                          \
        "processorArchitecture='ia64' "                                 \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif	/* _M_IA64 */

#endif	/* _MSC_FULL_VER */

#endif	/* !defined(_CRT_NOFORCE_MANIFEST) */

#endif	/* _DLL */

#ifdef  _MSC_VER
#undef _CRT_PACKING
#define _CRT_PACKING 8

#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#include <vadefs.h>

#ifdef  __cplusplus
extern "C" {
#endif

/* preprocessor string helpers */
#ifndef _CRT_STRINGIZE
#define __CRT_STRINGIZE(_Value) #_Value
#define _CRT_STRINGIZE(_Value) __CRT_STRINGIZE(_Value)
#endif

#ifndef _CRT_WIDE
#define __CRT_WIDE(_String) L ## _String
#define _CRT_WIDE(_String) __CRT_WIDE(_String)
#endif


#if !defined(_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300 /*IFSTRIP=IGN*/
#define _W64 __w64
#else
#define _W64
#endif
#endif

#ifndef _INTERNAL_IFSTRIP_
/* Define _CRTIMP1 */

#ifndef _CRTIMP1
#ifdef  CRTDLL1
#define _CRTIMP1 __declspec(dllexport)
#else   /* ndef CRTDLL1 */
#define _CRTIMP1 _CRTIMP
#endif  /* CRTDLL1 */
#endif  /* _CRTIMP1 */
#endif  /* _INTERNAL_IFSTRIP_ */

/* Define _CRTIMP_NOIA64 */
#ifndef _CRTIMP_NOIA64
#if defined(_M_IA64)
#define _CRTIMP_NOIA64
#else
#define _CRTIMP_NOIA64 _CRTIMP
#endif
#endif

/* Define _CRTIMP2 */

#ifndef _CRTIMP2
#if defined(CRTDLL2)
#define _CRTIMP2 __declspec(dllexport)
#else   /* ndef CRTDLL2 */
#if defined(_DLL) && !defined(_STATIC_CPPLIB)
#define _CRTIMP2 __declspec(dllimport)
#else   /* ndef _DLL && !STATIC_CPPLIB */
#define _CRTIMP2
#endif  /* _DLL && !STATIC_CPPLIB */
#endif  /* CRTDLL2 */
#endif  /* _CRTIMP2 */

/* Define _CRTIMP_ALTERNATIVE */

#ifndef _INTERNAL_IFSTRIP_
/* This _CRTIMP_ALTERNATIVE is used to mark the secure functions implemented in safecrt.lib, which are
   meant to be available downlevel. In Windows, they will be merged in msvcrt.lib (the import
   library, so Windows should change:
        #define _CRTIMP_ALTERNATIVE __declspec(dllimport)
   to:
        #define _CRTIMP_ALTERNATIVE
   since these function will never be compiled in the msvcrt.dll.
   Here the trick is done based on _CRT_ALTERNATIVE_INLINES which enforce that safecrt.h is included before
   every other standard include files.
 */
#endif
#ifndef _CRTIMP_ALTERNATIVE
#ifdef  CRTDLL
    #ifdef _SAFECRT_IMPL
    #define _CRTIMP_ALTERNATIVE
    #else
    #define _CRTIMP_ALTERNATIVE __declspec(dllexport)
    #endif
#else   /* ndef CRTDLL */
#ifdef  _DLL
#ifdef _CRT_ALTERNATIVE_INLINES
#define _CRTIMP_ALTERNATIVE
#else
#define _CRTIMP_ALTERNATIVE _CRTIMP
#define _CRT_ALTERNATIVE_IMPORTED
#endif
#else   /* ndef _DLL */
#define _CRTIMP_ALTERNATIVE
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP_ALTERNATIVE */

/* Define _MRTIMP */

#ifndef _MRTIMP
#ifdef MRTDLL
#if !defined(_M_CEE_PURE)
    #define _MRTIMP __declspec(dllexport)
#else
    #define _MRTIMP   
#endif
#else   /* ndef MRTDLL */
#define _MRTIMP __declspec(dllimport)
#endif  /* MRTDLL */
#endif  /* _MRTIMP */

/* Define _MRTIMP2 */
#ifndef _MRTIMP2
#if   defined(CRTDLL2)
#define _MRTIMP2	__declspec(dllexport)
#elif defined(MRTDLL)
#define _MRTIMP2 _MRTIMP
#else   /* ndef CRTDLL2 */

#if defined(_DLL) && !defined(_STATIC_CPPLIB)
#define _MRTIMP2	__declspec(dllimport)

#else   /* ndef _DLL && !STATIC_CPPLIB */
#define _MRTIMP2
#endif  /* _DLL && !STATIC_CPPLIB */

#endif  /* CRTDLL2 */
#endif  /* _MRTIMP2 */


#ifndef _MCRTIMP
#if defined(CRTDLL) || defined(MRTDLL)
#define _MCRTIMP __declspec(dllexport)
#else   /* ndef CRTDLL */
#ifdef  _DLL
#define _MCRTIMP __declspec(dllimport)
#else   /* ndef _DLL */
#define _MCRTIMP
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP */

#ifndef __CLR_OR_THIS_CALL
#if defined(MRTDLL) || defined(_M_CEE_PURE)
#define __CLR_OR_THIS_CALL  __clrcall
#else
#define __CLR_OR_THIS_CALL
#endif
#endif

#ifndef __CLRCALL_OR_CDECL
#if defined(MRTDLL) || defined(_M_CEE_PURE)
#define __CLRCALL_OR_CDECL __clrcall
#else
#define __CLRCALL_OR_CDECL __cdecl
#endif
#endif

#ifndef _CRTIMP_PURE
 #if defined(_M_CEE_PURE) || defined(_STATIC_CPPLIB)
  #define _CRTIMP_PURE
 #elif defined(MRTDLL)
  #define _CRTIMP_PURE
 #else
  #define _CRTIMP_PURE _CRTIMP
 #endif
#endif

#ifndef _PGLOBAL
#ifdef _M_CEE
  #if defined(__cplusplus_cli)
    #define _PGLOBAL __declspec(process)
  #else
    #define _PGLOBAL
  #endif
#else
#define _PGLOBAL
#endif
#endif

#ifndef _AGLOBAL
#ifdef _M_CEE
#define _AGLOBAL __declspec(appdomain)
#else
#define _AGLOBAL
#endif
#endif

/* define a specific constant for mixed mode */
#ifdef _M_CEE
#ifndef _M_CEE_PURE
#define _M_CEE_MIXED
#endif
#endif

/* Define __GOT_SECURE_LIB__ */
#define __GOT_SECURE_LIB__ 200402L

/* Define _CRT_INSECURE_DEPRECATE */
#ifndef _CRT_INSECURE_DEPRECATE
#ifdef _CRT_SECURE_NO_DEPRECATE
#define _CRT_INSECURE_DEPRECATE
#else
#define _CRT_INSECURE_DEPRECATE __declspec(deprecated)
#endif
#endif

/* Define _CRT_INSECURE_DEPRECATE_MEMORY */
#ifndef _CRT_INSECURE_DEPRECATE_MEMORY
#if !defined(_CRT_SECURE_DEPRECATE_MEMORY)
#define _CRT_INSECURE_DEPRECATE_MEMORY
#else
#define _CRT_INSECURE_DEPRECATE_MEMORY _CRT_INSECURE_DEPRECATE
#endif
#endif

/* Define _CRT_INSECURE_DEPRECATE_GLOBALS */
#ifndef _CRT_INSECURE_DEPRECATE_GLOBALS
#if defined(_CRT_SECURE_NO_DEPRECATE_GLOBALS)
#define _CRT_INSECURE_DEPRECATE_GLOBALS
#else
#define _CRT_INSECURE_DEPRECATE_GLOBALS _CRT_INSECURE_DEPRECATE
#endif
#endif

/* _SECURECRT_FILL_BUFFER_PATTERN is the same as _bNoMansLandFill */
#define _SECURECRT_FILL_BUFFER_PATTERN 0xFD

/* obsolete stuff */
#ifdef _CRTBLD
#ifndef _INTERNAL_IFSTRIP_
/* These are still used in the CRT sources only */
#define _CRT_OBSOLETE 
#else
#define _CRT_OBSOLETE __declspec(deprecated)
#endif
#endif

/* jit64 instrinsic stuff */
#ifndef _CRT_JIT_INTRINSIC
#if defined(_M_CEE) && defined(__cplusplus) && (defined(_M_AMD64) || defined(_M_IA64))
/* This is only needed when managed code is calling the native APIs, targeting the 64-bit runtime */
#define _CRT_JIT_INTRINSIC __declspec(jitintrinsic)
#else
#define _CRT_JIT_INTRINSIC 
#endif
#endif

/* Define overload switches */
#if !defined(_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0
#endif

#if !defined(_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT)
/* _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT is ignored if _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES is set to 0 */
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0
#endif

#if !defined(_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES)
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#endif

/* Define _CRT_NONSTDC_DEPRECATE */
#if !defined(_CRT_NONSTDC_DEPRECATE)
#if defined(_CRT_NONSTDC_NO_DEPRECATE) || defined(_POSIX_)
#define _CRT_NONSTDC_DEPRECATE
#else
#define _CRT_NONSTDC_DEPRECATE __declspec(deprecated)
#endif
#endif

#ifndef _SIZE_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64    size_t;
#else
typedef _W64 unsigned int   size_t;
#endif
#define _SIZE_T_DEFINED
#endif

#ifndef _INTPTR_T_DEFINED
#ifdef  _WIN64
typedef __int64             intptr_t;
#else
typedef _W64 int            intptr_t;
#endif
#define _INTPTR_T_DEFINED
#endif

#ifndef _UINTPTR_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64    uintptr_t;
#else
typedef _W64 unsigned int   uintptr_t;
#endif
#define _UINTPTR_T_DEFINED
#endif

#ifndef _PTRDIFF_T_DEFINED
#ifdef  _WIN64
typedef __int64             ptrdiff_t;
#else
typedef _W64 int            ptrdiff_t;
#endif
#define _PTRDIFF_T_DEFINED
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#ifndef _WINT_T
#define _WINT_T
typedef unsigned short wint_t;
#endif

#ifndef _WCTYPE_T_DEFINED
typedef unsigned short wctype_t;
#define _WCTYPE_T_DEFINED
#endif

#ifndef _VA_LIST_DEFINED
#ifdef _M_CEE_PURE
typedef System::ArgIterator va_list;
#else
typedef char *  va_list;
#endif
#define _VA_LIST_DEFINED
#endif


#ifdef _MS_SUA_ 

#define _USE_32BIT_TIME_T

#else /* _MS_SUA_ */

#ifdef  _USE_32BIT_TIME_T
#ifdef  _WIN64
#error You cannot use 32-bit time_t (_USE_32BIT_TIME_T) with _WIN64
#undef  _USE_32BIT_TIME_T
#endif
#else
#if     _INTEGRAL_MAX_BITS < 64 /*IFSTRIP=IGN*/
#define _USE_32BIT_TIME_T
#endif
#endif

#endif /* _MS_SUA_ */


#ifndef _ERRCODE_DEFINED
#define _ERRCODE_DEFINED
/* errcode is deprecated in favor or errno_t, which is part of the standard proposal */
#if !defined(__midl)
__declspec(deprecated) typedef int errcode;
#else
typedef int errcode;
#endif

typedef int errno_t;
#endif

#ifndef _TIME32_T_DEFINED
typedef _W64 __int32 __time32_t;   /* 32-bit time value */
#define _TIME32_T_DEFINED
#endif

#ifndef _TIME64_T_DEFINED
#if     _INTEGRAL_MAX_BITS >= 64 /*IFSTRIP=IGN*/
typedef __int64 __time64_t;     /* 64-bit time value */
#endif
#define _TIME64_T_DEFINED
#endif

#ifndef _TIME_T_DEFINED
#ifdef _USE_32BIT_TIME_T
typedef __time32_t time_t;      /* time value */
#else
typedef __time64_t time_t;      /* time value */
#endif
#define _TIME_T_DEFINED         /* avoid multiple def's of time_t */
#endif

#ifndef _CONST_RETURN
#ifdef  __cplusplus
#define _CONST_RETURN  const
#define _CRT_CONST_CORRECT_OVERLOADS
#else
#define _CONST_RETURN
#endif
#endif

#if !defined(UNALIGNED)
#if defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif

/* Define _CRTNOALIAS, _CRTRESTRICT */

#if     _MSC_FULL_VER >= 13102050 /*IFSTRIP=IGN*/
#if !defined(_MSC_VER_GREATER_THEN_13102050)
#define _MSC_VER_GREATER_THEN_13102050 
#endif
#endif

#if     ( defined(_M_IA64) && defined(_MSC_VER_GREATER_THEN_13102050) ) || _MSC_VER >= 1400 /*IFSTRIP=IGN*/
#ifndef _CRTNOALIAS
#define _CRTNOALIAS __declspec(noalias)
#endif  /* _CRTNOALIAS */

#ifndef _CRTRESTRICT
#define _CRTRESTRICT __declspec(restrict)
#endif  /* _CRTRESTRICT */

#else

#ifndef _CRTNOALIAS
#define _CRTNOALIAS
#endif  /* _CRTNOALIAS */

#ifndef _CRTRESTRICT
#define _CRTRESTRICT
#endif  /* _CRTRESTRICT */

#endif

/* Define __cdecl for non-Microsoft compilers */

#if     ( !defined(_MSC_VER) && !defined(__cdecl) )
#define __cdecl
#endif

#if !defined(__CRTDECL)
#if defined(_M_CEE_PURE)
#define __CRTDECL
#else
#define __CRTDECL   __cdecl
#endif
#endif

#ifndef _INTERNAL_IFSTRIP_
#ifdef  _MT
#define __UPDATE_LOCALE(ptd, ptloci)  if( ( (ptloci) != __ptlocinfo) &&      \
                                          !( (ptd)->_ownlocale & __globallocalestatus)) \
                                      {                                     \
                                          (ptloci) = __updatetlocinfo();    \
                                      }

#define __UPDATE_MBCP(ptd, ptmbci)  if( ( (ptmbci) != __ptmbcinfo) &&      \
                                          !( (ptd)->_ownlocale & __globallocalestatus)) \
                                      {                                     \
                                          (ptmbci) = __updatetmbcinfo();    \
                                      }
#else
#define __UPDATE_LOCALE(ptd, ptmbci)
#define __UPDATE_MBCP(ptd, ptmbci)
#endif

/* small function to set global read-only variables */
#ifndef _DEFINE_SET_FUNCTION
#define _DEFINE_SET_FUNCTION(_FuncName, _Type, _VarName) \
    __inline \
    void _FuncName(_Type _Value) \
    { \
        __pragma(warning(push)) \
        __pragma(warning(disable:4996)) \
        _VarName = _Value; \
        __pragma(warning(pop)) \
    }
#endif

#endif

#define _ARGMAX 100

/* _TRUNCATE */
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif

/* helper macros for cpp overloads */
#if defined(__cplusplus) && _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(_ReturnType, _FuncName, _DstType, _Dst) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size]) \
    { \
        return _FuncName(_Dst, _Size); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1) \
    { \
        return _FuncName(_Dst, _Size, _TArg1); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) \
    { \
        return _FuncName(_Dst, _Size, _TArg1, _TArg2); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        return _FuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) \
    { \
        return _FuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3, _TArg4); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1) \
    { \
        return _FuncName(_HArg1, _Dst, _Size, _TArg1); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) \
    { \
        return _FuncName(_HArg1, _Dst, _Size, _TArg1, _TArg2); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        return _FuncName(_HArg1, _Dst, _Size, _TArg1, _TArg2, _TArg3); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(_ReturnType, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType (&_Dst)[_Size]) \
    { \
        return _FuncName(_HArg1, _HArg2, _Dst, _Size); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg1); \
        return _VFuncName(_Dst, _Size, _TArg1, _ArgList); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    extern "C++" \
    { \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg2); \
        return _VFuncName(_Dst, _Size, _TArg1, _TArg2, _ArgList); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(_ReturnType, _FuncName, _DstType, _Src) \
    extern "C++" \
    { \
    template <size_t _DriveSize, size_t _DirSize, size_t _NameSize, size_t _ExtSize> \
    inline \
    _ReturnType __cdecl _FuncName(__in const _DstType *_Src, __out_ecount_opt(_DriveSize) _DstType (&_Drive)[_DriveSize], __out_ecount_opt(_DirSize) _DstType (&_Dir)[_DirSize], __out_ecount_opt(_NameSize) _DstType (&_Name)[_NameSize], __out_ecount_opt(_ExtSize) _DstType (&_Ext)[_ExtSize]) \
    { \
        return _FuncName(_Src, _Drive, _DriveSize, _Dir, _DirSize, _Name, _NameSize, _Ext, _ExtSize); \
    } \
    }

#else

#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(_ReturnType, _FuncName, _DstType, _Dst)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(_ReturnType, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)
#define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(_ReturnType, _FuncName, _DstType, _Src)

#endif /* _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES */

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _VFuncName##_s, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _VFuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE(_DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE(_DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)


#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst) \

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _VFuncName##_s, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE(_DeclSpec, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)


#if defined(__cplusplus) && _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES

#define __RETURN_POLICY_SAME(_FunctionCall, _Dst) return (_FunctionCall)
#define __RETURN_POLICY_DST(_FunctionCall, _Dst) return ((_FunctionCall) == 0 ? _Dst : 0)
#define __RETURN_POLICY_VOID(_FunctionCall, _Dst) (_FunctionCall); return
#define __EMPTY_DECLSPEC

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_DstType *_Dst) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_DstType *); \
        return _FuncName(_Dst); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size]) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, _Size), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1]) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, 1), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _DstType, _Dst) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_DstType *_Dst) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_DstType *); \
        return _FuncName(_Dst); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size]) \
    { \
        size_t _SizeRead = 0; \
        errno_t _Err = _FuncName##_s(_Dst + 2, (_Size - 2) < ((size_t)_Dst[0]) ? (_Size - 2) : ((size_t)_Dst[0]), &_SizeRead); \
        _Dst[1] = (_DstType)(_SizeRead); \
        return (_Err == 0 ? _Dst + 2 : 0); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1]) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<2>(_DstType (&_Dst)[2]) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_DstType *, _TType1); \
        return _FuncName(_Dst, _TArg1); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst, _TType1 _TArg1) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst, _TArg1); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_DstType *, _TType1, _TType2); \
        return _FuncName(_Dst, _TArg1, _TArg2); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst, _TArg1, _TArg2); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_DstType *, _TType1, _TType2, _TType3); \
        return _FuncName(_Dst, _TArg1, _TArg2, _TArg3); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst, _TArg1, _TArg2, _TArg3); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2, _TArg3), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_DstType *, _TType1, _TType2, _TType3, _TType4); \
        return _FuncName(_Dst, _TArg1, _TArg2, _TArg3, _TArg4); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst, _TArg1, _TArg2, _TArg3, _TArg4); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3, _TArg4), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) \
    { \
        _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2, _TArg3, _TArg4), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_HType1 _HArg1, _DstType *_Dst, _TType1 _TArg1) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_HType1, _DstType *, _TType1); \
        return _FuncName(_HArg1, _Dst, _TArg1); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _T _Dst, _TType1 _TArg1) \
    { \
        return __insecure_##_FuncName(_HArg1, (_DstType *)_Dst, _TArg1); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1) \
    { \
        _ReturnPolicy(_SecureFuncName(_HArg1, _Dst, _Size, _TArg1), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_HType1 _HArg1, _DstType (&_Dst)[1], _TType1 _TArg1) \
    { \
        _ReturnPolicy(_SecureFuncName(_HArg1, _Dst, 1, _TArg1), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    __inline \
    _ReturnType __cdecl __insecure_##_FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType *_Dst) \
    { \
        _DeclSpec _ReturnType __cdecl _FuncName(_HType1, _HType2, _DstType *); \
        return _FuncName(_HArg1, _HArg2, _Dst); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _T _Dst) \
    { \
        return __insecure_##_FuncName(_HArg1, _HArg2, (_DstType *)_Dst); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType (&_Dst)[_Size]) \
    { \
        _ReturnPolicy(_SecureFuncName(_HArg1, _HArg2, _Dst, _Size), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_HType1 _HArg1, _HType2 _HArg2, _DstType (&_Dst)[1]) \
    { \
        _ReturnPolicy(_SecureFuncName(_HArg1, _HArg2, _Dst, 1), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1) \
    __inline \
    _ReturnType __cdecl __insecure_##_VFuncName(_DstType *_Dst, _TType1 _TArg1, va_list _ArgList) \
    { \
        _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *, _TType1, va_list); \
        return _VFuncName(_Dst, _TArg1, _ArgList); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst, _TType1 _TArg1, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg1); \
        return __insecure_##_VFuncName((_DstType *)_Dst, _TArg1, _ArgList); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg1); \
        _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _ArgList), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg1); \
        _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _ArgList), _Dst); \
    } \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _VFuncName(_T _Dst, _TType1 _TArg1, va_list _ArgList) \
    { \
        return __insecure_##_VFuncName((_DstType *)_Dst, _TArg1, _ArgList); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _VFuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, va_list _ArgList) \
    { \
        _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _ArgList), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _VFuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, va_list _ArgList) \
    { \
        _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _ArgList), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __inline \
    _ReturnType __cdecl __insecure_##_VFuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) \
    { \
        _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *, _TType1, _TType2, va_list); \
        return _VFuncName(_Dst, _TArg1, _TArg2, _ArgList); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg2); \
        return __insecure_##_VFuncName((_DstType *)_Dst, _TArg1, _TArg2, _ArgList); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg2); \
        _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _TArg2, _ArgList), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, ...) \
    { \
        va_list _ArgList; \
        _crt_va_start(_ArgList, _TArg2); \
        _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _TArg2, _ArgList), _Dst); \
    } \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _VFuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) \
    { \
        return __insecure_##_VFuncName((_DstType *)_Dst, _TArg1, _TArg2, _ArgList); \
    } \
    template <size_t _Size> \
    inline \
    _ReturnType __cdecl _VFuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) \
    { \
        _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _TArg2, _ArgList), _Dst); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    _ReturnType __cdecl _VFuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) \
    { \
        _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _TArg2, _ArgList), _Dst); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __inline \
    size_t __cdecl __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2) \
    { \
        _DeclSpec size_t __cdecl _FuncName(_DstType *, _TType1, _TType2); \
        return _FuncName(_Dst, _TArg1, _TArg2); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    size_t __cdecl _FuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst, _TArg1, _TArg2); \
    } \
    template <size_t _Size> \
    inline \
    size_t __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) \
    { \
        size_t _Ret = 0; \
        _SecureFuncName(&_Ret, _Dst, _Size, _TArg1, _TArg2); \
        return (_Ret > 0 ? (_Ret - 1) : _Ret); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    size_t __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2) \
    { \
        size_t _Ret = 0; \
        _SecureFuncName(&_Ret, _Dst, 1, _TArg1, _TArg2); \
        return (_Ret > 0 ? (_Ret - 1) : _Ret); \
    } \
    }

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __inline \
    size_t __cdecl __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        _DeclSpec size_t __cdecl _FuncName(_DstType *, _TType1, _TType2, _TType3); \
        return _FuncName(_Dst, _TArg1, _TArg2, _TArg3); \
    } \
    extern "C++" \
    { \
    template <typename _T> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    size_t __cdecl _FuncName(_T _Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        return __insecure_##_FuncName((_DstType *)_Dst, _TArg1, _TArg2, _TArg3); \
    } \
    template <size_t _Size> \
    inline \
    size_t __cdecl _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        size_t _Ret = 0; \
        _SecureFuncName(&_Ret, _Dst, _Size, _TArg1, _TArg2, _TArg3); \
        return (_Ret > 0 ? (_Ret - 1) : _Ret); \
    } \
    template <> \
    inline \
    _CRT_INSECURE_DEPRECATE \
    size_t __cdecl _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) \
    { \
        size_t _Ret = 0; \
        _SecureFuncName(&_Ret, _Dst, 1, _TArg1, _TArg2, _TArg3); \
        return (_Ret > 0 ? (_Ret - 1) : _Ret); \
    } \
    }

#if _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

#else

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType *_Dst, _TType1 _TArg1);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, ...); \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *_Dst, _TType1 _TArg1, va_list _Args);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...); \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    _CRT_INSECURE_DEPRECATE _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

#endif /* _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT */

#else

#define __RETURN_POLICY_SAME(_FunctionCall)
#define __RETURN_POLICY_DST(_FunctionCall)
#define __RETURN_POLICY_VOID(_FunctionCall)
#define __EMPTY_DECLSPEC

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType *_Dst, _TType1 _TArg1);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, ...); \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *_Dst, _TType1 _TArg1, va_list _Args);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...); \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    _CRT_INSECURE_DEPRECATE _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType *_Dst, _TType1 _TArg1);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType *_Dst);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _DstType, _Dst, _TType1, _TArg1) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, ...); \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *_Dst, _TType1 _TArg1, va_list _Args);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...); \
    _CRT_INSECURE_DEPRECATE _DeclSpec _ReturnType __cdecl _VFuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2) \
    _CRT_INSECURE_DEPRECATE _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3) \
    _CRT_INSECURE_DEPRECATE _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

#endif /* _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES */

struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct * pthreadlocinfo;
typedef struct threadmbcinfostruct * pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct
{
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
} _locale_tstruct, *_locale_t;

#ifndef _TAGLC_ID_DEFINED
typedef struct tagLC_ID {
        unsigned short wLanguage;
        unsigned short wCountry;
        unsigned short wCodePage;
} LC_ID, *LPLC_ID;
#define _TAGLC_ID_DEFINED
#endif  /* _TAGLC_ID_DEFINED */

#ifndef _THREADLOCALEINFO
typedef struct threadlocaleinfostruct {
        int refcount;
        unsigned int lc_codepage;
        unsigned int lc_collate_cp;
        unsigned long lc_handle[6]; /* LCID */
        LC_ID lc_id[6];
        struct {
            char *locale;
            wchar_t *wlocale;
            int *refcount;
            int *wrefcount;
        } lc_category[6];
        int lc_clike;
        int mb_cur_max;
        int * lconv_intl_refcount;
        int * lconv_num_refcount;
        int * lconv_mon_refcount;
        struct lconv * lconv;
        int * ctype1_refcount;
        unsigned short * ctype1;
        const unsigned short * pctype;
        const unsigned char * pclmap;
        const unsigned char * pcumap;
        struct __lc_time_data * lc_time_curr;
} threadlocinfo;
#define _THREADLOCALEINFO
#endif

#ifdef  __cplusplus
}
#endif

/* 
We want to have declarations of our parameters in our headers to allow autocomplete to see
more descriptive information. However, to avoid any perf hit of adding all those extra
symbols to the symbol table on every compilation, we protect the parameters with _P macro
that expands to something only during autocomplete processing

In case a third party tool wants to see the parameter names, we also provide a named CRT
option that has the same impact as __FEACP__
*/

#define _PARAM(x) _P(x)
#if defined(__FEACP__) || defined (_CRT_ENABLE_PARAMETER_NAMES) || defined(_PREFAST_)
#define _P(x)   x
#else
#define _P(x)
#endif

#if defined(_PREFAST_) && defined(_PFT_SHOULD_CHECK_RETURN)
#define __checkReturn_opt __checkReturn
#else
#define __checkReturn_opt
#endif

#if defined(_PREFAST_) && defined(_PFT_SHOULD_CHECK_RETURN_WAT)
#define __checkReturn_wat __checkReturn
#else
#define __checkReturn_wat
#endif

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_CRTDEFS */
