#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "course.h"
#include "graph.h"
#include "plan.h"
#include "parse.h"

// creates/mallocs a plan object
// 
// parameters:
//   - list: first course in plan
//   - next: remaining courses in plan
plan* newPlan(courseList* list, plan* next) {
  plan* rtnVal = malloc(sizeof(plan));
  rtnVal->list = list;
  rtnVal->next = next;
  return rtnVal;
}

// reverses a plan
static plan* reversePlan(plan* pl) {
  plan* rtnVal = NULL;
  while (pl != NULL) {
    plan* temp = pl->next;
    pl->next = rtnVal;
    rtnVal = pl;
    pl = temp;
  }
  return rtnVal;
}

// reads a plan from a file
//
// parameters:
//  - f: pointer to input file
//  - graph: pointer to graph containing the courses

plan* readPlan(FILE* f, graph* graphPtr) {
  plan* rtnVal = NULL; // initially we have an empty plan
  courseList* currentCourseList = NULL; // initially empty course list
  char* line = readLine(f); // read first line
  char* tok;

  for (;;) {
    tok = parseToken(line, &line);
    if (tok == NULL) {
      if (currentCourseList != NULL) {
	rtnVal = newPlan(reverseCourseList(currentCourseList), rtnVal);
	currentCourseList = NULL;
      }
      line = readLine(f);
      if (line == NULL) break;
    }
    else {
        course *myCourse = lookupCourseInGraph(graphPtr, tok);
	if (myCourse == NULL) {
	  printf("Non-existent course in course-list: %s\n", tok);
	}
	else {
	  currentCourseList = newCourseList(myCourse, currentCourseList);
	}
    }
  }
  return reversePlan(rtnVal);
}

// analyzes a plan, telling whether any prerequisites are violated, and
// whether there are any repeated courses
//
void analyzePlan(plan* p, graph* g) {
  printf("'analyzePlan' not implemented\n");
}

// frees all memory for in a plan object; nulls out the pointer variable
//
// parameters:
//   - planRef: pointer to the pointer variable for the plan
void freePlan(plan** planRef) {
}
