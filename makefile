CC = gcc -g
SRCS = main.c graph.c dijkstra.c
OBJS = main.o graph.o dijkstra.o

# Compile the hw6 executable from a list of object files.  
hw6:	$(OBJS) main.h graph.h
	$(CC) -o hw6 $(OBJS)

# Compile the o files
main.o:	main.c graph.c graph.h
	$(CC) -c main.c

graph.o:	graph.c graph.h
	$(CC) -c graph.c

dijkstra.o:	dijkstra.c graph.h main.h
	$(CC) -c dijkstra.c

# A rule to clean up the directory of all object files and executable
# file.
clean:
	/bin/rm -f *.o hw6

