#ifndef _UTMPX_H
#define _UTMPX_H
 
#include<features.h>
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif

#if defined(_ALL_SOURCE) || !defined(_XOPEN_SOURCE) || (defined(_XOPEN_SOURCE) && defined(_XOPEN_SOURCE_EXTENDED))
	#include<sys/types.h>
	#include<sys/time.h>
	/*File paths macros*/
	#define _PATH_UTMPX 		"/var/adm/utmpx"
	#define _PATH_WTMPX 		"/var/adm/wtmpx"
	#define UTMPX_FILE 			_PATH_UTMPX
	#define WTMPX_FILE 			_PATH_WTMPX
	
	/*Size constants*/

	#define UT_LINESIZE 				32
	#define UT_IDSIZE 				UT_LINESIZE
	#define UT_HOSTSIZE 			128
	#define UT_NAMESIZE 			128

	/*Values of ut_type member*/

	#define EMPTY 					0 
	#define BOOT_TIME 				1
	#define OLD_TIME 				2
	#define NEW_TIME 				3
	#define USER_PROCESS 			4
	#define INIT_PROCESS 			5
	#define LOGIN_PROCESS 			6
	#define DEAD_PROCESS 			7
	#define ut_name 					ut_user
	#define ut_time 					ut_tv.tv_sec
	
	struct exit_status{
		short 			e_termination;	
		short 			e_exit;
		int 			reserved[2];
	};

	struct utmpx{
		char 			ut_line[UT_LINESIZE];
		char 			ut_user[UT_NAMESIZE];
		char 			ut_host[UT_HOSTSIZE];
		struct timeval 	ut_tv;
		pid_t 			ut_pid;
		uid_t 			ut_uid;
		char 			ut_id[UT_IDSIZE];
		short 			ut_type;
		struct exit_status ut_exit;
		u_int64_t 		_ut_uid64;
		int 			reserved[6];
	};
	#if defined(_ALL_SOURCE)
	int __cdecl renamewtmpx(const char *);
	int __cdecl wcs_renamewtmpx(const wchar_t *);
	#endif /*defined(_ALL_SOURCE) */

	#if defined(_ALL_SOURCE) || !defined(_XOPEN_SOURCE)
	int logout( char *);
	void login(struct utmpx *);
	#define logout(x)    (0)
	#endif /* defined(_ALL_SOURCE) || !defined(_XOPEN_SOURCE) */

	struct utmpx * _CRTAPI1 getutxent(void);
	struct utmpx * _CRTAPI1 getutxid(const struct utmpx *);
	struct utmpx * _CRTAPI1 getutxline(const struct utmpx *);
	struct utmpx * _CRTAPI1 pututxline(const struct utmpx *);
	void _CRTAPI1 endutxent(void);
	void _CRTAPI1 setutxent(void);

		
	
#endif
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
}
#endif
	
#endif /*_UTMPX_H*/
	
