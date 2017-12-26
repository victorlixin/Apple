/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    interix_mtdll.h

Abstract:

    Declaration of structures & functions required for accessing  
    thread's data.

Author:

    Amit Kumar Ghosh (amitgho@microsoft.com) 10-Feb-2005

Revision History:

--*/

#ifndef _MTDLL_H_

#define _MTDLL_H_

/* Structure for each thread's data */

struct _tiddata {
    int     _terrno;            /* errno value */

    /*
     * Per-Thread data needed by C++ Exception Handling
     */
    void *      _terminate;     /* terminate() routine */
    void *      _unexpected;    /* unexpected() routine */
    void *      _translator;    /* S.E. translator */
    void *      _purecall;      /* called when pure virtual happens */
    void *      _curexception;  /* current exception */
    void *      _curcontext;    /* current exception context */
    int         _ProcessingThrow; /* for uncaught_exception */
    void *	    _curexcspec;	  /* for handling exceptions thrown from std::unexpected */
#if defined(_M_IA64) || defined(_M_AMD64)
    void *      _pExitContext;
    void *      _pUnwindContext;
    void *      _pFrameInfoChain;
    unsigned __int64    _ImageBase;
#if defined(_M_IA64)
    unsigned __int64    _TargetGp;
#endif
    unsigned __int64    _ThrowImageBase;
    void *      _pForeignException;
#elif defined(_M_IX86)
    void *      _pFrameInfoChain;
#endif
    
    int _cxxReThrow;        /* Set to True if it's a rethrown C++ Exception */
};

typedef struct _tiddata * _ptiddata;
#if defined(_MT)
#define _mlock(l)               _cpplock(l)
#define _munlock(l)             _cppunlock(l)
#define __TRY __try{
#define __FINALLY   }__finally{
#define __END_TRY_FINALLY }
#else
#define _mlock(l)  
#define _munlock(l) 
#define __TRY
#define __FINALLY
#define __END_TRY_FINALLY 
#endif /* defined(_MT) */

/* Lock symbols */

#define _HEAP_LOCK      0      /* lock for heap allocator routines */
#define _TYPEINFO_LOCK  1      /* lock for type_info access        */
#define _CPP_NUM_LOCK      2

#ifdef __cplusplus
extern "C" {
#endif

int __cdecl _cpplock(int);
int __cdecl _cppunlock(int);
_ptiddata __cdecl _getptd(void);  /* return address of per-thread CRT data */

#ifdef __cplusplus
}
#endif


#endif /* _MTDLL_H_ */
