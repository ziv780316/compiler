#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int a = 10;
const char *s123 = "123";

extern int asm_int_add ( int a, int b );

int test ( int a, int b )
{
	int c = a + b;
	printf( "%d + %d = %d\n", a, b, c );
	return c;
}

int main ( int argc, char **argv )
{
	setbuf( stdout, 0 );
	printf( "%d\n", asm_int_add( 1, 2 ) );

	return EXIT_SUCCESS;
}

