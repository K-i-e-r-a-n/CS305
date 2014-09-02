hw1:	main.o
	gcc -o hw1 main.o

main.o:	main.c
	gcc -c  main.c

zip: hw1
	zip -o kieranlosh18.zip hw1 Makefile

.PHONY: clean
clean:	
	-rm hw1 main.o
