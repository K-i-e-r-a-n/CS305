/* File: convert.h
*
* Implementation of convertString(). Used in main.c.
*	
* Author: Kieran Losh
* Date Completed: 9/16/2014
*/
#include "convert.h"


/* convertString:
If the string passed in the arguments has a even number of characters, it is left unchanged and the function exits with value 0.
If the string passed has an odd number of characters, it 
Arguments: char* s - a string of characters to be evaluated and capitalized if it the number of characters is odd.

Returns:
	1 if s had an odd number of characters and the string was converted to upper case.
	0 if s had an even number of characters and was not modified.
*/
int convertString(char* s)
{
	if (strlen(s)%2 == 0) //if even, stop and return 0. 
		return 0;
	char* tempStr = s;
	for ( ; *tempStr; tempStr++) //I decided to have some fun with pointer arithmatic here. A new pointer (tempStr) is created to point at the same values as a,
								 //then it iterates in the loop and changes every character to its uppercase equivalent. The for loop stops evaluation when the value
								 //pointed at by tempStr is the null character, which has an integer value of zero.
		*tempStr = toupper(*tempStr);
	return 1; //indicates it converted the string to upper case.
}