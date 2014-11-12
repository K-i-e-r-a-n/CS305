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

#include "list.h"
#include "sort.h"


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
 *
 * CS305 students must implement this function for HW4.
 */
listNode * mergeSortHelper(listNode * head, listNodeCompareFcn compare)
{
	if (head == NULL || *head == NULL) //base case is list size of zero or one
	{
		return head;
	}

	int len = listLength(head);
	//two list halves. If number of elements is odd, the first half will be longer.
	node* firstHalf = head;
	node* secondHalf;
	//move the pointer forward to the second half of the list
	int lenTemp = len-2;
	while (lenTemp > 0)
	{
		head = head->next;
		lenTemp -= 2;
	}
	secondHalf = head->next;
	head->next = NULL; //split list completely
	//sort halves of the list
	firstHalf = helpListMergesort(firstHalf, listNodeCompareFcn compare);
	secondHalf = helpListMergesort(secondHalf, listNodeCompareFcn compare);

	//merge the sorted lists.
	return merge(firstHalf, secondHalf);
}

/* merge()
 * Parameters: 1. l1: the first linked list to be merged.
 *             2. l2: the second linked list to be merged.
 *
 * Description: Merge two sorted linked lists and return the merged
 *              list.
 *
 * CS305 students must implement this function for HW4.
 *
 */
listNode * merge(listNode * l1, listNode * l2, listNodeCompareFcn compare)
{
	//merged, sorted list to return
	listNode* rtnList;
	//end of list location, where next smallest element will be added.
	node** lastSpot = &rtnList;

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
			if (compare(l1, l2)
		}
	}

}

int listLength(listNode* head)
{
	int rtnVal = 0;
	for (head = head; head != NULL; head = head->next)
	{
		rtnVal++;
	}
	return rtnVal;
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

  return 0;
}

/* distanceCompare()
 *
 * Given two pointers to listNode, return 1 if the first one's
 * latitude + longitude place it closer to the University of Portland
 * Bell Tower than the second one.  Otherwise, return 0.
 *
 * CS305 students must implement this function for HW4.
 *
 * For full points, the comparison should be made based on the
 * distance between two points on a sphere.  For 80% credit
 * a simple comparison can be made between two points on a plane.  
 *
 */
int distanceCompare(listNode * l1, listNode * l2)
{
  
  return 0;

}
