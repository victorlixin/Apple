#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H
#if !defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
#include<sys/types.h>
#include<features.h>
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif


#define _IO(p1,p2)                 _IOC(IOC_VOID,(p1),(p2),0)
#define _IOC(inout,group,number,length) \
				(((inout)&0xE0000000)|\
				(((length)&0x1FFF)<<16) |\
				(((group)&0xFF) <<0x8)|\
				((number)&0xFF))
				


#define _IOR(p1,p2,p3) 			_IOC(IOC_OUT,(p1),(p2),sizeof(p3))
#define _IOW(p1,p2,p3) 			_IOC(IOC_IN,(p1),(p2),sizeof(p3))
#define _IOWR(p1,p2,p3) 			_IOC(IOC_INOUT,(p1),(p2),sizeof(p3))
#define _IOWV(p1,p2,p3) 			_IOC(IOC_VAL,(p1),(p2),sizeof(p3))

#define IOCBASECMD(p1) 			((p1)&0xe000ffff)
#define IOCGROUP(p1) 			(((p1)&0x0000ff00)>>8)
#define IOCPARM_LEN(p1) 		(((p1)&0x1fff0000)>>16)
#define UIOCCMD(p1)			 	_IO('u',p1)

/*File ioctl support (those not available with fcntl)*/
#define FIONBIO 					_IOW('f',2,int)
#define FIONREAD 				_IOR('f',1,int)

/*TIOCFLUSH status bits*/
#define FREAD 					0x0001
#define	FWRITE 					0x0002

/*Constants used with macro functions*/
#define	IOC_DIRMASK 			0xE0000000F 
#define	IOC_IN 					0x80000000 
#define	IOC_INOUT 				(IOC_IN|IOC_OUT)
#define	IOC_OUT				0x40000000 
#define	IOC_VAL					0xA0000000 
#define	IOC_VOID 				0x20000000 
#define	IOCPARM_MASK 			0x1FFF 
#define	IOCPARM_MAX 			0x0FFF 

/*Pseudo tty packet mode status bits*/

#define TIOCPKT_DATA            0x0000
#define TIOCPKT_FLUSHREAD       0x0001
#define TIOCPKT_FLUSHWRITE      0x0002
#define TIOCPKT_STOP            0x0004
#define TIOCPKT_START           0x0008
#define TIOCPKT_NOSTOP          0x0010
#define TIOCPKT_DOSTOP          0x0020
#define TIOCPKT_IOCTL           0x0040 


#define TIOCPKT                 _IOW('t',1,int)

/*Socket ioctl support*/
#define	SIOCATMARK 			_IOR('s',1,int)

/*Ioctl request aliases*/
#define	TCFLSH 					TIOCFLUSH
#define	TCGETA 					TIOCGETA
#define	TCSETA 					TIOCSETA
#define	TCSETAF 				TIOCSETAF
#define	TCSETAW 				TIOCSETAW

/*Status bits for TIOCMOD[SG]*/
#define	TIOCM_DTR 			0x0002
#define	TIOCM_RTS 			0x0004
#define	TIOCM_CTS 			0x0020
#define	TIOCM_CAR 			0x0040
#define	TIOCM_CD 			TIOCM_CAR
#define	TIOCM_RNG 			0x0080
#define	TIOCM_DSR 			0x0100
#define	TIOCM_RI 			TIOCM_RNG



/*Other macro constants available in ioctl.h for tty & pty ioctl support*/
#define	TIOCCBRK 		_IO('t',0x16)
#define	TIOCCDTR 		_IO('t',0x18)
#define	TIOCCONS 		_IOW('t',0x25,int)
#define	TIOCCRTS 		_IO('t',0x1A)
#define	TIOCDRAIN 		_IO('t',0x21)
#define	TIOCEXCL 		_IO('t',0x14)
#define	TIOCEXT 		_IOW('t',0x0B,int)
#define	TIOCFLUSH 		_IOW('t',0x22,int)
#define	TIOCGETA 		_IOR('t',0x1C,struct termios)
#define	TIOCGETD 		_IOR('t',0x10,int)
#define	TIOCGPGRP 		_IOR('t',0x12,int)
#define	TIOCGSIZE 		TIOCGWINSZ
#define	TIOCGWINSZ 	_IOR('t',0x04,struct winsize)
#define	TIOCHPCL 		TIOCHUPCL
#define	TIOCHUPCL 		_IOW('t',0x24,int)
#define	TIOCMBIC 		_IOW('t',0x0F,int)
#define	TIOCMBIS 		_IOW('t',0x0E,int)
#define	TIOCMODG 		_IOR('t',0x0C,int)
#define	TIOCMGET 		TIOCMODG
#define	TIOCMODS 		_IOW('t',0x0D,int)
#define	TIOCMSET 		TIOCMODS
#define	TIOCNXCL 		_IO('t',0x15)
#define	TIOCOUTQ 		_IOR('t',0x23,int)
#define	TIOCREMOTE 	_IOW('t',0x08,int)
#define	TIOCSBRK 		_IO('t',0x17)
#define	TIOCSCTTY 		_IO('t',0x9)
#define	TIOCSDTR 		_IO('t',0x19)
#define	TIOCSETA 		_IOW('t',0x1D,struct termios)
#define	TIOCSETAF		 _IOW('t',0x1F,struct termios)
#define	TIOCSETAR 		_IOW('t',0x20,struct termios)
#define	TIOCSETAW 		_IOW('t',0x1E,struct termios)
#define	TIOCSETD 		_IOW('t',0x11,int)
#define	TIOCSIG 		_IOWV('t',0x0A,int)
#define	TIOCSIGNAL 		TIOCSIG
#define	TIOCSSIZE 		TIOCSWINSZ
#define	TIOCSPGRP		 _IOW('t',0x13,int)
#define	TIOCSRTS 		_IO('t',0x1B)
#define	TIOCSTART 		_IO('t',0x03)
#define	TIOCSTI 		_IOW('t',0x06,int)
#define	TIOCSTOP 		_IO('t',0x02)
#define	TIOCSWINSZ 	_IOW('t',0x05,struct winsize)
#define	TIOCUCNTL 		_IOW('t',0x07,int)
#define	TTYDISC 		0x00
#define GIO_KEYMAP      _IOR('k', 6, keymap_t)
#define PIO_KEYMAP      _IOW('k', 7, keymap_t)



int _CRTAPI1 ioctl(int fd,int command,...);
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
}
#endif

#endif /*!defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)*/
struct winsize{
	unsigned short int ws_row; /*Row*/
	unsigned short int ws_col;  /*Column*/
	unsigned short int ws_xpixel; /*X-pixel*/
	unsigned short int ws_ypixel; /*Y-pixel*/
};

/* This is a pun for older SunOS code (3.2(?) and prior). It maps
 * onto struct winsize. Different structure and member names to do
 * the same thing. Don't write new or update code using this; use the
 * struct winsize above (more portable).
 */
struct ttysize {
	unsigned short ts_lines;	/* number of character rows */
	unsigned short ts_cols;		/* number of character columns */
	unsigned short ts_xxx;		/* number of pixels in X direction */
	unsigned short ts_yyy;		/* number of pixels in Y direction */
};

#endif /*_SYS_IOCTL_H*/




