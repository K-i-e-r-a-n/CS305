#ifndef __COURSE_H__
#define  __COURSE_H__

typedef struct CourseTag course;
typedef struct CourseListTag courseList;

// a course (graph vertex), which includes a name, a mark (used for traversal
// and a list of predecessors (graph edges)
struct CourseTag {
  char* name;
  int mark;
  courseList* preds;
};

// a linked list of courses
struct CourseListTag {
  course* course;
  courseList* next;
};

// prototypes
extern course* newCourse(char* name);
extern courseList* newCourseList(course* c, courseList* next);
extern course* lookupCourseInList(courseList* list, char* name);
extern courseList* reverseCourseList(courseList* cl);
extern course* findCourseInList(courseList* list, course* n);
#endif
