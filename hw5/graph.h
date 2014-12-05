#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct GraphTag graph;

// a graph, which is represented by a list of courses (graph vertices)
struct GraphTag {
  courseList* courses;
};

// prototypes
extern graph* newGraph();
extern course* lookupCourseInGraph(graph* graphPtr, char* name);
extern int addCourseToGraph(graph* graphPtr, char* name);
extern int linkCourses(graph* graphPtr, char* source, char* target);
extern course* findCircularity(graph* g);
extern int reportRedundancies(graph* g);
extern void listAllPrerequisites(graph* g, course* course);
extern void freeGraph(graph** graphRef);
extern void setMarks(graph* g, int mark);
#endif
