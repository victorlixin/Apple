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

#ifndef _INTERIX_ENV_H
#define _INTERIX_ENV_H 1
 
#ifndef _PWD_H_
#include <pwd.h>
#endif
#ifdef __cplusplus 
extern "C" { 
#endif 

typedef struct {
    char **array;
    size_t length;
    size_t capacity;
} env_t;

/*
 * action values
 */
#define ENV_APPEND	0
#define ENV_OVERRIDE	1
#define ENV_SETIFUNSET	2

extern env_t *	_CRTAPI1 env_alloc(void);
extern env_t *	_CRTAPI1 env_winlogin(struct passwd *);
extern env_t *	_CRTAPI1 env_login(struct passwd *);
extern env_t *	_CRTAPI1 env_cron(struct passwd *);
extern void	_CRTAPI1 env_free(env_t *);
extern char *	_CRTAPI1 env_get(env_t *,  char *);
extern int	_CRTAPI1 env_set(env_t *,  char *,  char *, int);
extern int	_CRTAPI1 env_unset(env_t *,  char *);
extern int	_CRTAPI1 env_put(env_t *,  char *, int);
extern char * 	_CRTAPI1 env_expand_win(env_t *,  char *);
extern void 	_CRTAPI1 env_strfree( char *);
extern int	_CRTAPI1 env_putarray(env_t *,  char **, int);
extern char **	_CRTAPI1 env_array(env_t*);

#ifdef __cplusplus 
}
#endif 
#endif /* _INTERIX_ENV_H */
