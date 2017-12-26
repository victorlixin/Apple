/*C+
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

/*
 * RCSid = $Header: //depot/InterixBSD/include/pty.h#1 2004/09/23 05:45:17 FAREAST\\ranas $
 */

#ifndef _PTY_H_
#define _PTY_H_ 1

#include <termios.h>
#include <sys/ioctl.h>

#define PTY_MASTER_DEV          "/dev/ptmx" 

#ifdef __cplusplus
extern "C" {
#endif

/*
 * openpty(master, slave, name, termp, winsizep); 
 * forkpty(master, name, termp, winsizep);
 */
extern int openpty(int*, int*, char *, struct termios *, struct winsize *);
extern pid_t forkpty(int*, char*, struct termios *, struct winsize *);


#ifdef __cplusplus
}
#endif

#endif /* _PTY_H_ */
