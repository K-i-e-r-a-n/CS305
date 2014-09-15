#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

int main (int argc, char * argv[])
{
	if (argc == 1)
	{
		printf("Incorrect number of parameters.\n");
		printf("Usage: %s [arg1 ... argn].\n", argv[0]);
		return EXIT_FAILURE;
	}
	else
	{
		int i;
		for (i = 1; i < argc; i++)
		{
			convertString(argv[i]);
		}
		for (i = 1; i < argc; i++)
		{
			printf("%s ", argv[i]);
			if (i%2 == 0)
				printf("\n");
		}
	}
	return EXIT_SUCCESS;
}