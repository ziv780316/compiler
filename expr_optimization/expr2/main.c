#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static int g_f2_count = 0;
static int g_f2_const_count = 0;

__attribute__((const, noinline))
double f2_const ( double x )
{
	++g_f2_const_count;
	return 2.0 * x;
}

__attribute__((noinline)) 
double f2 ( double x )
{
	++g_f2_count;
	return 2.0 * x;
}

__attribute__((noinline)) 
double f1 ( double x )
{
	return 0.5 * x;
}

__attribute__((noinline, optimize("-funsafe-math-optimizations"))) 
void expr_O2_gcse_const_reciprocal_asscociative ( double *in, double *out )
{
	double a = f1(in[0]) * f1(in[0]);
	double b = f2_const(in[0]) * f2_const(in[0]);
	*out = 0.5 * a * b / 3.0;
}

__attribute__((noinline, optimize("-freciprocal-math"))) 
void expr_O2_gcse_const_reciprocal ( double *in, double *out )
{
	double a = f1(in[0]) * f1(in[0]);
	double b = f2_const(in[0]) * f2_const(in[0]);
	*out = 0.5 * a * b / 3.0;
}

__attribute__((noinline))
void expr_O2_gcse_const ( double *in, double *out )
{
	double a = f1(in[0]) * f1(in[0]);
	double b = f2_const(in[0]) * f2_const(in[0]);
	*out = 0.5 * a * b / 3.0;
}

__attribute__((noinline))
void expr_O2_gcse ( double *in, double *out )
{
	double a = f1(in[0]) * f1(in[0]);
	double b = f2(in[0]) * f2(in[0]);
	*out = 0.5 * a * b / 3.0;
}

__attribute__((noinline, optimize("O0"))) 
void expr_O0 ( double *in, double *out )
{
	double a = f1(in[0]) * f1(in[0]);
	double b = f2(in[0]) * f2(in[0]);
	*out = 0.5 * a * b / 3.0;
}

int main ( int argc, char **argv )
{
	double in = argc;
	double out;

	expr_O0( &in, &out );
	printf( "* expr_O0:\n" );
	printf( "in=%le\n", in );
	printf( "out=%le\n", out );

	expr_O2_gcse( &in, &out );
	printf( "* expr_O2_gcse:\n" );
	printf( "in=%le\n", in );
	printf( "out=%le\n", out );

	expr_O2_gcse_const( &in, &out );
	printf( "* expr_O2_gcse_const:\n" );
	printf( "in=%le\n", in );
	printf( "out=%le\n", out );

	expr_O2_gcse_const_reciprocal( &in, &out );
	printf( "* expr_O2_gcse_const_reciprocal:\n" );
	printf( "in=%le\n", in );
	printf( "out=%le\n", out );

	expr_O2_gcse_const_reciprocal_asscociative( &in, &out );
	printf( "* expr_O2_gcse_const_reciprocal_asscociative:\n" );
	printf( "in=%le\n", in );
	printf( "out=%le\n", out );

	printf( "g_f2_count=%d\n", g_f2_count );
	printf( "g_f2_const_count=%d\n", g_f2_const_count );

	return EXIT_SUCCESS;
}

