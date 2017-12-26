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
 * RCSid = $Header: /E/interix/include/sys/reg.h,v 1.5 1998/09/17 19:36:34 SSI_DEV+mark Exp $
 *
 */ 

#ifndef _SYS_REG_H_
#define _SYS_REG_H_

#if defined(__cplusplus)
extern "C" {
#endif


#ifdef _M_IX86
/*
 * General register names for the I386
 */
#define GS	0
#define FS	1
#define ES	2
#define DS	3

#define EDI	4
#define ESI	5
#define EBX	6
#define EDX	7
#define ECX	8
#define EAX	9

#define EBP	10
#define EIP	11
#define CS	12
#define EFL	13
#define UESP	14
#define SS	15
#endif /* _M_IX86 */

#ifdef _M_ALPHA
/*
 * General register names for the Alpha
 */
#define REG_V0	0	/* return value */
#define REG_T0	1	/* temporary register 0 */
#define REG_T1	2
#define REG_T2	3
#define REG_T3	4
#define REG_T4	5
#define REG_T5	6
#define REG_T6	7
#define REG_T7	8
#define REG_S0	9	/* non-volatile register 0 */
#define REG_S1	10
#define REG_S2	11
#define REG_S3	12
#define REG_S4	13
#define REG_S5	14
#define REG_FP	15	/* frame pointer */
#define REG_A0	16	/* argument register 0 */
#define REG_A1	17
#define REG_A2	18
#define REG_A3	19
#define REG_A4	20
#define REG_A5	21
#define REG_T8	22
#define REG_T9	23
#define REG_T10	24
#define REG_T11	25
#define REG_RA	26	/* return address */
#define REG_T12	27
#define REG_AT	28	/* assembler temp */
#define REG_GP	29	/* global pointer */
#define REG_SP	30	/* stack pointer */
#define REG_ZERO 31	/* zero register */
#endif /* _M_ALPHA */


#if defined(__cplusplus)
}
#endif

#endif /* _SYS_REG_H_ */
