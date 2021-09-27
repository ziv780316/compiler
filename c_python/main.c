#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "c_python.h"

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

	// eval complex
	python_eval_string( "z = 1+1.5j" );
	py_val = python_get_object_value( "z", C_PYTHON_VALUE_TYPE_COMPLEX_64 );
	printf( "get z = %.15le+1j*%.15le\n", creal(py_val.cdval), cimag(py_val.cdval) );

	// list
	double *v = (double *) malloc (sizeof(double)*4);
	v[0] = 1.1;
	v[1] = 5.2;
	v[2] = 100;
	v[3] = -0.1;
	python_create_list( "v", v, 4, C_PYTHON_VALUE_TYPE_FLOAT_64 );
	python_eval_string( "v.sort();");
	double *v_sort = (double *) malloc (sizeof(double)*4);
	python_copy_list( "v", v_sort, 4, C_PYTHON_VALUE_TYPE_FLOAT_64 );
	for ( ssize_t i = 0; i < 4; ++i )
	{
		printf( "v_sort[%ld]=%.10le\n", i, v_sort[i] );
	}

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

	// run python script
	python_exec_py_script( "test.py" );

	// python use extern code in python (dlopen C module)
	append_import_module_search_path( "." );
	python_eval_string( 
	"import c_performance as c;"
	"val = c.norm( order=2, vector=[1, 2, 3], debug=1 );"
	"print( 'c.norm2 =', val );"
	"print( 'np.norm2=', np.linalg.norm([1, 2, 3], 2) );"
	);

	// sub plot
	char **name_list = (char **) malloc (sizeof(char*)*4);
	name_list[0] = "name1";
	name_list[1] = "name2";
	name_list[2] = "name3";
	name_list[3] = "name4";
	python_create_list( "name_list", name_list, 4, C_PYTHON_VALUE_TYPE_STRING );
	python_eval_string( 
	"t = np.arange(0,2,0.05);"
	"s1 = np.sin(2*np.pi*t);"
	"s2 = np.sin(2*np.pi*t/0.5);"
	"s3 = np.sin(2*np.pi*t/2);"
	"fig, axs = plt.subplots(2,2,figsize=(12,8));" // figsize unit is monitor inches
	"fig.suptitle('plot test');"
	"axs[0,0].plot(t,s1,'ro-',markersize=10);"
	"axs[0,0].set_ylabel('sin(2*pi*t)');"
	"axs[0,0].set_xlabel('time (s)');"
	"axs[1,0].plot(t,s2,'bs-');"
	"axs[1,0].set_ylabel('sin(2*pi*t/0.5)');"
	"axs[1,0].set_xlabel('time (s)');"
	"axs[0,1].plot(t,s3,'g-',linewidth=10);"
	"axs[0,1].set_ylabel('sin(2*pi*t/2)');"
	"axs[0,1].set_xlabel('time (s)');"
	"plt.show( block=False );" // non-block
	"fig.savefig('plot.png');"  // export
	""
	"fig, ax = plt.subplots();"
	"ax.plot(name_list, np.sin(range(len(name_list))),'p-');"
	"ax.set_ylabel('sin(list)');"
	"plt.show();"
	);

	// close C-Python
	python_close();

	return EXIT_SUCCESS;
}

