#ifndef __SORT_H__
#define __SORT_H__

/* sort.h
 *
 * Description: header file for the sort functionality for CS305 HW
 * #4.
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 10/16/2014
 *
 * CS305 students do not need to edit this file, but they may add to
 * it if they wish.
 */

#include "list.h"

/*
 * So that we may have parameterized sort, define 'listNodeCompareFcn' as a
 * type that is a (pointer to) function that takes two int parameters
 * and returns an int
 */
typedef int listNodeCompareFcn(listNode * a, listNode * b);

// Function prototypes for functions to be implemented by CS305 Students.
void mergeSort(listNode ** listPtr, listNodeCompareFcn compare);
int alphabetCompare(listNode * l1, listNode * l2);
int distanceCompare(listNode * l1, listNode * l2);

#endif
