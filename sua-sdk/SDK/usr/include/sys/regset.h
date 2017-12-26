/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is the unpublished, valuable, confidential property
 * of Microsoft Corporation.  Use is authorised only under the terms and
 * conditions set out in the source code licence agreement protecting this
 * Software Source.  Any unauthorised use or disclosure of this Software 
 * Source is prohibited.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' BY MICROSOFT CORPORATION AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 *
 * RCSid = $Header: /E/interix/include/sys/regset.h,v 1.8 1999/03/19 16:04:41 dmoen Exp $
 *
 */ 

#ifndef _SYS_REGSET_H_
#define _SYS_REGSET_H_

#if defined(__cplusplus)
extern "C" {
#endif


#include <features.h>
#include <sys/types.h>

/*
 * gregset_t, fpregset_t and mcontext_t
 * are all isomorphic to the NT CONTEXT structure.
 */

typedef struct {
    u_int64_t LowPart;
    u_int64_t HighPart;
} float128;


#ifdef _M_ALPHA
typedef struct {
    u_quad_t	 fpregs[32];	/* floating point registers */
    u_quad_t	 gregs[32];	/* general registers */
    u_quad_t	 fpcr;		/* floating point control register */
    u_quad_t	 softfpcr;	/* software extension to FPCR */
    u_quad_t	 fir;		/* fault instruction continuation address */
    unsigned int psr;		/* processor status */
    unsigned int reserved[5];
} gregset_t;
#endif /* _M_ALPHA */

#ifdef _M_IX86
typedef struct {
    unsigned reserved[7];
    struct {
	unsigned int  control;
	unsigned int  status;
	unsigned int  tag;
	unsigned int  erroroffset;
	unsigned int  errorselector;
	unsigned int  dataoffset;
	unsigned int  dataselector;
	unsigned int  fpregs[20];
	unsigned int  cr0npxstate;
    } fpstate;
    unsigned gregs[16];
    char extended[512];
} gregset_t;
#elif defined(_M_IA64)
typedef struct {
	unsigned int reserved[4];
	u_int64_t    debug[16];
	float128     lowFloat[14];
	float128     highFloat[112];
	u_int64_t    FPStatus;
	u_int64_t    IntRegL[11];
	u_int64_t    IntSp;
	u_int64_t    IntRegM[20];
	u_int64_t    Preds;
	u_int64_t    BrRp;
	u_int64_t    IntRegH[7];
	u_int64_t    AppReg[5];
	u_int64_t    RsPFS;
	u_int64_t    RsBSP;
	u_int64_t    StackRegH[3];
	u_int64_t    StatusReg[3];
	u_int64_t    IA32Reg[8];
	u_int64_t    pack;
} gregset_t;
#elif defined(_M_AMD64)
typedef struct {
	u_int64_t      reserved[7];
	unsigned short segment[6];
	unsigned int   eflags;
	u_int64_t      debug[6];
	u_int64_t      IntRegL[4];
	u_int64_t      Rsp;
	u_int64_t      IntRegH[11];
	u_int64_t      Rip;
	union {
		struct {
			unsigned short control;
			unsigned short status;
			unsigned char  tag;
			unsigned char  reserved1;
			unsigned short errorOpcode;
			unsigned int   errorOffset;
			unsigned short errorSelector;
			unsigned short reserved2;
			unsigned int   dataOffset;
			unsigned short dataSelector;
			unsigned short reserved3;
			unsigned int   MxCsr;
			unsigned int   MxCsr_mask;
			float128       floatReg[8];
			float128       xmmReg[16];
			unsigned char  reserved4[96];
		}fltsave;
		float128 fpstate[26];
	}fltstatus;
	float128  vectorReg[26];
	u_int64_t vectorControl;
	u_int64_t debugControl[5];
} gregset_t;

#endif

typedef gregset_t fpregset_t;

typedef union {
    gregset_t gregs;
    fpregset_t fpregs;
} mcontext_t;


#if defined(__cplusplus)
}
#endif

#endif /* _SYS_REGSET_H_ */
