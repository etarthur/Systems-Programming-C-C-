/*
 * life.c
 *
 *  Created on: Sep 14, 2017
 *      Author: etarthur
 */


#include <stdio.h>
#include "life.h"
#include <stdlib.h>

//declared all global variables that will be used by program and passed in by user through the command line

int rows;
int columns;
int gens;


/**boundayChecker consumes a board and a specific coordinate pair and returns what happens to the cell in the next generation.
 * boundaryChecker consumes a pointer to a board, and a coordinate pair to check. Checking is done by first checking if
 * the x,y pair requires extra behavior. There are 8 test cases, 4 of which trigger when x,y is on a corner of the board,
 * the other 4 trigger when x,y is on the edge of the board but not at a corner. This is done to make sure the check doesn't go out of bounds.
 * Then by looking at all neighbors around it calculates whether the cell will live or die in the next generation. This is done by using the
 * rules set forth in the assignment and outlined more in depth in the readme, general rules found at bottom in return block.
 * @param int** board: a pointer to the 2d array that is being checked
 * @param int x: the row of the coordinate pair being investigated.
 * @param int y: the column of the coordinate pair being investigated;
 * @return: the function either returns a 1 or 0, 0 meaning the cell is empty in the next generation, 1 meaning it's alive.
 */
int boundaryChecker(int **board, int x, int y){
	int around = 0;//the value of all the cells adjacent to board[x,y];
	if(around == 0){//starts the tree of logic to find around value.
		if(x==0 && y==0){//Checks if the cell is in the top right corner
			around = board[x+1][y] + board[x+1][y+1] + board[x][y+1];//corrects formula to account for array bounds
		}
		else if(x==rows-1 && y==columns-1){//Checks if the cell is in the bottom right corner
			around = board[x-1][y] + board[x-1][y-1] + board[x][y-1];//corrects formula to account for array bounds
		}
		else if(x==0 && y==columns-1){//Checks if the cell is in the top right corner
			around = board[x+1][y] + board[x+1][y-1] + board[x][y-1];//corrects formula to account for array bounds
		}
		else if(x==rows-1 && y==0){//Checks if the cell is in the bottom left corner
			around = board[x-1][y] + board[x-1][y-1] + board[x][y+1];//corrects formula to account for array bounds
		}
		else if(x==rows-1 && y!=0 && y!=columns-1){//Checks if the cell is located on bottom row
			around = board[x-1][y] + board[x-1][y-1] + board[x][y+1] + board[x-1][y-1] + board[x][y+1];//corrects formula to account for array bounds
		}
		else if(x==0 && y!=0 && y!= columns-1){//Checks if the cell is located on the top row
			around = board[x+1][y] + board[x+1][y-1] + board[x][y+1] + board[x+1][y-1] + board[x][y+1];//corrects formula to account for array bounds
		}
		else if(y==columns-1 && x!=0 && x!=rows-1){//Checks if the cell is located on the far right column
			around = board[x-1][y-1] + board[x-1][y] + board[x][y-1] + board[x+1][y] + board[x+1][y-1];//corrects formula to account for array bounds
		}
		else if(y==0 && x!=0 && x!=rows-1){//Checks if the cell is located on the far left column
			around = board[x-1][y+1] + board[x-1][y] + board[x][y+1] + board[x+1][y] + board[x+1][y+1];//corrects formula to account for array bounds
		}
		else{//the case for a majority of cells that have 8 neighbors and don't require special care
			around = board[x-1][y-1] + board[x-1][y] + board[x-1][y+1] + board[x][y-1] + board[x][y+1] + board[x+1][y-1] + board[x+1][y] + board[x+1][y+1];
		}
	}

	if((around == 2 || around==3) && board[x][y]){//if a cell has 2 or 3 neighbors and is alive it remains alive
		return 1;
	}
	else if(around==3 && board[x][y]==0){//if a cell has 3 neighbors, and has no life in it, it birthes life
		return 1;
	}
	else{//all other cases result in a cell dying
		return 0;
	}
}

/**playOne takes an old and new board and fills in the new board with a new generation generated from the old board
 * playOne works by taking a pointer to two different 2d arrays, one of which contains a generation, and the other
 * that will receive the new generation. The function then loops through all entries in the new board and sets them
 * accordingly to what generation would be produced from the old board using the boundaryChecker function to calculate
 * whether a cell is dead or alive
 * @param int** oldBoard: a pointer to a 2d array with information about the last generation in it
 * @param int** newBoard: a pointer to a 2d array that will store the new generation
*/
void playOne(int **oldBoard, int **newBoard){
	for(int x =0; x< rows; x++){//loops through every row, 0...rows-1, INVARIANT: x < rows, cannot exceed array dimensions
		for(int y =0; y< columns; y++){//loops through every columns, 0...columns-1, INVARIANT y < columns, same as above
			newBoard[x][y] = boundaryChecker(oldBoard,x,y);//generates elements on the new board, based off oldBoard, check
			//boundaryChecker's comment for information on how this is done
		}
	}
}

/** anyChange takes an old and new board and checks if there is any change between them
 * anyChange works by comparing every element of the old board with the new board and if there is a change returns 1,
 * otherwise 0, this is useful when trying to determine if a board is at steady state as this function will return 1.
 * This function may also be used on generations that are not sequential, therefore it can also track steady state between
 * any number of board states, they must all be passed in, in pairs though.
 * @param int** oldBoard: a pointer to a 2d array with a generation stored on it
 * @param int** newBoard: a pointer to a 2d array with a generation stored on it
 * @return: returns 1 if there was any difference between every element in both 2d arrays, otherwise returns 0
 */
int anyChange(int ** oldBoard, int ** newBoard){
	for(int x =0 ; x < rows; x++){//loops through every row, INVARIANT: x < rows-1, cannot exceed array dimensions, 0...rows
		for(int y =0; y < columns; y++){//loops through every column, INVARIANT: y < columns, cannot exceed array dimensions,0...columns-1
			if(oldBoard[x][y] != newBoard[x][y]){//checks if there is any difference between every element in both arrays
				return 1;
			}
	}
	}
	return 0;
}

/** steadyStateChecker consumes 3 2d arrays and returns 1 if they are at steady state or 0 otherwise.
 * steadyStateChecker checks if the game is at steady state( a state where the generations either remain the same
 * or oscillate between same states) this is done by using the anyChange function 3 times for the 3 different pairs
 * if any of them are the same then it is in steady state and returns 1 otherwise it returns 0
 * @param: int **a: pointer to an array with a board filled with a generation
 * @param: int **b: pointer to an array with a board filled with a generation
 * @param: int **c: pointer to an array with a board filled with a generation
 * @return: returns 1 if the game is at steady state otherwise returns 0
 */
int steadyStateChecker(int **a, int **b, int **c){
	if(((anyChange(a,b)== 0) || (anyChange(b,c)==0)) || anyChange(a,c)==0){//checks if any combination of the 3 boards is the same
		return 1;
	}
	else{//if the system is not at steady state it does this
		return 0;
	}
}

/**emptyBoardChecker consumes a board and returns 1 if there are no elements in the board
 * emptyBoardChecker works by looping through all cells in the board, and if any contain a value other than 0
 * it will return 0; If the board is empty it will returns 1. Yes this may look backwards but the values make sense
 * in the endingChecker function, check there for more information.
 * @param int** board: a pointer to the 2d array being checked
 * @return: returns 1 if the board is empty otherwise 0
 */
int emptyBoardChecker(int **board){
	for(int x =0; x< rows; x++){//loops through every row, INVARIANT: x < rows-1, loops from 0...rows
			for(int y =0; y< columns; y++){//loops through every column, INVARIANT: y < columns-1, loops from 0...columns
				if(board[x][y]){//if the cell contains any value greater than 0 this runs
					return 0;
				}
			}
		}
		return 1;//otherwise 1 is return to indicate empty board
}

/**endingChecker takes 3 2d arrays and returns 1 if the game should end
 * endingChecker uses steadyStateChecker, and emptyBoardChecker to check all the game ending conditions which are
 * the game is at steady state or everything has died. This works since steadyStateChecker and emptyBoardChecker return
 * 1 if its at steady state or empty, therefore this function can be written in one line that checks all of those.
 * @param int **a: a pointer to a 2d array(board) that is being checked
 * @param int **b: a pointer to a 2d array(board) that is being checked
 * @param int **ac: a pointer to a 2d array(board) that is being checked
 * @return: returns 0 if the game is not at an ending state, otherwise 1
 */
int endingChecker(int **a, int **b, int **c){
	int end = steadyStateChecker(a,b,c) + emptyBoardChecker(c) + emptyBoardChecker(b) + emptyBoardChecker(a);
	end = end + 1;//random arithmetic so that the compiler doesn't give the no use warning
	end = end - 1;
	return end;//returns 1+ if any of the
	//game ending conditions are true
}

/**playGame consumes 3 2d arrays and runs the game using all other functions priorly defined
 * playGame works by running through a loop of all generations and runs playOne every generation,
 * the function also checks for things like if pause and print are active and what to do then, every loop
 * after generation 3 the game is also checked to see if its over, g has to be above 3 to use the ending checker as
 * all 3 arrays must be initialized.
 * @param int ** A: one of three arrays that are used to store boards
 * @param int ** B: one of three arrays that are used to store boards
 * @param int ** C: one of three arrays that are used to store boards
 * @param int print: value of 1 if printing or 0 if not
 * @param int pause: value of 1 if want user input to pause, 0 otherwise
 */
void playGame(int **A, int **B, int **C, int print, int pause){
	char x;
	if(print){
		printf("Generation: 0\n");
		printBoard(rows,columns,C);//print the first generation
	}
	if(pause){
		printf("After every generation you must enter a character and hit enter to continue.\n");
	}
	for(int g = 0; g <= gens; g++){//loops through all generations, INVARIANT: g <= gens, loops through 0...gens
		if(pause){
			printf("Enter another char: \n");
			scanf(" %c",&x);;//if pause is true, then user input is required
		}
		if(print){
			printf("Generation: %d \n", g+1);
		}
		if(endingChecker(A,B,C) && g>=2){//checks if the game is over, after 3 generations are ran which is needed to use the
			//endingChecker
			printf("Simulation ended, because everything is dead or it is steady-state. The final generation: \n");//print game is over
			break;//break loop game ended
		}
		if(g%3==0){//this tree of ifs is used to determine which of 3 arrays to update, a==g%3==0
			playOne(C,A);//run one game and update a
			if(print) printBoard(rows,columns,A);//if print is true, then a is printed
		}
		if(g%3==1){//this is the tree for b, b==g%3==1
			playOne(A,B);
			if(print) printBoard(rows,columns,B);//if print is true, then b is printed
		}
		if(g%3==2){//final tree used to update c, c==g%3==2
			playOne(B,C);
			if(print) printBoard(rows,columns,C);//if print is true, then c is printed
		}
	}
	if(gens%3==0){//this logic tree prints out the final generation
			printBoard(rows,columns,A);
		}
		if(gens%3==1){
			printBoard(rows,columns,B);
		}
		else{
		printBoard(rows,columns,C);
		}
	if(endingChecker(A,B,C)){}//prevents both game ending prints to run
	else{
		printf("Simulation ended, as specified amount of generations was met. \n");//print game over out of generations
	}
}

/**main runs the entire program by calling all helper functions to simulate the game
 * main takes 6 arguments, well 5 but the first one is always the name of the program, it then sets those arguments
 * to the globals so that all functions can use them without passing them through,
 * it then initalizes the 3 arrays necessary to simulate the game. It then opens the input file, and
 * creates the board, and runs the game.
 * @param int argc: The number of arguments passed in + 1
 * @param char *argv[]: the values of the arguments passed in
 * @return main will return 0 if it worked,otherwise 1 to indicate failure.
 *
 */
int main(int argc, char *argv[]){
	if(argc<=4 || argc>7){//wrong number of parameters were passed in
		printf("Wrong number of parameters");
				return 1;
	}
	int * xptr;//intialize a pointer for the rows
	xptr = &rows;//set it equal to global rows address
	*xptr = atoi(argv[1]);//update globally
	int * yptr;//Same block as above but for columns
	yptr = &columns;
	*yptr = atoi(argv[2]);
	int * gptr;//same for generations
	gptr = &gens;
	*gptr = atoi(argv[3]);//^
	int print = 0;
	int pause = 0;
	if(argc >= 6){//if there are values for print and pause set them otherwise they are 0
		if(*argv[5]=='y'){//if print is y set it to true
			print = 1;
		}
	}
		if(argc == 7){//if pause was passed in
			if(*argv[6]=='y'){//^ same with pause
				pause = 1;
		}
	}
	int **a;//Initialize pointer to 2d array a
	a = (int **) malloc(rows*sizeof(int *));//allocate memory for data large enough to hold rows amount of arrays
	for(int i=0; i< rows;i++){//loop from 0...rows-1 INVARIANT: i < rows
		a[i] = (int *) malloc(columns*sizeof(int));//allocate memory for columns amount of integer in each subarray
	}

	int **b;//another 2d array initialization
	b = (int **) malloc(rows*sizeof(int *));
		for(int i=0; i< rows;i++){
			b[i] = (int *) malloc(columns*sizeof(int));
		}

	int **c;//yet another 2d array initialization
	c = (int **) malloc(rows*sizeof(int *));
	for(int i=0; i< rows;i++){
				c[i] = (int *) malloc(columns*sizeof(int));
			}


	FILE *ptr;//assign a pointer to FILE type
	ptr = fopen(argv[4],"r");//assign pointer to opening the file input passed from command line
	if(ptr==NULL)//if the file is empty or can't open
		fclose(ptr);//close it
	createBoard(rows,columns,ptr,c);//createBoard to start running the game
	playGame(a,b,c,print,pause);//play the game using the 3 arrays
	return 0;//return 1 if things worked
}
