#ifndef INVOKE_H
#define INVOKE_H

extern void* invoke(void* id, void* a, void* b, void* c, void* d, void* e, void* f);


#define INVOKE(id, a, b, c, d, e, f) invoke((void*)(id), (void*)(a), (void*)(b), (void*)(c), (void*)(d), (void*)(e), (void*)(f))
#define NULL (void*)0

#define SYS_READ(fd, buff, count) INVOKE(0, fd, buff, count, NULL, NULL, NULL)
#define SYS_WRITE(fd, buff, count) INVOKE(1, fd, buff, count, NULL, NULL, NULL)
#define SYS_OPEN(filename, flags, mode) INVOKE(2, filename, flags, mode, NULL, NULL, NULL)
#define SYS_CLOSE(fd) INVOKE(3, fd, NULL, NULL, NULL, NULL, NULL)
#define SYS_LSEEK(fd, offset, origin) INVOKE(8, fd, offset, origin, NULL, NULL, NULL)
#define SYS_EXIT(code) INVOKE(60, code, NULL, NULL, NULL, NULL, NULL)
#define SYS_BRK(brk) INVOKE(12, brk, NULL, NULL, NULL, NULL, NULL)

#define OPEN_RDONLY    00
#define OPEN_WRONLY    01
#define OPEN_RDWR      02
#define OPEN_ACCMODE   03
#define OPEN_CREAT     0100
#define OPEN_EXCL      0200
#define OPEN_NOCTTY    0400
#define OPEN_TRUNC     01000
#define OPEN_APPEND    02000
#define OPEN_NONBLOCK  04000
#define OPEN_DSYNC     010000
#define OPEN_FASYNC    020000
#define OPEN_DIRECT    040000
#define OPEN_LARGEFILE 0100000
#define OPEN_DIRECTORY 0200000
#define OPEN_NOFOLLOW  0400000
#define OPEN_NOATIME   01000000
#define OPEN_CLOEXEC   02000000
#define __OPEN_SYNC    04000000
#define __OPEN_TMPFILE 020000000
#define OPEN_NDELAY    OPEN_NONBLOCK
#define OPEN_TMPFILE   (__OPEN_TMPFILE | OPEN_DIRECTORY)
#define OPEN_SYNC      (__OPEN_SYNC | OPEN_DSYNC)

#endif

