/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */ 

#ifndef _SYS_SYSCALL_H_
#define _SYS_SYSCALL_H_
#ifdef __cplusplus 
extern "C" { 
#endif 
#include <sys/types.h>

extern ssize_t _CRTAPI1
syscall(int, ...);

#if 0	/*obsolete - replaced by SYS_prefork and SYS_postfork*/
#define SYS_fork			1
#endif
#define SYS_exec			2
#define SYS_waitpid			3
#define SYS_exit			4
#define SYS_kill			5
#define SYS_sigaction			6
#define SYS_sigprocmask			7
#define SYS_sigpending			8
#define SYS_sigsuspend			9
#define SYS_alarm			10
#define SYS_getids			11
/*Reusing already obsolete slots for pre and post fork api's*/
#define SYS_prefork			12
#define SYS_postfork			13
#if 0	/* obsolete - replaced by SYS_setids. */
#define SYS_setuid			12
#define SYS_setgid			13
#endif /* 0 */
#define SYS_getgroups			14
#define SYS_getdata			15
#if 0	/* obsolete slot; superceded call */
#define SYS_getlogin			15
	/* obsolete slot; handled in user mode */
#define SYS_cuserid			16
#endif /* 0 */
#define SYS_setsid			17
#define SYS_setpgid			18
#if 0	/* obsolete slots; handled in user mode */
#define SYS_uname			19
#define SYS_time			20
#endif
#define SYS_times			21
#define SYS_ttyname			22
#define SYS_isatty			23
#define SYS_sysconf			24
#define SYS_open			25
#define SYS_umask			26
#define SYS_link			27
#define SYS_mkdir			28
#define SYS_mkfifo			29
#define SYS_rmdir			30
#define SYS_rename			31
#define SYS_stat			32
#define SYS_fstat			33
#define SYS_access			34
#define SYS_chmod			35
#define SYS_chown			36
#define SYS_utime			37
#define SYS_remove			38
#define SYS_fpathconf			39
#define SYS_pipe			40
#define SYS_dup				41
#define SYS_dup2			42
#define SYS_close			43
#define SYS_read			44
#define SYS_write			45
#define SYS_fcntl			46
#define SYS_lseek			47
#define SYS_tcgetattr			48
#define SYS_tcsetattr			49
#define SYS_tcsendbreak			50
#define SYS_tcdrain			51
#define SYS_tcflush			52
#define SYS_tcflow			53
#define SYS_tcgetpgrp			54
#define SYS_tcsetpgrp			55
#define SYS_getpwuid			56
#define SYS_getpwnam			57
#define SYS_getgrgid			58
#define SYS_getgrnam			59
#define SYS_unlink			60
#define SYS_readdir			61
#define SYS_ftruncate			62
#define SYS_chdir			63
#define SYS_getcwd			64
#define SYS_null			65
#define SYS_semctl			66
#define SYS_semget			67
#define SYS_semop			68
#define SYS_shmat			69
#define SYS_shmctl			70
#define SYS_shmdt			71
#define SYS_shmget			72
#define SYS_msgctl			73
#define SYS_msgget			74
#define SYS_msgrcv			75
#define SYS_msgsnd			76
#define SYS_socket			77
#define SYS_accept			78
#define SYS_bind			79
#define SYS_connect			80
#define SYS_getpeername			81
#define SYS_getsockname			82
#define SYS_getsockopt			83
#define SYS_listen			84
#define SYS_recv			85
#define SYS_recvfrom			86
#define SYS_send			87
#define SYS_sendto			88
#define SYS_setsockopt			89
#define SYS_shutdown			90
#define SYS_gethostbyname		91
#define SYS_gethostbyaddr		92
#define SYS_getprotobyname		93
#define SYS_getprotobynumber		94
#define SYS_getservbyname		95
#define SYS_getservbyport		96
#define SYS_select			97
#define SYS_statvfs			98
#define SYS_fstatvfs			99
#define SYS_ptsname			100
#define SYS_fdcheck			101
#define SYS_ioctl			102
#define SYS_mmap			103
#define SYS_munmap			104
#define SYS_uidtontsid			105
#define SYS_gettzenv			106
#define SYS_login			107
#define SYS_renamewtmpx			108
#define SYS_fsync			109
#define SYS_itimer			110
#define SYS_setuser			111
#define SYS_flock			112
#define SYS_ipcs			113
#define SYS_socketpair			114
#define SYS_lchown			115
#define SYS_lstat			116
#define SYS_readlink			117
#define SYS_symlink			118
#define SYS_chpass			119
#define SYS_vfork			120
#define SYS_prio			121
#define SYS_unixpath2win    		122
#define SYS_winpath2unix    		123
#define SYS_getpdomain			124
#define SYS___xtiConfirmEndpointState	125
#define SYS___xtiUpdateEndpointState	126
#define SYS___xtiUnbindEndpoint		127
#define SYS_ttyslot			128
#define SYS_truncate			129
#define SYS_getrlimit			130
#define SYS_setrlimit			131
#define SYS_setids      		132	/* replaces setuid, setgid */
#define SYS_chroot			133
#define SYS_settimeofday		134
#define SYS_fchmod			135
#define SYS_fchown			136
#define SYS_fchdir			137
#define SYS_getsecret			138
#define SYS_setsecret			139
#if 0 /* Not implemented */
#define SYS_mount			140
#define SYS_umount			141
#endif
#define SYS_mknod			142
#if 0 /* Not Implemented */
#define SYS_sysfs			143
#endif
#define SYS_pthread_create	   	144
#define SYS_pthread_join   	    	145
#define SYS_pthread_exit   	    	146
#define SYS_pthread_detach 	    	147
#define SYS_inform_signalthread_handle  	148
#define SYS_pthread_sigmask 	    	149
#define SYS_pthread_kill 	    	150
#define SYS_pthread_set_cancel		151
#define SYS_signal_apc_received		152
#define SYS_sleep			153
#define SYS_get_thread_handle		154
#define SYS_dll_assert			155
#define SYS_sigwait                   156
#define SYS_open_nocancel      157
#define SYS_close_nocancel     158
#define SYS_read_nocancel      159
#define SYS_pthread_mutex_init  160
#define SYS_pthread_mutex_destroy   161
#define SYS_pthread_mutex_lock  162
#define SYS_pthread_mutex_timedlock 163
#define SYS_pthread_mutex_trylock   164
#define SYS_pthread_mutex_unlock	    165
#define SYS_pthread_cond_init   166
#define SYS_pthread_cond_destroy    167
#define SYS_pthread_cond_wait   168
#define SYS_pthread_cond_timedwait  169
#define SYS_pthread_cond_signal 170
#define SYS_pthread_cond_broadcast  171
#define SYS_pthread_rwlock_init 172
#define SYS_pthread_rwlock_destroy  173
#define SYS_pthread_rwlock_tryrdlock    174
#define SYS_pthread_rwlock_trywrlock    175
#define SYS_pthread_rwlock_rdlock   176
#define SYS_pthread_rwlock_wrlock   177
#define SYS_pthread_rwlock_unlock   178
#define SYS_pthread_rwlock_timedwrlock  179
#define SYS_pthread_rwlock_timedrdlock  180
#define SYS_sem_init    181
#define SYS_sem_destroy 182
#define SYS_sem_post    183
#define SYS_sem_getvalue    184
#define SYS_sem_timedwait   185
#define SYS_sem_trywait 186
#define SYS_sem_wait    187
#define SYS_pread       188
#define SYS_pwrite      189
#define SYS_vhangup     190
#define SYS_execinform	191
#define SYS_fork2		    192
#define SYS_fork2finish     	    193
#define SYS_getsid	            194
#define SYS_thread_create	    195
#define SYS_thread_destroy	    196
#define SYS_SEH_exception	    197
#define SYS_sendmsg             198
#define SYS_recvmsg             199
#define SYS_getaddrinfo		200
#define SYS_getnameinfo		201
#define SYS_if_nametoindex	202
#define SYS_if_indextoname	203
#define SYS_MAX			   204 
#ifdef __cplusplus 
}
#endif 

#endif /* _SYS_SYSCALL_H_ */
