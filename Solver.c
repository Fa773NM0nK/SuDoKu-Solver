#include "Solver.h"
#include <stdlib.h>
#include <stdio.h>

struct cell
{
	short int row, col;
};

static bool solve ( short int **, struct cell );
static struct cell next ( struct cell );
static struct cell next_avail ( short int **, struct cell );
static bool fits ( short int **, short unsigned int, struct cell );

short int ** allocate_sudoku ( short unsigned int size )
{
	short int **board;
	
	board = malloc ( size * sizeof ( short int * ) );
	
	short unsigned int i, j;
	for ( i = 0; i < size; i ++ )
	{
		board[i] = malloc ( size * sizeof ( short int ) );
		for ( j = 0; j < size; j ++ ) board[i][j] = -1;
	}
	
	return board;
}

bool deallocate_sudoku ( short int **board, short unsigned int size )
{
	short unsigned int i;
	for ( i = 0; i < size; i ++ )
	{
		free ( board[i] );
	}
	free ( board );
	
	return true;
}

bool read_sudoku ( const char *file, short int **sudoku, short unsigned int size )
{
	FILE *fp;
	
	fp = fopen ( file, "r" );
	
	short unsigned int ct, limit;
	
	ct = 0;
	limit = size * size;
	
	char ch;
	
	ch = fgetc ( fp );
	while ( ! feof ( fp ) && ct < limit )
	{
		if ( ch >= '1' && ch <= '9' )
		{
			sudoku[ct/size][ct%size] = ch - '0';
			ct ++;
		}
		else if ( ch == '.' )
		{
			sudoku[ct/size][ct%size] = -1;
			ct ++;
		}
		
		ch = fgetc ( fp );
	}
	
	return true;
}

bool solve_sudoku ( short int **sudoku )
{
	struct cell start;
	
	start.row = start.col = 0;
	
	return solve ( sudoku, next_avail ( sudoku, start ) );
}

static bool solve ( short int **sudoku, struct cell toFill )
{
	short unsigned int i;
	for ( i = 1; i <= 9; i ++ )
	{		
		if ( fits ( sudoku, i, toFill ) )
		{
			sudoku[toFill.row][toFill.col] = i;
			
			if ( next_avail ( sudoku, toFill ).row == -1 )
			{
				return true;
			}
			else
			{
				if ( solve ( sudoku, next_avail ( sudoku, toFill ) ) )
				{
					return true;
				}
				else
				{
					sudoku[toFill.row][toFill.col] = -1;
					continue;
				}
			}
		}
	}
	
	return false;
}

struct cell next ( struct cell current )
{
	current.col ++;
	
	if ( current.col == 9 )
	{
		current.col = 0;
		current.row ++;
	}
	
	if ( current.row == 9 )
	{
		current.row = current.col = -1;
	}
	
	return current;
}

static struct cell next_avail ( short int **sudoku, struct cell current )
{
	while ( current.row != -1 )
	{
		if ( sudoku[current.row][current.col] == -1 )
		{
			break;
		}		
		else
		{
			current = next ( current );
		}	
	}
	
	return current;
}

static bool fits ( short int **sudoku, short unsigned int value, struct cell pos )
{
	short unsigned int i, j;
	
	for ( i = 0; i < 9; i ++ )
	{
		if ( sudoku[pos.row][i] == value || sudoku[i][pos.col] == value ) break;
	}
	
	if ( i != 9 ) return false;
	
	struct cell block;
	
	block.row = ( pos.row / 3 ) * 3;
	block.col = ( pos.col / 3 ) * 3;
	
	bool flag = false;
	for ( i = 0; i < 3; i ++ )
	{
		for ( j = 0; j < 3; j ++ )
		{
			if ( sudoku[block.row + i][block.col + j] == value ) flag = true;
		}
	}
	
	if ( flag == true ) return false;
	
	return true;
}
