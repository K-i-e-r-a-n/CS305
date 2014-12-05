#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "course.h"
#include "graph.h"

#define UNSEEN 0
#define IN_PROGRESS 1
#define FINISHED 2

#define CYCLE_FREE 0
#define CYCLE 1

#define REDUNDANT 1

// creates a new graph object with no vertices and no edges
graph* newGraph() {
  graph* rtnVal = malloc(sizeof(graph));
  rtnVal->courses = NULL;
  return rtnVal;
}

// looks up a course in a graph by name
course* lookupCourseInGraph(graph* graphPtr, char* name) {
  return lookupCourseInList(graphPtr->courses, name);
}

// adds a course to a graph, given the name
//
// returns 0 if course by that name was already there
int addCourseToGraph(graph* graphPtr, char* name) {
  if (lookupCourseInGraph(graphPtr, name) == NULL) {
    graphPtr->courses = newCourseList(newCourse(name), graphPtr->courses);
    return 1;
  }
  else {
    printf("Multiple definitions of course %s\n", name);
    return 0;
  }
}

// adds an edge to a graph, given the source and target course names
int linkCourses(graph* graphPtr, char* source, char* target) {
  course* sourceCourse = lookupCourseInGraph(graphPtr, source);
  course* targetCourse = lookupCourseInGraph(graphPtr, target);
  if (sourceCourse == NULL) {
    printf("Attempt to set prerequisite for non-existent course: %s\n",
	   source);
    return 0;
  }
  else if (targetCourse == NULL) {
    printf("Attempt to set non-existent course as prerequisite: %s\n",
	   target);
    return 0;
  }
  else if (findCourseInList(sourceCourse->preds, targetCourse) != NULL) {
    printf("Course %s doubly-listed as prerequisite for %s\n",
	   target, source);
    return 0;
  }
  sourceCourse->preds = newCourseList(targetCourse, sourceCourse->preds);
  return 1;
}



// report number of redundant edges in a graph
int reportRedundancies(graph* g) {
  courseList* ptr;
  for (ptr = g->courses; ptr != NULL; ptr = ptr->next){
    setMarks(g, 0); //set all marks to zero 
    if (helpReportRedundancies(ptr) == REDUNDANT){
      printf("%s is redundant.\n", ptr->course->name);
     return REDUNDANT;
    }
  }
  return EXIT_SUCCESS;
}

//helper recursive function for finding redundant prereqs.
int helpReportRedundancies(courseList* cl){
  if (cl == NULL)
    return 0;
  if (cl->course->mark == 1){
    printf("Prequesite %s of ", cl->course->name);
    return REDUNDANT;
  }
  cl->course->mark = 1;
  courseList* ptr;
  for (ptr = cl->course->preds; ptr != NULL; ptr = ptr->next){
    if (helpReportRedundancies(ptr) == REDUNDANT){
      return REDUNDANT;
    }
  }
  return 0;
}

// finds a course in a graph that has a circularity, NULL if none
course* findCircularity(graph* g) {
  courseList* ptr;
  //set all marks to 0 (unseen).
  setMarks(g, UNSEEN);

  for (ptr = g->courses; ptr != NULL; ptr = ptr->next){
    //check if each course has cycles.
    if (helpFindCircularity(ptr) == CYCLE)
      return ptr->course;
  }
  return NULL;
}

//recursive helper function for findCircularity
int helpFindCircularity(courseList* c){
  if (c->course->mark == IN_PROGRESS) //if the mark is in progress, there is a loop
    return CYCLE;
  if (c->course->mark == FINISHED) //if the mark is finished, then the node has already been hit previously
    return CYCLE_FREE;
  c->course->mark = IN_PROGRESS; //mark that we are currently looking at this node
  courseList* ptr;
  for (ptr = c->course->preds; ptr != NULL; ptr = ptr->next){
    if (helpFindCircularity(ptr) == CYCLE) //if a cycle is found, return 
      return CYCLE;
  }
  c->course->mark = FINISHED;// when recursing through the edges is done, the analysis of the node is done. 
  return CYCLE_FREE;
}


// frees all memory for in a graph object; nulls out the pointer variable
//
// parameters:
//   - graphRef: pointer to the pointer variable for the graph
void freeGraph(graph** graphRef) {
    courseList** ptr = &((*graphRef)->courses);
  while (*ptr != NULL){
    courseList* temp = *ptr; //save copy to delete
    *ptr = (*ptr)->next; //iterate pointer
    free(temp->course);//free course
    free(temp); //delete element
  }
  *graphRef = NULL;
}

//sets all the marks of courses in a graph to the specified value.
void setMarks(graph* g, int value){
  courseList* ptr;
  for (ptr = g->courses; ptr != NULL; ptr = ptr->next){
    ptr->course->mark = value;
  }
}
