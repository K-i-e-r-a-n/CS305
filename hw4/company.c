/*
 * company.c
 *
 * Description: Provide an implementation for creating an emtpy
 * companyEntry.
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 10/16/2014
 *
 * CS305 students do not need to edit this file.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "company.h"

/*
 * Function: makeEmptyEntry()
 *
 * Description: Create an empty company entry, initializing all fields
 * to their appropriate NULL or zero values.
 */
companyEntry * makeEmptyEntry(void) {
  
  companyEntry * newEntry = malloc(sizeof(companyEntry));

  // Affirm that malloc was successful.
  if (!newEntry) return NULL;
  
  // Initialize all the character pointer type fields to NULL.
  newEntry->companyName = NULL;
  newEntry->companyDescription = NULL;
  newEntry->website = NULL;
  newEntry->streetAddr = NULL;
  newEntry->suiteNumber = NULL;
  newEntry->city = NULL;
  newEntry->state = NULL;

  // Initialize the zip to 0. USPS reports that 00000 is
  // not a valid zip code.  
  newEntry->zip = 0;

  // Inititalize the lat/lon to 0,0.  While this is an actual 
  // lat/lon, it's located in the middle of the Gulf of Guinea near
  // the African continent.  Hard to say that there's a tech company
  // located in deep seawater.  Though, maybe the Cobra Commander
  // relocated his underwater fortress there and he's hiring
  // generic white labcoats to run away from explosions in the
  // next movie.  Also: Ice doesn't sink.
  newEntry->latitude = 0;
  newEntry->latitude = 0;

  return newEntry;
}

/*
 * Function: freeCompanyEntry()
 *
 * Description: Free memory allocated to the fields of a company entry.
 *
 */
void freeCompanyEntry(companyEntry * entryPtr)
{
  // Affirm that this function was not handed a NULL pointer.
  if(!entryPtr) return;

  // If any of the pointers are not NULL, then free
  // their contents.
  if(!entryPtr->companyName)
    free(entryPtr->companyName);
  
  if(!entryPtr->companyDescription)
    free(entryPtr->companyDescription);
  
  if(!entryPtr->website)
    free(entryPtr->website);
  
  if(!entryPtr->streetAddr)
    free(entryPtr->streetAddr);
  
  if(!entryPtr->suiteNumber)
    free(entryPtr->suiteNumber);
  
  if(!entryPtr->city)
    free(entryPtr->city);

  if(!entryPtr->state)
    free(entryPtr->state);

  return;

}
