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
 * RCSid = $Header: /E/interix/include/sys/procfs.h,v 1.16 2000/03/27 20:27:21 jamespar Exp $
 */ 

#ifndef _SYS_PROCFS_H
#define _SYS_PROCFS_H


#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>

#include <signal.h>		/* siginfo_t, sigset_t, struct sigaction */
#include <ucontext.h>		/* ucontext_t */

#if (defined(_PSX_KERNEL) && defined(_WIN64))
#define ulong size_t
#define long ssize_t
#else
#define ulong unsigned long
#endif/*(defined(_PSX_KERNEL) && defined(_WIN64))*/

#define _UINT_BITS	(8*sizeof(u_int32_t))
#define __prinrange(set,i) ((unsigned)((i)-1) < 8 * sizeof(*(set)))
#define __prword(set,i)    ((u_int32_t*)(set))[((i)-1)/_UINT_BITS]
#define __prmask(i)        ((u_int32_t)1 << (((i)-1)%_UINT_BITS))
#define prfillset(x)    {int __t; \
                         for (__t=0;__t<sizeof(*(x))/sizeof(u_int32_t);__t++) \
			 ((u_int32_t *)(x))[__t]=-1; }
#define premptyset(x)   {int __t; \
                         for (__t=0;__t<sizeof(*(x))/sizeof(u_int32_t);__t++) \
			 ((u_int32_t *)(x))[__t]=0; }
#define praddset(set,i) \
	(__prinrange(set,i) ? (__prword(set,i) |= __prmask(i)) : 0)
#define prdelset(set,i)   \
	(__prinrange(set,i) ? (__prword(set,i) &= ~__prmask(i)) : 0)
#define prismember(set,i)   \
	(__prinrange(set,i) ? (__prword(set,i) & __prmask(i)) : 0)

typedef struct {
    ulong bits[16];
} sysset_t;

typedef ulong fltset_t;

/* values for pr_why in lwpstatus_t */
#define PR_SIGNALLED 	1
#define PR_SYSENTRY 	2
#define PR_SYSEXIT 	3
#define PR_REQUESTED 	4
#define PR_JOBCONTROL 	5
#define PR_FAULTED 	6

/*
 * The following values are for the pr_state field of pstatus_t.
 * These values are unsupported: they may change from one release
 * of Interix to the next.
 */
#define PR_Free		0
#define PR_Initializing	1
#define PR_Unconnected	2
#define PR_Active	3
#define PR_Stopped	4
#define PR_Waiting	5
#define PR_Tty		6
#define PR_Forking    7
#define PR_Execing	8
#define PR_Exiting	9
#define PR_Exited	10

/*
 * Process flags appear in pr_flags for both lwpstatus_t and pstatus_t;
 * some also used as args to PCSET and PCRESET commands.
 * The following flags are stored in the process table directly.
 * Other than PR_STEP, PR_FORK, PR_RLC, PR_KLC, PR_ASYNC, these flags
 * are unsupported: they may change from one release to the next.
 */

/* PR_NO_EXIT_ON_PARENT_OR_CHILD : 
 *    This flag is added to make Exit()/SafeToProcessExit() non-recursive, 
 *    when the underlying nt process for a chain of vfork processes got killed 
 *    from task manager (outside Interix).
 */
#define PR_NO_EXIT_ON_PARENT_OR_CHILD 0x00001 

#define PR_EXECED   0x00002	/* P_HAS_EXECED: process has execed */
#define PR_FOREIGN  0x00004	/* P_FOREIGN_EXEC: is a win32 process */
#define PR_ISTOP    0x00008	/* P_STOPPED: stopped by debugger */
#define PR_WAITED   0x00010	/* P_WAITED: process has been waited on */
#define PR_PGRP	    0x00020	/* P_PGRP_RESERVED: slot in use by pgrp */
#define PR_ASUSER   0x00040	/* P_ASUSER: ancestor called exec_asuser */
#define PR_STEP	    0x00080	/* single-step directive in effect */
#define PR_FORK	    0x00100	/* inherit trace flags on fork */
#define PR_RLC	    0x00200	/* run on last close (of a /proc fd) */
#define PR_KLC	    0x00400	/* kill on last close (of a /proc fd) */
#define PR_ASYNC    0x00800	/* asynchronous stop (debugging) */
#define PR_TOAST    0x01000	/* process is toast--current signal is fatal */
#define PR_SIGRPC   0x02000	/* signal delivery RPC in progress */
#define PR_DBGINIT  0x04000	/* process has debug port, is starting up */
#define PR_VFORKP   0x08000	/* process is a vfork parent */
#define PR_VFORKC   0x10000	/* process is a vfork child */
#define PR_VFORKS   0x20000	/* vfork process temp signal pause */
#define PR_SETID    0x40000	/* set[ug]id process, can't dump core */
#define PR_SAFE_EXIT 0x80000    /* process has entered safe exit */
#define PR_MIXMODE  0x100000	/* process is a mixed mode process */
#define PR_32_BIT   0x200000	/* 32-bit process */
#define PR_GCC_BINARY 0x400000  /* binary of the process was built by gcc */
#define PR_SU_NOPASS  0x800000  /* root has called setuser/setuid */
#define PR_TOKEN_SWAP 0x1000000 /* primary token swapped from hi-priv to lo-priv */
/*
 * The following flags are emulated by the /proc interface,
 * for compatibility for System V code:
 */
#define PR_ASLEEP   0x40000000	/* in an interruptible sleep, in a sys call */
#define PR_STOPPED  0x80000000	/* process is stopped */

#if 0
/*  gdb will decode the values below, if they are present, but doesn't
    otherwise require them */
#define PR_DSTOP    0x0020
#define PR_PTRACE   0x0080
#define PR_PCINVAL  0x0100
#define PR_ISSYS    0x0200
#define PR_PCOMPAT  0x1000
#endif /* 0 */

#define PRSYSARGS	16		/* max # of system call arguments */

typedef struct lwpstatus {
    long		pr_flags;	/* see above for bits */
    short		pr_why;		/* see above for values */
    short		pr_what;	/* ordinal of some sort; see pr_why */
    siginfo_t		pr_info;	
    short		pr_cursig;	/* signal about to be delivered */
    struct sigaction	pr_action;	/* action for pr_cursig */
    sigset_t		pr_lwppend;	/* set of signals pending to the lwp */
    int			pr_syscall;	/* current system call, or 0 */
    long		pr_sysarg[PRSYSARGS]; /* system call arguments */
    long		pr_result;	/* system call result */
    int			pr_errno;	/* system call result */
    ucontext_t		pr_context;	/* context (registers, et. al.) */
    int	                pr_lwpid;       /* specific lwp identifier */
    long		__reserved_space[15];
} lwpstatus_t;

typedef	struct {
    pid_t	 pr_pid;		/* process PID */
    pid_t	 pr_ppid;		/* parent process */
    pid_t	 pr_pgid;
    pid_t	 pr_sid;
    long	 pr_flags;		/* see above for values */
    sigset_t	 pr_sigtrace;		/* signals being traced */
    fltset_t	 pr_flttrace;		/* faults being traced;
					   ordinals in sys/fault.h */
    sysset_t	 pr_sysentry;		/* calls being traced */
    sysset_t	 pr_sysexit;		/* calls being traced (on exit) */
    sigset_t	 pr_sigpend;		/* (All) pending signals */
    lwpstatus_t	 pr_lwp;

    int		 pr_state;
    void *	 pr_signaldeliverer;
    void *	 pr_endsignaldeliverer;
    void *	 pr_nullapi;
    void *	 pr_endnullapi;
    int		 pr_inpsx;
    size_t pr_memremotedelta;
    long	 pr_natpid;
    long	 pr_natsid;
    unsigned int pr_openfdcount;
    int 	 pr_nlwp;  		/* number of lwps in the process */
    long	 __reserved_space[11];
} pstatus_t;

#define PRFNSZ		16
#define PRARGSZ		80

typedef quad_t timestruc_t;

typedef struct {
    void *	pr_wchan;
    signed char	pr_nice;
} lwpsinfo_t;

typedef struct {
    unsigned	pr_flag;		/* process flags */
    unsigned	pr_state;		/* process state */
    unsigned	pr_nlwp;		/* number of LWPs in process */
    pid_t	pr_pid;			/* process id */
    pid_t	pr_ppid;		/* parent process id */
    pid_t	pr_pgid;		/* process group id */
    pid_t       pr_natpid;		/* native PID */
    pid_t	pr_sid;			/* session id */
    pid_t	pr_natsid;		/* native sid */
    uid_t	pr_uid;			/* real user id */
    uid_t	pr_euid;		/* effective user id */
    uid_t	pr_suid;		/* saved user id */
    gid_t	pr_gid;			/* real group id */
    gid_t	pr_egid;		/* effective group id */
    gid_t	pr_sgid;		/* saved group id */
    size_t      pr_size;		/* size (Kb) */
    size_t      pr_rssize;		/* resident set size (Kb) */
    dev_t	pr_ttydev;		/* Controlling TTY */
    time_t      pr_start;		/* process start time */
    timestruc_t pr_time;		/* process cpu */
    timestruc_t pr_ctime;		/* kid's cpu */
    char	pr_fname[PRFNSZ];	/* last component of image pathname */
    char	pr_psargs[PRARGSZ];	/* truncated command line */
    int		pr_wstat;
    lwpsinfo_t  pr_lwp;
    u_int64_t	pr_uid64;		/* real user id */
    u_int64_t	pr_euid64;		/* effective user id */
    u_int64_t	pr_suid64;		/* saved user id */
    u_int64_t	pr_gid64;		/* real group id */
    u_int64_t	pr_egid64;		/* effective group id */
    u_int64_t	pr_sgid64;		/* saved group id */
    unsigned int pr_openfdcount;
    char	__reserved_space[512-52];
} psinfo_t;

#define PROC_CTL_WORD_TYPE int64_t

/* command words  to the control file */
#define PCSTOP 		 1      /* no args */
#define PCWSTOP 	 2      /* no args */
#define PCRUN 		 3      /* ulong, flags below */
#define PCSTRACE 	 4      /* sigset_t */
#define PCSSIG 		 5      /* siginfo_t */
#define PCKILL		 6      /* int (signal number) */
#define PCSFAULT	 7      /* fltset_t */
#define PCCFAULT         8      /* no arg */
#define PCSEXIT          9      /* sigset_t */
#define PCSENTRY        10      /* sigset_t */
#define PCSET		11      /* ulong, flags same as for pr_flags */
#define PCRESET		12      /* ulong, flags same as for pr_flags */
#define PCSREG 		13	/* gregset_t */
#define PCSFPREG 	14      /* fpregset_t */

/* possible values used by the flag word to PCRUN */
#define PRSTEP   	0x01
#define PRCFAULT 	0x02
#define PRCSIG   	0x04

/* values for pr_mflags */
#define MA_PHYS		0x01 /* self-conditional */
#define MA_STACK	0x02 
#define MA_BREAK	0x04 
#define MA_SHARED	0x08 
#define MA_READ		0x10 
#define MA_WRITE	0x20 
#define MA_EXEC		0x40 

#define PR_MAP_SIZE 32
typedef struct prmap {
    ulong pr_size;
    off_t   pr_off;
    void *  pr_vaddr;
    long    pr_mflags;
    char    pr_mapname[PR_MAP_SIZE];
    /*
     * The following members are from the MEMORY_BASIC_INFORMATION
     * structure, as filled in by the Win32 VirtualQuery() function.
     */
    void *  AllocationBase;
    ulong   AllocationProtect;
    ulong   State;
    ulong   Protect;
    ulong   Type;
} prmap_t;

#undef ulong
#if (defined(_PSX_KERNEL) && defined(_WIN64))
#undef long
#endif/*(defined(_PSX_KERNEL) && defined(_WIN64))*/

#if defined(__cplusplus)
}
#endif

#endif /* _SYS_PROCFS_H */
