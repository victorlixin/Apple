/***
*use_ansi.h - pragmas for ANSI Standard C++ libraries
*
*	Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This header is intended to force the use of the appropriate ANSI
*       Standard C++ libraries whenever it is included.
*
*       [Public]
*
****/


#if     _MSC_VER > 1000 /*IFSTRIP=IGN*/
#pragma once
#endif

#ifndef _USE_ANSI_CPP
#define _USE_ANSI_CPP

#ifdef _CRTBLD
#ifndef _INTERNAL_IFSTRIP_
#define _CRT_NOPRAGMA_LIBS
#else
#undef _CRT_NOPRAGMA_LIBS
#endif
#endif

#ifndef _CRT_NOPRAGMA_LIBS

#if !defined(_M_CEE_PURE) && !defined(MRTDLL)

#if defined(_DLL) && !defined(_STATIC_CPPLIB)
#ifdef _DEBUG
#pragma comment(lib,"msvcprtd")
#else	// _DEBUG
#pragma comment(lib,"msvcprt")
#endif	// _DEBUG

#if !defined(_STL_NOFORCE_MANIFEST) && !defined(_VC_NODEFAULTLIB)
#if _MSC_FULL_VER >= 140040130

#include <crtassem.h>

#ifdef _M_IX86

#ifdef _DEBUG
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' "         \
        "version='" _CRT_ASSEMBLY_VERSION "' "                           \
        "processorArchitecture='x86' "                                  \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
        "version='" _CRT_ASSEMBLY_VERSION "' "                           \
        "processorArchitecture='x86' "                                  \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif	/* _M_IX86 */

#ifdef _M_AMD64

#ifdef _DEBUG
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' "         \
        "version='" _CRT_ASSEMBLY_VERSION "' "                           \
        "processorArchitecture='amd64' "                                \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
        "version='" _CRT_ASSEMBLY_VERSION "' "                           \
        "processorArchitecture='amd64' "                                \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif	/* _M_AMD64 */

#ifdef _M_IA64

#ifdef _DEBUG
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".DebugCRT' "         \
        "version='" _CRT_ASSEMBLY_VERSION "' "                           \
        "processorArchitecture='ia64' "                                 \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
        "name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
        "version='" _CRT_ASSEMBLY_VERSION "' "                           \
        "processorArchitecture='ia64' "                                 \
        "publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif

#endif	// _MSC_FULL_VER

#endif	// !defined(_STL_NOFORCE_MANIFEST) && !defined(_VC_NODEFAULTLIB)

#else	// _DLL && !STATIC_CPPLIB
#ifdef _DEBUG
#pragma comment(lib,"libcpmtd")
#else	// _DEBUG
#pragma comment(lib,"libcpmt")
#endif	// _DEBUG
#endif	// _DLL && !STATIC_CPPLIB

#endif // !defined(_M_CEE_PURE) && !defined(MRTDLL)

#endif  // _CRT_NOPRAGMA_LIBS

#endif	// _USE_ANSI_CPP
