#ifndef _UN_H
#define _UN_H
#if defined(_ALL_SOURCE) || !defined(_XOPEN_SOURCE_EXTENDED) 
#include<sys/socket.h>
#else
#include<sys/types.h>
#endif
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif

#if defined(_ALL_SOURCE) || !defined(_XOPEN_SOURCE_EXTENDED) 
#define SUN_LEN(p1) ((sizeof((p1)->sun_family) + (strlen((p1)->sun_path)*sizeof(char)) ))	
#endif

#define SUN_PATH 104

struct sockaddr_un{
	sa_family_t 		sun_family;
	char 			sun_path[SUN_PATH];
};
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
}
#endif

#endif /*_UN_H*/

