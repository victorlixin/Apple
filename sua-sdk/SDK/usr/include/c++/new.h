
/***
*new.h - declarations and definitions for C++ memory allocation functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Contains the declarations for C++ memory allocation functions.
*
*       [Public]
*
*Revision History:
*       03-07-90  WAJ   Initial version.
*       04-09-91  JCR   ANSI keyword conformance
*       08-12-91  JCR   Renamed new.hxx to new.h
*       08-13-91  JCR   Better set_new_handler names (ANSI, etc.).
*       10-03-91  JCR   Added _OS2_IFSTRIP switches for ifstrip'ing purposes
*       10-30-91  JCR   Changed "nhew" to "hnew" (typo in name!)
*       11-13-91  JCR   32-bit version.
*       06-03-92  KRS   Fix CAVIAR #850: _CALLTYPE1 missing from prototype.
*       08-05-92  GJF   Function calling type and variable type macros.
*       01-21-93  GJF   Removed support for C6-386's _cdecl.
*       04-06-93  SKS   Replace _CRTAPI1/2 with __cdecl, _CRTVAR1 with nothing
*       04-07-93  SKS   Add _CRTIMP keyword for CRT DLL model
*       10-11-93  GJF   Support NT SDK and Cuda builds.
*       03-03-94  SKS   Add _query_new_handler(), _set/_query_new_mode().
*       03-31-94  GJF   Conditionalized typedef of _PNH so multiple
*                       inclusions of new.h will work.
*       05-03-94  CFW   Add set_new_handler.
*       06-03-94  SKS   Remove set_new_hander -- it does NOT conform to ANSI
*                       C++ working standard.  We may implement it later.
*       02-11-95  CFW   Add _CRTBLD to avoid users getting wrong headers.
*       02-14-95  CFW   Clean up Mac merge.
*       04-10-95  CFW   Add set_new_handler stub, fix _INC_NEW.
*       04-19-95  CFW   Change set_new_handler comments, add placement new.
*       05-24-95  CFW   Add ANSI new handler.
*       06-23-95  CFW   ANSI new handler removed from build.
*       10-05-95  SKS   Add __cdecl to new_handler prototype so that the
*                       cleansed new.h matches the checked-in version.
*       12-14-95  JWM   Add "#pragma once".
*       03-04-96  JWM   Replaced by C++ header "new".
*       03-04-96  JWM   MS-specific restored.
*       02-20-97  GJF   Cleaned out obsolete support for _CRTAPI* and _NTSDK.
*                       Also, detab-ed.
*       04-18-97  JWM   Placement operator delete() added.
*       04-21-97  JWM   Placement operator delete() now #if _MSC_VER >= 1200.
*       09-30-97  JWM   Restored not-so-obsolete _CRTAPI1 support.
*       10-07-97  RDL   Added IA64.
*       12-15-98  GJF   Changes for 64-bit size_t.
*       05-13-99  PML   Remove _CRTAPI1
*       05-17-99  PML   Remove all Macintosh support.
*       10-06-99  PML   Add _W64 modifier to types which are 32 bits in Win32,
*                       64 bits in Win64.
*       03-18-01  PML   Define new_handler/set_new_handler compatibly with
*                       definitions in <new> (vs7#194908).
*       06-15-01  PML   Duplicate defs of std::nothrow_t, std::nothrow from
*                       header <new> (vs7#237394)
*       09-11-03  SSM   Changed parameter name to match the one in <new>. 
*                       Whidbey - 170160
*       03-30-04  AC    Added _set_new_handler overload.
*                       VSW#250700
*       04-07-04  MSL   Fixed nothrow new to work in managed code
*                       VSW#216349
*       10-18-04  MSL   Managed new handler
*       11-18-04  ATC   SAL Annotations for CRT Headers
*
****/

#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#ifndef _INC_NEW
#define _INC_NEW

#ifdef  __cplusplus

#ifndef _MSC_EXTENSIONS
#include <new>
#endif

#include <crtdefs.h>

/* Protect against #define of new */
#pragma push_macro("new")
#undef  new

#ifndef _USE_OLD_STDCPP
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
#endif  /* _USE_OLD_STDCPP */

/* Define __cdecl for non-Microsoft compilers */

#if     ( !defined(_MSC_VER) && !defined(__cdecl) )
#define __cdecl
#endif

#ifdef  _MSC_EXTENSIONS
#ifdef  _USE_OLD_STDCPP
typedef void (__cdecl * new_handler) ();
_CRTIMP new_handler __cdecl set_new_handler(__in_opt new_handler _P(_NewHandler));
#else

namespace std {

#ifdef _M_CEE_PURE
typedef void (__clrcall * new_handler) ();
#else
typedef void (__cdecl * new_handler) ();
#endif
#ifdef _M_CEE
typedef void (__clrcall * _new_handler_m) ();
#endif
_CRTIMP2 new_handler __cdecl set_new_handler(__in_opt new_handler _P(_NewHandler)) throw();
#ifdef _M_CEE_MIXED
extern "C++" _MRTIMP _new_handler_m __cdecl set_new_handler(__in_opt _new_handler_m _P(_NewHandler)) throw();
extern "C++" _MRTIMP new_handler __cdecl set_new_handler(int) throw();
#endif

};

#ifdef _M_CEE
using std::_new_handler_m;
#endif
using std::new_handler;
using std::set_new_handler;
#endif
#endif

#ifndef __NOTHROW_T_DEFINED
#define __NOTHROW_T_DEFINED
namespace std {
        /* placement new tag type to suppress exceptions */
        struct nothrow_t {};

        /* constant for placement new tag */
        extern const nothrow_t nothrow;
};

__bcount_opt(_Size) void *__CRTDECL operator new(size_t _P(_Size), const std::nothrow_t&) throw();
__bcount_opt(_Size) void *__CRTDECL operator new[](size_t _P(_Size), const std::nothrow_t&) throw();
void __CRTDECL operator delete(void *, const std::nothrow_t&) throw();
void __CRTDECL operator delete[](void *, const std::nothrow_t&) throw();
#endif

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void *__CRTDECL operator new(size_t, void *_Where)
        {return (_Where); }
#if     _MSC_VER >= 1200 /*IFSTRIP=IGN*/
inline void __CRTDECL operator delete(void *, void *)
        {return; }
#endif
#endif


/* 
 * new mode flag -- when set, makes malloc() behave like new()
 */

_CRTIMP int __cdecl _query_new_mode( void );
_CRTIMP int __cdecl _set_new_mode( __in int _P(_NewMode));

#ifndef _PNH_DEFINED
#ifdef _M_CEE_PURE
typedef int (__clrcall * _PNH)( size_t );
#else
typedef int (__cdecl * _PNH)( size_t );
#endif
#define _PNH_DEFINED
#endif

_CRTIMP _PNH __cdecl _query_new_handler( void );
_CRTIMP _PNH __cdecl _set_new_handler( __in_opt _PNH _P(_NewHandler));

#if _MSC_VER >= 1400 && defined(_M_CEE) /*IFSTRIP=IGN*/
#ifndef __MPNH_DEFINED
typedef int (__clrcall * __MPNH)( size_t );
#define __MPNH_DEFINED
#endif

_MRTIMP __MPNH __cdecl __query_new_handler_m( void );
#ifdef _M_CEE_MIXED
/* _set_new_handler(int) is used to disambiguate NULL/0 */
_CRTIMP _PNH __cdecl _set_new_handler( __in int _P(_NewHandler));
extern "C++" _MRTIMP __MPNH __cdecl _set_new_handler(__in_opt __MPNH _P(_NewHandler));
#endif
#endif

/*
 * Microsoft extension: 
 *
 * _NO_ANSI_NEW_HANDLER de-activates the ANSI new_handler. Use this special value
 * to support old style (_set_new_handler) behavior.
 */

#ifndef _NO_ANSI_NH_DEFINED
#define _NO_ANSI_NEW_HANDLER  ((new_handler)-1)
#define _NO_ANSI_NEW_HANDLER_M  ((_new_handler_m)-1)
#define _NO_ANSI_NH_DEFINED
#endif

#pragma pop_macro("new")

#endif  /* __cplusplus */

#endif  /* _INC_NEW */
