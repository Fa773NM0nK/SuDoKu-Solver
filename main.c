#include "Solver.h"
#include <stdio.h>

int main ( void )
{
	short int **A;
	short unsigned int size = 9;
	short unsigned int i, j;
	
	A = allocate_sudoku ( size );
	
	read_sudoku ( "sudoku.txt", A, size );
	
	if ( solve_sudoku ( A ) )
	{
		printf ( "SOLVED!!!\n\n" );
	}
	else
	{
		printf ( "NOT SOLVED!!!\n\n" );
	}
	
	for ( i = 0; i < size; i ++ )
	{
		for ( j = 0; j < size; j ++ )
		{
			printf ( "%hd", A[i][j] );
			
			if ( (j+1)%3 == 0 ) printf ( "\t" );
			
		}
		printf ( "\n" );
		if ( (i+1)%3 == 0 ) printf ( "\n" );
	}
	
	deallocate_sudoku ( A, size );
	
	return 0;
}
