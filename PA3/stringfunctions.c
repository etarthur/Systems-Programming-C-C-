/*
 * stringfunctions.c
 *
 *  Created on: Sep 18, 2017
 *      Author: etarthur
 */

/**
 * stringfunctions contains functions that work with strings.
 */

#include <stdio.h>
#include "stringfunctions.h"
#include "tree.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/** compareString compares two string and returns the one which is alphabetically later.
 * comapreString works by comparing individual characters of the input strings, and using their integer values
 * to determine alphabetical order. This function works recursively, and if one string is longer than the other, and they
 * contain all the same characters it will return the on which is longer. This functions is used to determine where
 * strings belong in the binary tree.
 * @param i: the index being compared, input 0 for this in almost all cases
 * @param a: pointer to a string being compared
 * @param b: pointer to the second string being compared
 * @param alen: the length of string a
 * @param blen: the length of string b
 * @return int:returns 1 if the strings are the same, 0 if the first input is smaller, and 2 otherwise
 */
int compareString(int i,char *a, char *b,int alen, int blen){
	if(alen==blen && i==blen && a[i]==b[i]){//if the strings are the same return 1
		return 1;
	}
	else if(i==alen){//if the first string is smaller than the second and all elements are the same
		return 0;
	}
	else if (i==blen){//if the second string is smaller than the first and all elements are the same
		return 2;
	}
	else if(a[i]>b[i]){//if first string is alphaetically larger than the second one
		return 2;
	}
	else if(b[i]>a[i]){//if the second string is aplhabetically larger than the first one
		return 0;
	}
	else{//if the current elements inspected are the same
		i++;//increment i
		return compareString(i, a, b,alen,blen);//recursively call until end is reached
	}

}

/** printString consumes a string and prints it out
 * printString consumes a pointer to a string and prints it out, not a complex function,
 * but one used a lot, made to clean up repetition
 * @param a: a pointer to a string being printed
 */
void printString(char *a){
	printf("%s",a);//print out the string
}


/**stringCleaner consumes a string and cleans it of any punctuation or non alphabetical chars
 * stringCleaner loops through and checks all the characters to make sure they are either char or ' or -
 * and if not removes them it also places a terminating character at the end of the string.
 * @param s: the string to be cleaned
 */
void stringCleaner(char* s){
	char *p = s;
	int j =0;
	for(int i =0; i < strlen(s); i++){
		if((isalpha(p[i])) ||  p[i]=='\'' || p[i]=='-'){
			s[j++] = p[i];
		}
	}
	s[j] = '\0';
	 	int z = 0;
	  	while(s[z]!='\0'){
	  		s[z] = tolower(s[z]);
	  		z++;
	  	}
}



