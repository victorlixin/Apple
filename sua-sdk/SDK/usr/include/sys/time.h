#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#if !defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
#include<sys/types.h>
#include<features.h>

#if !defined(_XOPEN_SOURCE_EXTENDED)|| defined(_ALL_SOURCE)
#include<time.h>
#endif

#if defined(__cplusplus)
extern "C" {						
#endif

#ifndef FAR
#define FAR
#endif

#undef _howmany
#define _howmany(p1,p2)	(((p1)+p2-1) / p2)					

#if !defined(_NBBY)
#define _NBBY 			8						
#endif  /* end of _NBBY */

typedef long 			fdmask_t;
#define _NFDBITS 	(sizeof(fdmask_t)*_NBBY)


#if defined(_ALL_SOURCE)
typedef fdmask_t 		fd_mask;
#endif

#ifndef FD_SETSIZE
#define FD_SETSIZE      4096
#endif 

typedef struct fd_set {
	fdmask_t 		fds_bits[_howmany(FD_SETSIZE,_NFDBITS)];   
} fd_set;
	
#define FD_CLR(p1, p2) (((fd_set FAR *)(p2))->fds_bits[(p1)/_NFDBITS] &= ~(((fdmask_t)1) << ((p1) % _NFDBITS)))
	
#define FD_ISSET(p1, p2) \
        (((fd_set FAR *)(p2))->fds_bits[((p1) / _NFDBITS)] & (((fdmask_t)1) << ((p1) % _NFDBITS)))

#define FD_SET(p1, p2)(((fd_set FAR *)(p2))->fds_bits[(p1)/_NFDBITS] |= (((fdmask_t)1) << ((p1) % _NFDBITS)))

#define FD_ZERO(p1) (void) memset((p1), 0, sizeof(*(p1)))



#define ITIMER_REAL			0
#define ITIMER_VIRTUAL		1
#define ITIMER_PROF			2



struct timeval {
	time_t 			tv_sec;						
	suseconds_t			tv_usec;					
};

struct itimerval {
	struct timeval 	it_interval;					
	struct timeval 	it_value;					
};

#if defined(_ALL_SOURCE)

#define NFDBITS _NFDBITS
#if !defined _IMPORT_LIBCDLL_GLOBALS
struct timezone {
	int 				tz_minuteswest;						
	int 				tz_dsttime;							
};
#endif
#define FD_COPY(p1,p2) (memcpy(p1,p2,FD_SETSIZE))
#define timerclear(p1)(p1)->tv_sec = (p1)->tv_usec = 0
#define timercmp(p1, p2, p3) \
        ((p1)->tv_sec p3 (p2)->tv_sec || \
         (p1)->tv_sec == (p2)->tv_sec && (p1)->tv_usec p3 (p2)->tv_usec)
         
#define timerisset(p1)	((p1)->tv_sec || (p1)->tv_usec)
#define timeradd(tvp, uvp, vvp)                                         \
         do {                                                          \
               (vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;          \
               (vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;       \
               if ((vvp)->tv_usec >= 1000000) {                        \
                       (vvp)->tv_sec++;                                \
                       (vvp)->tv_usec -= 1000000;                      \
               }                                                       \
       } while (0)
 #define timersub(tvp, uvp, vvp)				\
       do {                                                            \
               (vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;          \
               (vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;       \
               if ((vvp)->tv_usec < 0) {                               \
                       (vvp)->tv_sec--;                                \
                       (vvp)->tv_usec += 1000000;                      \
               }                                                       \
       } while (0)
#endif /* end of  _ALL_SOURCE */


int _CRTAPI1 settimeofday(struct timeval *, void *);
int _CRTAPI1 getitimer(int, struct itimerval *);
int _CRTAPI1 gettimeofday(struct timeval *, void *);
#if !defined (_PSX_KERNEL) || defined (_PSX_DLL)
int _CRTAPI1 select(int, fd_set *, fd_set *, fd_set *,struct timeval *);
#endif /* !defined (PSX_SOCKET) || defined (_PSX_DLL)*/
int _CRTAPI1 setitimer(int, const struct itimerval *,struct itimerval *);

#if defined(__cplusplus)
}				
#endif
#endif /*!defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)*/
#endif /* _SYS_TIME_H */ 
