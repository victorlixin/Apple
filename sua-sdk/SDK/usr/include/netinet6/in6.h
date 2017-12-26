#ifndef __NETINET_IN_H_INCLUDED_
#error "do not include netinet6/in6.h directly, include netinet/in.h.  see RFC3493"
#endif

#ifndef _NETINET6_IN6_H
#define _NETINET6_IN6_H
#include <sys/types.h>

/*
 * IPv6 address
 */
struct in6_addr {
	union {
		uint8_t		__u6_addr8[16];
		uint16_t	__u6_addr16[8];
		uint32_t	__u6_addr32[4];
	} __u6_addr;			/* 128-bit IP6 address */
};

#define s6_addr   __u6_addr.__u6_addr8

#define INET6_ADDRSTRLEN	65

struct sockaddr_in6 {
    sa_family_t     sin6_family;    /* AF_INET6 */
    in_port_t       sin6_port;      /* transport layer port # */
    uint32_t        sin6_flowinfo;  /* IPv6 flow information */
    struct in6_addr sin6_addr;      /* IPv6 address */
    uint32_t        sin6_scope_id;  /* set of interfaces for a scope */
};

#define IN6ADDR_ANY_INIT \
	{{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6ADDR_LOOPBACK_INIT \
	{{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }}}


extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;

#define IN6_ARE_ADDR_EQUAL(a, b)			\
    (memcmp(&(a)->s6_addr[0], &(b)->s6_addr[0], sizeof(struct in6_addr)) == 0)


/*
 * Unspecified
 */
#define IN6_IS_ADDR_UNSPECIFIED(a)	\
	((*(const u_int32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[12]) == 0))

/*
 * Loopback
 */
#define IN6_IS_ADDR_LOOPBACK(a)		\
	((*(const u_int32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[12]) == ntohl(1)))

/*
 * IPv4 compatible
 */
#define IN6_IS_ADDR_V4COMPAT(a)		\
	((*(const u_int32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[8]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[12]) != 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[12]) != ntohl(1)))

/*
 * Mapped
 */
#define IN6_IS_ADDR_V4MAPPED(a)		      \
	((*(const u_int32_t *)(const void *)(&(a)->s6_addr[0]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[4]) == 0) &&	\
	 (*(const u_int32_t *)(const void *)(&(a)->s6_addr[8]) == ntohl(0x0000ffff)))

/*
 * Unicast Scope
 * Note that we must check topmost 10 bits only, not 16 bits (see RFC2373).
 */
#define IN6_IS_ADDR_LINKLOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#define IN6_IS_ADDR_SITELOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))

/*
 * Multicast
 */
#define IN6_IS_ADDR_MULTICAST(a)	((a)->s6_addr[0] == 0xff)
/* Option to use with [gs]etsockopt at the IPPROTO_IPV6 level */

#define __IPV6_ADDR_SCOPE_NODELOCAL	0x01
#define __IPV6_ADDR_SCOPE_INTFACELOCAL	0x01
#define __IPV6_ADDR_SCOPE_LINKLOCAL	0x02
#define __IPV6_ADDR_SCOPE_SITELOCAL	0x05
#define __IPV6_ADDR_SCOPE_ORGLOCAL	0x08	/* just used in this file */
#define __IPV6_ADDR_SCOPE_GLOBAL	0x0e

#define __IPV6_ADDR_MC_SCOPE(a)		((a)->s6_addr[1] & 0x0f) 
#define IN6_IS_ADDR_MC_NODELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_NODELOCAL))
#define IN6_IS_ADDR_MC_LINKLOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_LINKLOCAL))
#define IN6_IS_ADDR_MC_SITELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) && 	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_SITELOCAL))
#define IN6_IS_ADDR_MC_ORGLOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_ORGLOCAL))
#define IN6_IS_ADDR_MC_GLOBAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_GLOBAL))

#define IPV6_HDRINCL            2  /* Header is included with data */
#define IPV6_UNICAST_HOPS       4  /* Set/get IP unicast hop limit */
#define IPV6_MULTICAST_IF       9  /* Set/get IP multicast interface */
#define IPV6_MULTICAST_HOPS     10 /* Set/get IP multicast ttl */
#define IPV6_MULTICAST_LOOP     11 /* Set/get IP multicast loopback */
#define IPV6_ADD_MEMBERSHIP     12 /* Add an IP group membership */
#define IPV6_DROP_MEMBERSHIP    13 /* Drop an IP group membership */
#define IPV6_JOIN_GROUP         IPV6_ADD_MEMBERSHIP
#define IPV6_LEAVE_GROUP        IPV6_DROP_MEMBERSHIP
#define IPV6_PKTINFO            19 /* Receive packet information for ipv6 */
#define IPV6_HOPLIMIT           21 /* Receive packet hop limit */
#define IPV6_PROTECTION_LEVEL   23 /* Set/get IPv6 protection level */
#define IPV6_RTHDR		32 /* ip6_rthdr; send routing header */
#define IPV6_HOPOPTS		1 /* ip6_hbh; send hop-by-hop option */

//this is not supported by winsock
#define IPV6_NEXTHOP		48 /* sockaddr; next hop addr */
#define IPV6_DSTOPTS		50 /* ip6_dest; send dst option befor rthdr */
#define IPV6_RTHDR_LOOSE     0 /* this hop need not be a neighbor. XXX old spec */
#define IPV6_RTHDR_STRICT    0xff /* this hop must be a neighbor. XXX old spec */
#define IPV6_RTHDR_TYPE_0	0 	/* IPv6 routing header type 0 */
#define IPV6_PATHMTU		44	/* mtuinfo; get the current path MTU (sopt),
				      4 bytes int; MTU notification (cmsg) */
#define IPV6_RECVDSTOPTS	40 /* bool; recv dst option after rthdr */
#define IPV6_RECVHOPLIMIT	37 /* bool; recv hop limit */
#define IPV6_RECVHOPOPTS	39 /* bool; recv hop-by-hop option */
#define IPV6_RECVPKTINFO	36 /* bool; recv if, dst addr */
#define IPV6_RECVTCLASS		57 /* bool; recv traffic class values */
#define IPV6_RTHDRDSTOPTS	35 /* ip6_dest; send dst option before rthdr */
#define IPV6_RECVPATHMTU	43 /* bool; notify an according MTU */
#define IPV6_TCLASS		61 /* int; send traffic class value */
#define IPV6_USE_MIN_MTU	42 /* bool; send packets at the minimum MTU */
#define ICMP6_FILTER		18 /* icmp6_filter; icmp6 filter */

// These are supported by Winsock Now
#define IPV6_V6ONLY		27 /* bool; make AF_INET6 sockets v6 only */
#define IPV6_CHECKSUM		26 /* int; checksum offset for raw socket */
#define IPV6_DONTFRAG		14 /* bool; disable IPv6 fragmentation */
#define IPV6_RECVRTHDR		38 /* bool; recv routing header */

/*
 * Argument structure for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP.
 */
struct ipv6_mreq {
	struct in6_addr	ipv6mr_multiaddr;
	unsigned int	ipv6mr_interface;
};

/*
 * IPV6_PKTINFO: Packet information(RFC2292 sec 5)
 */
struct in6_pktinfo {
	struct in6_addr	ipi6_addr;	/* src/dst IPv6 address */
	unsigned int	ipi6_ifindex;	/* send/recv interface index */
};

/*
 * Control structure for IPV6_RECVPATHMTU socket option.
 */
struct ip6_mtuinfo {
	struct sockaddr_in6 ip6m_addr;	/* or sockaddr_storage? */
	uint32_t ip6m_mtu;
};

extern int inet6_opt_init(void *, int);
extern int inet6_opt_append (void *, int, int, uint8_t, int,
	uint8_t, void **);
extern int inet6_opt_finish(void *, int, int);
extern int inet6_opt_set_val(void *, int, void *, int);
extern int inet6_opt_next (void *, int, int, uint8_t *, int *,
	void **);
extern int inet6_opt_find (void *, int, int, uint8_t, int *,
	void **);
extern int inet6_opt_get_val(void *, int, void *, int);
extern int inet6_rth_space(int, int);
extern void *inet6_rth_init(void *, int, int, int);
extern int inet6_rth_add(void *, const struct in6_addr *);
extern int inet6_rth_reverse(const void *, void *);
extern int inet6_rth_segments(const void *);
extern struct in6_addr *inet6_rth_getaddr(const void *, int);

#endif
