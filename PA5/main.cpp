// main.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include "Organism.h"
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "Doodlebug.h"
#include "Ant.h"
#include <iostream>
using namespace std;

Organism*** grid;
int numD;
int numA;
int totalD;
int totalA;
int gridLen;

/**
 * onEdge() checks the cell which whose coordinates
 * are passed and returns a boolean indicating whether
 * it is on the edge of the grid or not
 *
 * @return boolean indicating whether the given cell is on the edge
 */
bool onEdge(int x, int y) {
	return (x == 0) || (x == gridLen - 1) || (y == 0) || (y == gridLen - 1);
}

/**
 * canAttack() returns a boolean indicating whether
 * the object in the given cell coordinates is able to attack
 *
 * @return boolean indicating whether the given cell contains an organism which is able to attack
 */
bool canAttack(int x, int y) {
	if (grid[x][y] == NULL) {
		return false;
	} else {
		return grid[x][y]->isPrey;
	}
}

/**
 * update() loops through the grid, updating canMove
 * for all organisms and then updates all organisms on the
 * grid, updating all doodlebugs first and all ants
 */
void update() {
	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		for (int j = 0; j < gridLen; j++) {//LOOP INVARIANT: j < gridLen, means  j will loop through every column from 0..gridLen-1
			if (grid[i][j] == NULL) {//if there is nothing there

			} else {//otherwise set the object able to move
				grid[i][j]->canMove = true;
			}
		}
	}

	// Loops through entire board, updating the state of all doodlebugs before the ants
	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		for (int j = 0; j < gridLen; j++) {//LOOP INVARIANT: j < gridLen, means  j will loop through every column from 0..gridLen-1
			if (grid[i][j] != NULL && grid[i][j]->canMove) {//if there is an organism there and it can move
				if (grid[i][j]->isPrey == false) {//if it is a doodlebug
					grid[i][j]->action();
				}
			}
		}
	}

	// Loops through entire board, updating the state of all ants after the doodlebugs
	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		for (int j = 0; j < gridLen; j++) {//LOOP INVARIANT: j < gridLen, means  j will loop through every column from 0..gridLen-1
			if (grid[i][j] != NULL && grid[i][j]->canMove) {//if there is an organism there and it can move
				if (grid[i][j]->isPrey == true) {//if it is an ant
					if (grid[i][j] == NULL) {//check again to make sure

					} else {//otherwise its an ant that can act
						grid[i][j]->action();
					}
				}
			}
		}
	}
}

/**
 * printBoard() loops through the grid, printing out
 * the current state of the grid with x's indicating
 * a doodlebug and o's indicating an ant
 */
void printBoard() {
	std::cout << endl << "|";
	for(int i =0; i < gridLen;i++){//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		std::cout << "-";
	}
	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		std::cout << "|" << endl << "|";
		for (int j = 0; j < gridLen; j++) {//LOOP INVARIANT: j < gridLen, means  j will loop through every column from 0..gridLen-1
			if (grid[i][j] == NULL) {//if there is no organism in the cell
				std::cout << " ";
			} else {
				if (grid[i][j]->isPrey) {//if there is an ant in the cell
					std::cout << "o";
				} else {
					std::cout << "x";//if there is a doodlebug in the cell
				}
			}
		}
	}
	std::cout << "|" << endl;
	std::cout << "|" ;
	for(int i =0; i < gridLen;i++){//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
			std::cout << "-";
		}
	std::cout << "|" << endl;
}

/**
 * main() handles running the simulation, passing arguments
 * initializing the grid, looping through eat step of the
 * simulation, printing out the results, and then deallocating
 * memory
 *
 * @return 0 for a successful program execution
 */
int main(int argc, char **argv) {
	gridLen = 20;//intialize gridLen to default
	int doodlebugs = 5;//intialize all command line inputs to default
	int ants = 100;
	int steps = 1000;
	int seed = 1;
	int pause = 0;
	switch (argc) {//switch that selects based on number of input, and changes variables accordingly
	case 7:
		pause = atoi(argv[6]);
	case 6:
		if (atoi(argv[5]) == 0) {
			seed = time(NULL);
		} else {
			seed = (atoi(argv[5]));
		}
	case 5:
		steps = (atoi(argv[4]));
	case 4:
		ants = atoi(argv[3]);
	case 3:
		doodlebugs = atoi(argv[2]);
	case 2:
		gridLen = atoi(argv[1]);
	default:
		break;
	}
	srand(seed);

	if (pause != 0) {//if pause is turned on
		std::cout << "The board will be printed every " << pause
				<< " turns, enter a character and press enter to continue the program when this occurs."
				<< endl;
	}
	if (ants + doodlebugs > gridLen * gridLen) {//if there are too many objects for gridspace
		std::cout
				<< "There are more Organisms than space on the board, will terminate"
				<< endl;
		return 1;
	}

	grid = (Organism***) malloc(sizeof(Organism**) * gridLen);//initlaize 2d array of pointers
	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		grid[i] = (Organism**) malloc(sizeof(Organism*) * gridLen);//set space for each row
	}

	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		for (int j = 0; j < gridLen; j++) {//LOOP INVARIANT: j < gridLen, means  j will loop through every column from 0..gridLen-1
			grid[i][j] = NULL;//default all cells to NULL
		}
	}

	for (int i = 0; i < doodlebugs; i++) {//LOOP INVARIANT: i < doodlebugs, means i will increment from 0..doodlebugs-1
		int x = rand() % gridLen;
		int y = rand() % gridLen;
		if (grid[x][y] == NULL) {//if cell is empty
			Doodlebug* temp = new Doodlebug(x, y);//create new doodlebug
			grid[x][y] = temp;
		} else {//otherwise cycle again and find a new spot that's available
			i--;
		}
	}
	for (int i = 0; i < ants; i++) {//LOOP INVARIANT: i < ants, means i will increment from 0..ants-1
		int x = rand() % gridLen;
		int y = rand() % gridLen;
		if (grid[x][y] == NULL) {//if the cell is empty
			Ant* temp = new Ant(x, y);//create new ant
			grid[x][y] = temp;
		} else {//otherwise cycle again and find a new spot that's available
			i--;
		}
	}

	int time = 0;
	char getChar;
	while (time < steps) {//LOOP INVARIANT: time < steps, time will increment from 0...steps-1 is the time of the simulation
		if (numD <= 0 || numA <= 0) {//if either species died out
			break;
		}
		update();
		if (pause != 0) {//if pause is turned on
			if (time % pause == 0) {//every nth time this will trigger, where n = pause
				printBoard();
				std::cin >> getChar;//require char input
			}
		}
		time++;
	}

	std::cout << "Command line: ";
	for (int i = 0; i < argc; i++) {//LOOP INVARIANT: i < argc, from 0...argc-1 prints out all command line values
		std::cout << argv[i] << " ";
	}
	std::cout << endl;
	std::cout << "The number of steps simulated was: " << time << endl;
	std::cout << "The total number of ants was: " << totalA
			<< " and the number of ants remaining was: " << numA << endl;
	std::cout << "The total number of Doodlebugs was: " << totalD
			<< " and the number of Doodlebugs remaining was: " << numD << endl;
	std::cout << "The final board was: " << endl;
	printBoard();

	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		for (int j = 0; j < gridLen; j++) {//LOOP INVARIANT: j < gridLen, means  j will loop through every column from 0..gridLen-1
			if (grid[i][j] != NULL) {//if there is an object here
				delete grid[i][j];//delete all objects in the board
			}
		}
	}

	for (int i = 0; i < gridLen; i++) {//LOOP INVARIANT: i < gridLen, means  i will loop through every row from 0..gridLen-1
		free(grid[i]);//free 2d array memory
	}
	free(grid);//free the last part of the grid
	return 0;
}

