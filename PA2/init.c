/*
 * init.c
 *
 *  Created on: Sep 14, 2017
 *      Author: etarthur
 */

#include <stdio.h>
#include "life.h"
#include <stdlib.h>

/** createBoard reads from a file and generates the first board for the game to run
 * createBoard consumes rows and columns, to generate the size of the board, it also
 * takes the file name and an array pointer to fill in with. The function then reads from the file and
 * initalizes the board according to what the file has in it. The input file must have less than 250 characters.
 * @param int rows: number of rows to generate
 * @param int columns: number of columns to generate
 * @FILE *fptr: pointer to a file that contains a pattern in it
 * @int * A[]: a pointer to a 2d array that will be updated with the board information
 */
void createBoard(int rows, int columns, FILE* fptr, int * A[]) {
	char C[250]; //the maximum characters in the input file is 250, C hold them
	for (int j = 0; j < 250; j++) { //loops through c 250 times and sets to char 'd
		C[j] = 'd';
	}
	FILE* input; //creates a pointer to a file
	input = fptr; //assign the pointer to the file
	int X[rows];//create a array that will be used such that the index number is the row number, and
	//the value per element is amount of elements in that row
	for (int i = 0; i < rows; i++){//INVARIANT: i < rows, loops through every element in this 1d array and sets it to zero.
		X[i]=0;
	}
	char c;
	if (!input) { //if the input doesn't open/no valid entry
		printf("No valid entry in file found");
		exit(-1); //breaks program with -1 so easy to find error
	}
	int i = 0; //intialize looping variable
	int lines = 0;//counts number of lines
	while (fscanf(input, "%c", &c) == 1) { //runs until the file ends, INVARIANT fscanf(...)==1, means that fscanf will run unitl eof
		if (c == '\n') { //if the character is a new line command char
			lines++; //increment lines, the number of lines
			C[i++] = '\n'; //increment i, and set \n into the array, used later to determine where line ends
		}
		else { //all other characters
			if (c == '\n') { //error checker to determine if this expression ran twice, only increment to get it off \n
				i++; //increment loop variable
			}
			else{
				//for every other character in the file
				X[lines] = X[lines] + 1;
				C[i++] = c; //place it in the array C
			}
		}
	}
	int maxIndex = 0;
	for(int m = 0; m <= lines;m++){
		if(X[m] > maxIndex){
			maxIndex = X[m];
		}
	}
	int z = 0; //z is the index of C, tracks to make sure doesn't go out of C bounds(250)
	int row = rows / 2 - lines / 2; //determine the starting row, is the middle of the board
	for (; row < rows; row++) { //loops through every row from row...rows, INVARIANT: row < rows
		if (z >= 249 || C[z] == 'd') { //if z is out of bounds of the array, or the array has reached terminating char 'd
			break; //end because ending conditions met
		}
		int column = columns / 2 - maxIndex / 2; //determine the center column
		for (; column < columns; column++) { //loops through every column from column...columns, INVARIANT column < columns
			if (z >= 249 || C[z] == 'd') { //same check as above
				break;
			}
			if (C[z] == '\n') { //if the current character is \n
				column = columns; //end loop by setting column out of its bounds
				z++; //increment the loop variable z
			} else { //runs for all characters except \n and d
				if (C[z] == 'x') { //if the current character is an x
					A[row][column] = 1; //set the current array element equal to 1
					z++; //increment loop variable
				} else { //runs for character o, since array is already set to 0 doesnt matter
					z++; //increment loop variable
				}
			}
		}
	}
}

/**printBoard loops through every element and prints out everyone, if the element has a 1 it prints x otherwise prints o
 * printBoard loops through all elements in a 2d array and prints out x for 1 or o for 0, creates the board representation
 * of the 2d array
 * @param int rows: the number of rows to print
 * @param int columns: the number of columns to print
 * @param int **board: the 2d array to be printed
 */
void printBoard(int rows, int columns, int **board) {
	for (int i = 0; i < rows; i++) { //loops through all rows,0...rows,INVARIANT: i < rows
		for (int j = 0; j < columns; j++) { //loops through all columns,0...columns,INVARIRANT j < columns
			if (board[i][j]) { //if the board has value 1 in that element
				printf("x"); //print x for 1
			} else { //all other element have 0
				printf("o"); //print out o for 0
			}
		}
		printf("\n"); //print a new line after every row
	}
	printf("\n"); //print a new line at the end of the function
}
