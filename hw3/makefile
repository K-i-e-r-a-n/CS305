# Filename: Makefile (for hw3)
# Author: 
# Created by: Tanya L. Crenshaw
# Date created: 9/30/2014
#
CC = gcc
OBJS = main.o aclist.o

# Compile the hw3 executable from a list of object files.  If none of
# the object files has changed, make will report 'hw3 is up to date.'
hw3:	$(OBJS)
	$(CC) -o hw3 $(OBJS)

# State the dependencies of the main object file.  If any changes are
# made in main.c or aclist.h main.o will be recreated.
%.o:	%.c aclist.h 
	$(CC) -c $<

clean: 
	-rm -f $(OBJS) hw3
