#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "course.h"
#include "graph.h"

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
  printf("'reportRedundancies' not implemented\n");
  return 0;
}

// finds a course in a graph that has a circularity, NULL if none
course* findCircularity(graph* g) {
  printf("'findCircularity' not implemented\n");
  return NULL;
}


// frees all memory for in a graph object; nulls out the pointer variable
//
// parameters:
//   - graphRef: pointer to the pointer variable for the graph
void freeGraph(graph** graphRef) {
}
