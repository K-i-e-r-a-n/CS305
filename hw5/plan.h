#ifndef __PLAN_H__
#define __PLAN_H__

#include "course.h"
#include "graph.h"

typedef struct PlanTag plan;

// a course plan
struct PlanTag {
  courseList* list; // courses in the first term
  plan* next; // courses in the rest of the terms
};

// prototypes
extern void analyzePlan(plan* p, graph* g);
extern course* checkCourse(courseList* c, int m);
extern course* helpCheckCourse(courseList* c, int m);
extern plan* newPlan(courseList* list, plan* next);
extern plan* readPlan(FILE* f, graph* graphPtr);
extern void freePlan(plan** planRef);
#endif
