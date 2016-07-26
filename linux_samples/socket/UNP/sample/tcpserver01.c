#include "unp.h"

void str_echo( int sockfd );

int main( int argc, char** argv ) {
	int listenfd;	
	struct sockaddr_in servaddr;

	listenfd = Socket( AF_INET, SOCK_STREAM, 0 );

	bzero( &servaddr, sizeof( servaddr ) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
	servaddr.sin_port = htons( 7778 );
	Bind( listenfd, (struct sockaddr*)&servaddr, sizeof( servaddr ) );
	Listen( listenfd, 5 );

	socklen_t clilen;
	struct sockaddr_in cliaddr;
	int connfd;
	pid_t childpid;
	for( ; ; ) {
		clilen = sizeof( cliaddr );
		connfd = Accept( listenfd, ( struct sockaddr* )&cliaddr, &clilen );
		if( ( childpid = Fork()) == 0 ) {
			Close( listenfd );
			str_echo( connfd );
			exit( 0 );
		}

		Close( connfd );
	}
}

void str_echo( int sockfd ) {
	ssize_t n;
	char buf[ MAXLINE ];

again:
	while( ( n = read( sockfd, buf, MAXLINE ) ) > 0 ) {
		printf( "read: %s", buf );
		Writen( sockfd, buf, n );
		bzero( buf, MAXLINE );
	}	
	printf( "n: %d, errno: %d\n", n, errno );

	if( n < 0 && errno == EINTR )
		goto again;
	else if( n < 0 )
		err_sys( "str_echo: read error" );
}