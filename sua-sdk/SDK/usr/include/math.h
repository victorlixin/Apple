/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * from: @(#)fdlibm.h 5.1 93/09/24
 * $FreeBSD: src/lib/msun/src/math.h,v 1.55 2005/02/04 14:08:32 das Exp $
 */

#ifndef _MATH_H_
#define	_MATH_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __ISO_C_VISIBLE 2000
#define __BSD_VISIBLE 500
#define __XSI_VISIBLE 200

static __inline double getInf()
{
        double d;
        int *p=(int *)&d;
        *p=0x00000000;
        *(p+1)=0x7ff00000;
        return d;
}

static __inline double getNAN()
{
        double d;
        int *p=(int *)&d;
        *p=0x00000000;
        *(p+1)=0x7fff0000;
        return d;
}


/*
 * ANSI/POSIX
 */
/*extern const union __infinity_un {
	unsigned char	__uc[8];
	double		__ud;
} __infinity;

extern const union __nan_un {
	unsigned char	__uc[sizeof(float)];
	float		__uf;
} __nan;*/

#ifdef __MATH_BUILTIN_CONSTANTS
#define	HUGE_VAL	__builtin_huge_val()
#else
#define HUGE_VAL        getInf()
#endif

#if __ISO_C_VISIBLE >= 1999
#define	FP_ILOGB0	(-INT_MAX)
#define	FP_ILOGBNAN	INT_MAX

#ifdef __MATH_BUILTIN_CONSTANTS
#define	HUGE_VALF	__builtin_huge_valf()
#define	HUGE_VALL	__builtin_huge_vall()
#define	INFINITY	__builtin_inf()
#define	NAN		__builtin_nan("")
#else
#define	HUGE_VALF	(float)HUGE_VAL
#define	HUGE_VALL	(double)HUGE_VAL
#define INFINITY        getInf()
#define NAN             getNAN()
#endif /* __MATH_BUILTIN_CONSTANTS */

#define	MATH_ERRNO	1
#define	MATH_ERREXCEPT	2
#define	math_errhandling	MATH_ERREXCEPT

#ifdef	__ia64__
#define	FP_FAST_FMA
#endif
#define	FP_FAST_FMAF

/* Symbolic constants to classify floating point numbers. */
#define	FP_INFINITE	0x01
#define	FP_NAN		0x02
#define	FP_NORMAL	0x04
#define	FP_SUBNORMAL	0x08
#define	FP_ZERO		0x10
/* fixing this macros as long double = double for us. */

#define	fpclassify(x) \
    ((sizeof (x) == sizeof (float)) ? __fpclassifyf(x) \
    : __fpclassifyd(x))

#define	isfinite(x)					\
    ((sizeof (x) == sizeof (float)) ? __isfinitef(x)	\
    : __isfinite(x))
    
#define	isinf(x)					\
    ((sizeof (x) == sizeof (float)) ? isinff(x)	\
    :	isinf(x))

#define	isnan(x)					\
    ((sizeof (x) == sizeof (float)) ? isnanf(x)		\
    : isnan(x))

#define	isnormal(x)					\
    ((sizeof (x) == sizeof (float)) ? __isnormalf(x)	\
    : __isnormal(x))

#ifdef __MATH_BUILTIN_RELOPS
#define	isgreater(x, y)		__builtin_isgreater((x), (y))
#define	isgreaterequal(x, y)	__builtin_isgreaterequal((x), (y))
#define	isless(x, y)		__builtin_isless((x), (y))
#define	islessequal(x, y)	__builtin_islessequal((x), (y))
#define	islessgreater(x, y)	__builtin_islessgreater((x), (y))
#define	isunordered(x, y)	__builtin_isunordered((x), (y))
#else
#define	isgreater(x, y)		(!isunordered((x), (y)) && (x) > (y))
#define	isgreaterequal(x, y)	(!isunordered((x), (y)) && (x) >= (y))
#define	isless(x, y)		(!isunordered((x), (y)) && (x) < (y))
#define	islessequal(x, y)	(!isunordered((x), (y)) && (x) <= (y))
#define	islessgreater(x, y)	(!isunordered((x), (y)) && \
					((x) > (y) || (y) > (x)))
#define	isunordered(x, y)	(isnan(x) || isnan(y))
#endif /* __MATH_BUILTIN_RELOPS */

#define	signbit(x)					\
    ((sizeof (x) == sizeof (float)) ? __signbitf(x)	\
    :__signbit(x))
 
typedef	double	double_t;
typedef	float 	float_t;
#endif /* __ISO_C_VISIBLE >= 1999 */

/*
 * XOPEN/SVID
 */
#if __BSD_VISIBLE || __XSI_VISIBLE
#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

#define	MAXFLOAT	((float)3.40282346638528860e+38)
extern int signgam;
#endif /* __BSD_VISIBLE || __XSI_VISIBLE */

#if __BSD_VISIBLE
#if 0
/* Old value from 4.4BSD-Lite math.h; this is probably better. */
#define	HUGE		HUGE_VAL
#else
#define	HUGE		MAXFLOAT
#endif
#endif /* __BSD_VISIBLE */

/*
 * Most of these functions depend on the rounding mode and have the side
 * effect of raising floating-point exceptions, so they are not declared
 * as __pure2.  In C99, FENV_ACCESS affects the purity of these functions.
 */
__BEGIN_DECLS
/*
 * ANSI/POSIX
 */
 // added from libc/gen. Our libc does not have this file.
int     __fpclassifyd(double);
int     __fpclassifyf(float);
			
int     __isfinitef(float);
int     __isfinite(double);
int     isinff(float);
int     __isnormalf(float);
int     __isnormal(double);
int     __signbit(double);
int     __signbitf(float);
double	acos(double);
double	asin(double);
double	atan(double);
double	atan2(double, double);
double	cos(double);
double	sin(double);
double	tan(double);

double	cosh(double);
double	sinh(double);
double	tanh(double);

double	exp(double);
double	frexp(double, int *);	/* fundamentally !__pure2 */
double	ldexp(double, int);
double	log(double);
double	log10(double);
double	modf(double, double *);	/* fundamentally !__pure2 */

double	pow(double, double);
double	sqrt(double);

double	ceil(double);
double  fabs(double) ;
double	floor(double);
double	fmod(double, double);

/*
 * These functions are not in C90.
 */
#if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE
double	acosh(double);
double	asinh(double);
double	atanh(double);
double	cbrt(double);
double	erf(double);
double	erfc(double);
double	expm1(double);
double	hypot(double, double);
/* Our ilogb raises no exceptions; we side with IEEE-754R and C99, not POSIX */
int     ilogb(double) ;
int     (isinf)(double) ;
int     (isnan)(double) ;
double	lgamma(double);
//long long llrint(double);
//long long llround(double);
double	log1p(double);
double	logb(double);
double	nextafter(double, double);
double	remainder(double, double);
double	rint(double);
#endif /* __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999 || __XSI_VISIBLE */

#if __BSD_VISIBLE || __XSI_VISIBLE
double	j0(double);
double	j1(double);
double	jn(int, double);
double	scalb(double, double);
double	y0(double);
double	y1(double);
double	yn(int, double);

#if __XSI_VISIBLE <= 500 || __BSD_VISIBLE
double	gamma(double);
#endif
#endif /* __BSD_VISIBLE || __XSI_VISIBLE */

#if __BSD_VISIBLE || __ISO_C_VISIBLE >= 1999
double  copysign(double, double) ;
double	fdim(double, double);
double  fmax(double, double) ;
double  fmin(double, double) ;
double	scalbln(double, long);
double	scalbn(double, int);
double	tgamma(double);
double	trunc(double);
#endif

/*
 * BSD math library entry points
 */
#if __BSD_VISIBLE
double	drem(double, double);
int     finite(double) ;
int     isnanf(float) ;

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
double	gamma_r(double, int *);
double	lgamma_r(double, int *);

/*
 * IEEE Test Vector
 */
double	significand(double);
#endif /* __BSD_VISIBLE */

/* float versions of ANSI/POSIX functions */
#if __ISO_C_VISIBLE >= 1999
float	acosf(float);
float	asinf(float);
float	atanf(float);
float	atan2f(float, float);
float	cosf(float);
float	sinf(float);
float	tanf(float);

float	coshf(float);
float	sinhf(float);
float	tanhf(float);

float	expf(float);
float	expm1f(float);
float	frexpf(float, int *);	/* fundamentally !__pure2 */
int     ilogbf(float) ;
float	ldexpf(float, int);
float	log10f(float);
float	log1pf(float);
float	logf(float);
float	modff(float, float *);	/* fundamentally !__pure2 */

float	powf(float, float);
float	sqrtf(float);

float	ceilf(float);
float   fabsf(float) ;
float	floorf(float);
float	fmodf(float, float);

float	erff(float);
float	erfcf(float);
float	hypotf(float, float);
float	lgammaf(float);

float	acoshf(float);
float	asinhf(float);
float	atanhf(float);
float	cbrtf(float);
float	logbf(float);
float   copysignf(float, float) ;
// we have long as long long in 32 bit
//long long llrintf(float);
//long long llroundf(float);
float	nextafterf(float, float);
float	remainderf(float, float);
float	rintf(float);
float	scalblnf(float, long);
float	scalbnf(float, int);
float	truncf(float);

float	fdimf(float, float);
float   fmaxf(float, float) ;
float   fminf(float, float) ;
#endif

/*
 * float versions of BSD math library entry points
 */
#if __BSD_VISIBLE
float	dremf(float, float);
int     finitef(float) ;
float	gammaf(float);
float	j0f(float);
float	j1f(float);
float	jnf(int, float);
float	scalbf(float, float);
float	y0f(float);
float	y1f(float);
float	ynf(int, float);

/*
 * Float versions of reentrant version of gamma & lgamma; passes
 * signgam back by reference as the second argument; user must
 * allocate space for signgam.
 */
float	gammaf_r(float, int *);
float	lgammaf_r(float, int *);

/*
 * float version of IEEE Test Vector
 */
float	significandf(float);
#endif	/* __BSD_VISIBLE */

/*
 * double versions of ISO/POSIX math functions
 */
#if __ISO_C_VISIBLE >= 1999
#if 0
double	acoshl(double);
double	acosl(double);
double	asinhl(double);
double	asinl(double);
double	atan2l(double, double);
double	atanhl(double);
double	atanl(double);
double	cbrtl(double);
#endif

#if 0
double	coshl(double);
double	cosl(double);
double	erfcl(double);
double	erfl(double);
double	exp2l(double);
double	expl(double);
double	expm1l(double);
#endif
#if 0
double	fmal(double, double, double);
#endif

#if 0
double	fmodl(double, double);
double     frexpl(double value, int *); /* fundamentally ! */
double	hypotl(double, double);
#endif

#if 0
double	ldexpl(double, int);
double	lgammal(double);
long long	llrintl(double);
long long	llroundl(double);
double	log10l(double);
double	log1pl(double);
double	log2l(double);
double	logbl(double);
double	logl(double);
long		lrintl(double);
long		lroundl(double);
double     modfl(double, double *); /* fundamentally ! */
double     nanl(const char *) ;
double	nearbyintl(double);
double	nextafterl(double, double);
double		nexttoward(double, double);
float		nexttowardf(float, double);
double	nexttowardl(double, double);
double	powl(double, double);
double	remainderl(double, double);
double	remquol(double, double, int *);
double	rintl(double);
double	roundl(double);
double	scalblnl(double, long);
double	scalbnl(double, int);
double	sinhl(double);
double	sinl(double);
double	sqrtl(double);
double	tanhl(double);
double	tanl(double);
double	tgammal(double);
double	truncl(double);
#endif

#endif /* __ISO_C_VISIBLE >= 1999 */
__END_DECLS

#ifndef __cplusplus
#define __fpclassifyl __fpclassifyd
#define isinfl isinf
#define  __isnanl isnan
#define  __isnormall __isnormal
#define __signbitl __signbit
#define fabsl fabs
#define fdiml fdim
#define floorl floor
#define fmaxl fmax
#define fminl fmin
#define ilogbl ilogb
#define ceill ceil
#define copysignl copysign
#endif

#undef __ISO_C_VISIBLE
#undef __BSD_VISIBLE
#undef __XSI_VISIBLE

#ifndef __cplusplus
#include<complex.h>
#endif /* __cplusplus */

/* Function prototypes */

unsigned int __cdecl _clearfp(void);
unsigned int __cdecl _controlfp(unsigned int,unsigned int);
unsigned int __cdecl _statusfp(void);
void __cdecl _fpreset(void);

#if defined(_M_IX86)
	void _statusfp2(unsigned int *pX86, unsigned int *pSSE2);
#endif

#define _clear87        _clearfp
#define _status87       _statusfp

/*
 * Abstract User Status Word bit definitions
 */

#define _SW_INEXACT     0x00000001              /* inexact (precision) */
#define _SW_UNDERFLOW   0x00000002              /* underflow */
#define _SW_OVERFLOW    0x00000004              /* overflow */
#define _SW_ZERODIVIDE  0x00000008              /* zero divide */
#define _SW_INVALID     0x00000010              /* invalid */
#define _SW_DENORMAL    0x00080000              /* denormal status bit */

/*
 * New Control Bit that specifies the ambiguity in control word.
 */
#define _EM_AMBIGUIOUS  0x80000000
/*
 * Abstract User Control Word Mask and bit definitions
 */
#define _MCW_EM         0x0008001f              /* interrupt Exception Masks */
#define _EM_INEXACT     0x00000001              /*   inexact (precision) */
#define _EM_UNDERFLOW   0x00000002              /*   underflow */
#define _EM_OVERFLOW    0x00000004              /*   overflow */
#define _EM_ZERODIVIDE  0x00000008              /*   zero divide */
#define _EM_INVALID     0x00000010              /*   invalid */
#define _EM_DENORMAL    0x00080000              /* denormal exception mask (_control87 only) */

#define _MCW_RC         0x00000300              /* Rounding Control */
#define _RC_NEAR        0x00000000              /*   near */
#define _RC_DOWN        0x00000100              /*   down */
#define _RC_UP          0x00000200              /*   up */
#define _RC_CHOP        0x00000300              /*   chop */

/*
 * i386 specific definitions
 */
#define _MCW_PC         0x00030000              /* Precision Control */
#define _PC_64          0x00000000              /*    64 bits */
#define _PC_53          0x00010000              /*    53 bits */
#define _PC_24          0x00020000              /*    24 bits */

#define _MCW_IC         0x00040000              /* Infinity Control */
#define _IC_AFFINE      0x00040000              /*   affine */
#define _IC_PROJECTIVE  0x00000000              /*   projective */

/*
 * RISC specific definitions
 */

#define _MCW_DN         0x03000000              /* Denormal Control */
#define _DN_SAVE        0x00000000              /*   save denormal results and operands */
#define _DN_FLUSH       0x01000000              /*   flush denormal results and operands to zero */
#define _DN_FLUSH_OPERANDS_SAVE_RESULTS 0x02000000  /*   flush operands to zero and save results */
#define _DN_SAVE_OPERANDS_FLUSH_RESULTS 0x03000000  /*   save operands and flush results to zero */

/* initial Control Word value */

#if     defined(_M_IX86)

#define _CW_DEFAULT ( _RC_NEAR + _PC_53 + _EM_INVALID + _EM_ZERODIVIDE + _EM_OVERFLOW + _EM_UNDERFLOW + _EM_INEXACT + _EM_DENORMAL)

#elif   defined(_M_IA64)

#define _CW_DEFAULT ( _RC_NEAR + _PC_64 + _EM_INVALID + _EM_ZERODIVIDE + _EM_OVERFLOW + _EM_UNDERFLOW + _EM_INEXACT + _EM_DENORMAL)

#elif   defined(_M_AMD64)

#define _CW_DEFAULT ( _RC_NEAR + _EM_INVALID + _EM_ZERODIVIDE + _EM_OVERFLOW + _EM_UNDERFLOW + _EM_INEXACT + _EM_DENORMAL)

#endif

unsigned int __cdecl _control87(unsigned int,unsigned int);
#if defined(_M_IX86)
int __control87_2(unsigned int newctrl, unsigned int mask,
                          unsigned int* x86_cw, unsigned int* sse2_cw);
#endif


#ifdef __cplusplus
}
#endif
#endif /* !_MATH_H_ */
