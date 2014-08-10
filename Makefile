wordstat: wordstat.o
	gcc -ansi -pedantic -Wall wordstat.o -o wordstat

clean:
	-rm -f wordstat.o
	-rm -f wordstat
