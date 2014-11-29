#ifndef __LIST_H__
#define __LIST_H__

/*
 * list.h
 *
 * Description: 
 *
 * 1. Define the fields in a node of a linked list
 * using the type struct listNodeTag, or listNode.
 *
 * 2. Define the function prototypes for the linked
 * list implementation found in list.c.
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 10/16/2014
 *
 * CS305 students do not need to edit this file.
 *
 */

#include "company.h"

#define INSERT_ERROR (-1)
#define INSERT_SUCCESS 0

/* Define a companyEntry in a linked list of
 * company entries.
 */
typedef struct listNodeTag{
  companyEntry * entryPtr;
  struct listNodeTag * next;
} listNode;

// Function prototypes for functions already implemented.
int count(listNode * listPtr);
int listInsert(companyEntry * newEntry, listNode ** listPtr);
void printList(listNode * listPtr, int mode);
void freeList(listNode ** listPtr);


#endif

