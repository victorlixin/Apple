#ifndef _NETDB_H
#define _NETDB_H

#include<sys/types.h>
#include<sys/socket.h>
#include<features.h>
#include<errno.h>
 
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif

#define herror(p1) 				perror(p1)
#define hstrerror(p1) 				strerror(p1)
#define h_addr 					h_addr_list[0]
#define h_errno 					errno
#define HOST_NOT_FOUND 		EHOSTNOTFOUND
#define NO_ADDRESS 				NO_DATA
#define NO_DATA 				ENODATA
#define NO_RECOVERY 			ENORECOVERY
#define TRY_AGAIN 				ETRYAGAIN

struct hostent{
	char*		h_name;
	char **		h_aliases;
	int 			h_addrtype;
	int 			h_length;
	char **		h_addr_list;
};

struct netent{
	char *		n_name;
	char **		n_aliases;
	int 			n_addrtype;
	uint32_t 		n_net;
};

struct protoent{
	char *		p_name;
	char **		p_aliases;
	int 			p_proto;
};

struct servent{
	char *		s_name;
	char **		s_aliases;
	int 			s_port;
	char *		s_proto;
};

/*
 * Ipv6 Support
 */
struct addrinfo {
	int	ai_flags;	/* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
	int	ai_family;	/* PF_xxx */
	int	ai_socktype;	/* SOCK_xxx */
	int	ai_protocol;	/* 0 or IPPROTO_xxx for IPv4 and IPv6 */
	size_t	ai_addrlen;	/* length of ai_addr */
	char	*ai_canonname;	/* canonical name for hostname */
	struct	sockaddr *ai_addr;	/* binary address */
	struct	addrinfo *ai_next;	/* next structure in linked list */
};

/*
 * Error return codes from getaddrinfo()
 */
#define	EAI_AGAIN	 		11002	/* temporary failure in name resolution */
#define	EAI_BADFLAGS	 	10022	/* invalid value for ai_flags */
#define	EAI_FAIL	 		11003	/* non-recoverable failure in name resolution */
#define	EAI_FAMILY	 		10047	/* ai_family not supported */
//This varies from windows to windows
#define	EAI_MEMORY		8		/* memory allocation failure */
#define	EAI_NONAME	 	11001	/* hostname nor servname provided, or not known */
#define	EAI_SERVICE	 	10109	/* servname not supported for ai_socktype */
#define	EAI_SOCKTYPE		10044	/* ai_socktype not supported */

#define	EAI_NODATA		EAI_NONAME

#if 1
//They are not supported by Winsock currently
#if 0
#define	EAI_OVERFLOW		14 	/* introduced only in rfc 3493 */
#endif
#define EAI_SYSTEM		11	/* A system error occurred; the error code can be found in errno. */

#endif
/*
 * Flag values for getaddrinfo()
 */
#define	AI_PASSIVE	0x00000001 /* get address to use bind() */
#define	AI_CANONNAME	0x00000002 /* fill ai_canonname */
#define	AI_NUMERICHOST	0x00000004 /* prevent host name resolution */
#define	AI_NUMERICSERV	0x00000008 /* prevent service name resolution */
/* valid flags for addrinfo (not a standard def, apps should not use it) */
#define AI_MASK \
    (AI_PASSIVE | AI_CANONNAME | AI_NUMERICHOST | AI_NUMERICSERV | \
    AI_ADDRCONFIG)

#define	AI_ALL		0x00000100 /* IPv6 and IPv4-mapped (with AI_V4MAPPED) */
#define	AI_V4MAPPED_CFG	0x00000200 /* accept IPv4-mapped if kernel supports */
#define	AI_ADDRCONFIG	0x00000400 /* only if any address is assigned */
#define	AI_V4MAPPED	0x00000800 /* accept IPv4-mapped IPv6 address */

/*
 * Constants for getnameinfo()
 */
#define	NI_MAXHOST	1025
#define	NI_MAXSERV	32

/*
 * Flag values for getnameinfo()
 */
#define	NI_NOFQDN	0x00000001
#define	NI_NUMERICHOST	0x00000002
#define	NI_NAMEREQD	0x00000004
#define	NI_NUMERICSERV	0x00000008
#define	NI_DGRAM	0x00000010
#if 1 /* obsolete */
#define NI_WITHSCOPEID	0x00000020
#endif

/*
 * Scope delimit character
 */
#define	SCOPE_DELIMITER	'%'


#ifndef _PSX_KERNEL
	struct hostent * _CRTAPI1 gethostbyname(const char *);
	struct hostent * _CRTAPI1 gethostbyaddr(const void *, socklen_t, int);
	struct hostent * _CRTAPI1 gethostent(void);
	void  _CRTAPI1 sethostent(int);
	void  _CRTAPI1 endhostent(void);
	struct protoent * _CRTAPI1 getprotobyname(const char *);
	struct protoent * _CRTAPI1 getprotobynumber(int);
	struct protoent * _CRTAPI1 getprotoent(void);
	void  _CRTAPI1 setprotoent(int);
	void  _CRTAPI1 endprotoent(void);
	int   _CRTAPI1 getaddrinfo(const char *, const char *, const struct addrinfo *, struct addrinfo **);
	int   _CRTAPI1 getnameinfo(const struct sockaddr *, socklen_t,  char *, socklen_t,  char *, socklen_t, int);
	void  _CRTAPI1 freeaddrinfo(struct addrinfo *);
	char  *_CRTAPI1 gai_strerror(int);

	struct servent * _CRTAPI1 getservbyname(const char *, const char *);
	struct servent * _CRTAPI1 getservbyport(int, const char *);
	struct servent * _CRTAPI1 getservent(void);
	void  _CRTAPI1 setservent(int);
	void  _CRTAPI1 endservent(void);
	struct netent * _CRTAPI1 getnetbyname(const char *);
	struct netent * _CRTAPI1 getnetbyaddr(uint32_t, int);
	struct netent * _CRTAPI1 getnetent(void);
	void  _CRTAPI1 setnetent(int);
	void  _CRTAPI1 endnetent(void);
#endif
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
}
#endif


#endif /*_NETDB_H*/
