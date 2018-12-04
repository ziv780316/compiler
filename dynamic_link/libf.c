

extern double f_main ( double x );

double f_lib ( double in )
{
	return 2.0 * f_main(in);
}
