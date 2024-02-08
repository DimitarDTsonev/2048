#ifndef GAME_2048_HEADER
#define GAME_2048_HEADER

#include<iostream>
#include<conio.h>		//	using for _getch()
#include<iomanip>		//	using for setw()

class Game2048 {
public:
	// Default Constructor:
	Game2048();

	// The game starts:
	void start();

private:
	// Data members:
	static const short GRID_SIZE = 4;
	unsigned grid[GRID_SIZE][GRID_SIZE];
	unsigned visibility[GRID_SIZE][GRID_SIZE];
	unsigned max;
	unsigned score;

	// Functionality:
	void printAll() const;
	void randomNumber(int);

	// Moving the matrix: 
	void moveInDirection(int, int);

	// Checks:
	bool isValidCell(int, int) const;
	bool isGameOver() const;
	bool getResult() const;
};
#endif // GAME_2048_HEADER
