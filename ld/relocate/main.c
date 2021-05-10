//
extern double atof( const char * );
extern int printf( const char *, ... );
extern double exp( double );

int main ( int argc, char **argv )
{
	if ( argc == 2 )
	{
		double x = atof( argv[1] );
		printf( "exp(%.10le)=%.10le\n", x, exp( x ) );
	}

	return 0;
}

