hw2: main.o convert.o
	gcc -o hw2 main.o convert.o 

main.o:	main.c
	gcc -c  main.c

convert.o: convert.h convert.c
	gcc -c convert.c

zip: 
	zip -o losh18.zip *.c *.h Makefile

.PHONY: clean
clean:	
	-rm hw2 *.o
