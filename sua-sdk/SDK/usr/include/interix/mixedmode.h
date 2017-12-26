//-----------------------------------------------------------------------------
// File:			MixedMode.h
//
// Copyright:		Copyright (c) Microsoft Corporation          
//
// Contents: 		This file contains Substitutes for definitions from Windows.h 
//
// Comments: 		Typedefs that can be used by Header Files that require Windows.h
//					Work Under Progress
//
//-----------------------------------------------------------------------------

#ifndef __MIXED_MODE_H
#define __MIXED_MODE_H
//Most of the Entries are copied from Windef.h

#ifdef __cplusplus
extern "C" { 			/* Assume C declarations for C++   */
#endif  /* __cplusplus */

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */
#ifndef BASETYPES
#define BASETYPES

/*
 * The definition of LONG to "int" has been done to take care of compilation with 
 * Windows (ODBC) headers (esp in 64-bit). "int" is a 32-bit in data type both on 
 * 32-bit as well as 64-bit platform. The ODBC DLLs expects "long" as a 32-bit datatype 
 * in all platforms. The definition below will keep it so for all platforms.
 */
typedef unsigned int ULONG;
typedef int LONG;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#define DLL_PROCESS_ATTACH   1    // winnt
#define DLL_THREAD_ATTACH    2    // winnt
#define DLL_THREAD_DETACH    3    // winnt
#define DLL_PROCESS_DETACH   0    // winnt

#ifndef FALSE
#define FALSE               0
#endif /*FALSE */

#ifndef TRUE
#define TRUE                1
#endif /*TRUE */

#ifndef IN
#define IN
#endif /*IN*/

#ifndef OUT
#define OUT
#endif /*OUT*/

#ifndef OPTIONAL
#define OPTIONAL
#endif /*OPTIONAL*/


#ifndef VOID
#define VOID void
#endif /*VOID*/

#define CONST const

typedef unsigned int        DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL		        *PBOOL;
typedef BOOL	            *LPBOOL;
typedef BYTE				*PBYTE;
typedef BYTE				*LPBYTE;
typedef int					*PINT;
typedef int					*LPINT;
typedef WORD				*PWORD;
typedef WORD				*LPWORD;

typedef DWORD		        *PDWORD;
typedef DWORD				*LPDWORD;
typedef void		        *LPVOID;
typedef CONST void			*LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;


#ifndef _MS_SUA_
#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */
#endif /* _MS_SUA_ */

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))

//From winnt.h
typedef void *HANDLE;
typedef HANDLE *PHANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
DECLARE_HANDLE            (HWND);
typedef char CHAR;
typedef short SHORT;

//
// UNICODE (Wide Character) types
//
//basetyps.h
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;
typedef CONST WCHAR *LPCWSTR, *PCWSTR;
//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef SHORT *PSHORT;  
typedef LONG *PLONG;    

//
// Flag (bit) fields
//

typedef BYTE   FCHAR;
typedef WORD   FSHORT;
typedef DWORD  FLONG;

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;
#endif

typedef struct _GUID {
    unsigned int  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;

#if defined(WIN32) || defined(__INTERIX) 
	#define SQL_API  __stdcall 
#else 
	#define SQL_API 
#endif

#ifdef _WIN64
typedef signed __int64      INT64;
typedef unsigned __int64    UINT64;
#define _int64 __int64      
#endif


#ifdef __cplusplus
}                                    /* End of extern "C" { */
#endif  /* __cplusplus */

#endif    //__MIXED_MODE_H


 

