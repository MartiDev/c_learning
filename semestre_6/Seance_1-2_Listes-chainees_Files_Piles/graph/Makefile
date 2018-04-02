CFLAGS+=-Wall
CFLAGS+=-std=c99

all: pile_file.o graph.o
	gcc $(CFLAGS) pile_file.o graph.o -o graph

pile_file.o: pile_file.c pile_file.h
	gcc $(CFLAGS) -c pile_file.c

graph.o : graph.c pile_file.h
	gcc $(CFLAGS) -c graph.c

clean:
	rm -f *.o
	rm -f graph
