#include <unistd.h>

size_t read( int fildes, void* buf, size_t nbytes );
size_t write( int fildes, const void* buf, size_t nbytes );
int close( int fildes );


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open( const char* path, int oflags );
int open( const char* path, int oflags, mode_t mode );