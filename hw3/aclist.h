/* Filename: aclist.h
 * Created by: Tanya L. Crenshaw
 * Modified by: Kieran Losh
 * Date created: 9/30/2014
 * Date modified: 10/21/2014
 */

#ifndef __ACLIST_H__
#define __ACLIST_H__

#define INITIALIZE_FAILURE (-1)
#define INITIALIZE_SUCCESS 0

#define ADD_ENTRY_FAILURE (-1)
#define ADD_ENTRY_SUCCESS 0

/* Define the rights for files.
 */
#define R_OWN 8     // Binary = 0b1000 
#define R_READ 4    // Binary = 0b0100
#define R_WRITE 2   // Binary = 0b0010
#define R_EXECUTE 1 // Binary = 0b0001
#define NUMBER_OF_RIGHTS 4 //total size of the bit field that stores the permissions

#define USER_NOT_FOUND (-3)
#define LIST_EMPTY_ERROR (-2)

#define DELETE_RIGHT_FAILURE (-1)
#define DELETE_RIGHT_SUCCESS 0

#define ADD_RIGHT_FAILURE (-1)
#define ADD_RIGHT_SUCCESS 0

#define DELETE_ENTRY_FAILURE (-1)
#define DELETE_ENTRY_SUCCESS 0

#define FREE_ACL_SUCCESS 0

/* Define the maximum length username and filename.
 */
#define MAX_LENGTH 128

/* Define structures.
 */

/* An Access Control Entry consists of a user's name, the rights that
 * a user may invoke on a file, and a pointer to the next Access
 * Control Entry in the linked list of entries.
 */
typedef struct AccessControlEntryTag {
  char user[MAX_LENGTH];
  unsigned int rights : 4;
  struct AccessControlEntryTag * next;  
} AccessControlEntry;

/* An Access Control List consists of a filename and a pointer to the
 * linked list of Access Control Entries that describe the users who
 * have access to that file and the rights they may invoke on that
 * file.
 */
typedef struct AccessControlListTag{
  char filename[MAX_LENGTH];
  AccessControlEntry * aces;
} AccessControlList;


int initializeACL(char * filename, AccessControlList ** aclPtr);
int addEntry(char * newUser, int rights, AccessControlList * acl);
void printACL(AccessControlList * acl);


int deleteRight(int right, char * username, AccessControlList * acl);
int addRight(int right, char * username, AccessControlList * acl);
int deleteEntry(char * username, AccessControlList * acl);
int freeACL(AccessControlList * acl);

/* NOTE: Students may add more functions than these, especially any
 * functions that improve the modularity of the program.
 */

#endif
