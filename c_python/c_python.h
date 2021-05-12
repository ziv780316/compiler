#ifndef C_PYTHON_H
#define C_PYTHON_H

#include "Python.h"

#ifdef Py_LIMITED_API
#error "Py_LIMITED_API defined, system python package cannot support C-python"
#endif

typedef union
{
	char cval;
	long lval;
	double dval;
	const char *sval;
} python_value_t;

void python_init ( int debug );
void python_close ();

int python_eval_string ( const char *command );
#define C_PYTHON_EVAL_OK 0
#define C_PYTHON_EVAL_FAIL 1

python_value_t python_get_object_value ( const char *name, int type );
python_value_t python_get_dict_value ( const char *name, const char *key, int type );
#define C_PYTHON_VALUE_TYPE_CHAR 0
#define C_PYTHON_VALUE_TYPE_INT_64 1
#define C_PYTHON_VALUE_TYPE_FLOAT_64 2
#define C_PYTHON_VALUE_TYPE_STRING 3


#endif
