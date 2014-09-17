/* File: convert.h
*
* Header file for convert.c, which has the implementation of convertString.
*	
* Author: Kieran Losh
* Date Completed: 9/16/2014
*/
#ifndef CONVERT_H
#define CONVERT_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* convertString:
If the string passed in the arguments has a even number of characters, it is left unchanged and the function exits with value 0.
If the string passed has an odd number of characters, it 
Arguments: char* s - a string of characters to be evaluated and capitalized if it the number of characters is odd.

Returns:
	1 if s had an odd number of characters and the string was converted to upper case.
	0 if s had an even number of characters and was not modified.
*/
int convertString (char* s);

#endif