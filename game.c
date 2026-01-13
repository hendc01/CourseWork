#include "game.h"
#include "gameTypes.h"
#include "inputSafe.h"
#include "render.h"
#include "gameMode.h"
#include <stdio.h>

void game ( void )
{
	board grid;
	
	menu1();
	
	initializer( &grid );
	gameInput( &grid );
	
}
/*Allow the user to input the grids, and checks if that block is empty*/
GameResult gameInput( board *grid	)
{
	State moveResult;
	int collum, row;
	Cell winner = CELL_EMPTY;
	int turn = 0;
	
	while( 1 )
	{
		printf("Type the collum:\n");
		collum = intInput(1, 3);
		printf("Type the row\n");
		row = intInput(1,3);
		collum--;
		row--;
		
		moveResult = gridAlloc( grid, row, collum, turn );
		displayMoveMsg( moveResult );
		
		if( moveResult == MOVE_OK )
		{
			printBoard( grid );
			winner = winChecker( grid );
			if( winner == CELL_X )
			{
				return RESULT_X_WINS;
			}
			else if( winner == CELL_O )
			{
				return RESULT_O_WINS;
			}
			else if( winner == CELL_EMPTY && turn == 8 )
			{
				return RESULT_DRAW;
			}
			turn++;
			int level = level1( grid, turn );
			if( level)
			{
				printBoard( grid );
				turn++;
			}
		}
		
	}	
}
/*Makes the board move*/
State gridAlloc( board *grid, int row, int collum, int turn )
{
	Cell who = whoTurn( turn );
	if( isCellEmpty( grid, row, collum ) == CELL_EMPTY )
	{
		grid->boardGrid[row][collum] = who;
		return MOVE_OK;
	}
	else
	{
		return MOVE_OCCUPIED;
	}
}
/*It return the value of the chose grid(Is a way to make the code more
readable, due to the function name)*/
Cell isCellEmpty( const board *grid, int r, int c )
{
	return grid->boardGrid[r][c];
}

Cell whoTurn( int turn )
{
	if( turn % 2 == 0 )
	{
		return CELL_X;
	}
	else if( turn % 2 != 0 )
	{
		return CELL_O;
	}
	return CELL_EMPTY;
}

void displayMoveMsg( State moveResult )
{
	switch ( moveResult ) 
	{
	case MOVE_OK:
		break;
	case MOVE_OCCUPIED:
		printf("Cell already occupied.\n");
		break;
	default:
		printf("MOVE ATTEMPT ERROR!\n");
		break;
	}
}
/*Initialize all the array grid to ENUM Cell_Empyty*/
void initializer ( board *grid )
{
	
	for( int r = 0 ; r < 3; r++ )
	{
		for( int c = 0 ; c < 3; c++ )
		{
			grid->boardGrid[r][c] = CELL_EMPTY;
		}
	}
	
}

Cell winChecker( const board *grid )
{
	/*Return cell_x, cell_o, cell_empty for drawn*/
	Cell dResult = diagonalChecker( grid );
	Cell vResult = verticalChecker( grid );
	Cell hResult = horizontalChecker( grid );
	if( dResult != CELL_EMPTY )
	{
		return dResult;
	}
	else if( vResult != CELL_EMPTY )
	{
		return vResult;
	}
	else if( hResult != CELL_EMPTY )
	{
		return hResult;
	}
	return CELL_EMPTY;
}


Cell horizontalChecker( const board *grid )
{
	for( int r = 0 ; r < 3 ; r++  )
	{
		Cell a = grid->boardGrid[r][0];
		/*Check the first first collum and 3 rows*/
		int standTest = ( a != CELL_EMPTY );
		/*If its false it wont return a*/
		for( int c = 1; c < 3 && standTest; c++ )
		{
			if (grid->boardGrid[r][c] != a)
			{
				standTest = 0;
			}
		}
		/*If standTest comes here been true it means it passed the test
		and i can return it without checking the other's(only one row
		can be true at time)*/
		if( standTest )
		{
			return a;
		}
	}
	return CELL_EMPTY;
}

Cell verticalChecker( const board *grid )
{
	for( int c = 0 ; c < 3 ; c++  )
	{
		Cell a = grid->boardGrid[0][c];
		/*Check the first first collum and 3 rows*/
		int standTest = ( a != CELL_EMPTY );
		/*If its false it wont return a*/
		for( int r = 1; r < 3 && standTest; r++ )
		{
			if (grid->boardGrid[r][c] != a)
			{
				standTest = 0;
			}
		}
		/*If standTest comes here been true it means it passed the test
		and i can return it without checking the other's(only one row
		can be true at time)*/
		if( standTest )
		{
			return a;
		}
	}
	return CELL_EMPTY;
}


Cell diagonalChecker(const board *grid)
{
	Cell a = grid->boardGrid[0][0]; 
	Cell b = grid->boardGrid[0][2];

	int standTest = (a != CELL_EMPTY);
	int inverseTest = (b != CELL_EMPTY);
	
	for (int j = 0, k = 2; j < 3; j++, k--)
	{
		/* Main diagonal: (0,0), (1,1), (2,2)*/
		if (grid->boardGrid[j][j] != a)
			standTest = 0;
		
		/*Second diagonal: (0,2), (1,1), (2,0)*/
		if (grid->boardGrid[j][k] != b)
			inverseTest = 0;
	}
	
	if (standTest)
		return a;
	
	if (inverseTest)
		return b;
	
	return CELL_EMPTY;
}




