/*
 * filefunctions.c
 *
 *  Created on: Sep 18, 2017
 *      Author: etarthur
 */

/**
 * filefunctions class has all the functions that read and write to files
 */
#include <stdio.h>
#include <stdlib.h>
#include "filefunctions.h"
#include "tree.h"


/** charAmount takes a file and returns the total number of characters in the file
 * charAmount scans through the file and increments for every character it then returns this number
 * @param ftr:  the pointer to the input file
 * @return int: the total number of characters in the file
 */
int charAmount(FILE * ftr){
	int x = 0;
	char c;
	while(fscanf(ftr," %c", &c)==1){
		x++;
	}
	return x;
}

/**printOrder takes a tree and an output file and prints out the words and their counts to the output file
 * printOrder works by using inOrder traversal of the tree since it is a binary tree it is sorted when elements
 * are added, therefore by traversing from the far left all the way to the far right notes it prints in order
 * @param tree: pointer to the tree being printed
 * @param ftr: pointer to the output file printed to
 */
void printOrder(BinaryTree *tree, FILE *ftr){
	if(tree==NULL){//if tree is empty do nothing
		return;
	}
	printOrder(tree->left,ftr);//recursively call again left
	fprintf(ftr,"%6d   %s \n", tree->times,tree->string);//print out the number of times and the string
	printOrder(tree->right,ftr);//recursively call again right
}
