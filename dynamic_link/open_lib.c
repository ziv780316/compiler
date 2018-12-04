#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>

#include "open_lib.h"

void *open_so_lib ( char *name )
{
	void *handle = dlopen( name, RTLD_NOW | RTLD_GLOBAL );
	if ( !handle )
	{
		fprintf( stderr, "[Error] dlopen '%s' fail --> %s\n", name, dlerror() );
		abort();
	}
	dlerror(); // clear error

	return handle;
}

void *get_symbol ( void *handle, char *name )
{
	void *sym = dlsym ( handle, name );
	if ( !sym )
	{
		fprintf( stderr, "[Error] load symbol '%s' fail --> %s\n", name, dlerror() );
		abort();
	}
	dlerror(); // clear error

	return sym;
}

void close_so_lib ( void *handle )
{
	int fail = dlclose( handle );
	if ( fail )
	{
		fprintf( stderr, "[Error] dlclose fail --> %s\n", dlerror() );
		abort();
	}
	dlerror(); // clear error
}

void prepend_env ( char *name, char *val )
{
	int overwrite = true;
	int fail;

	char *origin = getenv( name );
	if ( !origin )
	{
		// there is no env defined
		fail = setenv( name, val, overwrite );
		if ( fail )
		{
			fprintf( stderr, "[Error] setenv fail --> %s\n", strerror(errno) );
			abort();
		}
	}
	else
	{
		// the env is already defined 
		int len = strlen( origin ) + strlen( val ) + 2; // + 2 is ':' and '\0'
		char *buf = (char *) malloc ( sizeof(char) * len );
		sprintf( buf, "%s:%s", val, origin );
		fail = setenv( name, buf, overwrite );
		if ( fail )
		{
			fprintf( stderr, "[Error] setenv fail --> %s\n", strerror(errno) );
			abort();
		}
	}
}

