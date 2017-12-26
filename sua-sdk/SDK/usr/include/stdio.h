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
 *  Rcsid = $Header: /E/interix/include/stdio.h,v 1.25 1999/04/23 02:38:02 SSI_DEV+mark Exp $
 */ 

/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stdio.h	8.4 (Berkeley) 1/4/94
 */

#ifndef	_STDIO_H_
#define	_STDIO_H_

#include <features.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
# ifdef __cplusplus
#    define NULL        0
# else
#    define NULL        ((void *)0)
# endif /*__cplusplus*/
#endif /*NULL*/

typedef off_t fpos_t;

#define	BUFSIZ	1024		/* size of buffer used by setbuf */
#define	EOF	(-1)

/*
 * FOPEN_MAX is a minimum maximum, and is the number of streams that
 * stdio can provide without attempting to allocate further resources
 * (which could fail).  DO NOT USE this for anything.
 */
				/* must be >= _POSIX_STREAM_MAX <limits.h> */
#define	FOPEN_MAX	20	
#define	FILENAME_MAX	512	/* must be <= PATH_MAX <limits.h> */

#define	P_tmpdir	"/tmp/"
#define	L_tmpnam	1024	/* XXX must be >= PATH_MAX */

#ifndef TMP_MAX
#define	TMP_MAX		17576	/* 26 * 26 * 26 */
#endif

#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif
#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif
#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif

#if !defined (_IMPORT_LIBCDLL_GLOBALS)
#define	stdin	(&__sF[0])
#define	stdout	(&__sF[1])
#define	stderr	(&__sF[2])
#else
#include <globalexport.h>
#define stdin ((FILE*)libc_global(G_STDIN))
#define stdout ((FILE*)libc_global(G_STDOUT))
#define stderr ((FILE*)libc_global(G_STDERR))
#endif

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) \
			 || ((__STDC__ - 0 == 0) && !defined(_POSIX_C_SOURCE))

/* get definition of va_list */
#ifndef _VA_LIST_DEFINED
#include <va_list.h>
#endif /*_VA_LIST_DEFINED*/

#endif /*defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) ... */


#ifndef _VA_LIST_DEFINED
/* don't already have definition of va_list, so get __va_list definition */
#ifndef _HIDDEN_VA_LIST_DEFINED
#define _HIDDEN_VA_LIST		/* get hidden definition of __va_list */
#include <va_list.h>
#undef _HIDDEN_VA_LIST
#endif /* _HIDDEN_VA_LIST_DEFINED */
#endif /* _VA_LIST_DEFINED*/


#define	_FSTDIO			/* Define for BSD new stdio */

/*
 * NB: to fit things in six character monocase externals, the stdio
 * code uses the prefix `__s' for stdio objects, typically followed
 * by a three-character attempt at a mnemonic.
 */

/* stdio buffers */
struct __sbuf {
	unsigned char *_base;
	int	_size;
};

/* hold a buncha junk that would grow the ABI */
struct __sFILEX;

/*
 * stdio state variables.
 *
 * The following always hold:
 *
 *	if (_flags&(__SLBF|__SWR)) == (__SLBF|__SWR),
 *		_lbfsize is -_bf._size, else _lbfsize is 0
 *	if _flags&__SRD, _w is 0
 *	if _flags&__SWR, _r is 0
 *
 * This ensures that the getc and putc macros (or inline functions) never
 * try to write or read from a file that is in `read' or `write' mode.
 * (Moreover, they can, and do, automatically switch from read mode to
 * write mode, and back, on "r+" and "w+" files.)
 *
 * _lbfsize is used only to make the inline line-buffered output stream
 * code as compact as possible.
 *
 * _ub, _up, and _ur are used when ungetc() pushes back more characters
 * than fit in the current _bf, or when ungetc() pushes back a character
 * that does not match the previous one in _bf.  When this happens,
 * _ub._base becomes non-nil (i.e., a stream has ungetc() data iff
 * _ub._base!=NULL) and _up and _ur save the current values of _p and _r.
 *
 * NB: see WARNING above before changing the layout of this structure!
 */
typedef	struct __sFILE {
	unsigned char *_p;	/* current position in (some) buffer */
	int	_r;		/* read space left for getc() */
	int	_w;		/* write space left for putc() */
	short	_flags;		/* flags, below; this FILE is free if 0 */
	short	_file;		/* fileno, if Unix descriptor, else -1 */
	struct	__sbuf _bf;	/* the buffer (at least 1 byte, if !NULL) */
	int	_lbfsize;	/* 0 or -_bf._size, for inline putc */

	/* operations */
	void	*_cookie;	/* cookie passed to io functions */
	int	(*_close) (void *);
	int	(*_read)  (void *, char *, int);
	fpos_t	(*_seek)  (void *, fpos_t, int);
	int	(*_write) (void *, const char *, int);

	/* separate buffer for long sequences of ungetc() */
	struct	__sbuf _ub;	/* ungetc buffer */
	struct __sFILEX *_extra; /* additions to FILE to not break ABI */
	int	_ur;		/* saved _r when _r is counting ungetc data */

	/* tricks to meet minimum requirements even when malloc() fails */
	unsigned char _ubuf[3];	/* guarantee an ungetc() buffer */
	unsigned char _nbuf[1];	/* guarantee a getc() buffer */

	/* separate buffer for fgetln() when line crosses buffer boundary */
	struct	__sbuf _lb;	/* buffer for fgetln() */

	/* Unix stdio files get aligned to block boundaries on fseek() */
	int	_blksize;	/* stat.st_blksize (may be != _bf._size) */
	fpos_t	_offset;	/* current lseek offset (see WARNING) */
} FILE;

extern FILE __sF[];

#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimisation */
#define	__SNPT	0x0800		/* do not do fseek() optimisation */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
#define	__SMOD	0x2000		/* true => fgetln modified _p text */
#define	__SALC	0x4000		/* allocate string space dynamically */
#define	__SIGN	0x8000		/* ignore this file in _fwalk */

/*
 * The following three definitions are for ANSI C, which took them
 * from System V, which brilliantly took internal interface macros and
 * made them official arguments to setvbuf(), without renaming them.
 * Hence, these ugly _IOxxx names are *supposed* to appear in user code.
 *
 * Although numbered as their counterparts above, the implementation
 * does not rely on this.
 */
#define	_IOFBF	0		/* setvbuf should set fully buffered */
#define	_IOLBF	1		/* setvbuf should set line buffered */
#define	_IONBF	2		/* setvbuf should set unbuffered */

/*
 * Functions defined in ANSI C standard.
 */

#if defined ( _REENTRANT ) || (_POSIX_C_SOURCE - 0 >= 199506L)
extern void __cdecl flockfile(FILE *);
extern void __cdecl funlockfile(FILE *);
extern int __cdecl ftrylockfile(FILE *);
extern int __cdecl getc_unlocked(FILE *);
extern int __cdecl getchar_unlocked(void);
extern int __cdecl putc_unlocked(int, FILE *);
extern int __cdecl putchar_unlocked(int);
#endif /*_REENTRANT*/

extern void   __cdecl clearerr (FILE *);
extern int    __cdecl fclose (FILE *);
extern int    __cdecl feof (FILE *);
extern int    __cdecl ferror (FILE *);
extern int    __cdecl fflush (FILE *);
extern int    __cdecl fgetc (FILE *);
extern int    __cdecl fgetpos (FILE *, fpos_t *);
extern char * __cdecl fgets (char *, int, FILE *);
extern FILE * __cdecl fopen (const char *, const char *);
extern int    __cdecl fprintf (FILE *, const char *, ...);
extern int    __cdecl fputc (int, FILE *);
extern int    __cdecl fputs (const char *, FILE *);
extern size_t __cdecl fread (void *, size_t, size_t, FILE *);
extern FILE * __cdecl freopen (const char *, const char *, FILE *);
extern int    __cdecl fscanf (FILE *, const char *, ...);
extern int    __cdecl fseek (FILE *, long, int);
extern int    __cdecl fsetpos (FILE *, const fpos_t *);
extern long   __cdecl ftell (FILE *);
extern size_t __cdecl fwrite (const void *, size_t, size_t, FILE *);
extern int    __cdecl getc (FILE *);
extern int    __cdecl getchar (void);
extern char * __cdecl gets (char *);
extern void   __cdecl perror (const char *);
extern int    __cdecl printf (const char *, ...);
extern int    __cdecl putc (int, FILE *);
extern int    __cdecl putchar (int);
extern int    __cdecl puts (const char *);
extern int    __cdecl remove (const char *);
extern int    __cdecl rename  (const char *, const char *);
extern void    __cdecl rewind (FILE *);
extern int    __cdecl scanf (const char *, ...);
extern void   __cdecl setbuf (FILE *, char *);
extern int    __cdecl setvbuf (FILE *, char *, int, size_t);
extern int    __cdecl sprintf (char *, const char *, ...);
extern int    __cdecl asprintf(char **, char const *, ...);
extern int    __cdecl sscanf (const char *, const char *, ...);
extern FILE * __cdecl tmpfile (void);
extern char * __cdecl tmpnam (char *);
extern int    __cdecl ungetc (int, FILE *);
extern off_t ftello(FILE *fp);
extern int fseeko(FILE *, off_t, int);

#ifdef _VA_LIST_DEFINED
extern int    __cdecl vfprintf (FILE *, const char *, va_list);
extern int    __cdecl vprintf (const char *, va_list);
extern int    __cdecl vsprintf (char *, const char *, va_list);
extern int    __cdecl vasprintf (char **, const char *, va_list);
#else
extern int    __cdecl vfprintf (FILE *, const char *, __va_list);
extern int    __cdecl vprintf (const char *, __va_list);
extern int    __cdecl vsprintf (char *, const char *, __va_list);
extern int    __cdecl vasprintf (char **, const char *, __va_list);
#endif /*_VA_LIST_DEFINED*/

#if defined(_ALL_SOURCE) || defined(_POSIX_C_SOURCE) \
		 	 || defined(_XOPEN_SOURCE) || (__STDC__ - 0 == 0)
/*
 * Functions defined in POSIX 1003.1.
 */
#define   L_ctermid	1024	/* size for ctermid(); PATH_MAX */

char	* __cdecl ctermid (char *);
FILE	* __cdecl fdopen (int, const char *);
int	  __cdecl fileno (FILE *);


#endif /* _ALL_SOURCE ... */

#if (__STDC__ - 0 == 0) || _POSIX_C_SOURCE >= 2 || defined(_ALL_SOURCE) \
		        || defined(_XOPEN_SOURCE)
/* POSIX.2-1992 and XOPEN */
int   __cdecl pclose (FILE *);
FILE* __cdecl popen (const char *, const char *);
#endif /* POSIX.2 */

#if defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) \
			 || ((__STDC__ - 0 == 0) && !defined(POSIX_C_SOURCE))

extern char* __cdecl tempnam (const char *, const char *);
extern int   __cdecl getopt(int, char * const [], const char *);

#if !defined (_IMPORT_LIBCDLL_GLOBALS)
/* EXTERNAL VARIABLES for getopt() */
extern char *optarg;
extern int   optind, opterr, optopt;
#else
#include <globalexport.h>
#define optarg ((char*)libc_global(G_OPTARG))
#define optind (*((int*)libc_global(G_OPTIND)))
#define opterr (*((int*)libc_global(G_OPTERR)))
#define optopt (*((int*)libc_global(G_OPTOPT)))
#endif

#define	L_cuserid	128	/* size for cuserid(); UT_NAMESIZE */
extern char * __cdecl cuserid(char *);
extern int    __cdecl getw(FILE *);
extern int    __cdecl putw (int, FILE *);

#endif /*defined(_ALL_SOURCE) || defined(_XOPEN_SOURCE) .... */

/*
 * Routines that are purely local.
 */
#if (__STDC__-0==0) || defined (_ALL_SOURCE)  \
		    || (!defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE))
/* widechar routines */
extern int __cdecl wcs_remove (const wchar_t *);
extern int __cdecl wcs_rename (const wchar_t *, const wchar_t *);

extern char*	__cdecl fgetln (FILE *, size_t *);
extern int	__cdecl fpurge (FILE *);
extern void	__cdecl setbuffer (FILE *, char *, int);
extern int	__cdecl setlinebuf (FILE *);
extern int	__cdecl snprintf (char *, size_t, const char *, ...);

#ifdef _VA_LIST_DEFINED
extern int __cdecl vsnprintf (char *, size_t, const char *, va_list);
extern int __cdecl vscanf (const char *, va_list);
extern int __cdecl vsscanf (const char *, const char *, va_list);
#else
extern int __cdecl vsnprintf (char *, size_t, const char *, __va_list);
extern int __cdecl vscanf (const char *, __va_list);
extern int __cdecl vsscanf (const char *, const char *, __va_list);
#endif /* _VA_LIST_DEFINED */


/*
 * vfscanf is a #define because the function is used internally and
 * (unlike vfscanf) the name __vfscanf is guaranteed not to collide
 * with a user function when _ANSI_SOURCE or _POSIX_SOURCE is defined.
 */
#define	 vfscanf	__vfscanf

/*
 * Stdio function-access interface.
 */
FILE	*funopen (
		const void *,
		int (*)(void *, char *, int),
		int (*)(void *, const char *, int),
		fpos_t (*)(void *, fpos_t, int),
		int (*)(void *));
#define	fropen(cookie, fn) funopen(cookie, fn, 0, 0, 0)
#define	fwopen(cookie, fn) funopen(cookie, 0, fn, 0, 0)
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */

/*
 * Functions internal to the implementation.
 */
extern int	__cdecl __srget (FILE *);
extern int	__cdecl __swbuf (int, FILE *);
#ifdef _VA_LIST_DEFINED
extern int	__cdecl __vfscanf (FILE *, const char *, va_list);
#else
extern int	__cdecl __vfscanf (FILE *, const char *, __va_list);
#endif /* _VA_LIST_DEFINED */

/*
 * The __sfoo macros are here so that we can 
 * define function versions in the C library.
 */
#define	__sgetc(p) (--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))

#if defined(__GNUC__) && defined(__STDC__)
static __inline int __sputc(int _c, FILE *_p) {
	if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
		return (*_p->_p++ = _c);
	else
		return (__swbuf(_c, _p));
}
#else
/*
 * This has been tuned to generate reasonable code on the vax using pcc.
 */
#define	__sputc(c, p) \
	(--(p)->_w < 0 ? \
		(p)->_w >= (p)->_lbfsize ? \
			(*(p)->_p = (c)), *(p)->_p != '\n' ? \
				(int)*(p)->_p++ : \
				__swbuf('\n', p) : \
			__swbuf((int)(c), p) : \
		(*(p)->_p = (c), (int)*(p)->_p++))
#endif

#define	__sfeof(p)	(((p)->_flags & __SEOF) != 0)
#define	__sferror(p)	(((p)->_flags & __SERR) != 0)
#define	__sclearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	__sfileno(p)	((p)->_file)

#ifndef _REENTRANT
#ifndef lint
#define	getc(fp)	__sgetc(fp)
#define putc(x, fp)	__sputc(x, fp)
#define clearerr(fp)    __sclearerr(fp)
#define	feof(p)		__sfeof(p)
#define	ferror(p)	__sferror(p)
#define	fileno(p)	__sfileno(p)
#endif /* lint */

#define	getchar()	getc(stdin)
#define	putchar(x)	putc(x, stdout)

#endif /* _REENTRANT */
#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H_ */
