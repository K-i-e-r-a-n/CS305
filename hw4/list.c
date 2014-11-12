/* 
 * list.c
 * 
 * Description: Contains a linked list implementation for the company
 * entry node.
 *
 * CS305 students do not need to edit this file.
 */


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "usage.h"

/* Function: count()
 *
 * Description: Given a linked list, return the number of nodes
 * in the list.
 */
int count(listNode * listPtr)
{
  if (listPtr != NULL)
    {
      return 1 + count(listPtr->next);
    }

  return 0;

}

/* 
 * Function: listInsert()
 *
 * Description: Given a node initialized with company information,
 * insert it into the linked list.
 *
 */
int listInsert(companyEntry * newEntry, listNode ** listPtr)
{
#ifdef DEBUG  
  printf("\nInserting: %s\n\n", newEntry->companyName);
#endif

  // Writing secure code is mostly a matter of being paranoid about
  // your inputs. If either parameter is NULL, no work can be done.
  if(listPtr == NULL)
    {
      return INSERT_ERROR;
    }

  if(newEntry == NULL)
    {
      return INSERT_ERROR;
    }

  // Insert the new node into the front of the list.
  listNode * newNode = malloc(sizeof(listNode));
  
  newNode->entryPtr = newEntry;
  newNode->next = *listPtr;
  *listPtr = newNode;

  return INSERT_SUCCESS;
}


/*
 * Function: printList()
 *
 * Description: Print a linked list. If mode is VERBOSE, print every
 * field of every node.  Otherwise, print its name, zip, and lat,lon.
 *
 */
void printList(listNode * listPtr, int mode)
{

  if(listPtr != NULL && listPtr->entryPtr != NULL)
    {

      if (mode == VERBOSE_MODE)
	{
	  printf("* %s\n  %s\n  %s\n", listPtr->entryPtr->companyName, listPtr->entryPtr->companyDescription, listPtr->entryPtr->website);
	  printf("  %s, %s\n", listPtr->entryPtr->streetAddr, listPtr->entryPtr->suiteNumber);
	  printf("  %s, %s %d\n", listPtr->entryPtr->city, listPtr->entryPtr->state, listPtr->entryPtr->zip);
	  printf("  (%f, %f)\n", listPtr->entryPtr->latitude, listPtr->entryPtr->longitude); 
	  printList(listPtr->next, mode);
	}

      else
	{
	  printf("* %s: ", listPtr->entryPtr->companyName);
	  printf("(%f, %f)\n", listPtr->entryPtr->latitude, listPtr->entryPtr->longitude); 
	  printList(listPtr->next, mode);
	}
    }

  return;

}

/*
 * Function: freeList()
 *
 * Description: Free memory allocated to a linked list.  This function
 * also frees all memory associated with the allocated company
 * entries in each listNode.
 *
 */
void freeList(listNode ** listPtr)
{
  if(listPtr == NULL)
    return;

  listNode * current = *listPtr;
  listNode * next = NULL;

  while(current != NULL)
    {
      next = current->next;
      freeCompanyEntry(current->entryPtr);
      free(current);	
      current = next;
    }

  // Avoid future dangling pointer dereferencing by initializing the
  // contents of listPtr to NULL.
  *listPtr=NULL;

  return;

}
