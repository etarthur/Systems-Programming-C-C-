/*
 * life.h
 *
 *  Created on: Sep 14, 2017
 *      Author: etarthur
 */

#ifndef LIFE_H_
#define LIFE_H_

#include<stdio.h>

void createBoard(int rows, int columns,FILE* fptr, int * A[]);
void printBoard(int rows, int columns, int **board);


#endif /* LIFE_H_ */
