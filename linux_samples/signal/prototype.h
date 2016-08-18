#include <signal.h>

void (*signal( int signo, void (*func)( int )))( int );

int sigemptyset( sigset_t* set );
int sigfillset( sigset_t* set );
int sigaddset( sigset_t* set, int signo );
int sigdelset( sigset_t* set, int signo );
int sigismember( const sigset_t* set, int signo );