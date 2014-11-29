#ifndef __COMPANY_H__
#define __COMPANY_H__

/*
 * company.h
 *
 * Description: 
 *
 * 1. Define the fields in a company entry
 *
 * 2. Define the function prototypes for the companyEntry
 * implementation found in company.c.
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 10/16/2014
 *
 * CS305 students do not need to edit this file.
 *
 */


#define COMPANY_ENTRY_FIELDS 10
#define COMPANY_STRING_FIELDS 7

/* Define a companyEntry
 */
typedef struct companyEntryTag{
  char * companyName;
  char * companyDescription;
  char * website;
  char * streetAddr;
  char * suiteNumber;
  char * city;
  char * state;
  int zip;
  double latitude;
  double longitude;
} companyEntry;

// Function prototypes for functions already implemented.
companyEntry * makeEmptyEntry(void);
void freeCompanyEntry(companyEntry * entryPtr);

#endif
