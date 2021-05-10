#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "c_python.h"

void python_init ()
{
	Py_InitializeEx( 0 ); // 0 is means do not use python signal handler (Py_Initialize will call Py_InitializeEx(1))
}

void python_close ()
{
	Py_Finalize();
}

python_value_t python_eval_string ( const char *str )
{
	static python_value_t py_val;
	PyRun_SimpleString( str );
	return py_val;
}

