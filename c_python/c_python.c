#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "c_python.h"

static int g_debug_python = 0;

static const char *python_get_object_type_name ( PyObject *obj );
static char *python_get_object_c_str ( PyObject *obj );

#define VAR_INTERNAL_TOKEN "___use_in_c_python"

void python_init ( int debug )
{
	Py_InitializeEx( 0 ); // 0 is means do not use python signal handler (Py_Initialize will call Py_InitializeEx(1))

	PyObject *module = PyImport_AddModule("__main__");
	if ( module == NULL )
	{
		fprintf( stderr, "[Error] python import module __main__ fail\n" );
		exit(1);
	}

	python_eval_string( "import re as re" );
	python_eval_string( "import matplotlib.pyplot as plt" );
	python_eval_string( "import numpy as np" );

	g_debug_python = debug;
}

void python_close ()
{
	Py_Finalize();
}


int python_eval_string ( const char *fmt, ... )
{
	va_list arg_list;
	va_start( arg_list, fmt );
	char command[BUFSIZ];
	if ( vsprintf( command, fmt, arg_list ) < 0 )
	{
		fprintf( stderr, "vsprintf error with format '%s' --> %s\n", fmt, strerror(errno) );
		exit(1);
	}
	va_end( arg_list );

	PyObject *module = PyImport_AddModule("__main__");
	if ( module == NULL )
	{
		fprintf( stderr, "[Error] python import module __main__ fail\n" );
		exit(1);
	}

	PyObject *dict = PyModule_GetDict( module );
	if ( !dict )
	{
		fprintf( stderr, "[Error] python fetch local and global variable dict fail from module __main__\n" );
		exit(1);
	}

	// use PyRun_StringFlags(const char *str, int start_token, PyObject *globals, PyObject *locals, PyCompilerFlags *flags);
	PyObject *ret_obj = PyRun_StringFlags( command, Py_file_input, dict, dict, NULL );
	if ( !ret_obj )
	{
		fprintf( stderr, "[Error] python execute command %s fail\n", command );
		PyErr_Print();
		return C_PYTHON_EVAL_FAIL;
	}

	Py_DECREF( ret_obj ); // decrease obj reference

	return C_PYTHON_EVAL_OK;
}

python_value_t python_get_object_value ( const char *name, int type )
{
	PyObject *module = PyImport_AddModule("__main__");
	if ( module == NULL )
	{
		fprintf( stderr, "[Error] python import module __main__ fail\n" );
		exit(1);
	}

	PyObject *obj = PyObject_GetAttrString( module, name );
	if ( !obj )
	{
		fprintf( stderr, "[Error] cannot find %s in module __main__ dictionary\n", name );
		exit(1);
	}

	if ( g_debug_python )
	{
		fprintf( stderr, "[DEBUG] object '%s' type=%s\n", name, python_get_object_type_name(obj) );
	}
	if ( g_debug_python )
	{
		char *c_str = python_get_object_c_str( obj );
		fprintf( stderr, "[DEBUG] object '%s' c_str=%s\n", name, c_str );
		free( c_str );
	}

	python_value_t val;
	if ( C_PYTHON_VALUE_TYPE_STRING == type )
	{
		char *c_str = python_get_object_c_str( obj );
		val.sval = c_str;
	}
	else if ( C_PYTHON_VALUE_TYPE_INT_64 == type )
	{
		long lval = PyLong_AsLong( obj );
		if ( -1 == lval )
		{
			fprintf( stderr, "[Error] python translate %s into long fail\n", name );
			exit(1);
		}
		val.lval = lval;
	}
	else if ( C_PYTHON_VALUE_TYPE_FLOAT_64 == type )
	{
		double dval = PyFloat_AsDouble( obj );
		if ( -1 == dval )
		{
			fprintf( stderr, "[Error] python translate %s into double fail\n", name );
			exit(1);
		}
		val.dval = dval;
	}

	return val;
}

python_value_t python_get_dict_value ( const char *name, const char *key, int type )
{
	PyObject *module = PyImport_AddModule("__main__");
	if ( module == NULL )
	{
		fprintf( stderr, "[Error] python import module __main__ fail\n" );
		exit(1);
	}

	PyObject *obj = PyObject_GetAttrString( module, name );
	if ( !obj )
	{
		fprintf( stderr, "[Error] cannot find %s in module __main__ dictionary\n", name );
		exit(1);
	}

	if ( g_debug_python )
	{
		fprintf( stderr, "[DEBUG] object '%s' type=%s\n", name, python_get_object_type_name(obj) );
	}

	PyObject *val_obj = PyDict_GetItemString( obj, key );
	if ( !val_obj )
	{
		fprintf( stderr, "[Error] dict '%s' hash key '%s' fail\n", name, key );
		exit(1);
	}

	python_value_t val;
	if ( C_PYTHON_VALUE_TYPE_STRING == type )
	{
		val.sval = python_get_object_c_str( val_obj );
	}
	else if ( C_PYTHON_VALUE_TYPE_INT_64 == type )
	{
		long lval = PyLong_AsLong( val_obj );
		if ( -1 == lval )
		{
			fprintf( stderr, "[Error] python translate %s['%s'] into long fail\n", name, key );
			exit(1);
		}
		val.lval = lval;
	}
	else if ( C_PYTHON_VALUE_TYPE_FLOAT_64 == type )
	{
		double dval = PyFloat_AsDouble( val_obj );
		if ( -1 == dval )
		{
			fprintf( stderr, "[Error] python translate %s['%s'] into double fail\n", name, key );
			exit(1);
		}
		val.dval = dval;
	}

	return val;
}

char *python_re_string_slice ( const char *str, const char *pattern, int idx, int ignore_case )
{
	char local_var_match[BUFSIZ];
	sprintf( local_var_match, "match_%s", VAR_INTERNAL_TOKEN );
	int eval_status;
	if ( ignore_case )
	{
		eval_status = python_eval_string( "%s = re.search('%s', '%s', re.IGNORECASE )", local_var_match, pattern, str);
	}
	else
	{
		eval_status = python_eval_string( "%s = re.search('%s', '%s' )", local_var_match, pattern, str);
	}
	if ( C_PYTHON_EVAL_FAIL == eval_status )
	{
		fprintf( stderr, "[Error] re.search method fail\n" );
		exit(1);
	}

	PyObject *module = PyImport_AddModule("__main__");
	if ( module == NULL )
	{
		fprintf( stderr, "[Error] python import module __main__ fail\n" );
		exit(1);
	}

	PyObject *obj = PyObject_GetAttrString( module, local_var_match );
	if ( !obj )
	{
		fprintf( stderr, "[Error] cannot find %s in module __main__ dictionary\n", local_var_match );
		exit(1);
	}
	if ( g_debug_python )
	{
		fprintf( stderr, "[DEBUG] object '%s' type=%s\n", local_var_match, python_get_object_type_name(obj) );
	}

	if ( &_PyNone_Type == Py_TYPE(obj) )
	{
		fprintf( stderr, "[Error] str=%s pattern=%s match fail\n", str, pattern );
		return NULL;
	}

	char local_var_str[BUFSIZ];
	sprintf( local_var_str, "str_%s", VAR_INTERNAL_TOKEN );
	if ( C_PYTHON_EVAL_FAIL == python_eval_string( "%s = %s.group(%d)", local_var_str, local_var_match, idx) )
	{
		fprintf( stderr, "[Error] %s.group method fail\n", local_var_match );
		exit(1);
	}

	python_value_t py_val = python_get_object_value ( local_var_str, C_PYTHON_VALUE_TYPE_STRING );
	return py_val.sval;
}

// -------------------------------------------------------------------------------
// Internal function
// -------------------------------------------------------------------------------
static const char *python_get_object_type_name ( PyObject *obj )
{
	return Py_TYPE(obj)->tp_name;
}

static char *python_get_object_c_str ( PyObject *obj )
{
	// compute a string representation, python 3 has no PyString_AsString
	PyObject *repr_obj = PyObject_Repr( obj ); 
	if ( !repr_obj )
	{
		fprintf( stderr, "[Error] translate object to UTF-8 object fail\n" );
		exit(1);
	}
	if ( !PyUnicode_Check(repr_obj) ) 
	{
		fprintf( stderr, "[Error] translate object to UTF-8 object fail\n" );
		exit(1);
	}

	PyObject *byte_obj = PyUnicode_AsEncodedString( repr_obj, "utf-8", "[Error]");
	if ( !byte_obj )
	{
		fprintf( stderr, "[Error] translate UTF-8 byte to string byte object fail\n" );
		exit(1);
	}

	const char *c_str = PyBytes_AS_STRING( byte_obj );
	if ( !c_str )
	{
		fprintf( stderr, "[Error] translate string byte object into c_str fail\n" );
		exit(1);
	}

	return strdup(c_str);
}
