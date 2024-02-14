#include"2048.h"

// Default constructor where all the data members are initialise
Game2048::Game2048() : max(0), score(0) {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = 0;
		}
	}

	memset(visibility, 0, sizeof(visibility));
	srand((unsigned)time(NULL));
	randomNumber(2);
}

// That is the function that executes the game. The function first print the grid. After that there is a loop   
void Game2048::start() {
	printAll();

	while (true) {
		char ch = _getch();
		switch (ch) {
		case 'w':
		case 'W':
		case 72:
			moveInDirection(-1, 0);			// Moving UP
			break;
		case 's':
		case 'S':
		case 80:
			moveInDirection(1, 0);			// Moving DOWN
			break;
		case 'a':
		case 'A':
		case 75:
			moveInDirection(0, -1);			// Moving LEFT
			break;
		case 'd':
		case 'D':
		case 77:
			moveInDirection(0, 1);			// Moving RIGHT
			break;
		case 27:					// Stops the game using escape key
			return;
		default:
			continue;				// Ignore invalid keys
		}

		randomNumber(1);
		system("cls");
		printAll();
		if (isGameOver()) {
			std::cout << "Game Over! \n";
			break;
		}
		if (getResult()) {
			std::cout << "You Win! \n";
			break;
		}
	}
	std::cout << "Thanks for playing! \n";
}

// Print function that have the instruction of the game and nested for loop for printing the grid
void Game2048::printAll() const {
	std::cout << std::setw(70) << " Welcome to 2048! \n"
		<< "Instructions: \n The goal of the game is to collect numbers by dragging them in the four directions with the help of the"
		<< "arrows on the \n keyboard or with the letters 'a', 'w', 's', 'd'. You win the game if it is one cell and you have collected"
		<< " the number 2048!\n Let's play 2048. Good luck! \n";

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (j == 0) {
				std::cout << std::setw(53) << grid[i][j];
			}
			else {
				std::cout << std::setw(7) << grid[i][j];
			}
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << std::setw(85) << "Max:" << max << "     " << "Score:" << score << std::endl;
}

// randomNumber gets a parameter which is the count of the random numbers to place on the free spaces on the grid. 
// The function finds an empty space on the grid and add a number(2 or 4) randomly generated
void Game2048::randomNumber(int countOfNumsToPlace) {
	while (countOfNumsToPlace) {
		short randRow = rand() % 4;
		short randColumn = rand() % 4;

		if (visibility[randRow][randColumn] == 0) {
			visibility[randRow][randColumn] = 1;
			short randNum = rand() % 4 + 2;

			if (randNum % 2 != 0) {
				randNum -= 1;
			}
			grid[randRow][randColumn] = randNum;

			--countOfNumsToPlace;
		}
	}
	system("cls");
}

// The funciton of the movement
void Game2048::moveInDirection(int deltaRow, int deltaColumn) {
	// Define the direction of movement based on deltaRow and deltaColumn
	unsigned startRow = (deltaRow == 1) ? GRID_SIZE - 1 : 0,
		startColumn = (deltaColumn == 1) ? GRID_SIZE - 1 : 0,
		endRow = (deltaRow == 1) ? -1 : GRID_SIZE,
		endColumn = (deltaColumn == 1) ? -1 : GRID_SIZE,
		rowStep = (deltaRow == 1) ? -1 : 1,
		columnStep = (deltaColumn == 1) ? -1 : 1;

	// Iterate through the grid based on the direction of movement
	for (int i = startRow; i != endRow; i += rowStep) {
		for (int j = startColumn; j != endColumn; j += columnStep) {
			if (visibility[i][j] == 1) {
				// Find the farthest empty cell along the direction of movement
				int newRow = i;
				int newColumn = j;

				while (isValidCell(newRow + deltaRow, newColumn + deltaColumn) && grid[newRow + deltaRow][newColumn + deltaColumn] == 0) {
					newRow += deltaRow;
					newColumn += deltaColumn;
				}

				// Move the value to the farthest empty cell
				if (newRow != i || newColumn != j) {
					grid[newRow][newColumn] = grid[i][j];
					grid[i][j] = 0;
					visibility[newRow][newColumn] = 1;
					visibility[i][j] = 0;
				}

				// Merge adjacent cells if their values are equal
				if (isValidCell(newRow + deltaRow, newColumn + deltaColumn) && grid[newRow + deltaRow][newColumn + deltaColumn] == grid[newRow][newColumn]) {
					grid[newRow + deltaRow][newColumn + deltaColumn] *= 2;
					grid[newRow][newColumn] = 0;
					visibility[newRow][newColumn] = 0;

					max = std::max(max, grid[newRow + deltaRow][newColumn + deltaColumn]);
					score += grid[newRow + deltaRow][newColumn + deltaColumn];
				}
			}
		}
	}
}

// Helper functions see if cell is valid, to get is there more empty space on the grid and if the player have the number 2048

bool Game2048::isValidCell(int row, int column) const {
	return row >= 0 && row < GRID_SIZE && column >= 0 && column < GRID_SIZE;
}

bool Game2048::isGameOver() const {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (visibility[i][j] == 0) {
				return false;				// Continue the game
			}
		}
	}
	return true;							// Break the game
}

bool Game2048::getResult() const {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (grid[i][j] == 2048)
				return true;
		}
	}
	return false;
}
