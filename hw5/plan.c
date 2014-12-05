#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "course.h"
#include "graph.h"
#include "plan.h"
#include "parse.h"
#include <stdbool.h>

#define VALID 0
#define INVALID 1

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
  setMarks(g, 0);//zero all marks
  plan* ptr; //iteration pointer
  int mark = 1;//variable to keep track of the current term.
  bool problems = false; //keep track of errors

  //mark all of the courses with the term that they are scheduled in.
  for (ptr = p; ptr != NULL; ptr = ptr->next){
    courseList* cl;
    for (cl = ptr->list; cl != NULL; cl = cl->next){
      cl->course->mark = mark;
    }
    mark++;
  }

  mark = 1; //reset mark.
  //loop through
  for (ptr = p; ptr != NULL; ptr = ptr->next){
    problems = false;
    courseList* cl;
    for (cl = ptr->list; cl != NULL; cl = cl->next){
      if (cl->course->mark != mark){ //check for duplicate schedulings
        printf("Term %d: %s is in the schedule more than once.\n", mark, cl->course->name);
        cl->course->mark = mark; //set it so that it is caught in the other terms as well
        problems = true; 
      }
      
      course* temp;
      if (temp = checkCourse(cl, mark)){//check for missing prereqs. If none are found, checkCourse returns NULL, and the if statement is false.
        printf("Term %d: %s scheduled without prerequisite %s.\n", mark,  cl->course->name, temp->name);
        problems = true;
      }
    } 
    if (!problems) //if no problems were found, say so!
      printf("Term %d: no problems found.\n", mark);
    mark++;
  }
}
 //helper function that is used for the first case of course prerequisite checking
course* checkCourse(courseList* c, int m){
  courseList* ptr; //no mark checking here since it would cause issues with self-dependency
  course* temp; //storage of returned value from helpCheckCourse
  for (ptr = c->course->preds; ptr != NULL; ptr = ptr->next){ //iterate through prereqs
    if(temp = helpCheckCourse(ptr, m))
      return temp;
  }
  return NULL;
}

//checks to see if a course has all necessary prereqs scheduled.
course* helpCheckCourse(courseList* c, int m){
  if (c->course->mark >= m || c->course->mark == 0) //if the course is not scheduled in the terms before, then it is missing from the schedule and the schedule is invalid.
    return c->course; //returns course pointer for printing purposes.
  courseList* ptr;
  course* temp;
  for (ptr = c->course->preds; ptr != NULL; ptr = ptr->next){//iterate through list of prereqs
    if(temp = helpCheckCourse(ptr, m))
      return temp;
  }
  return NULL;
}

// frees all memory for in a plan object; nulls out the pointer variable
//
// parameters:
//   - planRef: pointer to the pointer variable for the plan
void freePlan(plan** planRef) {
  plan** ptr = planRef;
  while (*ptr != NULL){
    plan* temp = *ptr; //save copy to delete
    *ptr = (*ptr)->next; //iterate pointer
    free(temp); //delete element
  }
  *planRef = NULL;
}
