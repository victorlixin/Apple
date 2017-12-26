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

/*
 * RCSID = $Header: /E/interix/include/locale.h,v 1.7 2000/02/11 08:53:50 NORTHAMERICA+markfunk Exp $
 */

#ifndef _LOCALE_INTERIX_H_
#define _LOCALE_INTERIX_H_


#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>

/* Locale categories */

#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5
#define LC_MESSAGES     6

#define _LC_FIRST	LC_ALL
#define _LC_LAST	LC_MESSAGES
#define LC_MAX 		LC_MESSAGES

#define _LC_DIR_DEFAULT           "/usr/share/locale/"
#define _LC_DATA_DIR_DEFAULT      "/usr/share/localedef/"
#define _LC_DIR_CHARMAPS_NAME     "charmaps"

struct lconv {
        char *decimal_point;
        char *thousands_sep;
        char *grouping;
        char *int_curr_symbol;
        char *currency_symbol;
        char *mon_decimal_point;
        char *mon_thousands_sep;
        char *mon_grouping;
        char *positive_sign;
        char *negative_sign;
        char int_frac_digits;
        char frac_digits;
        char p_cs_precedes;
        char p_sep_by_space;
        char n_cs_precedes;
        char n_sep_by_space;
        char p_sign_posn;
        char n_sign_posn;
        };

/* function prototypes */

extern char * __cdecl setlocale(int __category, const char *__locale);
extern struct lconv * __cdecl localeconv(void);

#ifndef NULL
# ifdef __cplusplus
#    define NULL        0
# else
#    define NULL        ((void *)0)
# endif /*__cplusplus*/
#endif /*NULL*/


#if defined(__cplusplus)
}
#endif

#endif /* _LOCALE_INTERIX_H_ */
