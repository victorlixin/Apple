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
 * RCSID = $Header: /E/interix/include/sys/mkdev.h,v 1.3 2000/03/27 22:28:14 jamespar Exp $
 *
 */

#ifndef _SYS_MKDEV_H_
#define _SYS_MKDEV_H_

/*
 * Interix major device numbers.  These will be found
 * in major(st_dev), major(st_rdev).
 */

/*
 * tty-type devices.
 */
#define S_DEV_TTY	   1        /* /dev/ttyn[00-63] */
#define S_DEV_CONSOLE	   2        /* /dev/console */
#define S_DEV_CTRL_TTY	   3        /* /dev/tty */
#define S_DEV_PTM	   4        /* /dev/pty?? [p0-Ef]*/
#define S_DEV_PTS	   5        /* /dev/tty?? [p0-Ef]*/
#define S_DEV_PTMX	   6        /* /dev/ptmx */
#define S_DEV_SERIAL	   7        /* /dev/tty?? [00-1f] */

/*
 * stream-type devices.
 */
#define S_DEV_TAPE	  17        /* /dev/tape? */
#define S_DEV_PIPE	  18        /* User created FIFO */
#define S_DEV_SOCKET	  19        /* User created socket */
#define S_DEV_XTI	  20        /* User created */

/*
 * Virtual filesystem devices.
 */
#define S_DEV_PROC	  32        /* /proc */
#define S_DEV_PSTAT	  33        /* /proc/nn */
#define S_DEV_NET	  34        /* /net */
#define S_DEV_DEV	  35        /* internal use */
#define S_DEV_DRVLST	  36        /* internal use*/
#define S_DEV_MEM	  37	    /* internal use */

/*
 * Char/block special file types.
 */
#define S_DEV_SPECIAL	  48        /* /dev/null and other specials */

// Minor device numbers for specials
//
#define _MINOR_NULL       	0  
			    //  1 - historically /dev/tty 
#define _MINOR_FULL       	2  
#define _MINOR_ZERO       	3  
			    //  4 - unused 
#define _MINOR_RANDOM     	5  
#define _MINOR_URANDOM    	6  



#define S_DEV_DISK	  52        /* internal use */
#define S_DEV_VOLUME	  53        /* internal use */

/*
 * Filesystem types.
 */
#define S_DEV_ROOT	  64        /* internal use */
#define S_DEV_DRIVE	  65        /* internal use */
#define S_DEV_LFS	  66        /* internal use */
#define S_DEV_NFS	  67        /* internal use */
#define S_DEV_CIFS	  68        /* internal use */
#define S_DEV_UNC	  69        /* internal use */


#define major(x)	((0 == ((x)&0xff000000))?(x):((x)>>24))
#define minor(x)	((0 == ((x)&0xff000000))?0:((x)&0x00ffffff))
#define mkdev(x, y)	(((x)<<24)|((y)&0x00ffffff))

#endif /* _SYS_MKDEV_H_ */
