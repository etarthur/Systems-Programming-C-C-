/*
 * tree.c
 *
 *  Created on: Sep 17, 2017
 *      Author: etarthur
 */

/**
 * Tree class has all the functions that work with binary trees
 */

#include <stdio.h>
#include "stringfunctions.h"
#include <string.h>
#include "tree.h"
#include <stdlib.h>
#include <ctype.h>


/**addNode takes a string and a binary tree and returns a pointer to the new tree with the added element
 * addNode works by using compareString to find the correct spot for the node within the tree and places it there
 * recursively. If string is already in tree, its times field is incremented
 * @param a: the string to be added to the tree, or if already in increment the number of times
 * @param tree: the tree to be added to
 * @return BinaryTree* returns a pointer to the new tree with added node
 */
BinaryTree* addNode(char *a, BinaryTree * tree){
	if(tree == NULL){
		tree = malloc(sizeof(BinaryTree));//Initialize space for the node
		tree->left = NULL;//Initialize node
		tree->right = NULL;
		tree->times = 1;
		tree->string = malloc(sizeof(char)* strlen(a));//initialize space for the string
		tree->string = strdup(a);//add string by copying it
		tree->length = strlen(tree->string);
		return tree;
	}
	else if(compareString(0,a, tree->string, strlen(a),tree->length)==1){//if the input string is the same as the current node string
		tree->times++;//increment times
	}
	else if(compareString(0, a, tree->string, strlen(a),tree->length)==2){//if the input string is larger than the current node
		tree->right = addNode(a,tree->right);//recursively move to the right
	}
	else if(compareString(0, a, tree->string, strlen(a),tree->length)==0){//if the input string is less than the current node
		tree->left = addNode(a,tree->left);//recursively move to the left
	}
	return tree;
}



/**totalWords takes a tree and returns the number of words(including repeats)
 * totalWords works similar to printOrder it traverses the tree in order and adds all the words recursively
 * @param tree: the tree that all the strings are stored in
 * @return int: the total number of words in the tree
 */

int totalWords(BinaryTree *tree){
	if(tree==NULL){//if tree is empty return 0
		return 0;
	}
	else{//otherwise the tree has things
				if(tree->left==NULL && tree->right == NULL){//if last element in subtree, return times
					return tree->times;
				}
				else{//otherwise return current node times and its left and right subtree nodes recurisvely
					return (tree->times + totalWords(tree->left) + totalWords(tree->right));
				}
}
}

/**specificWords takes a tree and returns the number of unique words within
 * Works identical to total words but instead it only adds one not the amount of times a string appears. Works
 * by recursively going down the tree and adding 1 for every node.
 * @param tree: the tree that has all the words in it to be counted
 * @return int: the amount of unique words in the tree
 */
int specificWords(BinaryTree* tree){
	if(tree==NULL){//if tree is empty return nothing
		return 0;
	}
	else{//otherwise the tree has something
		if(tree->left==NULL && tree->right == NULL){//return 1 for bottom nodes
			return 1;
		}
		else{//otherwise return 1 + recusively call all left subtree and right subtree
			return (1 + specificWords(tree->left) + specificWords(tree->right));
		}
	}
}







