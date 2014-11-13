# Filename: Makefile 
# Created by: Tanya L. Crenshaw
# Date updated: 10/16/2014
#
# Use this file to compile the programming 
# assignment #4 for CS305.  It may be invoked
# from the command line using the make tool
# by simply typing:
#
# $ make
#
# CS305 Students do not need to edit this file.
#
CC = gcc
ARGS = -lm 
OBJS = main.o company.o list.o readLine.o sort.o tree.o
HEADERS = list.h sort.h readLine.h usage.h tree.h

hw4:	$(OBJS) $(HEADERS)
	$(CC) -o hw4 $(OBJS) $(ARGS)

main.o:	main.c $(HEADERS)
	$(CC) -c main.c

readLine.o:	readLine.c readLine.h
	$(CC) -c readLine.c

list.o:	list.c list.h usage.h
	$(CC) -c list.c

sort.o:	sort.c sort.h list.h
	$(CC) -c sort.c

tree.o: tree.c tree.h
	$(CC) -c tree.c

company.o:	company.c company.h
	$(CC) -c company.c	

clean: 
	-rm -f $(OBJS) 
	-rm -f hw4
