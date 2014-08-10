wordstat: wordstat.o
	gcc -ansi -pedantic -Wall wordstat.o -o wordstat
wordstat.o: wordstat.c
	gcc -ansi -pedantic -Wall -c wordstat.c
clean:
	-rm -f wordstat.o
	-rm -f wordstat
