OBJS = main.o course.o graph.o plan.o parse.o
CC = gcc
GCC = $(CC)
FLAGS = -g

all: hw5

hw5: $(OBJS)
	$(GCC) $(FLAGS) -o hw5 $(OBJS)

main.o: main.c course.h graph.h plan.h
	$(GCC) -c main.c

course.o: course.c course.h
	$(GCC) -c course.c

graph.o: graph.c course.h graph.h
	$(GCC) -c graph.c

plan.o: plan.c course.h graph.h plan.h
	$(GCC) -c plan.c

parse.o: parse.c parse.h
	$(GCC) -c parse.c

clean:
	rm -f $(OBJS) hw5
