// 非阻塞式I/O

int flags;

/* Set a socket as nonblocking */
if( ( flags = fcntl( fd, F_GETFL, 0 )) < 0 )
	err_sys( "F_GETFL error" );
flags |= O_NONBLOCK;
if( fcntl( fd, F_SETFL, flags) < 0)
	err_sys( "F_GETFL error" );

/* close nonblocking flag */
flags &= ~O_NONBLOCK;
if( fcntl( fd, F_GETFL, flags ) < 0 )
	err_sys( "F_SETFL error" );