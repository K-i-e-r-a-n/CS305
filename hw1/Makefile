hw1:	main.o
	gcc -o hw1 main.o

main.o:	main.c
	gcc -c  main.c

zip: 
	zip -o losh18.zip main.c Makefile

.PHONY: clean
clean:	
	-rm hw1 main.o
