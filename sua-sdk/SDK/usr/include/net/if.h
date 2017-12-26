 
#ifndef _NET_IF_H_
#define _NET_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IF_NAMESIZE	256

char * __cdecl if_indextoname(unsigned int ifindex,  char *name);
unsigned int __cdecl if_nametoindex(const char *);

#ifdef __cplusplus
}
#endif


#endif
