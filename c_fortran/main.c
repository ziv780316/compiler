#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// fortran module
double norm ( double *x, int n, int order, int debug );

int main ( int argc, char **argv )
{
	setbuf( stdout, 0 );
	int debug = 1;
	double x[3] = { -3, 2, 4 };
	double result;

	result = norm( x, 3, 1, debug );
	printf( "norm1 result=%.15le\n", result );
	result = norm( x, 3, 2, debug );
	printf( "norm2 result=%.15le\n", result );

	return EXIT_SUCCESS;
}

