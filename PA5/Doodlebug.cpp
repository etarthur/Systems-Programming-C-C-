// Doodlebug.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include "Doodlebug.h"
#include <stdlib.h>
#include "Organism.h"
#include "main.h"

extern Organism*** grid;
extern int numD;
extern int totalD;
extern int gridLen;

/**
 * Doodlebug() is the constructor for a Doodlebug
 * object with no parameters
 */
Doodlebug::Doodlebug() {
	// TODO Auto-generated constructor stub

}

/**
 * Doodlebug() is the constructor for a Doodlebug object with
 * coordinates as parameters, and is initialized with default
 * values. It increments the count of total and current
 * doodlebugs
 */
Doodlebug::Doodlebug(int x, int y) {
	this->x = x;
	this->y = y;
	this->age = 0;
	this->hunger = 0;
	this->isPrey = false;
	totalD++;
	numD++;
}

/**
 * ~Doodlebug() is the destructor for a Doodlebug object,
 * it decrements the number of current doodlebugs
 */
Doodlebug::~Doodlebug() {
	// TODO Auto-generated destructor stub
	numD--;
}

/**
 *  getTime() is a getter function for the turns
 *  which the doodlebug has been alive
 *
 *  @return age of the Doodlebug object
 */
int Doodlebug::getTime() {
	return age;
}

/**
 * isMove() checks the state of the given cell
 * to see whether the object can be moved into
 * by an existing Doodlebug
 *
 * @return a boolean for if the cell can be moved into
 */
bool Doodlebug::isMove(int x, int y) {
	return (grid[x][y] == NULL);
}

/**
 * simpleMove() attempts to move a doodlebug into an
 * adjacent cell, choosing one randomly and trying the
 * rest. If none of the cases which were tried work,
 * move() calls itself recursively to try again. It also
 * checks whether it is on the edge of the grid, and
 * terminates if the ant is unable to move
 */
void Doodlebug::simpleMove() {
	int random = rand() % 4;
	int basex = this->x;
	int basey = this->y;
	switch (random) {//go to a random direction and check if it can move, if not it cascades downward
	case 0:
		if (basey == gridLen - 1) {//if on right
		} else {
			if (isMove(x, y + 1)) {
				this->y++;
				return;
			}
		}
	case 1:
		if (basex == gridLen - 1) {//if on bottom
		} else {
			if (isMove(x + 1, y)) {
				this->x++;
				return;
			}
		}
	case 2:
		if (basey == 0) {//if on left
		} else {
			if (isMove(x, y - 1)) {
				this->y--;
				return;
			}
		}
	case 3:
		if (basex == 0) {//if on top
		} else {
			if (isMove(x - 1, y)) {
				this->x--;
				return;
			}
		}
	}

	// Check the original coordinates of the doodlebug to see if it is in a position where it cannot move
	if (onEdge(basex, basey)) {//if an object is on the edge
		if (basex == 0 && basey == 0) {//if top left corner
			if (!(isMove(x, y + 1) || isMove(x + 1, y))) {
				return;
			}
		}
		if (basex == 0 && basey == gridLen - 1) {//if top right corner
			if (!(isMove(x, y - 1) || isMove(x + 1, y))) {
				return;
			}
		}
		if (basex == gridLen - 1 && basey == 0) {//if bottom left corner
			if (!(isMove(x - 1, y + 1) || isMove(x, y + 1))) {
				return;
			}
		}
		if (basey == gridLen - 1 && basex == gridLen - 1) {//if bottom right corner
			if (!(isMove(x, y - 1) || isMove(x - 1, y))) {
				return;
			}
		}
		if (basex == 0) {//if on top row
			if (!(isMove(x, y + 1) || isMove(x, y - 1) || isMove(x + 1, y))) {
				return;
			}
		}
		if (basex == gridLen - 1) {//if on last row
			if (!(isMove(x, y + 1) || isMove(x, y - 1) || isMove(x - 1, y))) {
				return;
			}
		}
		if (basey == 0) {//if on first column
			if (!(isMove(x, y + 1) || isMove(x + 1, y) || isMove(x - 1, y))) {
				return;
			}
		}
		if (basey == gridLen - 1) {//if on last column
			if (!(isMove(x, y - 1) || isMove(x + 1, y) || isMove(x - 1, y))) {
				return;
			}
		}
	} else {//otherwise in the middle area
		if (!(isMove(x, y + 1) || isMove(x, y - 1) || isMove(x + 1, y)
				|| isMove(x - 1, y))) {
			return;
		}
	}
	if (basey == y && basex == x) {//if it didn't move but can
		move();
	}
}

/**
 * move() checks the adjacent cells for prey,
 * and attacks if it can. If it cannot, calls
 * simpleMove() to move the the Doodlebug
 */
void Doodlebug::move() {
	bool aroundPrey;
	int random = rand() % 4; // Randomly choose a direction to check first
	int basex = this->x;
	int basey = this->y;
	if (onEdge(basex, basey)) {//on an edge?
		if (basex == 0 && basey == 0) {//top corner
			aroundPrey = (canAttack(basex + 1, basey)
					|| canAttack(basex, basey + 1));
		}
		if (basex == gridLen - 1 && basey == 0) {//bottom corner
			aroundPrey = (canAttack(basex - 1, basey)
					|| canAttack(basex, basey + 1));
		}
		if (basey == gridLen - 1 && basex == 0) {//top corner
			aroundPrey = (canAttack(basex + 1, basey)
					|| canAttack(basex, basey - 1));
		}
		if (basex == gridLen - 1 && basey == gridLen - 1) {//bottom corner
			aroundPrey = (canAttack(basex - 1, basey)
					|| canAttack(basex, basey - 1));
		}
		if (basex == 0 && basey != 0 && basey != gridLen - 1) {//on top edge
			aroundPrey = (canAttack(basex + 1, basey))
					|| (canAttack(basex, basey - 1))
					|| (canAttack(basex, basey + 1));
		}
		if (basex == gridLen - 1 && basey != 0 && basey != gridLen - 1) {//on bottom edge
			aroundPrey = (canAttack(basex - 1, basey))
					|| (canAttack(basex, basey - 1))
					|| (canAttack(basex, basey + 1));
		}
		if (basey == 0 && basey != gridLen - 1 && basex != 0
				&& basex != gridLen - 1) {//on left side
			aroundPrey = (canAttack(basex - 1, basey))
					|| (canAttack(basex + 1, basey))
					|| (canAttack(basex, basey + 1));
		}
		if (basey == gridLen - 1 && basey != 0 && basex != 0
				&& basex != gridLen - 1) {//on right edge
			aroundPrey = (canAttack(basex - 1, basey))
					|| (canAttack(basex + 1, basey))
					|| (canAttack(basex, basey - 1));
		}
	} else {//otherwise in middle
		aroundPrey = (canAttack(basex - 1, basey))
				|| (canAttack(basex + 1, basey))
				|| (canAttack(basex, basey - 1))
				|| (canAttack(basex, basey + 1));
	}
	if (aroundPrey) {
		switch (random) {
		case 0: // Cell to left
			if (basex == 0) {
				break;
			}
			if (canAttack(basex - 1, basey)) {
				delete grid[basex - 1][basey];
				grid[basex - 1][basey] = NULL;
				this->x--;
				this->hunger = -1;
				return;
			}
		case 1: // Cell to right
			if (basex == gridLen - 1) {
				break;
			}
			if (canAttack(basex + 1, basey)) {
				delete grid[basex + 1][basey];
				grid[basex + 1][basey] = NULL;
				this->x++;
				this->hunger = -1;
				return;
			}
		case 2: // Cell below
			if (basey == 0) {
				break;
			}
			if (canAttack(basex, basey - 1)) {
				delete grid[basex][basey - 1];
				grid[basex][basey - 1] = NULL;
				this->y--;
				this->hunger = -1;
				return;
			}
		case 3: // Cell above
			if (basey == gridLen-1) {
				break;
			}
			if (canAttack(basex, basey + 1)) {
				delete grid[basex][basey + 1];
				grid[basex][basey + 1] = NULL;
				this->y++;
				this->hunger = -1;
				return;
			}
		}
	} else {
		this->simpleMove();
	}
}

/**
 * breed() checks the age of the doodlebug and creates a
 * new doodlebug if the age of the doodlebug is at least 8.
 * Upon creating a new doodlebug, moves it into an adjacent
 * cell and resets the age of the current doodlebug
 *
 * @return pointer to the newly born doodlebug or a null
 * object if breeding conditions are not met
 */
Doodlebug* Doodlebug::breed() {
	if (age >= 8) {//if able to breed
		Doodlebug* temp = new Doodlebug(x, y);
		temp->move();
		int nx = temp->x;
		int ny = temp->y;
		delete temp;
		if (nx != x || ny != y) {//if possible to have child
			Doodlebug* baby = new Doodlebug(nx, ny);
			totalD--;
			age = -1;//set to -1 because increments after to 0 after a turn
			return baby;
		} else {//otherwise cant breed, age isnt reset

		}
	}
	return NULL;
}

/**
 * starve() checks the hunger of the doodlebug and
 * kills off the doodlebug if the hunger conditions
 * are met.
 *
 * @return boolean indicating whether the doodlebug
 * starved or not
 */
bool Doodlebug::starve() {
	if (this->hunger == 3) {//if starving
		grid[this->x][this->y] = NULL;
		delete this;
		return true;
	} else {
		return false;//dead
	}
}

/**
 * action() processes a regular turn of an ant, moving the
 * ant and checking if it can breed in the current turn
 */
void Doodlebug::action() {
	bool isDead = this->starve();
	if (isDead) {//if it died do nothing
		return;
	}
	grid[this->x][this->y] = NULL;
	this->move();
	grid[this->x][this->y] = this;
	this->canMove = false;
	this->age++;
	this->hunger++;
	if (this->age < 8) {//if not able to breed
		return;
	} else {//can breed
		Doodlebug* child = this->breed();
		if (child == NULL) {
			totalD--;
			return;
		} else {
			grid[child->x][child->y] = child;
			return;
		}

	}
}

