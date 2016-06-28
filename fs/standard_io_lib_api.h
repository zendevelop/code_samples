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