bookstats: string.o statistics.o queue.o line.o bookstats.o
	gcc -o bookstats -std=c11 -Wall -ggdb3 bookstats.o queue.o statistics.o string.o line.o -lpthread
	
string.o:
	gcc -c string.c

statistics.o:
	gcc -c statistics.c
	
queue.o:
	gcc -c queue.c
	
line.o:
	gcc -c line.c
	
bookstats.o:
	gcc -c bookstats.c
	
clean:
	rm -f string.o
	rm -f statistics.o
	rm -f queue.o
	rm -f bookstats.o
	rm -f line.o
	rm -f bookstats
