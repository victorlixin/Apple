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

#ifndef _SYS_FAULT_H_
#define _SYS_FAULT_H_


#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Ordinals for hardware fault conditions, from System V.
 * When a process takes an unhandled exception, the NT exception code
 * is mapped onto one of these codes, and also onto a signal.
 * These values are used by the /proc interface: see <sys/procfs.h>.
 */

#define FLTWATCH	1
#define FLTKWATCH	2
#define FLTPRIV		3	/* STATUS_PRIVILEGED_INSTRUCTION */
#define FLTILL 		4
#define FLTBPT 		5	/* STATUS_BREAKPOINT */
#define FLTTRACE 	6	/* STATUS_SINGLE_STEP */
#define FLTSTACK 	7
#define FLTACCESS 	8	/* ACCESS_VIOLATION, DATATYPE_MISALIGNMENT */
#define FLTBOUNDS 	9
#define FLTIOVF 	10	/* INTEGER_OVERFLOW */
#define FLTIZDIV 	11	/* INTEGER_DIVIDE_BY_ZERO */
#define FLTFPE 		12	/* floating point exceptions */
#define FLTPAGE 	13
#define FLTEXCEPTION	14	/* unclassified NT exception */
#define FLTHARDERROR	15	/* NT hard error */


#if defined(__cplusplus)
}
#endif

#endif /* _SYS_FAULT_H */
