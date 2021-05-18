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

	// regular expression
	int ignore_case = 1;
	char *pattern = "[vi]\\((\\S+)\\)\\s*=\\s*(\\S+)";
	char *str_test = "V(node1) = 1.234e+03";
	char *node_name = python_re_string_slice( str_test, pattern, 1, ignore_case );
	char *node_value = python_re_string_slice( str_test, pattern, 2, ignore_case );
	printf( "re pattern = %s\n", pattern );
	printf( "slice group 1 = %s\n", node_name );
	printf( "slice group 2 = %s\n", node_value );

	// plot
	python_eval_string( 
	"t = np.arange(0,2,0.05);"
	"s1 = np.sin(2*np.pi*t);"
	"s2 = np.sin(2*np.pi*t/0.5);"
	"s3 = np.sin(2*np.pi*t/2);"
	"fig = plt.figure(1);"
	"fig.suptitle('plot test');"
	"plt.subplot(3,1,1);"
	"plt.plot(t,s1,'ro-',markersize=10);"
	"ax = plt.gca();"
	"ax.set_ylabel('sin(2*pi*t)');"
	"plt.subplot(3,1,2);"
	"plt.plot(t,s2,'bs-');"
	"ax = plt.gca();"
	"ax.set_ylabel('sin(2*pi*t/0.5)');"
	"plt.subplot(3,1,3);"
	"plt.plot(t,s3,'g-',linewidth=10);"
	"ax = plt.gca();"
	"ax.set_ylabel('sin(2*pi*t/2)');"
	"ax.set_xlabel('time (s)');"
	"plt.show();"
	"fig.savefig('plot.png');"
	);

	// close C-Python
	python_close();

	return EXIT_SUCCESS;
}

