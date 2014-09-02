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

int main(int argc, char** argv)
{
	if (argc < MIN_ARGUMENTS) // if there are less arguments than expected, print error and correct usage, then exit with failure status
	{
		printf("Error: Too few parameters.\n");
		printf("usage: ./hw1 arg1 [arg2 ... arg4].\n");
		return EXIT_FAILURE;
	}
	else if (argc > MAX_ARGUMENTS) //if there are too many arguments, print error and usage, then exit with failure status
	{
		printf("Error: Too many arguments.\n");
		printf("usage: ./hw1 arg1 [arg2 ... arg4].\n");
		return EXIT_FAILURE;
	}
	else
	{
		printf("%d parameters.\n", argc);
		int i = 0;
		for (i = 1; i < argc; i++) // starting at the 2nd argument, loop through the last argument
		{
			printf("%s kg = %7f TP.\n", argv[i], atoi(argv[i]) * KG_TO_PRIUS); // print kg and TP equivalent
		}
	}
	return EXIT_SUCCESS;
}

