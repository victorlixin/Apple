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
 *   Rcsid = $Header: /E/interix/include/tar.h,v 1.4 1998/07/10 14:09:52 SSI_DEV+mark Exp $
 */

/*++
Copyright (c) 1992  Microsoft Corporation
Module Name:
	tar.h
Abstract:
	Stuff for the 'tar' data interchange format, as in 1003.1-88
	(10.1.1)
--*/

#ifndef _TAR_H_
#define _TAR_H_

#if defined(__cplusplus)
extern "C" {
#endif


#include <features.h>

#define TMAGIC	"ustar"		/* ustar and a nul	*/
#define TMAGLEN	6
#define TVERSION "00"		/* 00 and no nul	*/
#define TVERSLEN 2

/* Values used in typeflag field */

#define REGTYPE		'0'		/* regular file		*/
#define AREGTYPE	'\0'		/* regular file		*/
#define LNKTYPE		'1'		/* link			*/
#define SYMTYPE		'2'		/* symlink		*/
#define CHRTYPE		'3'		/* character special	*/
#define BLKTYPE		'4'		/* block special	*/
#define DIRTYPE		'5'		/* directory		*/
#define FIFOTYPE	'6'		/* FIFO special		*/
#define CONTTYPE	'7'		/* high-performance	*/

/* Bits used in the mode field -- values in octal */

#define TSUID	04000			/* set UID on execution		*/
#define TSGID	02000			/* set GID on execution 	*/
#define TSVTX	01000			/* reserved			*/
					/* File Permissions		*/
#define TUREAD	00400			/* read by owner		*/
#define TUWRITE 00200			/* write by owner		*/
#define TUEXEC	00100			/* execute/search by owner	*/
#define TGREAD	00040			/* read by group		*/
#define TGWRITE	00020			/* write by group		*/
#define TGEXEC	00010			/* execute/search by group	*/
#define TOREAD	00004			/* read by other		*/
#define TOWRITE 00002			/* write by other		*/
#define TOEXEC	00001			/* execute/search by other	*/


#if defined(__cplusplus)
}
#endif

#endif 	/* _TAR_H_ */
