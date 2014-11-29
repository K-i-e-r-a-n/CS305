#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

// macro to convert number to a string literal
#define stringify(x) helpStringify(x)
#define helpStringify(x) #x

// size of buffer for string reading
#define BUFFER_SIZE 2000

// prototypes
static char* createString(char* start, char* end);

// reads a line, creating a malloc'd string that contains the contents
// of the line that is read
char* readLine(FILE* f) {
  // return NULL if EOF
  if (feof(f)) {
    return NULL;
  }
  // read the string into the buffer
  char buffer[BUFFER_SIZE+1];
  int count = 0;
  fscanf(f, "%" stringify(BUFFER_SIZE) "[^\n]%n", buffer, &count);

  // malloc/initialize the string
  char* rtnVal = malloc(count+1);
  strncpy(rtnVal, buffer, count);
  rtnVal[count] = '\0';

  // skip the newline
  fscanf(f, "\n");

  // return the string value
  return rtnVal;
}

// creates/mallocs a string containing the characters from 'start' to (but
// not including) 'end'
static char* createString(char* start, char* end) {
  int len = end-start;
  char* rtnVal = malloc(len+1);
  strncpy(rtnVal, start, len);
  rtnVal[len] = '\0';
  return rtnVal;
}

// parses a token from a string; returns NULL if no token is available
//
// parameters:
//  str - starting location for scanning the token
//  putNext - place to store the starting location for the next token to
//    to be reead
char* parseToken(char* str, char** putNext) {
  // place to start
  char* tokStart = NULL;

  // loop through the string as long as we don't find a null
  // character or space
  for (;;) {
    if (*str == '\0') {
      // null character
      if (tokStart == NULL) {
	// if have seen nothing, return NULL: no token
	*putNext = NULL;
	return NULL;
      }
      else {
	// have seen something: return a token
	*putNext = str;
	return createString(tokStart, str);
      }
    }
    else if (isspace(*str)) {
      // have a space
      if (tokStart == NULL) {
	// have not seen token, just move beyond current space
	str++;
      }
      else {
	// have seed token; now we know where to end it: return it
	*putNext = str;
	return createString(tokStart, str);
      }
    }
    else {
      // non-blank, non-space
      if (tokStart == NULL) {
	// if have not started token, mark the beginning
	tokStart = str;
      }
      // move to next character
      str++;
    }
  }
}
