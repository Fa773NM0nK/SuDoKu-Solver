#ifndef SUDOKU_SOLVER_H
	
	#define SUDOKU_SOLVER_H

		#include <stdbool.h>

		bool solve_sudoku ( short int ** );
		
		bool read_sudoku ( const char *, short int **, short unsigned int );
		
		short int ** allocate_sudoku ( short unsigned int );
		
		bool deallocate_sudoku ( short int **, short unsigned int size );

#endif
