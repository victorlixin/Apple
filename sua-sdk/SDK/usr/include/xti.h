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
 */ 

/*
 * xti.h    -- XTI API definitions.
 */

#ifndef _XTI_H_
#define _XTI_H_
 
#if defined(__cplusplus)
extern "C" {
#endif

/*
 * t_errno  -- The XTI error code global variable.
 */
extern int t_errno;

/*
 * Error codes that may be found in the t_error external variable.
 */
#define TZERO    	0   /* no error */
#define TBADADDR    	1   /* incorrect addr format */
#define TBADOPT     	2   /* incorrect option format */
#define TACCES      	3   /* incorrect permissions */
#define TBADF       	4   /* illegal transport fd */
#define TNOADDR     	5   /* couldn't allocate addr */
#define TOUTSTATE   	6   /* out of state */
#define TBADSEQ     	7   /* bad call sequence number */
#define TSYSERR     	8   /* system error */
#define TLOOK       	9   /* event requires attention */
#define TBADDATA    	10  /* illegal amount of data */
#define TBUFOVFLW   	11  /* buffer not large enough */
#define TFLOW       	12  /* flow control */
#define TNODATA     	13  /* no data */
#define TNODIS      	14  /* discon_ind not found on queue */
#define TNOUDERR    	15  /* unitdata error not found */
#define TBADFLAG    	16  /* bad flags */
#define TNOREL      	17  /* no ord rel found on queue */
#define TNOTSUPPORT 	18  /* primitive/action not supported */
#define TSTATECHNG  	19  /* state is in process of changing */
#define TNOSTRUCTYPE	20  /* unsupported struct-type requested */
#define TBADNAME    	21  /* invalid transport provider name */
#define TBADQLEN    	22  /* qlen is zero */
#define TADDRBUSY   	23  /* address in use */
#define TINDOUT     	24  /* outstanding connection indications */
#define TPROVMISMATCH	25  /* transport provider mismatch */
#define TRESQLEN     	25  /* resfd specified to accept w/qlen >0 */
#define TRESADDR     	27  /* resfd not bound to same addr as fd */
#define TQFULL       	28  /* incoming connection queue full */
#define TPROTO       	29  /* XTI protocol error */

#define MAX_T_ERRNO 	30

/*
 * XTI events returned by t_look().
 */
#define T_LISTEN	0x0001	/* connection indication received */
#define T_CONNECT	0x0002	/* connect confirmation received */
#define T_DATA  	0x0004	/* normal data received */
#define T_EXDATA	0x0008	/* expedited data received */
#define T_DISCONNECT	0x0010	/* disconnect received */
#define T_UDERR 	0x0040	/* datagram error indication */
#define T_ORDREL	0x0080	/* orderly release indication */
#define T_GODATA	0x0100	/* sending normal data is again possible */
#define T_GOEXDATA	0x0200	/* sending expedited data is again possible */

/*
 * flags used by the XTI interfaces.  T_NEGOTIATE and after are used
 * primarily for option negotiation.
 */
#define T_MORE		0x0001	/* more data */
#define T_EXPEDITED	0x0002	/* expedited data */
#define T_NEGOTIATE	0x0004	/* set options */
#define T_CHECK		0x0008	/* check options */
#define T_DEFAULT	0x0010	/* get default options */
#define T_SUCCESS	0x0020	/* successful */
#define T_FAILURE	0x0040	/* failure */
#define T_CURRENT	0x0080	/* get current options */
#define T_PARTSUCCESS	0x0100	/* partial success */
#define T_READONLY	0x0200	/* read-only option */
#define T_NOTSUPPORT	0x0400	/* option not supported */

/*
 * Protocol-specific service limits.
 */
struct t_info {

    long addr;	    /* max size of the transport protocol address */
    long options;   /* max number of bytes of protocol-specific options */
    long tsdu;	    /* max size of a transport service data unit */
    long etsdu;	    /* max size of ecpedited transport service data unit */
    long connect;   /* max amount of data allowed at connection establishment */
    long discon;    /* max data allowed on t_snddis() and t_rcvdis() calls */
    long servtype;  /* service type supported by transport provider */
    long flags;	    /* other info about the transport provider */
};

/*
 * Manifest constants representing Service types.
 */
#define T_COTS	    01	/* connection-oriented transport service */
#define T_COTS_ORD  02	/* connection oriented /w orderly release */
#define T_CLTS	    03	/* connectionless transport service */

/*
 * Flags used by the 'flags' member of struct t_info.
 */
#define T_SENDZERO  0x0001  /* TP supports zero-length TSDUs */

/*
 * The netbuf structure.
 */
struct netbuf {

    unsigned int    maxlen;
    unsigned int    len;
    char	    *buf;
};

/*
 * The t_bind structure.
 */
struct t_bind {

    struct netbuf   addr;
    unsigned	    qlen;
};

/*
 * The t_opthdr structure.
 */
struct t_opthdr {

    unsigned long len;      /* total length of option in bytes */
    unsigned long level;    /* protocol level affected */
    unsigned long name;	    /* option name */
    unsigned long status;   /* status value */

			    /*
			     * This structure is always followed by the
			     * option value.
			     */
};

/*
 * The options management structure.
 */
struct t_optmgmt {

    struct netbuf   opt;
    long	    flags;
};

/*
 * The disconnect structure.
 */
struct t_discon {

    struct netbuf   udata;   	/* user date */
    int		    reason;  	/* reason code */
    int		    sequence;	/* sequence number */
};

/*
 * The call structure.
 */
struct t_call {

    struct netbuf   addr;	/* address */
    struct netbuf   opt;	/* options */
    struct netbuf   udata;	/* user data */
    int		    sequence;	/* sequence number */
};

/*
 * The datagram structure.
 */
struct t_unitdata {

    struct netbuf   addr;   /* address */
    struct netbuf   opt;    /* options */
    struct netbuf   udata;  /* user data */
};

/*
 * The unitdata error structure.
 */
struct t_uderr {

    struct netbuf   addr;   /* address */
    struct netbuf   opt;    /* options */
    long	    error;  /* error code */
};

/*
 * These manifest constants let t_alloc() know what kind of structure to
 * allocate.
 */
#define T_BIND	    1	/* struct t_bind */
#define T_OPTMGMT   2	/* struct t_optmgmt */
#define T_CALL	    3	/* struct t_call */
#define T_DIS	    4	/* struct t_discon */
#define T_UNITDATA  5	/* struct t_unitdata */
#define T_UDERROR   6	/* struct t_uderr */
#define T_INFO	    7	/* struct t_info */

/*
 * The following flags indicate to t_alloc() which of the fields of the
 * above to allocate.
 */
#define	T_ADDR	0x0001	/* address */
#define T_OPT	0x0002	/* options */
#define T_UDATA	0x0004	/* user data */
#define T_ALL	0xffff	/* all fht above fields */

/*
 * These are the states returned by t_getstate().
 */
#define T_UNBND	    1	/* unbound */
#define T_IDLE	    2	/* idle */
#define T_OUTCON    3	/* outgoing connection pending */
#define T_INCON	    4	/* incoming connection pending */
#define T_DATAXFER  5	/* data transfer */
#define T_OUTREL    6	/* outgoing release pending */
#define T_INREL	    7	/* incoming release pending */

/*
 * General purpose defines.
 */
#define T_YES	    1
#define	T_NO	    0
#define T_UNUSED    -1
#define T_NULL	    0
#define T_ABSREQ    0x8000

/*
 * T_INFINITE and T_INVALID are values used in t_info.
 */
#define T_INFINITE  -1
#define T_INVALID   -2

/*
 * General definitions for option management.
 */
#define T_UNSPEC    (~0 - 2)
#define T_ALLOPT    (0)

#define T_ALIGN(p)  (  ((unsigned long)(p) + (sizeof(long) - 1)) \
		     & ~(sizeof(long) - 1 ))

#define OPT_NEXTHDR(pbuf, buflen, popt) \
( \
      ((char *)(popt) + T_ALIGN( (popt)->len ) < (char *)(pbuf) + (buflen)) \
    ? (struct t_opthdr *)((char *)(popt) + T_ALIGN( (popt)->len )) \
    : (struct t_opthdr *)0)

/*
 * XTI level options.
 */
#define XTI_GENERIC 	0xffff
#define XTI_DEBUG   	0x0001  /* enable debugging */
#define XTI_LINGER  	0x0002  /* linger on close if data present */
#define XTI_RCVBUF   	0x1002  /* receive buffer size */
#define XTI_RCVLOWAT	0x1004	/* receive low-water mark */
#define XTI_SNDBUG  	0X1001  /* send buffer size */
#define XTI_SNDLOWAT	0x1003	/* send low-water mark */

/*
 * The structure used with the linger option.
 */
struct t_linger {

    long    l_onoff;	/* option on/off */
    long    l_linger;	/* linger time */
};

/*
 * Definition of the ISO transport classes.
 */
#define	T_CLASS0    0
#define	T_CLASS1    1
#define	T_CLASS2    2
#define	T_CLASS3    3
#define	T_CLASS4    4

/*
 * Definition of transport priorities.
 */
#define T_PRITOP    0
#define T_PRIHIGH   1
#define T_PRIMID    2
#define T_PRILOW    3
#define T_PRIDFLT   4

/*
 * Definitions of protection levels.
 */
#define T_NOPROTECT	    1
#define T_PASSIVEPROTECT    2
#define T_ACTIVEPROTECT	    4

/*
 * Default value for the length of TPDUs.
 */
#define T_LTPDUDFLT 0x0080  /* constant obsolete in XPG4 */

/*
 * Option structure to supply desired communication rate.
 */
struct rate {

    long targetvalue;	 /* target value */
    long minacceptvalue; /* minimally acceptable value */
};

/*
 * Option structure to supply 'required rate values'.
 */
struct reqvalue {

    struct rate called;     /* called rate */
    struct rate	calling;    /* calling rate */
};

/*
 * Option structure to supply desired throughput.
 */
struct thrpt {

    struct reqvalue maxthrpt;	/* maximum throughput */
    struct reqvalue avgthrpt;	/* average throughput */
};

/*
 * Option structure to supply desired transit delay.
 */
struct transdel {

    struct reqvalue maxdel; /* maximum transit delay */
    struct reqvalue avgdel; /* average transit delay */
};

/*
 * Protocol levels.
 */
#define ISO_TP	0x0100

/*
 * Quality of service and expedited data options (ISO 8072:1986).
 */
#define TCO_THROUGHPUT	    0X0001
#define TCO_TRANSDEL	    0x0002
#define TCO_RESERRORRATE    0x0003
#define TCO_TRANSFFAILPROB  0x0004
#define TCO_ESTGAILPROB	    0x0005
#define TCO_RELFAILPROB	    0x0006
#define TCO_ESTDELAY	    0x0007
#define TCO_RELDELAY	    0x0008
#define TCO_CONNRESIL	    0x0009
#define TCO_PROTECTION	    0x000a
#define TCO_PRIORITY	    0x000b
#define TCO_EXPD	    0x000c

#define TCL_TRANSDEL	    0x000d
#define TCL_RESERRORRATE    TCO_RESERRORRATE
#define TCL_PROTEXTION	    TCO_PROTECTION
#define TCL_PRIORITY	    TCO_PRIORITY

/*
 * Management options.
 */
#define TCO_LTPDU	0x0100
#define TCO_ACKTIME	0x0200
#define TCO_REASTIME	0x0300
#define TCO_EXTFORM	0x0400
#define TCO_FLOWCRTL	0x0500
#define TCO_CHECKSUM	0x0600
#define TCO_NETEXP	0x0700
#define TCO_NETRECPTCF	0x0800
#define TCO_PREFCLASS	0x0900
#define TCO_ALTCLASS1	0x0a00
#define TCO_ALTCLASS2	0x0b00
#define TCO_ALTCLASS3	0x0c00
#define TCO_ALTCLASS4	0x0d00

#define TCL_CHECKSUM	TCO_CHECKSUM

/*
 * Internet specific options.
 */

/*
 * TCP level options.
 */
#define INET_TCP    0x06

#define TCP_NODELAY	0x01	/* don't delay packets to coalesce */
#define TCP_MAXSEG	0x02	/* get maximum segment size */
#define TCP_KEEPALIVE	0x08	/* check, if connections are alive */

/*
 * Structure to be used with TCP_KEEPALIVE.
 */
struct t_kpalive {

    long kp_onoff;	/* option on/off */
    long kp_timeout;	/* timeout in minutes */
};

#define T_GARBAGE   0x02

/*
 * UDP level options.
 */
#define INET_UDP    0x11

#define UDP_CHECKSUM	TCO_CHECKSUM

/*
 * IP level options.
 */
#define INET_IP	0x00

#ifndef IP_OPTIONS
#define IP_OPTIONS  	0x01    /* IP per-packet options */
#endif

#ifndef IP_TOS
#define IP_TOS	    	0x02    /* IP per-packet type of service */
#endif

#ifndef IP_TTL
#define IP_TTL	    	0x03    /* IP per-packet time to live */
#endif

#define IP_REUSEADDR	0x04	/* alloc local address reuse */
#define IP_DONTROUTE	0x10	/* just use interface addresses */
#define IP_BROADCAST	0x20	/* permit sending of broadcast msgs */

/*
 * IP_TOS precedence levels.
 */
#define T_ROUTINE	0
#define T_PRIORITY	1
#define T_IMMEDIATE	2
#define T_FLASH		3
#define T_OVERRIDEFLASH	4
#define T_CRITIC_ECP	5
#define T_INETCONTROL	6
#define T_NETCONTROL	7

/*
 * IP_TOS types of service.
 */
#define T_NTOS	    0x0000
#define T_LDELAY    0x0010
#define T_HITHRPT   0x0008
#define T_HIREL	    0x0004

#define SET_TOS(prec, tos)  ((0x07 & (prec)) << 5 | (0x1c & (tos)))


/*
 * XTI library functions.
 */
extern int 	__cdecl t_accept(int, int, struct t_call *);
extern char *	__cdecl t_alloc(int, int, int);
extern int	__cdecl t_bind(int, struct t_bind *, struct t_bind *);
extern int	__cdecl t_close(int);
extern int	__cdecl t_connect(int, struct t_call *, struct t_call *);
extern int	__cdecl t_error( char *);
extern int	__cdecl t_free( char *, int);
extern int	__cdecl t_getinfo(int, struct t_info *);
extern int	__cdecl t_getprotaddr(int, struct t_bind *, struct t_bind *);
extern int	__cdecl t_getstate(int);
extern int	__cdecl t_listen(int, struct t_call *);
extern int	__cdecl t_look(int);
extern int	__cdecl t_open( char *, int, struct t_info *);
extern int	__cdecl t_optmgmt(int, struct t_optmgmt *, struct t_optmgmt *);
extern int	__cdecl t_rcv(int,  char *, unsigned int,  int *);
extern int	__cdecl t_rcvconnect(int, struct t_call *);
extern int	__cdecl t_rcvdis(int, struct t_discon *);
extern int	__cdecl t_rcvrel(int);
extern int	__cdecl t_rcvudata(int, struct t_unitdata *, int *);
extern int	__cdecl t_rcvuderr(int, struct t_uderr *);
extern char *	__cdecl t_strerror(int);
extern int	__cdecl t_snd(int,  char *, unsigned int, int);
extern int	__cdecl t_snddis(int, struct t_call *);
extern int	__cdecl t_sndrel(int);
extern int	__cdecl t_sndudata(int, struct t_unitdata *);
extern int	__cdecl t_sync(int);
extern int	__cdecl t_unbind(int);

#if defined(__cplusplus)
}
#endif

#endif /* _XTI_H_ */

