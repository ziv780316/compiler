#ifndef C_PYTHON_H
#define C_PYTHON_H

#include <stdarg.h>
#include "Python.h"

#ifdef Py_LIMITED_API
#error "Py_LIMITED_API defined, system python package cannot support C-python"
#endif

typedef union
{
	char cval;
	int ival;
	long lval;
	double dval;
	char *sval;
} python_value_t;

void python_init ( int debug );
void python_close ();

int python_eval_string ( const char *fmt, ... );
#define C_PYTHON_EVAL_OK 0
#define C_PYTHON_EVAL_FAIL 1

python_value_t python_get_object_value ( const char *name, int type );
python_value_t python_get_dict_value ( const char *name, const char *key, int type );
void python_create_list ( const char *name, void *dest, ssize_t length, int type );
void python_copy_list ( const char *name, void *dest, ssize_t length, int type );
#define C_PYTHON_VALUE_TYPE_CHAR 0
#define C_PYTHON_VALUE_TYPE_INT_32 1
#define C_PYTHON_VALUE_TYPE_INT_64 1
#define C_PYTHON_VALUE_TYPE_FLOAT_64 2
#define C_PYTHON_VALUE_TYPE_STRING 3

char *python_re_string_slice ( const char *str, const char *pattern, int idx, int ignore_case );

#endif

