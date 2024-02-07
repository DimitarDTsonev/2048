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
			moveUp();
			break;
		case 's':
		case 'S':
		case 80:
			moveDown();
			break;
		case 'a':
		case 'A':
		case 75:
			moveLeft();
			break;
		case 'd':
		case 'D':
		case 77:
			moveRight();
			break;
		case 27:							// Stops the game
			return;
		default:
			continue;						// Ignore invalid keys
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

// The folling four functions implements the movement of the numbers on the grid
void Game2048::moveUp() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (visibility[j][i] == 1) {
				for (int k = j - 1; k >= 0; k--) {
					if (visibility[k][i] == 1) {
						if (grid[k][i] == grid[k + 1][i]) {
							grid[k][i] += grid[k][i];
							grid[k + 1][i] = 0;
							visibility[k + 1][i] = 0;

							max = std::max(max, grid[k][i]);
							score += grid[k][i];

							break;
						}
						else {
							break;
						}
					}
					else {
						int temp = grid[k][i];

						grid[k][i] = grid[k + 1][i];
						grid[k + 1][i] = temp;

						visibility[k + 1][i] = 0;
						visibility[k][i] = 1;
					}
				}
			}
		}
	}
}

void Game2048::moveDown() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = GRID_SIZE - 1; j >= 0; j--) {
			if (visibility[j][i] == 1) {
				for (int k = j + 1; k < GRID_SIZE; k++) {
					if (visibility[k][i] == 1) {
						if (grid[k][i] == grid[k - 1][i]) {
							grid[k][i] += grid[k - 1][i];
							grid[k - 1][i] = 0;
							visibility[k - 1][i] = 0;

							max = std::max(max, grid[k][i]);
							score += grid[k][i];

							break;
						}
						else {
							break;
						}
					}
					else {
						int temp = grid[k][i];

						grid[k][i] = grid[k - 1][i];
						grid[k - 1][i] = temp;

						visibility[k - 1][i] = 0;
						visibility[k][i] = 1;
					}
				}
			}
		}
	}
}

void Game2048::moveLeft() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (visibility[i][j] == 1) {
				for (int k = j - 1; k >= 0; k--) {
					if (visibility[i][k] == 1) {
						if (grid[i][k] == grid[i][k + 1]) {
							grid[i][k] += grid[i][k + 1];
							grid[i][k + 1] = 0;
							visibility[i][k + 1] = 0;

							max = std::max(max, grid[i][k]);
							score += grid[i][k];

							break;
						}
						else {
							break;
						}
					}
					else {
						int temp = grid[i][k];

						grid[i][k] = grid[i][k + 1];
						grid[i][k + 1] = temp;

						visibility[i][k + 1] = 0;
						visibility[i][k] = 1;
					}
				}
			}
		}
	}
}

void Game2048::moveRight() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = GRID_SIZE - 1; j >= 0; j--) {
			if (visibility[i][j] == 1) {
				for (int k = j + 1; k < GRID_SIZE; k++) {
					if (visibility[i][k] == 1) {
						if (grid[i][k] == grid[i][k - 1]) {
							grid[i][k] += grid[i][k - 1];
							grid[i][k - 1] = 0;
							visibility[i][k - 1] = 0;

							max = std::max(max, grid[i][k]);
							score += grid[i][k];

							break;
						}
						else {
							break;
						}
					}
					else {
						int temp = grid[i][k];

						grid[i][k] = grid[i][k - 1];
						grid[i][k - 1] = temp;

						visibility[i][k - 1] = 0;
						visibility[i][k] = 1;
					}
				}
			}
		}
	}
}

// Helper functions to get is there more empty space on the grid and if the player have the number 2048
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