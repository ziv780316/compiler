#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "c_python.h"

int main ( int argc, char **argv )
{
	python_init( 1 ); // debug = 1

	python_value_t py_val;

	// show in stdout
	python_eval_string( "print('Hello World!')" );

	// eval long
	python_eval_string( "x = 3**10" );
	py_val = python_get_object_value( "x", C_PYTHON_VALUE_TYPE_INT_64 );
	printf( "get x = %ld\n", py_val.lval );

	// eval double
	python_eval_string( "x = 2**0.5" );
	py_val = python_get_object_value( "x", C_PYTHON_VALUE_TYPE_FLOAT_64 );
	printf( "get x = %.15le\n", py_val.dval );

	// dict
	python_eval_string(
	"map = {};" 
	"map['key1'] = 123;" 
	"map['key2'] = 1.0/3;" 
	"map['key3'] = 'test';" 
	"map['key4'] = 3**100;"  // C cannot handle arbitrary length ing
	);
	py_val = python_get_dict_value( "map", "key1", C_PYTHON_VALUE_TYPE_INT_64 );
	printf( "get map['key1'] = %ld\n", py_val.lval );
	py_val = python_get_dict_value( "map", "key2", C_PYTHON_VALUE_TYPE_FLOAT_64 );
	printf( "get map['key2'] = %.15le\n", py_val.dval );
	py_val = python_get_dict_value( "map", "key3", C_PYTHON_VALUE_TYPE_STRING );
	printf( "get map['key3'] = %s\n", py_val.sval );
	py_val = python_get_dict_value( "map", "key4", C_PYTHON_VALUE_TYPE_STRING );
	printf( "get map['key4'] = %s\n", py_val.sval );

	python_close();

	return EXIT_SUCCESS;
}

