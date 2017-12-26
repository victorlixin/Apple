/* dlfcn.h -- User functions for run-time dynamic loading.
   Copyright (C) 1995, 1996 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef	_DLFCN_H

#define	_DLFCN_H 1
#include <features.h>

/* The MODE argument to `dlopen' contains one of the following: */
#define RTLD_LAZY	0x001	/* Lazy function call binding.  */
#define RTLD_NOW	0x002	/* Immediate function call binding.  */
#ifdef _ALL_SOURCE
#define	RTLD_BINDING_MASK 0x3	/* Mask of binding time value.  */
#endif

/* If the following bit is set in the MODE argument to `dlopen',
   the symbols of the loaded object and its dependencies are made
   visible as if the object were linked directly into the program.  */
#define RTLD_GLOBAL	0x100
#define RTLD_LOCAL	0

#ifdef _ALL_SOURCE
/* If the first argument of `dlsym' is set to RTLD_NEXT the run-time
   address of the symbol called NAME in the next shared object is
   returned.  The "next" relation is defined by the order the shared
   objects were loaded.  */
#define RTLD_NEXT	((void *) -1l)
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* Open the shared object FILE and map it in; return a handle that can be
   passed to `dlsym' to get symbol values from it.  */
extern void *dlopen (const char *, int);

/* Unmap and close a shared object opened by `dlopen'.
   The handle cannot be used again after calling `dlclose'.  */
extern int dlclose (void *);

/* Find the run-time address in the shared object HANDLE refers to
   of the symbol called NAME.  */
extern void *dlsym (void *, const char *);

/* When any of the above functions fails, call this function
   to return a string describing the error.  Each call resets
   the error string so that a following call returns null.  */
extern char *dlerror (void);

#ifdef _ALL_SOURCE
/* Fill in *INFO with the following information about ADDRESS.
   Returns 0 iff no shared object's segments contain that address.  */
typedef struct
  {
    const char *dli_fname;	/* File name of defining object.  */
    void *dli_fbase;		/* Load address of that object.  */
    const char *dli_sname;	/* Name of nearest symbol.  */
    void *dli_saddr;		/* Exact value of nearest symbol.  */
  } Dl_info;

extern int dladdr (void *__address, Dl_info *__info);
#endif

#ifdef  __cplusplus
}
#endif

#endif	/* dlfcn.h */
