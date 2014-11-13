/* 
 * sort.c
 * 
 * Author: Kieran Losh
 * 
 * Description: Contains sorting functions that operate on the linked
 * list implementation for the company entry node found in
 * list.[c,h].
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define USE_MATH_DEFINES //so that M_PI is defined.

#include "list.h"
#include "sort.h"

//latitude of the UP Belltower as given by Google Maps
#define UP_BELL_TOWER_LAT 45.5712237
#define UP_BELL_TOWER_LONG -122.7260584

// Function prototypes for helper functions used only within this
// file.  They are declared as static since they should be global
// function declarations available only to this file.
static listNode * mergeSortHelper(listNode * head, listNodeCompareFcn compare);
static listNode * merge(listNode * l1, listNode * l2, listNodeCompareFcn compare);


/* mergeSort()
 *
 * CS305 students should *not* alter this function for HW4.  Nope
 * Don't do it.
 */
void mergeSort(listNode ** listPtr, listNodeCompareFcn compare)
{
  // mergeSort() calls mergeSortHelper which performs the actual
  // merge sort algorithm.  This function simply points the head
  // of the list at the result of the sorting.
  *listPtr = mergeSortHelper(*listPtr, compare);
}

// CS305 Students must implement the function stubs below.  To maximize points earned
// on the homework, students should also supply function comment headers as well as
// document the function bodies with useful comments.


/* mergeSortHelper()
 * Helper function that performs the splitting of each list into sublists until the base case is reached.
 */
listNode* mergeSortHelper(listNode * head, listNodeCompareFcn compare)
{
	if (head == NULL || head->next == NULL) //base case is list size of zero or one
	{
		return head;
	}

	int len = count(head);
	//two list halves. If number of elements is odd, the first half will be longer.
	listNode* firstHalf = head;
	listNode* secondHalf;
	//move the pointer forward to the second half of the list
	int lenTemp = len-2;
	while (lenTemp > 0)
	{
		head = head->next;
		lenTemp -= 2;
	}
	secondHalf = head->next;
	head->next = NULL; //split list completely by nulling pointer from the first to the second
	//sort halves of the list
	firstHalf = mergeSortHelper(firstHalf, compare);
	secondHalf = mergeSortHelper(secondHalf, compare);

	//merge the sorted lists.
	return merge(firstHalf, secondHalf, compare);
}

/* merge()
 * Parameters: 1. l1: the first linked list to be merged.
 *             2. l2: the second linked list to be merged.
 *
 * Description: Merge two sorted linked lists and return the merged
 *              list.
 *
 */
listNode * merge(listNode * l1, listNode * l2, listNodeCompareFcn compare)
{
	//merged, sorted list to return
	listNode* rtnList;
	//end of list location, where next smallest element will be added.
	listNode** lastSpot = &rtnList;

	for(;;)
	{
		if (l1 == NULL) // when the first list is empty, append remainder of 2nd list to rtnList
		{
			*lastSpot = l2;
			break;
		}
		else if (l2 == NULL)// when the first list is empty, append remainder of 2nd list to rtnList
		{
			*lastSpot = l1;
			break;
		}
		else //neither list is empty
		{
			if (compare(l1, l2)) //smaller element in first list
			{
				*lastSpot = l1; //move front of list 1 to the back of the new sorted list
				lastSpot = &l1->next; //move lastSpot pointer to pointer of last element
				l1 = l1->next; //remove element from first list by moving the starting pointer to the next element.
			}
			else //smaller element is in the second list 
			{ 
				*lastSpot = l2; //move front element of list 2 to back of new sorted list 
				lastSpot = &l2->next; //move lastSpot pointer to pointer of last element
				l2 = l2->next; //remove element from second list by moving the starting pointer to the next element.
			}
		}
	}
	return rtnList;
}

/* alphabetCompare()
 *
 * Given two pointers to listNode, return 1 if the first one's
 * companyName is lexicographically less than the second one.
 * Otherwise, return 0.
 * 
 * For example, if l1->companyName is 'aaaa' and l2->companyName is
 * 'aaab' then l1->companyName is less than l2->companyName.
 *  
 */
int alphabetCompare(listNode * l1, listNode * l2)
{
	return strcmp(l1->entryPtr->companyName, l2->entryPtr->companyName) < 0; //strcmp returns a negative number if 
}

/* distanceCompare()
 *
 * Given two pointers to listNode, return 1 if the first one's
 * latitude + longitude place it closer to the University of Portland
 * Bell Tower than the second one.  Otherwise, return 0.
 *
 * Uses the haversine formula for distances between two latitude (phi) and
 * longitude (lambda) pairs on the surface of a sphere.
 */
int distanceCompare(listNode * l1, listNode * l2)
{
	float radius = 6371; //radius of the earth in km.
	
	double phi1 = l1->entryPtr->latitude*M_PI/180.0; //Convert latitude of the first company to radians
	double phi2 = UP_BELL_TOWER_LAT*M_PI/180.0; //convert latitude of bell tower to radians
	double deltaPhi = phi2 - phi1;
	double deltaLambda = (UP_BELL_TOWER_LONG - l1->entryPtr->longitude)*M_PI/180.0;

	double a = sin(deltaPhi/2.0) * sin(deltaPhi/2) + cos(phi1) * cos(phi2) * sin(deltaLambda/2.0) * sin(deltaLambda/2.0);

	double c = 2*atan2(sqrt(a), sqrt(1-a));

	double dist1 = radius * c;

	double phi3 = l2->entryPtr->latitude*M_PI/180.0; //Convert latitude of the first company to radians
	double phi4 = UP_BELL_TOWER_LAT*M_PI/180.0; //convert latitude of bell tower to radians
	double deltaPhi1 = phi4 - phi3; 
	double deltaLambda1 = (UP_BELL_TOWER_LONG - l2->entryPtr->longitude)*M_PI/180.0;

	double a1 = sin(deltaPhi1/2.0) * sin(deltaPhi1/2) + cos(phi3) * cos(phi4) * sin(deltaLambda1/2.0) * sin(deltaLambda1/2.0);

	double c1 = 2*atan2(sqrt(a1), sqrt(1-a1));

	double dist2 = radius * c1;
	return dist2 >= dist1; //the example uses equal as closer (return 1) when sorted by distance, so I did as well to match output.
}
