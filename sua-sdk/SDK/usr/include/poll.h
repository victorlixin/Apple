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
#ifndef _POLL_H_
#define _POLL_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <features.h>

#define POLLIN	    0x0001
#define POLLRDNORM  0x0002
#define POLLRDBAND  0x0004
#define POLLPRI	    0x0008
#define POLLOUT	    POLLWRNORM
#define POLLWRNORM  0x0010
#define POLLWRBAND  0x0020
#define POLLERR	    0x0040
#define POLLHUP	    0x0080
#define POLLNVAL    0x0100

struct pollfd {
   int		fd;
   short int	events;
   short int	revents;
};

typedef unsigned int nfds_t;

int _CRTAPI1 poll(struct pollfd fds[], nfds_t nfds, int timeout);

#if defined(__cplusplus)
}
#endif

#endif /* _POLL_H_ */
