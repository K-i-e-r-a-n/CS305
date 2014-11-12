#ifndef __TREE_H__
#define __TREE_H__

/*
 * tree.h
 *
 * Description: 
 *
 * 1. Define the fields in a node of a binary search tree.
 *
 * 2. Define the function prototypes for the tree implementation found
 in tree.c
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 10/16/2014
 *
 * CS305 students do not need to edit this file, but they may add to
 * it if they wish.
 *
 */

#include "company.h"
#include "list.h"

/* Define a companyEntry in a linked list of
 * company entries.
 */
typedef struct treeNodeTag{
  companyEntry * entryPtr;
  struct treeNodeTag * left;
  struct treeNodeTag * right;
} treeNode;

// Function prototypes for functions to be implemented by CS305 Students.
int treeInsert(listNode * list, treeNode ** rootPtr);
void printTree(treeNode * root);
void freeTree(treeNode ** rootPtr);


#endif

