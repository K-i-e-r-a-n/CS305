/* 
 * tree.c
 * 
 * Author: Kieran Losh
 *
 * Description: Contains a binary search tree implementation for the company
 * entry node.
 */


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "company.h"
#include "list.h"
#include "tree.h"


/* treeInsert()
 * Parameters:
 * list: list element to enter into the tree
 * rootPtr: pointer to the root pointer of the tree
 *
 * Description: inserts a list into the binary tree in
 * the correct sorted order. Returns -1 if the tree or 
 * list pointers are null.
 */
int treeInsert(listNode * list, treeNode ** rootPtr)
{
	if (list == NULL || rootPtr == NULL)
			return -1;
	listNode* ptr; //pointer to a listNode to iterate through the list with
	for (ptr = list; ptr != NULL; ptr = ptr->next)
	{
		treeNode** spot = rootPtr; //pointer to pointer to iterate through the tree with
		while (*spot != NULL) //if we haven't hit the edge of the tree
		{   //if the name of the company being added is lexicographically less than the current node's, move to the left
			if (strcmp(ptr->entryPtr->companyName, (*spot)->entryPtr->companyName) < 0)
				spot = &(*spot)->left;
			else //if it is greater, move right
				spot = &(*spot)->right;
		}
		treeNode* newNode = (treeNode*)(malloc(sizeof(treeNode)));
		newNode->entryPtr = ptr->entryPtr;
		newNode->left = NULL;
		newNode->right = NULL;
		*spot = newNode;
	}
	return 0;
}

/* printTree()
 * Parameters: root: binary search tree to print
 * Description: Prints the binary tree using In Order Traversal
 * to print (recursive implementation).
 */
void printTree(treeNode * root){
	if (root == NULL) //if an empty tree is passed don't do anything
		return;
	if (root->left != NULL) //if a left node is present, print it
		printTree(root->left); 
	//print info of current node.
	  printf("* %s: ", root->entryPtr->companyName); 
	  printf("(%f, %f)\n", root->entryPtr->latitude, root->entryPtr->longitude);
	if (root->right != NULL) //if a right node is present, print it
		printTree(root->right);
}

/* freeTree()
 * Parameters: rootPtr: a pointer to the pointer of the tree 
 * we will delete and free the memory of.
 * 
 */
void freeTree(treeNode ** rootPtr)
{
	if (rootPtr == NULL || *rootPtr == NULL)
		return;
	//if the node has any children, free them first
	if ((*rootPtr)->left != NULL)
		freeTree(&(*rootPtr)->left);
	if ((*rootPtr)->left != NULL)
		freeTree(&(*rootPtr)->right);
	//store pointer to node being deleted.
	treeNode* temp = *rootPtr;
	//null out pointer to node
	*rootPtr = NULL;
	//free company and node
	freeCompanyEntry(temp->entryPtr);
	free(temp);
}


