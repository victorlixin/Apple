/***
*setjmp.h - definitions/declarations for setjmp/longjmp routines
*
*       Copyright (c) 1985-1992, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines the machine-dependent buffer used by
*       setjmp/longjmp to save and restore the program state, and
*       declarations for those routines.
*       [ANSI/System V]
*
****/

/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is modified Microsoft Source which is copyrighted
 * by Microsoft Corporation.  The Microsoft copyright appears 
 * elsewhere in this source module.
 * 
 * Modifications made to this Software Source are copyrighted by
 * Microsoft Corporation., and are the unpublished, valuable, confidential
 * property of Microsoft Corporation.  Use is therefore authorised only 
 * under the terms and conditions set out in the source code licence 
 * agreement protecting this Software Source.  Any unauthorised use or 
 * disclosure of this Software Source is prohibited.
 *
 * THESE SOFTWARE MODIFICATIONS ARE PROVIDED ``AS IS'' BY MICROSOFT CORP.
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 */

/*
 *  RCSid = $Header: /E/interix/include/setjmp.h,v 1.12 1999/09/30 18:55:16 mark Exp $
 */


#ifndef _SETJMP_H_
#define _SETJMP_H_

#include <features.h>

#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus*/

/*
 * Definitions specific to particular setjmp implementations.
 */
#if defined(_M_IX86)

/*
 * MS C8-32 or older MS C6-386 compilers
 */
#define _JBLEN  16
#define _JBTYPE int

/*
 * Define jump buffer layout for x86 setjmp/longjmp
 */

typedef struct __JUMP_BUFFER {
	unsigned long Ebp;
	unsigned long Ebx;
	unsigned long Edi;
	unsigned long Esi;
	unsigned long Esp;
	unsigned long Eip;
	unsigned long Registration;
	unsigned long TryLevel;
	unsigned long Cookie;
	unsigned long UnwindFunc;
	unsigned long UnwindData[6];
} _JUMP_BUFFER;

#elif defined(_M_AMD64)

#ifndef _INC_SETJMPEX
#define setjmp  _setjmp
#endif

/*
 * AMD64 setjmp definitions.
 */

typedef struct __declspec(align(16)) _SETJMP_FLOAT128 {
    unsigned __int64 Part[2];
} SETJMP_FLOAT128;

#define _JBLEN  16
typedef SETJMP_FLOAT128 _JBTYPE;

typedef struct _JUMP_BUFFER {
    unsigned __int64 Frame;
    unsigned __int64 Rbx;
    unsigned __int64 Rsp;
    unsigned __int64 Rbp;
    unsigned __int64 Rsi;
    unsigned __int64 Rdi;
    unsigned __int64 R12;
    unsigned __int64 R13;
    unsigned __int64 R14;
    unsigned __int64 R15;
    unsigned __int64 Rip;
    unsigned int MxCsr;
    unsigned short FpCsr;
    unsigned short Spare;

    SETJMP_FLOAT128 Xmm6;
    SETJMP_FLOAT128 Xmm7;
    SETJMP_FLOAT128 Xmm8;
    SETJMP_FLOAT128 Xmm9;
    SETJMP_FLOAT128 Xmm10;
    SETJMP_FLOAT128 Xmm11;
    SETJMP_FLOAT128 Xmm12;
    SETJMP_FLOAT128 Xmm13;
    SETJMP_FLOAT128 Xmm14;
    SETJMP_FLOAT128 Xmm15;
} _JUMP_BUFFER;

#elif defined(_M_IA64)

/*
 * Minimum length is 528 bytes
 * Since this is allocated as an array of "SETJMP_FLOAT128", the
 * number of entries required is 33 (16-byte aligned).
 */

/* Avoid conflicts with winnt.h FLOAT128 by giving the typedef another name. */
typedef __declspec(align(16)) struct _SETJMP_FLOAT128 {
    __int64 LowPart;
    __int64 HighPart;
} SETJMP_FLOAT128;
                                  
#define _JBLEN  33
typedef SETJMP_FLOAT128 _JBTYPE;
#ifndef _INC_SETJMPEX
#define setjmp  _setjmp
#endif
/*
 * Define jump buffer layout for IA64 setjmp/longjmp.
 */

typedef struct __JUMP_BUFFER {

    /*
     * x86 reserved.
     */

    unsigned int iAReserved[6];

    /*
     * x86 C9.0 compatibility
     */

    unsigned int Registration;  /* point to the UnwindData field. */
    unsigned int TryLevel;      /* ignored by setjmp */
    unsigned int Cookie;        /* set to "VC20" by setjmp */
    unsigned int UnwindFunc;    /* set to EM longjmp() by setjmp */

    /*
     * First dword is zero to indicate it's an exception registration
     * record prepared by EM setjmp function.
     * Second dword is set to 0 for unsafe EM setjmp, and 1 for safe
     * EM setjmp.
     * Third dword is set to the setjmp site memory stack frame pointer.
     * Fourth dword is set to the setjmp site backing store frame pointer.
     */

    unsigned int UnwindData[6];

    /*
     * floating point status register,
     * and preserved floating point registers fs0 - fs19
     */

    SETJMP_FLOAT128 FltS0;
    SETJMP_FLOAT128 FltS1;
    SETJMP_FLOAT128 FltS2;
    SETJMP_FLOAT128 FltS3;
    SETJMP_FLOAT128 FltS4;
    SETJMP_FLOAT128 FltS5;
    SETJMP_FLOAT128 FltS6;
    SETJMP_FLOAT128 FltS7;
    SETJMP_FLOAT128 FltS8;
    SETJMP_FLOAT128 FltS9;
    SETJMP_FLOAT128 FltS10;
    SETJMP_FLOAT128 FltS11;
    SETJMP_FLOAT128 FltS12;
    SETJMP_FLOAT128 FltS13;
    SETJMP_FLOAT128 FltS14;
    SETJMP_FLOAT128 FltS15;
    SETJMP_FLOAT128 FltS16;
    SETJMP_FLOAT128 FltS17;
    SETJMP_FLOAT128 FltS18;
    SETJMP_FLOAT128 FltS19;

    __int64 FPSR;

    /*
     * return link and preserved branch registers bs0 - bs4
     */

    __int64 StIIP;     /* continuation address */
    __int64 BrS0;
    __int64 BrS1;
    __int64 BrS2;
    __int64 BrS3;
    __int64 BrS4;

    /*
     * preserved general registers s0 - s3, sp, nats
     */

    __int64 IntS0;
    __int64 IntS1;
    __int64 IntS2;
    __int64 IntS3;

    /*
     * bsp, pfs, unat, lc
     */

    __int64 RsBSP;
    __int64 RsPFS;     /* previous frame marker (cfm of setjmp's caller) */
    __int64 ApUNAT;    /* User Nat collection register (preserved) */
    __int64 ApLC;      /* loop counter */

    __int64 IntSp;     /* memory stack pointer */
    __int64 IntNats;   /* Nat bits of preserved integer regs s0 - s3 */
    __int64 Preds;     /* predicates */

} _JUMP_BUFFER;

#elif defined(_ALPHA_)

/*
 * Alpha implementations need a _JBLEN of 20 quadwords.
 * A double is used only to obtain quadword size and alignment.
 */

#define _JBLEN  20
#define _JBTYPE double

/*
 * Define jump buffer layout for Alpha setjmp/longjmp.
 * A double is used only to obtain quadword size and alignment.
 */

typedef struct __JUMP_BUFFER {
    unsigned long Fp;
    unsigned long Pc;
    unsigned long Seb;
    unsigned long Type;
    double FltF2;
    double FltF3;
    double FltF4;
    double FltF5;
    double FltF6;
    double FltF7;
    double FltF8;
    double FltF9;
    double IntS0;
    double IntS1;
    double IntS2;
    double IntS3;
    double IntS4;
    double IntS5;
    double IntS6;
    double IntSp;
    double Fir;
    double Fill;
} _JUMP_BUFFER;

#endif /* _M_IX86/_ALPHA_ */

/* define the buffer type for holding the state information.  We
   always leave room for the signal mask.  */

#ifndef _JMP_BUF_DEFINED
typedef  _JBTYPE  jmp_buf[_JBLEN+2];
#define _JMP_BUF_DEFINED
#endif

#ifndef _SIGJMP_BUF_DEFINED
#define _SIGJMP_BUF_DEFINED
/*
 * sigjmp buf is just a jmp_buf plus an int to say whether the sigmask
 * is saved or not, and a sigmask_t for the mask if it is saved.
 */

typedef _JBTYPE sigjmp_buf[_JBLEN + 2];
#endif /* _SIGJMP_BUF_DEFINED */

/* function prototypes */

extern int  _CRTAPI1 _setjmp(jmp_buf);   /* For some standards and _PSX_LIB */
extern void _CRTAPI1 _longjmp(jmp_buf, int);
extern int  _CRTAPI1 setjmp(jmp_buf);
extern void _CRTAPI1 longjmp(jmp_buf, int);
extern int  _CRTAPI1 sigsetjmp(sigjmp_buf, int);
extern void _CRTAPI1 siglongjmp(sigjmp_buf, int);

/*
 * Machine specific prototypes/redefinitions - Must be after the general
 * prototypes.
 */
#if defined(_M_IX86)

#ifdef _PSX_LIB

/* PSX dll must use longjmpex() since it doesn't link 
 * with the Interix libc.a
 */
extern int  _CRTAPI1 _longjmpex(jmp_buf, int);
#define setjmp _setjmp        /* This is what MSVC recognizes as special. */
#define longjmp _longjmpex

#else  /* ! _PSX_LIB */

/* The real setjmp is 'required' to be a macro; 
 * - we want it to call  _ssetjmp(). 
 */
extern int  _CRTAPI1 _ssetjmp(jmp_buf, int);  /* The real one. */
#define setjmp(x) _ssetjmp(x,1) /* And we don't want MSVC to recognize this. */

#endif /* _PSX_LIB */

#elif defined(_ALPHA_)
/*
 * _sigjmp_store_mask() is only needed on non-i386 systems (ALPHA).
 */
extern _JBTYPE * _CRTAPI1 _sigjmp_store_mask(sigjmp_buf, int);
extern int  _CRTAPI1 _ssetjmp(jmp_buf);  /* The real one. */
#define setjmp _ssetjmp
#define sigsetjmp(_env, _save)  setjmp( _sigjmp_store_mask((_env), (_save)) )

#elif defined(_M_IA64)

/*#define setjmp  _setjmp has already been done and translation of
 *longjmp to longjmpex no needed for ia64.
 *setjmp by default will now save the signal mask for ia64 hence we need to 
 *traslate any calls to sigsetjmp to setjmp.
 */
#ifndef _PSX_LIB
#define sigsetjmp(x,y) _setjmp(x)
extern void _CRTAPI1 longjmpex(jmp_buf, int);
#define longjmp siglongjmp
#endif/*!_PSX_LIB*/

#elif defined(_M_AMD64)

/*#define setjmp  _setjmp has already been done and translation of
 *longjmp to longjmpex no needed for amd64.
 *setjmp by default will now save the signal mask for amd64 hence we need to 
 *traslate any calls to sigsetjmp to setjmp.
 */
#if !defined(_PSX_LIB) || defined(__cplusplus)
#define sigsetjmp(x,y) _setjmp(x)
extern void _CRTAPI1 longjmpex(jmp_buf, int);
#define longjmp siglongjmp
#endif/*!_PSX_LIB || __cplusplus*/

#endif 


#ifdef __cplusplus
}
#endif /*_cplusplus*/

#endif  /* _SETJMP_H_ */
