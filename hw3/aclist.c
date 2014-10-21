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
#include <math.h>

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
        //formatting fix to make the output neat - the first case should not have a leading comma
        if (currentNode == acl -> aces)
        {
          printf(" %s (", currentNode->user);
        }
        else 
        {
          //print the name of the current user with leading comma
    	    printf(", %s (", currentNode->user);
        }
        //array of chars that corresponds to rights. Specifically, for a number of a right, the corresponding character is at position log2(right)
        char* rightChars = "xwro";
        //for loop index
        int i;
        //loop through the possible values of permissions, and AND the current permission against the user rights to determine if the user has them
        for (i = NUMBER_OF_RIGHTS - 1; i >= 0; i--) //loop iterates backwards to print in the standard order (orwx)
        {
          //AND user rights with current right (2^i) to determine if the user has that right
          if (currentNode->rights & (int)(pow(2, i)))
            //print the letter of the right
            printf("%c", rightChars[i]);
        } 
        printf(")"); //match the parenthesis around the permissions

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

/* Function:    deleteRight()
 * Parameters:  right, the bit-masked right to remove from the user's permissions
                username, the username of the user whose right we wish to remove
                acl, a pointer to the AccessControlList
 * Description: This function removes the specified right from the specified user's bit-masked rights.
 */
int deleteRight(int right, char * username, AccessControlList * acl)
{
  //check to make sure the list is populated
  if (acl == NULL)
    return LIST_EMPTY_ERROR;

  //check to make sure that the right is a valid right
  if ((right != R_OWN) && (right != R_READ) && (right != R_WRITE) && (right != R_EXECUTE))
    return DELETE_RIGHT_FAILURE;


  //Pointer to the current element. 
  AccessControlEntry* currentNode;
  //initialize the current node to the first element pointed at by the ACL
  
  //standard for loop to iterate through the list
  for (currentNode = acl->aces; currentNode != NULL; currentNode = currentNode->next)
  {
    if (strcmp(currentNode->user, username) == 0)
    {
      currentNode->rights &= ~(right); // ANDing with the inverse of the right removes the right from the bitmask. 
    }
 }

  return DELETE_RIGHT_SUCCESS;

}

/* Function:    addRight()
 * Parameters:  right, the bit-masked right to add to the user's permissions
                username, the username of the user whose rights we wish to add to
                acl, a pointer to the AccessControlList
 * Description: This function adds a specified right to the specified user's bit-masked rights.         
 */
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
