#include <stdarg.h>
#include <stdio.h>

int c_printf ( const char *fmt, ... )
{
	va_list va;
	va_start(va, fmt);

	int ret;
	ret = vprintf( fmt, va );

	va_end(va);

	return ret;
}

