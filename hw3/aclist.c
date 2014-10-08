/* Filename: aclist.c
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 9/30/2014
 *
 * Description: This file contains a partial implementation of an
 *               access control list data structure.  The functions
 *               implemented are:
 * 
 *               1. initializeACL(): create the access control list
 *                  node that contains the file name and the pointer
 *                  to the linked list of entries.
 *
 *               2. addEntry(): insert a new entry into an access
 *               control list.
 *
 *               3. printList(): print the contents of an access
 *               control list.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aclist.h"

/* Function:    initializeACL()
 *
 * Parameters:  1. filename: The name of the file for this access
 *              control list.  
 *
 *              2. aclPtr: The address of a NULL pointer to an access
 *              control list.  Description: Allocate memory for an
 *              access control list.  Initialize the access control
 *              list with the filename.
 */
int initializeACL(char * filename, AccessControlList ** aclPtr)
{

  /* Check if aclPtr is NULL.  If so, then this function cannot
   * proceed. 
   */
  if (aclPtr == NULL)
    {
      return INITIALIZE_FAILURE;
    }
  
  /* Check if the access control list pointer is NULL.  If it's not
   * NULL, this access control list may have already been initialized.
   */
  if (*aclPtr != NULL)
    {
      return INITIALIZE_FAILURE;
    }

  /* Allocate enough memory to hold an access control list.  
   */
  (*aclPtr) = malloc(sizeof(AccessControlList));

  /* Copy the filename into the new access control list.
   */
  strncpy((*aclPtr) -> filename, filename, MAX_LENGTH);  
  
  /* Set the pointer to the list of access control entries to NULL
   * as there are no entries at this time.
   */
  (*aclPtr) -> aces = NULL;

  return INITIALIZE_SUCCESS;
}
 
/* Function:    addEntry()
 * Parameters:  1. newUser, the new user to be inserted into the access control list.
 *              2. rights, the rights applied to the new user.
 *              3. acl, a pointer to the list.
 * Description: This function inserts a user and set of rights into an 
 *              access control list.  
 */
int addEntry(char * newUser, int rights, AccessControlList * acl)
{

  /* Create a temporary pointer which initially points to the same location
   * as the start of the list of entries.
   */
  AccessControlEntry * currentNode;

  /* Create a pointer which will point to the new element to be
   * added to the list of entries.
   */
  AccessControlEntry * newNode;


  /* Check if the access control list pointer is empty.  If so,
   * then this list is not well-formed.  One cannot add a new user
   * to an empty access control list.
   */
  if (acl == NULL)
    {
      return ADD_ENTRY_FAILURE;
    }

  /* Allocate enough memory to hold an access control entry.
   */
  newNode = malloc(sizeof(AccessControlEntry));

  /* Initialize the new node with the username.
   */
  strncpy(newNode -> user, newUser, MAX_LENGTH);
	
  /* No null character is added by strncpy, so add one deliberately
   */
  newNode -> user[MAX_LENGTH -1] = '\0';
  
  /* Initialize the new node with the user's rights. 
   */
  newNode -> rights = rights;


  /* Set the next pointer to NULL 
   */
  newNode -> next = NULL;

  /* Check if the list has 0 users.  If so, simply point at the
   * new user and exit the function.
   */
  if (acl -> aces == NULL)
    {
#ifdef DEBUG_MODE_2
  printf("Filename: %s, Line no: %d \n", __FILE__, __LINE__);
#endif 
      acl -> aces = newNode;
      return ADD_ENTRY_SUCCESS;
    }

  /* Otherwise, there is at least one entry in the linked list of
   * access control entries.
   */
  currentNode = acl -> aces;


  /* Insert the new entry at the front of the list.
   */
  newNode -> next = acl -> aces;
  acl-> aces = newNode;

#ifdef DEBUG_MODE_2
  printf("Filename: %s, Line no: %d \n", __FILE__, __LINE__);
#endif 

  return 0;
}

/* Function:    printACL()
 * Parameters:  head, a pointer to a list node
 * Description: This function prints the contents of a list of
 *              AccessControlEntries (ACE) in an AccessControlList:
 *
 *              printList: ( filename:  ACE1, ACE2, ..., ACEN)
 *
 *              If the AccessControlList is empty, it prints:
 * 
 *              printList: ( empty access control list)
 */
void printACL(AccessControlList * acl)
{

  /* Create a temporary pointer will point to the current node
   * being printed in the access control list.
   */
  AccessControlEntry * currentNode;

  /* Print an initial "(" 
   */
  printf("printList: (");

  /* Check if the access control list is empty.
   */
  if (acl == NULL)
    {
      printf(" empty access control list )\n");
      return;
    }

  /* Print the filename.
   */
  printf("File: %s. ", acl -> filename);

  /* Check if there are any users who have rights to this file 
   */
  if (acl-> aces != NULL)
    {
      /* Point to the beginning of the list and print the 
       * first element in the list.
       */
      currentNode = acl -> aces;

      /* Traverse the list to the last element of the list.  As long
       * as the next pointer of the node is not NULL, then there is
       * still another element in the list.
       */     
      while(currentNode != NULL)
	{

	  //************************************************************
	  // CS305 Students must replace the following line of code so
	  // that this function actually prints the rights oxwr.
	  printf(", %s (rights)", currentNode->user);


	  // Point to the next entry
	  currentNode = currentNode->next;
	}
    }

  else
    {
      printf("  No entries.");
    }
      
  /* Print the final parenthesis 
   */
  printf(") \n");

  return;
}

/* CS305 students must implement the following functions.  Students are
 * responsible for adding comment headers to each function.  Examples
 * of function headers are provided in the functions above.
 */

int deleteRight(int right, char * username, AccessControlList * acl)
{
  return 0;

}

int addRight(int right, char * username, AccessControlList * acl)
{
  return 0;
}

int deleteEntry(char * username, AccessControlList * acl)
{
  return 0;
}

int freeACL(AccessControlList * acl)
{
  return 0;
}
