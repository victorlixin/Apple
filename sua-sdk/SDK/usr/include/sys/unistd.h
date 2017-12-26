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
 *  Rcsid = $Header: 
 */

#ifndef _SYS_UNISTD_H_
#define _SYS_UNISTD_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * POSIX.1-1990 Section 4.8.1 (symbolic constants for sysconf())
 */
#define _SC_ARG_MAX		1
#define _SC_CHILD_MAX		2
#define _SC_CLK_TCK		3
#define _SC_NGROUPS_MAX		4
#define _SC_OPEN_MAX		5
#define _SC_JOB_CONTROL		6
#define _SC_SAVED_IDS		7
#define _SC_STREAM_MAX		8
#define _SC_TZNAME_MAX		9
#define _SC_VERSION		10
/*
 * additional constants - from POSIX.2-1992 extensions: B.10.2 Table B-19
 */
#define _SC_BC_BASE_MAX		11
#define _SC_BC_DIM_MAX		12
#define _SC_BC_SCALE_MAX	13
#define _SC_BC_STRING_MAX	14
#define _SC_COLL_WEIGHTS_MAX	15
#define _SC_EXPR_NEST_MAX	16
#define _SC_LINE_MAX		17
#define _SC_RE_DUP_MAX		18
#define _SC_2_VERSION		19
#define _SC_2_C_DEV		20
#define _SC_2_C_BIND		21
#define _SC_2_CHAR_TERM		22
#define _SC_2_FORT_DEV		23
#define _SC_2_FORT_RUN		24
#define _SC_2_LOCALEDEF		25
#define _SC_2_SW_DEV		26
#define _SC_2_UPE		27

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)
/* XPG4_UNIX extensions */
#  define _SC_PAGE_SIZE         28
#  define _SC_PAGESIZE          _SC_PAGE_SIZE
#  define _SC_ATEXIT_MAX	29
#  define _SC_IOV_MAX	        30
#  define _SC_XOPEN_UNIX	31
				/* room for expansion */
/* XPG4 extensions */
#define _SC_PASS_MAX		40
#define _SC_XOPEN_CRYPT		41
#define _SC_XOPEN_ENH_I18N	42
#define _SC_XOPEN_SHM		43
#define _SC_XOPEN_VERSION	44
#endif /*defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE)*/

#define _SC_2_C_VERSION	45

#define _SC_SEMAPHORES          490
#define _SC_SEM_NSEMS_MAX       491
#define _SC_SEM_VALUE_MAX       492

/* symbolic constants for sysconf() for pthreads */
#define _SC_THREADS             501
#define _SC_THREAD_ATTR_STACKSIZE       502
#define _SC_THREAD_ATTR_STACKADDR       503
#define _SC_THREAD_PRIORITY_SCHEDULING  504
#define _SC_THREAD_SAFE_FUNCTIONS       505
#define _SC_THREAD_KEYS_MAX	506
#define _SC_THREAD_THREADS_MAX	507
#define _SC_THREAD_STACK_MIN	508
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 509

#define _SC_SPIN_LOCKS          601
#define _SC_READER_WRITER_LOCKS 602  

/* symbolic constants for sysconf() for Re-entrant functions*/
#define _SC_TTY_NAME_MAX        611
#define _SC_LOGIN_NAME_MAX      612
#define _SC_GETPW_R_SIZE_MAX    613
#define _SC_GETGR_R_SIZE_MAX    614

/* Symbolic constants for sysconf() for data type models */
#define _SC_XBS5_ILP32_OFF32  621 /* 32-bit int, long, pointer and off_t */
#define _SC_XBS5_ILP32_OFFBIG 622 /* 32-bit int, long, pointer, and 64-bit off_t */
#define _SC_XBS5_LP64_OFF64   623 /* 32-bit int, 64-bit long, pointer, off_t*/
#define _SC_XBS5_LPBIG_OFFBIG 624 /* at least 32-bit int, at least 64-bit long, pointer, off_t */

// don't change the sequence
#define _CS_XBS5_ILP32_OFF32_CFLAGS 		631
#define _CS_XBS5_ILP32_OFF32_LDFLAGS 		632
#define _CS_XBS5_ILP32_OFF32_LIBS 			633
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS 	634
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS 		635
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS 	636
#define _CS_XBS5_ILP32_OFFBIG_LIBS 		637
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS 	638
#define _CS_XBS5_LP64_OFF64_CFLAGS 		639
#define _CS_XBS5_LP64_OFF64_LDFLAGS 		640
#define _CS_XBS5_LP64_OFF64_LIBS 			641
#define _CS_XBS5_LP64_OFF64_LINTFLAGS 	642
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS 		643
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS 	644
#define _CS_XBS5_LPBIG_OFFBIG_LIBS 		645
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS 	646
#ifdef __cplusplus
}
#endif

#endif /* _SYS_UNISTD_ */
