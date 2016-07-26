#include "unp.h"

ssize_t writen( int fd, const void* vptr, size_t n ) {
	size_t left, size;
	const char* ptr;

	ptr = vptr;
	left = n;
	while( left > 0 ) {
		if( ( size = write( fd, ptr, left ) ) <= 0 ) {
			if( size < 0 && errno == EINTR ) {
				size = 0;
			} else {
				return -1;
			}
		}
		left -= size;
		ptr += size;
	}

	return n;
}

void Writen( int fd, void* ptr, size_t n ) {
	if( writen( fd, ptr, n ) != n )
		err_sys( "writen error" );
}
