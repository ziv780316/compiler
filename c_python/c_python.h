#ifndef C_PYTHON_H
#define C_PYTHON_H

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

void python_init ();
void python_close ();
python_value_t python_eval_string ( const char *str );

#endif

