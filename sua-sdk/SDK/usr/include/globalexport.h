/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *
 * This header contains the enumeration of all global varibales in the libc.
 * 
 * The function libc_global() retrives the value or pointer of the global 
 * variable that exists in libc built as a Windows DLL with appropriate 
 * l/r value.
 */

#ifndef _GLOBALEXPORT_H_
#define _GLOBALEXPORT_H_
#ifdef __cplusplus 
extern "C" { 
#endif 

typedef enum _LIBC_GLOBAL_T {
    G_STDIN,          /* FILE*           : stdin           :  r-value */
    G_STDOUT,         /* FILE*           : stdout          :  r-value */
    G_STDERR,         /* FILE*           : stderr          :  r-value */
    G_GETDATE_ERR,    /* int             : getdate_err     : lr-value */
    G_OPTARG,         /* char*           : optarg          : lr-value */ 
    G_OPTRESET,       /* int             : optrest         : lr-value */
    G_OPTOPT,         /* int             : optopt          : lr-value */
    G_OPTIND,         /* int             : optopt          : lr-value */
    G_OPTERR,         /* int             : opterr          : lr-value */
    G_SUBOPTARG,      /* char*           : suboptarg       : lr-value */
    G_TZNAME,         /* char**          : tzname          : lr-value */
    G_TIMEZONE,       /* long int        : timezone        : lr-value */
    G_DAYLIGHT,       /* int             : daylight        : lr-value */
    G_PWCACHE_ENABLE, /* int             : pwcache_enable  : lr-value */
    G_MB_CUR_MAX,     /* int             : __mb_cur_max    :  r-value */
    G_ICTYPE,         /* unsigned short* : _ictype         : lr-value */
    G_SYS_NSIG,       /* int             : _sys_nsig       :  r-value */
    G_SYS_SIGLIST,    /* char **         : _sys_siglist    : lr-value */
    G_SYS_SIGNAME     /* char **         : _sys_signame    : lr-value */
} LIBC_GLOBAL_ENUM;

void * libc_global(LIBC_GLOBAL_ENUM);
#ifdef __cplusplus 
}
#endif 

#endif

