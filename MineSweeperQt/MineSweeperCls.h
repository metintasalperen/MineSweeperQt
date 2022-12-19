#ifndef MINESWEEPERCLS_H
#define MINESWEEPERCLS_H

#include "EnumPkg.h"
#include "StructPkg.h"

class MineSweeperCls
{
private:
	TileStc* MineField;
	unsigned int MaxRow;
	unsigned int MaxColumn;
	unsigned int MineCount;
	bool FirstInput;
	GameStatusEnum GameState;

private:
	// Maps 2d mine field array to 1d array
	unsigned int CalculateIndex(unsigned int row, unsigned int column);

	// Allocates memory according to user defined mine field size
	// Initializes mine field
	// 
	// Returns success if allocation successful
	// Returns error if allocation failed
	ResultEnum CreateMineField();

	// Randomly places mines to mine field
	// Mines are not placed to the user input tile and its neighbors
	void PlaceMines(unsigned int row, unsigned int column);

	// Calculates the number of mines that is adjacent to given cell
	unsigned int FindAdjacentMineCount(unsigned int row, unsigned int column);

	// Calculates the number of flags that is adjacent to given cell
	unsigned int FindAdjacentFlagCount(unsigned int row, unsigned int column);

	// Adds flag to the given cell
	void FlagCell(unsigned int row, unsigned int column);

	// Opens given cell if it is unflagged
	// If given cell does not contain mine, calculates neighbor mine count and set that cell to calculated number
	// If no neighbor contains mine, recursively opens all neighbors as well
	// If given cell has mine, then ends game
	void OpenCell(unsigned int row, unsigned int column, bool firstIteration);

	// Deallocates memory when game ends
	void DestroyMineField();

	// Checks game status
	GameStatusEnum CheckGameStatus();

public:

	// Default constructor
	MineSweeperCls();

	// Sets user defined mine field size and mine count
	ResultEnum SetOptions(unsigned int row, unsigned int column, unsigned int mineCount);

	// Processes user input
	GameStatusEnum ProcessUserInput(unsigned int row, unsigned int column, UserActionEnum userAction);
};

#endif