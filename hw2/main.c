/* File: main.c
*
* Takes an arbitrary number of string arguments and does two things with them:
*-If the length of an individual string is odd, it converts all of the alphabetical characters to their uppercase equivalents,
*-Prints them out in sets of two.
*	
* Author: Kieran Losh
* Date Completed: 9/16/2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"


/* main():
Takes an arbitrary number of string arguments and does two things with them:
-If the length of an individual string is odd, it converts all of the alphabetical characters to their uppercase equivalents,
-Prints them out in sets of two.

Arguments: 
int argc: number of arguments from the command line
char*  argv[]: array of strings that are the command line argumetns, including the name of the executable

Returns:
EXIT_FAILURE if no additional arguments are entered
EXIT_SUCCESS if the program ran successfully.
*/
int main (int argc, char * argv[])
{
	if (argc == 1) //if the program is called with no additional arguments, print an error message with usage guidelines and return with error value.
	{
		printf("Incorrect number of parameters.\n");
		printf("Usage: %s [arg1 ... argn].\n", argv[0]);
		return EXIT_FAILURE;
	}
	else 
	{
		int i; //index for loops
		for (i = 1; i < argc; i++)
		{
			convertString(argv[i]); //see documentation for convertString for information
		}
		for (i = 1; i < argc; i++) //printing loop
		{
			printf("%s ", argv[i]); //prints string from the argument list
			if (i%2 == 0) //if the index is even, print a newline character after printing the string
				printf("\n");
		}
		if (argc%2 == 0)
			printf("\n"); //if the number of arguments (excluding the executable) is odd because there would not be a newline otherwise.
	}
	return EXIT_SUCCESS; //return success value!
}

