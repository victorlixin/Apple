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
 *  RCSID = $Header: /E/interix/include/signal.h,v 1.30 1999/06/14 15:17:19 jamesp Exp $
 *
 */ 

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <features.h>

#include <sys/types.h>	/* for pid_t */

#if (defined(_PSX_KERNEL) && defined(_WIN64))
#define ulong size_t
#define long ssize_t
#else
#define ulong unsigned long
#endif/*(defined(_PSX_KERNEL) && defined(_WIN64))*/

#ifdef __cplusplus
extern "C" {
#endif

typedef int sig_atomic_t;
typedef u_int32_t sigset_t;
typedef void (_CRTAPI1 * sighandler_t)(int);
typedef sighandler_t _handler;	 /* backward compatability with MS headers */

#define SIG_ERR  ((sighandler_t) -1)           /* signal error value */
#define SIG_DFL  ((sighandler_t)  0)           /* default signal action */
#define SIG_IGN  ((sighandler_t)  1)           /* ignore signal */
#define SIG_HOLD ((sighandler_t)  2)           /* hold signal */

/*
 * Historic signals, from V7 Unix.
 * Names and numbers conform to V7, SysV, BSD, Posix, SUS.
 * (Posix and SUS do not require SIGEMT.)
 */
#define SIGHUP	1
#define SIGINT	2
#define SIGQUIT	3
#define SIGILL	4
#define SIGTRAP	5
#define SIGABRT	6
#define SIGEXCEPT 7	/* unclassified NT exception--historically SIGEMT */
#define SIGFPE	8
#define SIGKILL	9
#define SIGBUS	10
#define SIGSEGV	11
#define SIGSYS	12
#define SIGPIPE	13
#define SIGALRM	14
#define SIGTERM	15

/*
 * Modern signals--all are required by Posix and SUS,
 * except SIGWINCH, which conforms to SysV and BSD.
 * Names and numbers conform to SysV (except SIGIO--SysV has SIGPWR instead).
 * BSD has different numbering, lacks SIGPOLL, has SIGINFO.
 */
#define SIGUSR1	16
#define SIGUSR2	17
#define SIGCHLD	18
#define SIGIO	19
#define SIGWINCH 20
#define SIGURG	21
#define SIGPOLL	22
#define SIGSTOP	23
#define SIGTSTP	24
#define SIGCONT	25
#define SIGTTIN	26
#define SIGTTOU	27
#define SIGVTALRM 28
#define SIGPROF	29
#define SIGXCPU	30
#define SIGXFSZ	31
#define SIGCANCEL 32

/*  NSIG - valid signals are from 1 to NSIG-1 */
#undef NSIG
#define NSIG 33	    


/*
 *  Other signal names - for compatibility with other UNIX's only
 */
#define SIGIOT  SIGABRT /* old signal for PDP11/VAX I/O trap instruction */
#define SIGCLD  SIGCHLD /* old signal for death of child */



struct sigaction {
    sighandler_t sa_handler;
    sigset_t sa_mask;
    int sa_flags;
	    /* protect the non-std, non-reserved struct member
	     * from any unexpected expansion
	     */
	    #undef _reserved_for_sa_sigaction
    void (*_reserved_for_sa_sigaction)();
};

/*
 * flags for sigaction's sa_flags
 */
#define SA_NOCLDSTOP 0x00000001
#define SA_RESTART   0x00000002
#define SA_RESETHAND   0x00000004

/*
 * values for 'how' argument in sigprocmask()
 */
#define SIG_BLOCK    1
#define SIG_UNBLOCK  2
#define SIG_SETMASK  3


int _CRTAPI1 kill(pid_t, int signo);
int _CRTAPI1 pthread_kill(pthread_t, int);
int _CRTAPI1 pthread_sigmask(int, const sigset_t *, sigset_t *);
int _CRTAPI1 raise(int signo);
int _CRTAPI1 sigaction(int, const struct sigaction *, struct sigaction *);
int _CRTAPI1 sigaddset(sigset_t *, int signo);
int _CRTAPI1 sigdelset(sigset_t *, int signo);
int _CRTAPI1 sigemptyset(sigset_t *);
int _CRTAPI1 sigfillset(sigset_t *);
int _CRTAPI1 sigismember(const sigset_t *, int signo);
int _CRTAPI1 sigpending(sigset_t *);
int _CRTAPI1 sigprocmask(int how, const sigset_t *, sigset_t *);
int _CRTAPI1 sigsuspend(const sigset_t *);
int _CRTAPI1 sigwait(const sigset_t *, int*);

sighandler_t _CRTAPI1 signal(int signo, sighandler_t);


#if defined(_ALL_SOURCE) \
        || (defined(_XOPEN_SOURCE)&&(_XOPEN_SOURCE_EXTENDED==1))
/*
 * XPG4 (and SVID2) routines
 */
int _CRTAPI1 sighold(int signo);
int _CRTAPI1 sigignore(int signo);
int _CRTAPI1 sigpause(int signo);
int _CRTAPI1 sigrelse(int signo);
sighandler_t _CRTAPI1 sigset(int signo, sighandler_t);

int _CRTAPI1 killpg(pid_t pgid, int sig);

typedef struct {
    void * ss_sp;
    size_t ss_size;
    int    ss_flags;
} stack_t;


/*
 * Values for si_code member of siginfo_t.
 * These are reasons why a signal was delivered.
 *
 * If a process takes an NT exception, the exception is mapped
 * to a signal, as indicated by comments below.
 * Codes marked "Interix" are Interix extensions.
 */

/* if si_code <= 0, si_pid and si_uid describe the sending process */
#define SIFROMUSER(sip)		((sip)->si_code <=0) 
#define SIFROMKERNEL(sip)	((sip)->si_code >0) 

#define SI_USER		0	/* kill() */
#if 0
/* Solaris codes that we don't support yet. */
#define SI_QUEUE	(-2)	/* sigqueue() */
#define SI_TIMER	(-3)	/* timer expiration */
#define SI_ASYNCIO	(-4)	/* async i/o completion */
#define SI_MESGQ	(-5)	/* message arrival */
#endif /* 0 - Solaris */

#define SI_TTY		1000	/* Interix: from the tty driver */
#define SI_SERVICE	1001	/* Interix: from the service manager */
#define SI_ORPHANED	1002	/* Interix: pgrp orphaned with stopped procs */

/* for these codes, si_addr is address of faulting instruction */
#define ILL_ILLOPC	1	/* STATUS_ILLEGAL_INSTRUCTION */
#define ILL_ILLOPN	2
#define ILL_ILLADR	3
#define ILL_ILLTRP	4
#define ILL_PRVOPC	6	/* STATUS_PRIVILEGED_INSTRUCTION */
#define ILL_PRVREG	7
#define ILL_COPROC	8
#define ILL_BADSTK	9

/* for these codes, si_addr is address of faulting instruction */
#define FPE_INTDIV	1	/* STATUS_INTEGER_DIVIDE_BY_ZERO */
#define FPE_INTOVF	2	/* STATUS_INTEGER_OVERFLOW */
#define FPE_FLTDIV	3	/* STATUS_FLOAT_DIVIDE_BY_ZERO */
#define FPE_FLTOVF	4	/* STATUS_FLOAT_OVERFLOW */
#define FPE_FLTUND	5	/* STATUS_FLOAT_UNDERFLOW */
#define FPE_FLTRES	6	/* STATUS_FLOAT_INEXACT_RESULT */
#define FPE_FLTINV	7	/* STATUS_FLOAT_INVALID_OPERATION */
#define FPE_FLTSUB	8	/* STATUS_ARRAY_BOUNDS_EXCEEDED */
#define FPE_FLTDEN	9	/* Interix: STATUS_FLOAT_DENORMAL_OPERAND */
#define FPE_FLTSTK	10	/* Interix: STATUS_FLOAT_STACK_CHECK */

/* for these codes, si_addr is address of faulting memory reference */
#define SEGV_MAPERR	1
#define SEGV_ACCERR	2	/* STATUS_ACCESS_VIOLATION */

/* for these codes, si_addr is address of faulting memory reference */
#define BUS_ADRALN	1	/* STATUS_DATATYPE_MISALIGNMENT */
#define BUS_ADRERR	2
#define BUS_OBJERR	3

#define TRAP_BRKPT	1	/* STATUS_BREAKPOINT */
#define TRAP_TRACE	2	/* STATUS_SINGLE_STEP */

/* for these codes, u.exc.code is an NT status code */
#define EXCEPT_EXCEPT	1	/* Interix: unclassified NT exception */
#define EXCEPT_HARDERR	2	/* Interix: NT hard error */

#define KILL_INITFAIL	1	/* Interix: process initialization failure */

/* for these codes, si_pid, si_status, si_uid are defined */
#define CLD_EXITED	1
#define CLD_KILLED	2
#define CLD_DUMPED	3
#define CLD_TRAPPED	4
#define CLD_STOPPED	5
#define CLD_CONTINUED	6

/* for POLL_{IN,OUT,MSG}, si_band is the band event */
#define POLL_IN		1
#define POLL_OUT	2
#define POLL_MSG	3
#define POLL_ERR	4
#define POLL_PRI	5
#define POLL_HUP	6

#define HUP_MODEM	1	/* Interix: modem disconnect */
#define HUP_TSTP	2	/* Interix: TSTP, TTIN or TTOU sent to orphan */

#define _SIGINFO_ARGC_MAX 15
typedef struct siginfo {
    int 	si_signo;
    int 	si_errno;
    int 	si_code;
    union {
	struct {
	    pid_t   __pid;
	    uid_t   __uid;
	    int	    __status;
	    u_int64_t __uid64;
	} __proc;
	struct {
	    long    __band;
	} __file;
	struct {
	    void *  __addr;
	    void *  __pc;
		/* Address of faulting instruction.
		 * For an NT exception, this is ExceptionAddress.
		 * For an NT hard error, this is unused. */
	    unsigned __firstchance;
		/* For an NT exception, this is the FirstChance flag.
		 * For an NT hard error, this is unused. */
	    unsigned __status;
		/* An NT status code describing the fault.
		 * For an NT exception, this is ExceptionCode.
		 * For an NT hard error, this is Status. */
	    unsigned __flags;
		/* For an NT exception, this is ExceptionFlags.
		 * For an NT hard error, this is UnicodeStringParameterMask. */
	    int __argc;
	    ulong __argv[_SIGINFO_ARGC_MAX];
	    /*
	      * For synchronous signals, this is thread id for which
	      * the signal is generated
	      */
	    int32_t __threadId;
		/* For an NT exception, this is ExceptionInformation.
		 * For an NT hard error, this is Parameters. */
	    long __reserved_space[5];
	} __fault;
    } __data;
} siginfo_t;

#define si_addr	    __data.__fault.__addr
#define si_pc	    __data.__fault.__pc
#define	si_band	    __data.__file.__band
#define	si_pid	    __data.__proc.__pid
#define si_status   __data.__proc.__status
#define	si_uid	    __data.__proc.__uid
#define	si_uid64    __data.__proc.__uid64
#endif /* (defined(_XOPEN_SOURCE)&&(_XOPEN_SOURCE_EXTENDED==1)) || ... */


#if defined (_ALL_SOURCE)

/* valid signals from 1..MAXSIG :  MAXSIG is from SVR4 systems */
#define MAXSIG  NSIG-1

#if !defined (_IMPORT_LIBCDLL_GLOBALS)
extern const char * const _sys_siglist[];
extern const char * const _sys_signame[];
extern const int _sys_nsig;
#else
#include <globalexport.h>
#define _sys_siglist ((char**)libc_global(G_SYS_SIGLIST))
#define _sys_signame ((char**)libc_global(G_SYS_SIGNAME))
#define _sys_nsig ((int)libc_global(G_SYS_NSIG))
#endif

/* sigaction handler is called sighandler_t on Interix, sig_t on BSD */
typedef sighandler_t sig_t;

/*
 * BSD signal.h has a synonym for SIG_ERR
 */
#define BADSIG SIG_ERR

/*
 * BSD4.3 compatibility 
 *   - define struct sigvec to be same as struct sigaction
 *   - assumes signal mask fits into an 'int'
 *   -  so NSIG-1 should be <= 32
 */
#if NSIG > 33
#pragma message ("ERROR: cannot support BSD43 compatability mode")
#endif

/*
 * Macro for converting signal number to a mask suitable for sigblock().
 * For BSD backward compatability.
 * This only works as long as sigset_t is the same size as an 'int'
 */
int sigmask(int sig);
#define sigmask(m)    ( 1 <<  ((m)-1) )

struct sigvec {
    sighandler_t sa_handler;
    int sa_mask;
    int sa_flags;
    void (*reserved_for_sa_sigaction)();
};

int _CRTAPI1 sigblock(int mask);
int _CRTAPI1 sigsetmask(int mask);
int _CRTAPI1 sigvec(int signo, struct sigvec *sv, struct sigvec *osv);
/* sigpause() - BSD version NOT supported - conflict with XPG4 version */


#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#undef ulong
#if (defined(_PSX_KERNEL) && defined(_WIN64))
#undef long
#endif/*(defined(_PSX_KERNEL) && defined(_WIN64))*/

#endif /* _SIGNAL_H_ */
