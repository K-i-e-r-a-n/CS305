////////////////////////////////////////////////////////////////
// main.c - reads prerequisite and course-plan files, and calls methods
//   to analyze them
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "course.h"
#include "graph.h"
#include "plan.h"
#include "parse.h"

// prototypes
static void addCoursesFromTextFile(FILE* f, graph* graphPtr,
				   char* sourceName, char* restOfLine);
/*
 * main - main entry point for program
 */
int main(int argc, char* argv[]) {

  // ensure that there are exactly two arguments
  if (argc != 3) {
    printf("Need exactly two arguments\n");
    return EXIT_FAILURE;
  }

  // Open the prequisite file, create an empty graph and add the graph
  // vertices and edges read from the file.
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Could not open file %s.\n", argv[1]);
    return EXIT_FAILURE;
  }
  // empty graph
  graph* myGraph = newGraph();
  // read vertices/edges from file
  addCoursesFromTextFile(f, myGraph, NULL, "");
  fclose(f);

  // list the number of courses, and the maximum number of prerequisites
  // for a course
  int numCourses = 0; // number courses seen so far
  int maxPrereqs = 0; // max number prereqs seen so far
  courseList* nl;
  // count nodes; find max neighbors
  for (nl = myGraph->courses; nl != NULL; nl = nl->next) {
    int numPrereqs = 0;
    numCourses++;
    courseList* nl2;
    // count prereqs
    for (nl2 = nl->course->preds; nl2 != NULL; nl2 = nl2->next) {
      numPrereqs++;
    }
    // update max of greater
    if (numPrereqs > maxPrereqs) {
      maxPrereqs = numPrereqs;
    }
  }
  // print the values
  printf("Total number of courses: %d; ", numCourses);
  printf("largest number of prerequisites for a course: %d.\n", maxPrereqs);

  // determine/report if the prerequisite list has any circularities
  course* circ = findCircularity(myGraph);
  if (circ != NULL) {
    printf("Prerequisite circularity detected for %s\n", circ->name);
    return EXIT_FAILURE;
  }
  printf("No prerequisite circularities found.\n");

  // report redundancies
  if (reportRedundancies(myGraph) == 0) {
    printf("No prerequisite redundancies found.\n");
  }

  // read a student's course plan from a file
  FILE* f2 = fopen(argv[2], "r");
  if (f2 == NULL) {
    printf("Could not open file %s.\n", argv[2]);
    return EXIT_FAILURE;
  }
  plan* myPlan = readPlan(f2, myGraph);
  fclose(f2);
  
  // print the proposed schedule
  printf("================proposed schedule================\n");
  plan* pl;
  int termNum = 1;
  for (pl = myPlan; pl != NULL; pl = pl->next) {
    courseList* cl;
    printf("Term %d:", termNum);
    for (cl = pl->list; cl != NULL; cl = cl->next) {
      printf(" %s", cl->course->name);
    }
    printf("\n");
    termNum++;
  }
  
  // analyze the student's schedule
  printf("================schedule analysis================\n");
  analyzePlan(myPlan, myGraph);

  // free memory
  freePlan(&myPlan);
  freeGraph(&myGraph);
}

// reads courses and prerequisites from a text file; adding edges and
// vertices to the graph
//
// Parameters:
//   f - pointer to the input file
//   graphPtr - pointer to the graph to which elements should be added
//   sourceName - name of the current vertex (to which prerequisites
//       are being added)
//   restOfLine - the rest of the line current being processed
static void addCoursesFromTextFile(FILE* f, graph* graphPtr,
				   char* sourceName, char* restOfLine) {
  // if no source name, it's an error to have a non-colon
  // if colon, it becomes the new source name
  // if non colon, add to list for source name on way back out

  // read a token (or hit EOF)
  char* tok;
  for (;;) {
    // read token from current line, if any
    tok = parseToken(restOfLine, &restOfLine);
    if (tok != NULL) break;
    // no token, so read next line
    restOfLine = readLine(f);
    if (restOfLine == NULL) {
      return;
    }
  }

  // if token ends with ':', remove the ':' and create node by that
  // name; otherwise link the node to the current node
  int tokLen = strlen(tok);
  if (tok[tokLen-1] == ':') {
    // have a source
    tok[tokLen-1] = '\0'; // quash the ':'
    addCourseToGraph(graphPtr, tok); // add the course as a vertex
    // process rest of file
    addCoursesFromTextFile(f, graphPtr, tok, restOfLine);
  }
  else if (restOfLine == NULL) {
    // end of file: end recursion
  }
  else {
    // process rest of file
    addCoursesFromTextFile(f, graphPtr, sourceName, restOfLine);
    // link the current course to a prereq
    linkCourses(graphPtr, sourceName, tok);
  }
}
