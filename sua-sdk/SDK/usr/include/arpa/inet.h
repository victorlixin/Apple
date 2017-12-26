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

#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_


#if defined(__cplusplus)
extern "C" {
#endif

#include <netinet/in.h>
#include <sys/endian.h>	 /* for _BYTE_ORDER */

in_addr_t htonl(in_addr_t hostlong);
in_port_t htons(in_port_t hostshort);
in_addr_t ntohl(in_addr_t netlong);
in_port_t ntohs(in_port_t netshort);

#if _BYTE_ORDER == _BIG_ENDIAN 
/* don't need library routines for these on a BIG_ENDIAN machine */
#define htonl(x) (x)
#define htons(x) (x)
#define ntohl(x) (x)
#define ntohs(x) (x)
#endif  /* BIG_ENDIAN */

in_addr_t      inet_addr(const char *);
in_addr_t      inet_lnaof(struct in_addr);
struct in_addr inet_makeaddr(in_addr_t, in_addr_t );
in_addr_t      inet_netof(struct in_addr );
in_addr_t      inet_network(const char *);
char*          inet_ntoa(struct in_addr );
int	       inet_aton(const char *, struct in_addr *);
const char	*inet_ntop(int, const void * , char * , int);
int		 inet_pton(int, const char * , void * );

#if defined(__cplusplus)
}
#endif


#endif /* _ARPA_INET_H_ */
