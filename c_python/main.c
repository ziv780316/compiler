#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "c_python.h"

double c_exp( double x, double limit )
{
	return exp( fmin(limit, x) );
}

// registed C function used in python
static PyObject *_c_exp( PyObject *self, PyObject *args, PyObject *kwargs )
{
	double x = NAN;  // non-optional argument
	double limit = 30; // optional argument
	static char *kwlist[] = { "x", "limit", NULL };

	// | use to separate non-optional and optional argument
	if ( !PyArg_ParseTupleAndKeywords( args, kwargs, "d|d", kwlist, &x, &limit) ) 
	{
		fprintf( stderr, "[Error] python parse tuple and keyword fail\n" );
		exit(1);
	}

	double y = c_exp( x, limit );
	PyObject *obj = Py_BuildValue( "d", y );  // d for double, l for long
	if ( !obj )
	{
		fprintf( stderr, "[Error] build objct value fail\n" );
		exit(1);
	}
	return obj;
}

int main ( int argc, char **argv )
{
	// init C-Python
	python_value_t py_val;
	python_init( 1 ); // debug = 1

	// show in stdout
	python_eval_string( "print('%s test C-Python ...')", getenv("USER") );

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

	// call regist C function in python
	if ( 0 )
	{
		python_eval_string( 
		"x = c_exp(30, 30);"
		"z = c_exp(40, 30);"
		"z = c_exp(50);"
		"print( 'x=', x );"
		);
	}

	// close C-Python
	python_close();

	return EXIT_SUCCESS;
}

