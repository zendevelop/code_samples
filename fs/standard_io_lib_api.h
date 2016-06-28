#include <stdio.h>

FILE* fopen( const char* filename, const char* mode );
size_t fread( void* ptr, size_t size, size_t nitems, FILE* stream );
size_t fwrite( const void* ptr, size_t size, size_t nitems, FILE* stream );
int fclose( FILE* stream );

int fflush( FILE* stream );
int fseek( FILE* stream, log int offset, int whence );

int fgetc( FILE* stream );
int getc( FILE* stream );
int getchar();

int fputc( int c, FILE* stream );
int putc( int c, FILE* stream );
int putchar( int c );

char* fgets( char* s, int n, FILE* stream );
char* gets( char* s );

/* Formatted Input and Output */
int printf( const char* format, ... );
int sprintf( char* s, const char* format, ... );
int fprintf( FILE* stream, const char* format, ... );


int scanf( const char* format, ... );
int fscanf( FILE* stream, const char* format, ... );
int sscanf( const char* s, const char* format, ... );

/*
fgetpos
gsetpos
ftell
rewind
freopen
setvbuf
remove
*/

/* Stream Errors */
#include <errno.h>

extern int errno;


#include <stdio.h>

int ferror( FILE* stream );
int feof( FILE* stream );
void clearerr( FILE* stream );


/* Streams and File Descriptors */
#include <stdio.h>

int fileno( FILE* stream );
FILE* fdopen( int fildes, const char* mode );


/* File and Directory Maintenance */
#include <sys/stat.h>

int chmod( const char* path, mode_t mode );



#include <sys/types.h>
#include <unistd.h>

int chown( const char* path, uid_t owner, gid_t group );


#include <unistd.h>

int unlink( const char* path );
int link( const char* path1, const char* path2 );
int symlink( const char* path1, const char* path2 );


#include <sys/types.h>
#include <sys/stat.h>

int mkdir( const char* path, mode_t mode );


#include <unistd.h>

int rmdir( const char* path );
int chdir( const char* path );
char* getcwd( char* buf, size_t size );


/* Scanning Directories */
#include <sys/types.h>
#include <dirent.h>

DIR* opendir( const char* name );
struct dirent* readdir( DIR* dirp );
long int telldir( DIR* dirp );
void seekdir( DIR* dirp, long int loc );
int closedir( DIR* dirp );