#include "convert.h"


/* convertString:
If the string passed in the arguments



*/
int convertString(char* s)
{
	if (strlen(s)%2 == 0)
		return 0;
	char* tempStr = s;
	for ( ; *tempStr; tempStr++)
		*tempStr = toupper(*tempStr);
	return 1;
}