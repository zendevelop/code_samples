#include <unistd.h>

size_t read( int fildes, void* buf, size_t nbytes );
size_t write( int fildes, const void* buf, size_t nbytes );
int close( int fildes );
int ioctl( int fildes, int cmd, ... );
int dup( int fildes );
int dup2( int fildes, int fildes2 );


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open( const char* path, int oflags );
int open( const char* path, int oflags, mode_t mode );


#include <unistd.h>
#include <yss/types.h>

off_t lseek( int fildes, off_t offset, int whence );


#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int fstat( int fildes, struct stat* buf );
int stat( const char* path, struct stat* buf );
int lstat( const char* path, struct stat* buf );