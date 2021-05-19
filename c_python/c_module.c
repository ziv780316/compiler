#include <math.h>

#include "Python.h"

static PyObject *_c_norm( PyObject *self, PyObject *args, PyObject *kwargs );

static PyMethodDef c_performance_methods[] = 
{
  {"norm", (PyCFunction) _c_norm, METH_VARARGS | METH_KEYWORDS, "calculation of vector norm 2."},
  {NULL, NULL, 0, NULL} // NULL struct as ending
};

static struct PyModuleDef c_performance_module = {
  PyModuleDef_HEAD_INIT,
  "c_performance",
  "A module containing methods with faster performance",
  -1, // memory allocation size, modules which do support multiple initialization set their m_size = -1
  c_performance_methods
};

PyMODINIT_FUNC PyInit_c_performance () 
{
  return PyModule_Create( &c_performance_module );
}

static PyObject *_c_norm( PyObject *self, PyObject *args, PyObject *kwargs )
{
	PyObject *pylist = NULL;  // non-optional argument
	long order = 2;  // optional argument
	long debug = 0;
	static char *kwlist[] = { "vector", "order", "debug", NULL };

	// | use to separate non-optional and optional argument
	if ( !PyArg_ParseTupleAndKeywords( args, kwargs, "O|ll", kwlist, &pylist, &order, &debug ) )
	{
		fprintf( stderr, "[Error] python parse tuple and keyword fail\n" );
		exit(1);
	}

	ssize_t pylist_length = PyList_Size( pylist );
	if ( debug )
	{
		fprintf( stderr, "[DEBUG] parse arg of %s:\n", __func__ );
		fprintf( stderr, "[DEBUG] vector=[ " );
		for ( ssize_t i = 0; i < pylist_length; ++i )
		{
			PyObject *val_obj = PyList_GetItem( pylist, i );
			if ( !val_obj )
			{
				fprintf( stderr, "[Error] list get item of index %ld fail\n", i );
				exit(1);
			}
			double x = PyFloat_AsDouble( val_obj );
			if ( -1 == x )
			{
				fprintf( stderr, "[Error] python translate object into double fail\n" );
				exit(1);
			}
			fprintf( stderr, "%.10le ", x );
		}
		fprintf( stderr, "]\n" );
		fprintf( stderr, "[DEBUG] order=%ld\n", order );
	}

	double norm = NAN;
	if ( pylist_length <= 0 )
	{
		//
	}
	else
	{
		// c code
		double sum = 0;
		for ( ssize_t i = 0; i < pylist_length; ++i )
		{
			PyObject *val_obj = PyList_GetItem( pylist, i );
			if ( !val_obj )
			{
				fprintf( stderr, "[Error] list get item of index %ld fail\n", i );
				exit(1);
			}
			double x = PyFloat_AsDouble( val_obj );
			if ( -1 == x )
			{
				fprintf( stderr, "[Error] python translate object into double fail\n" );
				exit(1);
			}

			if ( 1 == order )
			{
				sum += fabs(x);
			}
			else if ( 2 == order )
			{
				sum += x * x;
			}
		}
		if ( 1 == order )
		{
			norm = sum / order;
		}
		else if ( 2 == order )
		{
			norm = sqrt( sum );
		}
	}

	// construct return value
	PyObject *obj = Py_BuildValue( "d", norm );  // d for double, l for long
	if ( !obj )
	{
		fprintf( stderr, "[Error] build float objct value %.10le fail\n", norm );
		exit(1);
	}
	return obj;
}

