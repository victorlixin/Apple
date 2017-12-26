/*C+
 * 
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
 * Rcsid = $Header: /E/interix/include/cpio.h,v 1.1 1999/01/18 19:52:26 SSI_DEV+mark Exp $
 */ 

#ifndef _CPIO_H_
#define _CPIO_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * values needed by the c_mode field in a cpio archive header
 */
#define C_IRUSR         0000400
#define C_IWUSR         0000200
#define C_IXUSR         0000100
#define C_IRGRP         0000040
#define C_IWGRP         0000020
#define C_IXGRP         0000010
#define C_IROTH         0000004
#define C_IWOTH         0000002
#define C_IXOTH         0000001
#define C_ISUID         0004000
#define C_ISGID         0002000
#define C_ISVTX         0001000
#define C_ISDIR         0040000
#define C_ISFIFO        0010000
#define C_ISREG         0100000
#define C_ISBLK         0060000
#define C_ISCHR         0020000
#define C_ISCTG         0110000
#define C_ISLNK         0120000
#define C_ISSOCK        0140000

/* magic symbol used to identify the particular type of 
 * cpio archive header format
 */
#define MAGIC           "070707"    /* fields interpreted as octal numbers*/

#ifdef  __cplusplus
}
#endif

#endif /* _CPIO_H_ */
