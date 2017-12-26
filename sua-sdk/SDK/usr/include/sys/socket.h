#ifndef  _SYS_SOCKET_H_
#define  _SYS_SOCKET_H_

#include<sys/types.h>
#include<sys/uio.h>
#include<features.h>

#if defined(__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif


/*Socket types*/
#define SOCK_STREAM 			        0x0001
#define SOCK_DGRAM 				0x0002
#define SOCK_RAW 				0x0003
#define SOCK_RDM 				0x0004
#define SOCK_SEQPACKET 			        0x0005
#define SOL_SOCKET 				0xFFFF


#define SO_DEBUG        			0x0001          
#define SO_ACCEPTCONN   		        0x0002          
#define SO_REUSEADDR    			0x0004          
#define SO_MAXCONN 				0x0005         
#define SO_KEEPALIVE    			0x0008         
#define SO_DONTROUTE    			0x0010         
#define SO_BROADCAST    			0x0020         
#define SO_USELOOPBACK  		        0x0040         
#define SO_LINGER       			0x0080         
#define SO_OOBINLINE    			0x0100         
#define SO_SNDBUF       			0x1001         
#define SO_RCVBUF       			0x1002         
#define SO_SNDLOWAT     			0x1003         
#define SO_RCVLOWAT     			0x1004         
#define SO_SNDTIMEO     			0x1005         
#define SO_RCVTIMEO     			0x1006         
#define SO_ERROR        			0x1007         
#define SO_TYPE         			0x1008         





#define SO_ATMARK 				0x6001
#define SO_CONNECT_TIME 		        0x700C
#define SO_DONTLINGER 			        ((int)(~SO_LINGER))
#define SO_EXCLUSIVEADDRUSE 	                ((int)(~SO_REUSEADDR))
#define SO_MAXDG 				0x7009
#define SO_MAXPATHDG 			        0x700A


#define SOMAXCONN       			0x0005 




#define MSG_OOB         			0x0001            
#define MSG_PEEK        			0x0002            
#define MSG_DONTROUTE                           0x0004            
#define MSG_MAXIOVLEN   		        0x0010
#define	MSG_WAITALL				0x0040	
#define	MSG_DONTWAIT	                        0x0080
#define MSG_PARTIAL     			0x8000  





#define AF_LOCAL				0x0001
#define AF_INET 		 		0x0002
#define AF_IPX 					0x0006
#define AF_APPLETALK 			        0x0010
/*
 * Ipv6 Support
 */
#define	AF_INET6				23		/* IPv6 */



#ifndef _PSX_KERNEL
#define AF_MAX 					0x0010
#endif

#define AF_NETBIOS 			 	0x0011
#define AF_UNIX 				AF_LOCAL
#define AF_UNSPEC 				0x0000


#define SHUT_RD 				0x0000
#define SHUT_WR 				0x0001
#define SHUT_RDWR 				0x0002



#define PF_APPLETALK 			        AF_APPLETALK
#define PF_INET 				AF_INET
#define PF_IPX 					AF_IPX
#define PF_LOCAL 				AF_LOCAL
/*
 * Ipv6 Support
 */
#define	PF_INET6				AF_INET6

#ifndef _PSX_KERNEL
#define PF_MAX 					AF_MAX
#endif

#define PF_NETBIOS 				AF_NETBIOS
#define PF_UNIX 				PF_LOCAL
#define PF_UNSPEC 				AF_UNSPEC

#define MSG_TRUNC 				0x0000
#define MSG_CTRUNC 				0x0020	
#define SCM_RIGHTS 				0x0001	
	



typedef int socklen_t;


struct sockaddr{
	sa_family_t 		        sa_family;
	char 			        sa_data[14];
};

struct linger{
	int 				l_onoff;
	int 				l_linger;
};


struct msghdr {
      void*				msg_name;        		
      socklen_t  		        msg_namelen;     	
      struct iovec*		        msg_iov;     			
      size_t     			msg_iovlen;      		
      void*				msg_control;     		
      socklen_t  		        msg_controllen;  	
      int        			msg_flags;       		
};

struct cmsghdr {
      socklen_t  		        cmsg_len;   			
      int        			cmsg_level; 			
      int        			cmsg_type;  		
        /*unsigned char cmsg_data[] follows; */
};

/*
 * Ipv6 Support
 */

/*
 * RFC 2553: protocol-independent placeholder for socket addresses
 */
#define	_SS_MAXSIZE	128U
#define	_SS_ALIGNSIZE	(sizeof(int64_t))
#define	_SS_PAD1SIZE	(_SS_ALIGNSIZE - sizeof(sa_family_t))
#define	_SS_PAD2SIZE	(_SS_MAXSIZE - sizeof(sa_family_t) - _SS_PAD1SIZE - _SS_ALIGNSIZE)

/*
 * sockaddr does not contain sa_len hence this definition
 */
struct sockaddr_storage {
	sa_family_t	ss_family;	/* address family */
	char		__ss_pad1[_SS_PAD1SIZE];
	int64_t		__ss_align;	/* force desired struct alignment */
	char		__ss_pad2[_SS_PAD2SIZE];
};



/* Work Around for Wincrypt.h #define with Same Name */
#if defined(_PSX_KERNEL) 
#ifdef CMSG_DATA
#undef CMSG_DATA
#endif /* CMSG_DATA */
#endif /* _PSX_KERNEL */

#if !(defined(_XOPEN_SOURCE) && (1==_XOPEN_SOURCE_EXTENDED))
  
#define CMSG_ALIGN(p)  		(((unsigned)(p) + 0x3) & ~ 0x3)
#define CMSG_DATA(cmsg)   	((unsigned char *)(cmsg) + CMSG_ALIGN(sizeof(struct cmsghdr)))
#define CMSG_SPACE(len) 		( CMSG_ALIGN(len)  + CMSG_ALIGN(sizeof(struct cmsghdr)) )
#define CMSG_LEN(len) 		( CMSG_ALIGN(sizeof(struct cmsghdr)) + len)

#define CMSG_FIRSTHDR(mhdr) \
           ( (mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? \
             (struct cmsghdr *)(mhdr)->msg_control : \
             (struct cmsghdr *)NULL )


#define CMSG_NXTHDR(mhdr, cmsg) \
        ( ((cmsg) == NULL) ? CMSG_FIRSTHDR(mhdr) : \
          (((unsigned char *)(cmsg) + CMSG_ALIGN((cmsg)->cmsg_len) \
                             + CMSG_ALIGN(sizeof(struct cmsghdr)) > \
            (unsigned char *)((mhdr)->msg_control) + (mhdr)->msg_controllen) ? \
           (struct cmsghdr *)NULL : \
           (struct cmsghdr *)((unsigned char *)(cmsg) + CMSG_ALIGN((cmsg)->cmsg_len))) )
	  	
	  	
#endif /*!(defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE_EXTENDED==1))*/



#if !defined (_PSX_KERNEL) || defined (_PSX_DLL)
int  		_CRTAPI1 accept(int, struct sockaddr *, socklen_t *);
int  		_CRTAPI1 bind(int, const struct sockaddr *, socklen_t);
int  		_CRTAPI1 connect(int, const struct sockaddr *, socklen_t);
int  		_CRTAPI1 getpeername(int, struct sockaddr *, socklen_t *);
int  		_CRTAPI1 getsockname(int, struct sockaddr *, socklen_t *);
int  		_CRTAPI1 getsockopt(int, int, int, void *, socklen_t *);
int  		_CRTAPI1 listen(int, int);
ssize_t  	_CRTAPI1 recv(int, void *, size_t, int);
ssize_t  	_CRTAPI1 recvfrom(int, void *, size_t, int,struct sockaddr *, socklen_t *);
ssize_t  	_CRTAPI1 send(int, const void *, size_t, int);
ssize_t  	_CRTAPI1 sendto(int, const void *, size_t, int, const struct sockaddr *,socklen_t);
int  		_CRTAPI1 setsockopt(int, int, int, const void *, socklen_t);
int  		_CRTAPI1 shutdown(int, int);
int  		_CRTAPI1 socket(int, int, int);
int  		_CRTAPI1 socketpair(int, int, int, int[2]);
ssize_t 	_CRTAPI1 sendmsg(int , const struct msghdr *, int );
ssize_t 	_CRTAPI1 recvmsg(int ,struct msghdr *, int );
#endif  /* PSX_SOCKET*/

#if defined(__cplusplus) || defined(__CPLUSPLUS__)
}
#endif

#endif /* _SYS_SOCKET_H_*/
