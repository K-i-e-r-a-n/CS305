#ifndef __PARSE_H__
#define __PARSE_H__

#include <stdio.h>

// prototypes
extern char* readLine(FILE* f);
extern char* parseToken(char* str, char** putNext);

#endif
