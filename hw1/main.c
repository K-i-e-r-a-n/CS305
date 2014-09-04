/* File: hw1.c
*
* Converts integer values inputted as command line arguments from kg to the equivalent
* number of Toyota Priuses. 
*	
* Author: Kieran Losh
* Date Completed:
*/
#include <stdio.h>
#include <stdlib.h>
#define KG_TO_PRIUS (1.0/1325.0) //conversion from kg to toyota priuses
#define MIN_ARGUMENTS 2  //minimum number of expected arguments
#define MAX_ARGUMENTS 5 //maximum number of expected arguments


/*	Function main()
*
*	Desc: Runs the main program. 1 to 4 command line arguments are read in as an integer amount of kg, then 
*	the value is converted to an equivalent amount of Toyota Priuses and printed out.
*
*	Parameters:
*	-argc: number of command line arguments, including name of executable
* 	-argv: array of strings that are the command line arguments
*  
*   Returns:
*	EXIT_FAILURE if there are less than 2 command line arguments or more than 5, including executable name.
*	EXIT_SUCCESS otherwise.
*/
int main(int argc, char** argv)
{
	if (argc < MIN_ARGUMENTS) // if there are less arguments than expected, print error and correct usage, then exit with failure status
	{
		printf("Error: Too few parameters.\n");
		printf("usage: ./hw1 arg1 [arg2 ... arg4].\n");
		return EXIT_FAILURE;
	}
	else if (argc > MAX_ARGUMENTS) //if there are too many arguments, print error and correct usage, then exit with failure status
	{
		printf("Error: Too many arguments.\n");
		printf("usage: ./hw1 arg1 [arg2 ... arg4].\n");
		return EXIT_FAILURE;
	}
	else
	{
		printf("%d parameters.\n", argc); //print number of command line arguments entered.
		int i = 0; //index for loop.
		for (i = 1; i < argc; i++) // looping through from the 2nd to the number of arguments.
		{
			printf("%s kg = %7f TP.\n", argv[i], atoi(argv[i]) * KG_TO_PRIUS); // print kg and TP equivalent
		}
	}
	return EXIT_SUCCESS;
}

