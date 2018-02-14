/*
 * main.c
 *
 *  Created on: Sep 20, 2017
 *      Author: etarthur
 */

/**
 * main class that runs program uses helper functions from other classes to do most of the work. only function is main()
 */
#include <stdio.h>
#include "stringfunctions.h"
#include "tree.h"
#include "filefunctions.h"
#include <stdlib.h>
#include <string.h>

/**main takes input from the command line and runs the program which prints out all the words in the input files
 * main using all other functions defined in the project, opens all input, "cleans" all the words and outputs them along
 * with how many times they appear in a specified output file.
 * @param argc: Number of arguments passed in from command line + 1, the total amount of arguments
 * @param argv: The user input, in this case the first spot is output file the rest are input files
 * @return int: main will return 0 if it worked or 1 otherwise.
 */

int main(int argc,char **argv){
	BinaryTree *tree = malloc(sizeof(BinaryTree));//intialize BinaryTree
	tree = NULL;
	if(argc < 3 ){//Checks if the user inputed the correct amount of parameters
		printf("Input files required, program could not be run");
		return 1;
	}
	FILE * ftr;
	char* string = malloc(40*sizeof(char));
	for(int i = 2; i < argc; i++){//loops through all user input files, INVARIANT i < argc, means i is less than the amount
			//of user input + 1
			ftr = fopen(argv[i],"r");//cast pointer to open input file
			while(fscanf(ftr,"%s",string)==1){//loops through every string in the file, INVARIANT fscanf==1, means will only run
				//while there are things to scan, otherwise EOF is returned and while ends
				//helper function that cleans strings by removing certain characters specificed in assigment
				stringCleaner(string);
				if(string[0]=='\0' || (string[0] == '-' && strlen(string)==1)|| (string[0]== '\'' && strlen(string)==1) || string[0]==' '){}
				else{
					tree= addNode(string,tree);
				}//if the string is empty do nothing

			}
			fclose(ftr);
	}
		ftr = fopen(argv[1],"w");
		printOrder(tree,ftr);//print out all the strings into a document
		int total = totalWords(tree);//calculate total words
		int specific = specificWords(tree);//calculate specific words
		fprintf(ftr,"Total Words: %d, Specific words: %d \n", total,specific);//print out total and specific number of words
		free(ftr);
		free(tree);

}

