#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>

#include "open_lib.h"

double f_main ( double x )
{
	return 3.0 * x;
}

int main ( int argc, char **argv )
{
	prepend_env( "LD_LIBRARY_PATH", "/home/lintu/baba/compiler/dynamic_link" );
	void *handle = open_so_lib( "libf.so" );

	double (*fp) (double) = (double (*) (double)) get_symbol ( handle, "f_lib" );

	double x = (double) argc;

	printf( "f_lib(%.10e)=%.10e\n", x, fp(x) );

	return EXIT_SUCCESS;
}

