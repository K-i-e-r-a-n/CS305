////////////////////////////////////////////////////////////////
// course.c - defines a course data type. A course consists of a name, a
//   'mark' (used to aid in traversal) and a list of predecessors
//   (prerequisites)

////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "course.h"

// create (malloc) a new course object, with no predecessors (prequisites)
//
// parameters:
//   name - the name of the course
course* newCourse(char* name) {
  course* rtnVal = malloc(sizeof(course));
  rtnVal->name = name;
  rtnVal->mark = 0;
  rtnVal->preds = NULL;
  return rtnVal;
}

// create (malloc) a new course-list
//
// parameters:
//   c - the course in this course list
//   next - the next element in the list
courseList* newCourseList(course* c, courseList* next) {
  courseList* rtnVal = malloc(sizeof(courseList));
  rtnVal->course = c;
  rtnVal->next = next;
  return rtnVal;
}

// finds a course in a list, returning NULL if not there
//
// parameters:
//   list - the course list
//   c - the course to look for
course* findCourseInList(courseList* list, course* c) {
  courseList* p;
  for (p = list; p != NULL; p = p->next) {
    if (p->course == c) {
      return p->course;
    }
  }
  return NULL;
}

// finds a course in a list, returning NULL if not there
//
// parameters:
//   list - the course list
//   name - the name of the course to look for
course* lookupCourseInList(courseList* list, char* name) {
  courseList* p;
  for (p = list; p != NULL; p = p->next) {
    if (strcmp(name, p->course->name) == 0) {
      return p->course;
    }
  }
  return NULL;
}

// reverses a course list (in place)
//
// parameters:
//   list - the course list
//
// returns: the new head of the list
courseList* reverseCourseList(courseList* cl) {
  courseList* rtnVal = NULL;
  while (cl != NULL) {
    courseList* temp = cl->next;
    cl->next = rtnVal;
    rtnVal = cl;
    cl = temp;
  }
  return rtnVal;
}
