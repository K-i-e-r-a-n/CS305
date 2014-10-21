/* Filename: main.c
 * Created by: Tanya L. Crenshaw
 * Modified by: Kieran Losh
 * Date created: 9/30/2014
 * Date modified: 10/21/2014
 *
 * Description: 1. Open and read from a file passed via command line.
 *
 *              2. Take the values from the file and create an access
 *              control list.  
 *
 *              3. Print the access control list.
 *
 *              4. Parse a second file passed via command line.
 *              Execute commands from the file to alter the access
 *              control list created in step 2. 
 *
 *              5. Print the resulting access control list.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aclist.h"

/* Constant definitions. 
 */
#define FILE_OPEN_FAILED EXIT_FAILURE
#define PARSE_SUCCESS 0
#define PARSE_FAILURE (-1)

#define REQUIRED_ARGS 3
#define ARGS_ERROR "%s error: incorrect number of parameters.\n"
#define USAGE "usage: %s <aclFile> <commandFile>\n"

/* Function prototypes for this file.
 */
void usage(int argc, char * argv[]);
int parseInputFile(char * filename, AccessControlList ** aclPtr);
int parseCommandFile(char * filename, AccessControlList * acl);


/* Main entrypoint of the program */
int main(int argc, char **argv)
{

  /* Declare a pointer to an Access Control List that will be created
   * from the first input file.  Initially, it is empty, so initialize
   * it to NULL.
   */
  AccessControlList * acl = NULL;

  /* Check that the number of command line parameters is correct
   */
  usage(argc, argv);

  /* Parse the first input file, constructing an access control list
   * for a single file.  If parsing fails, exit the program.
   */
  if (parseInputFile(argv[1], &acl) == PARSE_FAILURE)
    {
      printf("File parsing failed.  Exiting program. \n");
      freeACL(acl);
      return EXIT_FAILURE;
    }

  /* Print the resulting acl */
  printACL(acl);
  printf("\n");

  /* Parse the second input file, altering the access control list
   * that was created by the first input file.  
   */
  if (parseCommandFile(argv[2], acl) == PARSE_FAILURE)
    {
      printf("Command file parsing failed.  Exiting program. \n");
      freeACL(acl);
      return EXIT_FAILURE;
    }

  /* Print the resulting acl */
  printACL(acl);
  printf("\n");  

  /* Cleanup the memory allocated to the acl */
  freeACL(acl);

  printf("Exiting program.\n");
  
  return EXIT_SUCCESS;
   
}


/* Function: usage()
 * Parameters: 1. argc: the number of parameters entered at the command 
 *                      line.
 *             2. argv: an array of pointers, each pointing to each string 
 *                      entered at the command line.
 * 
 * Description: If the program is called with the correct argc, it
 *              does nothing; otherwise it informs the user of the
 *              usage and exits the program.
 */
void usage(int argc, char * argv[])
{
  if (argc != REQUIRED_ARGS)
    {
      printf(ARGS_ERROR, argv[0]);
      printf(USAGE, argv[0]);
      exit(EXIT_FAILURE);
    }
}


/* Function: parseInputFile()
 * Parameters: 1. filename: The name of the file to be parsed.
 *             2. listptr:  The address of the pointer to the access control
 *                          list that will be created as a result of
 *                          parsing the file.
 *
 * Description: This function reads an input file and constructs an
 *              access control list from the contents of the file.  The 
 *              expected input file format is:
 * 
 *     f: <filename>
 *     user1
 *     <integer describing rights for user1>
 *     user2
 *     <integer describing rights for user2>
 *     ...
 *     userN
 *     <integer describing rights for userN>
 *
 *  The set of rights available are own, read, write, and execute and
 *  are expressed in four bits.  For example, if a user owns and may read
 *  the file, his set of rights is expressed by 0b1100 or 12.
 *  
 *  Only one access control list is created as a result of this function call.
 *
 *  Usernames may not begin with a colon or an asterix.
 *            
 */
int parseInputFile(char * filename, AccessControlList ** aclPtr)
{

  /* Create a file pointer for the input file, filename.
   */
  FILE *ifp;

  /* Declare variables to temporarily hold characters and integers
   * read from the filename parameter.
   */
  char a;
  int d;

  /* Create an array of characters to temporarily hold the filename
   * and usernames read from the input file.  MAX_LENGTH is defined by
   * the access control list data structure.
   */
  char word[MAX_LENGTH];

  /* Attempt to open the file for reading using the "r" flag.
   */
  ifp = fopen(filename, "r");

  /* Check that the file open operation was successful.  If it 
   * was not successful, leave the function with an error code.
   */
  if (ifp == NULL)
    {
      return FILE_OPEN_FAILED;
    }

  /* Otherwise, indicate the file was successfully opened.
   */
  printf("%s was successfully opened.\nParsing access control entries from file.\n", filename);

  /* The file opening was successful, so begin parsing the file.
   */
  while(fscanf(ifp, "%c", &a) == 1)
    {
      /* If a colon is read, that indicates that the subsequent word is the filename
       * intended for this access control list. 
       */
      if(a == ':')
	{
	  /* Read the subsequent word, which is the filename */
	  if( fscanf(ifp, "%s", word) != 1)
	    {
	      fclose(ifp);
	      return PARSE_FAILURE;
	    }

	  printf("Creating a new access control list for file: %s.\n", word);
		
	  /* Initialize an ACL with this filename. If initialization failed,
	   * exit this function
	   */
	  if ( initializeACL(word, aclPtr) != INITIALIZE_SUCCESS) 
	    {
	      /* ACL initialization failed. */
	      fclose(ifp);
	      return PARSE_FAILURE;
	    }
	}

	/* If '*' is read, that indicates that the subsequent word is a username. 
	 */
      else if(a == '*')
	  {
	    /* Read the subsequent word, which is the username */
	    if( fscanf(ifp, "%s", word) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;	  
	      }

	    /* Read the subsequent integer, which are the user's rights */
	    if( fscanf(ifp, "%d", &d) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;
	      }

	    /* Add a new entry to the access control list */
	    addEntry(word, d, (*aclPtr));
	  }
	
    }
  
  /* Gracefully close the file now that it is no longer needed.
   */
  fclose(ifp);

  return PARSE_SUCCESS;
    
}

/* Function: parseCommandFile()
 * Parameters: 1. filename: The name of the file to be parsed.
 *             2. listptr:  The address of the pointer to the access control
 *                          list that will be altered as a result of
 *                          parsing the file.
 *
 * Description: This function reads an input file and alters an access
 *              control list based on the contents of the file.  The
 *              possible commands are:
 *
 *    dr: Delete Right.
 *    ar: Add Right.
 *    de: Delete Entry.
 *
 *  For example, if the file reads,
 *
 *  dr
 *  vegdahl
 *  4
 * 
 *  Then the access control list should be altered so that the user
 *  'vegdahl' no longer has the right to 'write' to the file.  See
 *  aclist.h for a mapping from integers to rights.
 *
 */
int parseCommandFile(char * filename, AccessControlList * acl)
{

  /* Create a file pointer for the input file, filename.
   */
  FILE *ifp;

  /* Declare an integer to temporarily hold characters and integers
   * read from the filename parameter.
   */
  int a;

  /* Create an array of characters to temporarily hold the filename
   * and usernames read from the input file.  MAX_LENGTH is defined by
   * the access control list data structure.
   */
  char word[MAX_LENGTH];

  /* Attempt to open the file for reading using the "r" flag.
   */
  ifp = fopen(filename, "r");

  /* Check that the file open operation was successful.  If it 
   * was not successful, leave the function with an error code.
   */
  if (ifp == NULL)
    {
      return FILE_OPEN_FAILED;
    }

  /* Otherwise, indicate the file was successfully opened.
   */
  printf("%s was successfully opened.\nParsing commands from file.\n", filename);

  /* The file opening was successful, so begin parsing the file.
   */
  while(fscanf(ifp, "%s", word) == 1)
    {
      if(strncmp(word, "dr", MAX_LENGTH) == 0)
	{

	    /* Read the subsequent word, which is the username */
	    if( fscanf(ifp, "%s", word) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;	  
	      } 

	    /* Read the subsequent integer, which are the user's rights */
	    if( fscanf(ifp, "%d", &a) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;
	      }

	    printf("Delete right = %d from user %s \n", a, word);
	    
	    /* Invoke the deleteRight() operation according to the
	     * parsed command 
	     */
	    deleteRight(a, word, acl);
	}

      else if(strncmp(word, "ar", MAX_LENGTH) == 0)
	{
	    /* Read the subsequent word, which is the username */
	    if( fscanf(ifp, "%s", word) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;	  
	      }

	    /* Read the subsequent integer, which are the user's rights */
	    if( fscanf(ifp, "%d", &a) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;
	      }

	    printf("Add right = %d to user %s \n", a, word);
	    
	    /* Invoke the addRight() operation according to the
	     * parsed command 
	     */
	    addRight(a, word, acl);
	}

      else if(strncmp(word, "de", MAX_LENGTH) == 0 )
	{
	    /* Read the subsequent word, which is the username */
	    if( fscanf(ifp, "%s", word) != 1)
	      {
		fclose(ifp);
		return PARSE_FAILURE;	  
	      }
	    
	    printf("Delete user %s \n", word);

	    /* Invoke the addRight() operation according to the
	     * parsed command 
	     */
	    deleteEntry(word, acl);
	}
    }

  /* Gracefully close the file now that it is no longer needed.
   */  
  fclose(ifp);

  return PARSE_SUCCESS;
}
