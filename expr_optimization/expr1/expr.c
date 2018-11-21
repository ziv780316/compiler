#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

__attribute__((noinline))
void f ( double *in, double *out )
{
	*out = (3.0 * in[0]) * 1.0 * 2.0 / ((3.0 * in[0]) * (3.0 * in[0])) / 4.0;
}

int main ( int argc, char **argv )
{
	double x = argc;
	double y;

	f( &x, &y );

	printf( "y=%le\n", y );

	return EXIT_SUCCESS;
}

