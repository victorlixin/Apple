#ifndef _MMAN_H
#define _MMAN_H
#if defined(__cplusplus) || defined(__CPLUSPLUS__)
extern "C" {
#endif

#include <sys/types.h>

/*Protection flags*/
#define PROT_NONE 			0x00
#define PROT_READ 			0x01
#define PROT_WRITE 			0x02
#define PROT_EXEC 			0x04
#define PROC_DATA 			PROT_READ|PROT_WRITE
#define PROC_TEXT 			PROT_READ|PROT_EXEC


#define SHARED 				0x10
#define PRIVATE 				0x20



/*Sharing flags*/
#define MAP_SHARED 			0x01
#define MAP_PRIVATE 		0x02
#define MAP_FIXED 			0x10


/*Additional sharing flags*/
#define MAP_VARIABLE 		0x000
#define MAP_COPY 			0x010
#define MAP_RENAME 			0x020
#define MAP_NORESERVE 		0x040
#define MAP_INHERIT 		0x080
#define MAP_NOEXTEND 		0x100
#define MAP_HASSEMAPHORE 	0x200


/*Mapping type flags*/
#define MAP_ANON 			0x1000
#define MAP_ANONYMOUS 		0x1000
#define MAP_FILE 			0x0000

/*Madvise flags*/

#define MADV_NORMAL 		0x00
#define MADV_RANDOM 		0x01
#define MADV_SEQUENTIAL 	0x02
#define MADV_WILLNEED 		0x03
#define MADV_DONTNEED 		0x04

/*Msync flags*/
#define MS_SYNC 				0x01
#define MS_ASYNC 			0x02
#define MS_INVALIDATE 		0x04


/*Memcntl flags*/
#define MC_SYNC 				0x01
#define MC_ADVISE 			0x04
#define MC_PROTECT 			0x07

#define MAP_FAILED 			(void*)(-1)

int 		_CRTAPI1 madvise(void*, size_t, int);
int    		_CRTAPI1 mctl(void *, size_t, int, int);
int 		_CRTAPI1 memcntl(void*, size_t, int, void*, int, int);
void * 		_CRTAPI1 mmap  (void *, size_t, int, int, int, off_t);
int  		_CRTAPI1 mprotect(void *, size_t, int);
int  		_CRTAPI1 msync(void *, size_t, int);
int  		_CRTAPI1 munmap(void *, size_t);

#if defined(__cplusplus) || defined(__CPLUSPLUS__)
}
#endif

#endif /*_MMAN_H*/
