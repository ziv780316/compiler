#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* 
	search in binary tree (if not found, then do default tag)

                 4
	      /     \
             2       6
            / \     / \
           1   3   5   7

	switch O(log(n)) 

	switch with jump table O(1)

	if-else O(n)
*/

__attribute__((noinline, optimize("no-jump-tables")))
int f_switch_no_table ( int i, int *out )
{
	switch ( i )
	{
		case 1:
			*out = 1;
			break;

		case 2:
			*out = 2;
			break;

		case 3:
			*out = 3;
			break;

		case 4:
			*out = 4;
			break;

		case 5:
			*out = 5;
			break;

		case 6:
			*out = 6;
			break;

		case 7:
			*out = 7;
			break;

		default:
			*out = 0;
			break;
	}
}

// gcc construct table if case num >= 5
__attribute__((noinline))
int f_switch_table ( int i, int *out )
{
	switch ( i )
	{
		case 1:
			*out = 1;
			break;

		case 2:
			*out = 2;
			break;

		case 3:
			*out = 3;
			break;

		case 4:
			*out = 4;
			break;

		case 5:
			*out = 5;
			break;

		case 6:
			*out = 6;
			break;

		case 7:
			*out = 7;
			break;

		default:
			*out = 0;
			break;
	}
}

__attribute__((noinline, optimize("O3")))
void f_if ( int i, int *out )
{
	if ( 1 == i )
	{
		*out = 1;
	}
	else if ( 2 == i )
	{
		*out = 2;
	}
	else if ( 3 == i )
	{
		*out = 3;
	}
	else if ( 4 == i )
	{
		*out = 4;
	}
	else if ( 5 == i )
	{
		*out = 5;
	}
	else if ( 6 == i )
	{
		*out = 6;
	}
	else if ( 7 == i )
	{
		*out = 7;
	}
	else
	{
		*out = 0;
	}
}

int main ( int argc, char **argv )
{
	int out;
	f_switch_no_table ( argc, &out );
	printf( "out=%d\n", out );

	f_switch_table ( argc, &out );
	printf( "out=%d\n", out );
	
	f_if ( argc, &out );
	printf( "out=%d\n", out );

	return EXIT_SUCCESS;
}

