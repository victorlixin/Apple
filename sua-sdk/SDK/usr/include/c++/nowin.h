/***
*nowin.h -
*
*	Copyright (c) 1996, Microsoft Corporation. All rights reserved.
*
*Purpose:
*	Declare misc. types, macros, etc. for non-Windows platforms that would
*       normally be declared in windows.h
*
*Revision History:
*       04-25-96  PNT	Module Created.
*
****/

#if !defined(_NOWIN_INCLUDED)
#define _NOWIN_INCLUDED

typedef int                     INT;
typedef unsigned int            UINT;
typedef unsigned short          USHORT;
typedef USHORT                 *PUSHORT;
typedef char                    CHAR;
typedef CHAR                   *PCHAR;
typedef unsigned char           UCHAR;
typedef UCHAR                  *PUCHAR;
typedef char                   *PSZ;
typedef unsigned char           BYTE;
typedef unsigned short          WORD;
typedef unsigned __int32        DWORD;
typedef DWORD                  *DWORD_PTR;
typedef int                     BOOL;
typedef unsigned char           BOOLEAN;
typedef BOOLEAN                *PBOOLEAN;
typedef int                     BOOL;
typedef void                    VOID;
typedef VOID                   *PVOID;
typedef long 			LONG;

typedef struct _EXCEPTION_RECORD *PEXCEPTION_RECORD;

#define NULL                    0

#define FALSE	                0
#define TRUE	                1

#define IN
#define OUT
#define OPTIONAL

#define FAR
#define WINAPI
typedef int                     (FAR WINAPI *FARPROC)();

#ifndef NOMINMAX

#ifndef max
#define max(a, b)               (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b)               (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */

// Determine if an argument is present by testing the value of the pointer
// to the argument value.
//

#define ARGUMENT_PRESENT(ArgumentPointer)    (\
    (CHAR *)(ArgumentPointer) != (CHAR *)(NULL) )

//
// Exception record definition.
//

#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum number of exception parameters

#define SIZE_OF_80387_REGISTERS      80

typedef struct _FLOATING_SAVE_AREA {
    DWORD   ControlWord;
    DWORD   StatusWord;
    DWORD   TagWord;
    DWORD   ErrorOffset;
    DWORD   ErrorSelector;
    DWORD   DataOffset;
    DWORD   DataSelector;
    BYTE    RegisterArea[SIZE_OF_80387_REGISTERS];
    DWORD   Cr0NpxState;
} FLOATING_SAVE_AREA;

typedef FLOATING_SAVE_AREA *PFLOATING_SAVE_AREA;
#define MAXIMUM_SUPPORTED_EXTENSION     512

#if defined(_M_IX86)
typedef struct _CONTEXT {

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a threads context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    DWORD ContextFlags;

    //
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    //

    DWORD   Dr0;
    DWORD   Dr1;
    DWORD   Dr2;
    DWORD   Dr3;
    DWORD   Dr6;
    DWORD   Dr7;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    //

    FLOATING_SAVE_AREA FloatSave;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_SEGMENTS.
    //

    DWORD   SegGs;
    DWORD   SegFs;
    DWORD   SegEs;
    DWORD   SegDs;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_INTEGER.
    //

    DWORD   Edi;
    DWORD   Esi;
    DWORD   Ebx;
    DWORD   Edx;
    DWORD   Ecx;
    DWORD   Eax;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_CONTROL.
    //

    DWORD   Ebp;
    DWORD   Eip;
    DWORD   SegCs;              // MUST BE SANITIZED
    DWORD   EFlags;             // MUST BE SANITIZED
    DWORD   Esp;
    DWORD   SegSs;

    //
    // This section is specified/returned if the ContextFlags word
    // contains the flag CONTEXT_EXTENDED_REGISTERS.
    // The format and contexts are processor specific
    //

    BYTE    ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];

} CONTEXT;

typedef CONTEXT *PCONTEXT;
#endif

#if defined (_M_AMD64)

typedef long long             LONGLONG;
typedef unsigned long long    ULONGLONG;
typedef unsigned long long    ULONG64;
typedef void                 *HANDLE;


/*
 * amitgho @ 01-Jan-2005
 * ---------------------
 *    Copied from ntamd64.h
 */

typedef struct _RUNTIME_FUNCTION {
    __int32 BeginAddress;
    __int32 EndAddress;
    __int32 UnwindData;
} RUNTIME_FUNCTION, *PRUNTIME_FUNCTION;

#if defined(_WIN64)
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
#else
typedef _W64 unsigned long ULONG_PTR, *PULONG_PTR;
#endif

typedef struct __declspec(align(16)) _M128 {
    ULONGLONG Low;
    LONGLONG High;
} M128, *PM128;

//
// Format of data for 32-bit fxsave/fxrstor instructions.
//

typedef struct _XMM_SAVE_AREA32 {
    USHORT ControlWord;
    USHORT StatusWord;
    UCHAR TagWord;
    UCHAR Reserved1;
    USHORT ErrorOpcode;
    unsigned __int32 ErrorOffset;
    USHORT ErrorSelector;
    USHORT Reserved2;
    unsigned __int32 DataOffset;
    USHORT DataSelector;
    USHORT Reserved3;
    unsigned __int32 MxCsr;
    unsigned __int32 MxCsr_Mask;
    M128 FloatRegisters[8];
    M128 XmmRegisters[16];
    UCHAR Reserved4[96];
} XMM_SAVE_AREA32, *PXMM_SAVE_AREA32;

typedef struct __declspec(align(16)) _CONTEXT {

    //
    // Register parameter home addresses.
    //
    // N.B. These fields are for convience - they could be used to extend the
    //      context record in the future.
    //

    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    ULONG64 P5Home;
    ULONG64 P6Home;

    //
    // Control flags.
    //

    unsigned __int32 ContextFlags;
    unsigned __int32 MxCsr;

    //
    // Segment Registers and processor flags.
    //

    USHORT SegCs;
    USHORT SegDs;
    USHORT SegEs;
    USHORT SegFs;
    USHORT SegGs;
    USHORT SegSs;
    unsigned __int32 EFlags;

    //
    // Debug registers
    //

    ULONG64 Dr0;
    ULONG64 Dr1;
    ULONG64 Dr2;
    ULONG64 Dr3;
    ULONG64 Dr6;
    ULONG64 Dr7;

    //
    // Integer registers.
    //

    ULONG64 Rax;
    ULONG64 Rcx;
    ULONG64 Rdx;
    ULONG64 Rbx;
    ULONG64 Rsp;
    ULONG64 Rbp;
    ULONG64 Rsi;
    ULONG64 Rdi;
    ULONG64 R8;
    ULONG64 R9;
    ULONG64 R10;
    ULONG64 R11;
    ULONG64 R12;
    ULONG64 R13;
    ULONG64 R14;
    ULONG64 R15;

    //
    // Program counter.
    //

    ULONG64 Rip;

    //
    // Floating point state.
    //

    union {
        XMM_SAVE_AREA32 FltSave;
        struct {
            M128 Header[2];
            M128 Legacy[8];
            M128 Xmm0;
            M128 Xmm1;
            M128 Xmm2;
            M128 Xmm3;
            M128 Xmm4;
            M128 Xmm5;
            M128 Xmm6;
            M128 Xmm7;
            M128 Xmm8;
            M128 Xmm9;
            M128 Xmm10;
            M128 Xmm11;
            M128 Xmm12;
            M128 Xmm13;
            M128 Xmm14;
            M128 Xmm15;
        };
    };

    //
    // Vector registers.
    //

    M128 VectorRegister[26];
    ULONG64 VectorControl;

    //
    // Special debug control registers.
    //

    ULONG64 DebugControl;
    ULONG64 LastBranchToRip;
    ULONG64 LastBranchFromRip;
    ULONG64 LastExceptionToRip;
    ULONG64 LastExceptionFromRip;
} CONTEXT, *PCONTEXT;
#endif

#if !defined(_W64) 

#if defined(_X86_) && _MSC_VER >= 1300
#define _W64 __w64
#else
#define _W64
#endif

#endif

#if !defined(PULONG_PTR)
#if defined(_WIN64)
typedef unsigned __int64 *      PULONG_PTR;
#else
typedef _W64 unsigned long *    PULONG_PTR;
#endif
#endif

// Taken from wtypes.h
#ifndef _LCID_DEFINED
#define _LCID_DEFINED
typedef DWORD LCID;
#endif // !_LCID_DEFINED

// Taken from winnls.h
typedef DWORD LCTYPE;


//=========  copied from subsys\inc\psxinterlk.h ========================

#ifdef _M_IX86

/*
 * The intrinsics generated by the MSVC compiler do *not* make sense to
 * Donnte and jamespar.  So we have returned to defining our own.
 */
#pragma warning(disable:4035)

#define FASTCALL __fastcall
/*
 * Imcrement the long at address 'i'.
 */
__inline long FASTCALL
InterlockedIncrement(long *i)
{
    __asm {

	mov	eax, 1
	mov	ecx, i
   lock xadd	[ecx], eax
	inc	eax
    }
}

/*
 * Decrement the long at address 'i'.
 */
__inline long FASTCALL
InterlockedDecrement(long *i)
{
    __asm {

	mov	eax, -1
	mov	ecx, i
   lock xadd	[ecx], eax
	dec	eax
    }
}

/*
 * If 'comperand' is equal to the value stored at 'target', then 'value'
 * will be stored at 'target' and 'comperand' will be returned.  Otherwise the
 * value stored at 'target' will be returned.
 */
__inline long FASTCALL
InterlockedCompareExchange(long *target, long value, long comperand)
{
    __asm {

	mov	eax, comperand
	mov	ecx, target
	mov	edx, value
   lock	cmpxchg	[ecx], edx
    }
}


/*
 * Store 'value' at 'target' and return the previous value at 'target'.
 */
__inline long FASTCALL
InterlockedExchange(long *target, long value)
{
    __asm {

	mov	eax, value
	mov	ecx, target
   lock xchg	[ecx], eax
    }
}

/*
 * Store 'value' at 'target' and return the sum of the previous value at
 * 'target' and 'value'.
 */
__inline long FASTCALL
InterlockedExchangeAdd(long *target, long value)
{
    __asm {

	mov	eax, value
	mov	ecx, target
   lock xadd	[ecx], eax
    }
}

#pragma warning(default:4035)

#else /* _M_IX86 */

#define FASTCALL __fastcall
#define InterlockedIncrement _InterlockedIncrement64
#define InterlockedDecrement _InterlockedDecrement64
#define InterlockedExchange _InterlockedExchange64
#define InterlockedExchangeAdd _InterlockedExchangeAdd64
#define InterlockedCompareExchange _InterlockedCompareExchange64

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
__inline __int64 FASTCALL
InterlockedIncrement(long *i);

__inline __int64 FASTCALL
InterlockedDecrement(long *i);

__inline __int64 FASTCALL
InterlockedExchange(long *target, long value);

__inline __int64 FASTCALL
InterlockedExchangeAdd(long *Addend, long Value);

__inline __int64 FASTCALL
InterlockedCompareExchange(long *Destination, long ExChange, long Comperand);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#pragma intrinsic(_InterlockedIncrement64)
#pragma intrinsic(_InterlockedDecrement64)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedCompareExchange64)
#endif /* _M_I386 */

#endif
