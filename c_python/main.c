#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "c_python.h"

int main ( int argc, char **argv )
{
	python_init();

	python_eval_string( "print('Hello World!')" );

	python_close();

	return EXIT_SUCCESS;
}

