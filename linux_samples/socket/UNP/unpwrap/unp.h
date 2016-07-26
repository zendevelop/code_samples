#ifndef __UNP_H__
#define __UNP_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
//#include <cstddef.h>

#define	MAXLINE		4096	/* max text line length */
#define	LISTENQ		1024	/* 2nd argument to listen() */

int Socket( int family, int type, int protocol );
void Bind( int fd, const struct sockaddr* sa, socklen_t salen );
void Listen( int fd, int backlog );
int Accept( int fd, struct sockaddr* sa, socklen_t* salenptr );
void Connect( int fd, const struct sockaddr* sa, socklen_t salen );

ssize_t writen( int fd, const void* buf, size_t size );
void Writen( int fd, void* buf, size_t size );
ssize_t Readline( int, void*, size_t );

const char* Inet_ntop( int, const void*, char*, size_t );
void Inet_pton( int, const char*, void* );

pid_t Fork();
void Close( int fd );

char* Fgets( char*, int, FILE* );
void Fputs( const char* , FILE* );

void err_sys( const char*, ... );
void err_dump( const char*, ... );
void err_quit( const char*, ... );
void err_msg( const char*, ... );
void err_ret( const char*, ... );

#endif