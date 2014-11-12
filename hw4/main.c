/* Filename: main.c
 * Created by: Tanya L. Crenshaw
 * Date created: 10/16/2014
 *
 * CS305 students do not need to edit this file.
 */

// Includes
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "usage.h"
#include "sort.h"
#include "list.h"
#include "tree.h"
#include "company.h"
#include "readLine.h"

// Constants
#define PARSE_SUCCESS -1

// A small MACRO to simplify some of the informative error and success
// statements in the main function.
#define mainlog(x) printf("%s: " x ", %s.\n",argv[0], argv[fileIndex])

// Function prototypes
int usage(int argc, char * argv[]);
int parseFile(FILE * fp, listNode ** list);

int main(int argc, char * argv[])
{
  FILE * fp = NULL;

  // Create an empty linked list of companies and an empty tree of
  // companies.
  listNode * companyListPtr = NULL;
  treeNode * companyTreePtr = NULL;

  int n;

  int fileIndex = 1;
  int mode = usage(argc, argv);

  // If this program was invoked with a flag, then the name of the
  // input file may be found in argv[2];
  if (mode > 0)
    fileIndex = 2;

  // Attempt to open the file.
  if((fp = fopen(argv[fileIndex],"r")) == NULL)
    {
      mainlog("File not found");
      return EXIT_FAILURE;
    }

  // Attempt to parse the file and store the results in the linked
  // list companyListPtr.
  if((n = parseFile(fp, &companyListPtr)) != PARSE_SUCCESS)
    {
      printf("Parse error on line no. %d. \n", n);
      mainlog("Error parsing file");
      fclose(fp);
      return EXIT_FAILURE;
    }
  
  mainlog("Successfully parsed file");
		
  // Print the unsorted linked list that resulted from parsing the
  // file.
  printList(companyListPtr, mode);
  printf("There are %d nodes in the list.\n\n", count(companyListPtr));
 
 
 // If the '-t' flag was supplied to the program, then insert
  // each company entry into a binary search tree and print the tree
  // in order.
  if(mode == TREE_MODE)
    {

      // Insert the linked list of companies into the tree pointed
      // to by companyTreePtr.
      treeInsert(companyListPtr, &companyTreePtr);

      printf("\n****Sorted alphabetically****\n");
      printTree(companyTreePtr);
    }     

  // If the '-m' flag was supplied to the program, then perform merge
  // sort on the linked list and print the list in alphabetical order.
  else if (mode == MERGESORT_MODE)
    {
      mergeSort(&companyListPtr, alphabetCompare);

      printf("\n****Sorted alphabetically****\n");
      printList(companyListPtr, mode);    
    }

  // If the '-d' flag was supplied to the program, then perform merge
  // sort on the linked list and print the list in order of distance
  // from the University of Portland bell tower.
  else if (mode == DISTANCE_MODE)
    {
      mergeSort(&companyListPtr, distanceCompare);

      printf("\n****Sorted by distance****\n");
      printList(companyListPtr, mode);    
    }

  // All done with the linked list.  Free memory back into the wild so
  // that it may frolic in the wilderness.  Hopefully the memory has
  // not been weakened by its servitude.
  //    http://www.youtube.com/watch?v=63YruDd2nJY
  freeList(&companyListPtr);
  freeTree(&companyTreePtr);

  fclose(fp);

  return EXIT_SUCCESS;
}

/* Function: parseFile()
 * Parameters:
 *
 * Description: Given a file pointer and a node pointer
 * this function reads a company entry from the file, allocates a
 * node for it, and inserts it into the linked list pointed to
 * by p.
 *
 */
int parseFile(FILE * fp, listNode ** list)
{
  char c;
  int i = 0;
  int lineCount = 0;
  
  companyEntry * newEntry = NULL;

  // If the input file is well-formed, the first character
  // of each company entry is preceeded by a '*'.  At the 
  // top of each loop iteration, affirm that the * is there.
  // if not, the file is not well-formed, it has not followed
  // the expected format, and we should return with an error code.
  while((c = fgetc(fp)) == '*')
    {      
      // Create a new company entry to be placed in the new
      // node.
      newEntry = makeEmptyEntry();
      
      // Eat the space after the asterix
      fgetc(fp);

#ifdef DEBUG
      printf("Debug print at line no. %d\n", __LINE__);
#endif
      
      // Read a line from the file and store it in a field
      // of the newNode.  
      newEntry->companyName = readLine(fp);
      newEntry->companyDescription = readLine(fp);
      newEntry->website = readLine(fp);
      newEntry->streetAddr = readLine(fp);
      newEntry->suiteNumber = readLine(fp);
      newEntry->city = readLine(fp);
      newEntry->state = readLine(fp);
      newEntry->zip = atoi(readLine(fp));
      newEntry->latitude = atof(readLine(fp));
      newEntry->longitude = atof(readLine(fp));

      char ** p = &(newEntry->companyName);

      // Loop through the character pointer fields of newNode and make
      // sure that no pointer is NULL.  If any pointer is NULL, then 
      // readLine() failed and the function should be exited.

      // Reset i to check the latest entry read from the file.
      i = 0;

      
      while(i < COMPANY_STRING_FIELDS)
	{
	  if(*p == NULL)
	    {
	      // Free the entry, new node, and previously
	      // constructed list before bailing from 
	      // this function.
	      freeCompanyEntry(newEntry);
	      freeList(list);

	      return lineCount + i;
	    }

	  p++;
	  i++;
	}

#ifdef DEBUG
      printf("Debug print at line no. %d\n", __LINE__);
#endif

      lineCount = lineCount + COMPANY_ENTRY_FIELDS;

      // 
      // Use the insert() function to insert it into
      // a linked list.
      listInsert(newEntry, list);

#ifdef DEBUG
      printf("Inserted %s \n", newEntry->companyName);
#endif

      // Eat the blank line between the company entries. 
      // If the line is not blank, the file is not well-formed
      // and we should return with an error code.
      char * eatLine = readLine(fp);
      lineCount++;
      
      // Maybe we are at the end of the file.
      if(eatLine == NULL)
	{
	  c = EOF;
	  break;
	}

      // Maybe we didn't just eat an empty line.
      if(!strncmp(" ", eatLine, 1))
	{
	  // Break out of this loop because a parse error
	  // was found.  The blank line that was
	  // expected is not there.
	  free(eatLine);
	  break;
	}

      // We don't need to keep the line that was read
      // to pass over the blank line between entries.
      free(eatLine);

    }

#ifdef DEBUG
      printf("Last value of c: %c\n", c);
      printf("Debug print at line no. %d\n", __LINE__);
#endif

  // At this moment, the loop is done executing.  Is it because
  // the END OF FILE was reached, or because the file is badly-formed?
  // If the file was successfully parsed, return success code,
  // otherwise return the line number at which the file was badly
  // formed.

  if(c == EOF)
    {
      return PARSE_SUCCESS;
    }
  else
    {
      freeList(list);

      return lineCount;
    }

  return PARSE_SUCCESS;

}



/* Function: usage()
 * Parameters: 1. argc: the number of parameters entered at the command 
 *                      line.
 *             2. argv: an array of pointers, each pointing to each string 
 *                      entered at the command line.
 * 
 * Description: If the program is called with the correct argc, it
 *              returns a code for the flag used at program invocation; 
 *              otherwise it informs the user of the usage and exits 
 *              the program.
 */
int usage(int argc, char * argv[])
{

  // Affirm that the program is invoked with MIN_ARGS to MAX_ARGS
  // arguments.  If not, exit the program.
  if (argc < MIN_ARGS || argc > MAX_ARGS )
    {
      printf(USAGE, argv[0]);
      exit(EXIT_FAILURE);
    }

  if(argc == MIN_ARGS)
    return NO_MODE;


  // Check for flags and return the appropriate mode 
  // value.
  else if(argc == MAX_ARGS)
    {
      if(!strncmp(argv[1], VERBOSE_FLAG, FLAG_SIZE))
	return VERBOSE_MODE;

      if(!strncmp(argv[1], T_FLAG, FLAG_SIZE))
	return TREE_MODE;

      if(!strncmp(argv[1], MS_FLAG, FLAG_SIZE))
	return MERGESORT_MODE;

      if(!strncmp(argv[1], D_FLAG, FLAG_SIZE))
	return DISTANCE_MODE;

      else
	{
	  printf(USAGE, argv[0]);
	  exit(EXIT_FAILURE);
	}

    }

  return NO_MODE;
}

