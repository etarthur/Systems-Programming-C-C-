/*
 * tree.h
 *
 *  Created on: Sep 19, 2017
 *      Author: etarthur
 */

#ifndef TREE_H_
#define TREE_H_

//BinaryTree Struct
typedef struct BinaryTree{
	char* string;//pointer to a string
	int length;//length of the string
	int times;//# of times the string appears
	struct BinaryTree *left;//the left subtree
	struct BinaryTree *right;//the right subtree
}BinaryTree;


BinaryTree* addNode(char *a, BinaryTree *tree);
int totalWords(BinaryTree *tree);
int specificWords(BinaryTree* tree);

#endif /* TREE_H_ */
