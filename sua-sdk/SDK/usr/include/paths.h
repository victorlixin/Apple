/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * 
 * This Software Source is derived from software that is included 
 * in the 4.4BSD-Lite release which is copyrighted by The Regents 
 * of the University of California.  The Berkeley copyright appears 
 * elsewhere in this source module.
 * 
 * Modifications made to this Software Source are copyrighted by
 * Microsoft Corporation., and are the unpublished, valuable, confidential
 * property of Microsoft Corporation.  Use is therefore authorised only 
 * under the terms and conditions set out in the source code licence 
 * agreement protecting this Software Source.  Any unauthorised use or 
 * disclosure of this Software Source is prohibited.
 *
 * THESE SOFTWARE MODIFICATIONS ARE PROVIDED ``AS IS'' BY MICROSOFT CORP.
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *C-
 *
 */

/*
 * RCSid = $Header: /E/interix/include/paths.h,v 1.13 1999/11/01 16:06:34 mark Exp $
 */

#ifndef _PATHS_H_
#define	_PATHS_H_

#include <features.h>

/*
 * These paths are described as single rooted paths. 
 *
 * NOTE:
 *   For Interix/OpenNT 2.x and earlier the user needs to 
 *   prefix these paths with the installation root directory
 *   usually by using the _prefixInstallPath() API.
 *   This provides the most long term compatability.
 */

/* Provide trailing slash, since mostly used for building pathnames. */
#define	_PATH_BIN	"/bin/"
#define	_PATH_CONTRIB_BIN	"/usr/contrib/bin/"
#define	_PATH_DEV	"/dev/"
#define	_PATH_TMP	"/tmp/"
#define	_PATH_VARRUN	"/var/run/"
#define _PATH_PROC	"/proc/"
#define	_PATH_LOGFILES_DIR	"/var/adm/log/"

// historically, PATH_MAILDIR and PATH_MAN did not have trailing '/'
// even though they are directories
//
#define	_PATH_MAILDIR	"/var/mail"
#define	_PATH_MANDIR	"/usr/share/man"
#define	_PATH_MAN	_PATH_MANDIR		// obsolete - compatibility

/* program/file names */
#define	_PATH_BSHELL	"/bin/sh"
#define	_PATH_CSHELL	"/bin/csh"
#define	_PATH_KSHELL	"/bin/ksh"
#define	_PATH_TCSHELL	"/bin/tcsh"
#define	_PATH_DEVNULL	"/dev/null"
#define	_PATH_DEVFS	"/dev/fs"
#define	_PATH_LOGIN	"/bin/login"
#define	_PATH_NAMED	"/usr/sbin/named"
#define	_PATH_NAMEDXFER	"/usr/sbin/named-xfer"
#define	_PATH_NOLOGIN	"/etc/nologin"
#define	_PATH_SHELLS	"/etc/shells"
#define	_PATH_TTY	"/dev/tty"
#define	_PATH_VI	"/bin/vi"
#define _PATH_SENDMAIL	"/usr/sbin/sendmail"
#define _PATH_HEQUIV	"/etc/hosts.equiv"
#define _PATH_DEFPATH	"/bin"

/* Most programs want the traditional behaviour of cpp.
 * Thus, must use /lib/cpp
 */
#define	_PATH_CPP	"/lib/cpp"
#define	_PATH_CPP_NEW	_PATH_CONTRIB_BIN "cpp"

#endif /* !_PATHS_H_ */
