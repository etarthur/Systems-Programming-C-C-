/*
 * stringfunctions.h
 *
 *  Created on: Sep 18, 2017
 *      Author: etarthur
 */

#ifndef STRINGFUNCTIONS_H_
#define STRINGFUNCTIONS_H_

#include "tree.h"


int compareString(int i,char *a, char *b,int alen, int blen);
void printString(char *a);
void addString(char *a, int length, BinaryTree *tree);
//int cleanStringLen(char *b, int length);
void stringCleaner(char* b);
void printOrder(BinaryTree *tree, FILE *ftr);

#endif /* STRINGFUNCTIONS_H_ */
