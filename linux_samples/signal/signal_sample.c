#include <signal.h>

static void sig_usr(int);

int main( void ) {
	if( signal( SIGUSR1, sig_usr ) == SIG_ERR )
		err_sys( "can't catch SIGUSR1" );
	if( signal( SIGUSR2, sig_usr ) == SIG_ERR )
		err_sys( "can't catch SIGUSR2" );o

	for( ; ; )
		pause();
}

static void sig_usr( int signo ) {
	if( signo == SIGUSR1 ) {
		printf( "received SUGUSR1\n" );
	} else if( signo == SIGUSR2 ) {
		printf( "received SIGUSR2\n" );
	} else
		err_dump( "received signal %d\n", signo );

	return;
}


// run sample
//$ a.out &
// [1]	4720
//$ kill -USR1 4720 