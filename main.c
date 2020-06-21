/*
 * CS 305 HW 6
 * Author: Tammy VanDeGrift, based on prior CS 303 HW by Tanya Crenshaw
 * main.c
 * creates a graph of airports and runs dijkstra's algorithm to find
 * the shortest cost flight path from a source to a destination
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "main.h"
#include "graph.h"

/* 
 * main
 * Creates a graph of airports and runs dijkstra's algorithm to find 
 * the shortest path from a source airport to a destination airport.
 * usage: hw6 PDX MCO
 */
int main(int argc, char * argv[]) {
  // Create an array of airport names (vertices in graph).  
  char * airports[] = {"PDX", "SEA", "SFO", "LAX", "DEN", "ATL", "JFK", "MSP", "ORD", "DFW", "DTW", "SAN", "PVD", "ANC", "MCO", "PHL", "PHX", "IAD"};

  // Calculate the number of airports in the array.
  int numberOfAirports = sizeof(airports)/sizeof(char *);

  // Check command line arguments.
  if(argc != REQ_PARAM) {
    usage(argv[0]);
  }
  // Are the city names too long?
  if(strlen(argv[SRC]) > MAXWIDTH) {
    err(argv[1]);
  }
  if(strlen(argv[DST]) > MAXWIDTH) {
    err(argv[2]);
  }
  // Are the names given at the command line in the list of airports?
  int i = 0;
  int srcfound = 0;
  int dstfound = 0;
  for(i = 0; i < numberOfAirports; i++) {
    if(strncmp(argv[SRC], airports[i], MAXWIDTH) == 0) srcfound = 1;
    if(strncmp(argv[DST], airports[i], MAXWIDTH) == 0) dstfound = 1;
  }
  
  if(!srcfound) {
    err(argv[SRC]);
  }
  if(!dstfound) {
    err(argv[DST]);
  }

  // Sort the array of airport names lexicographically using the built-in
  // C function qsort().
  qsort(airports, sizeof(airports)/sizeof(*airports), sizeof(*airports), 
	compare);

  printf("Creating a graph for %d airports.\n", numberOfAirports);

  // Given a number and a list of labels, initialize a graph data structure
  // for that many nodes, labeled with the labels.
  struct Graph * flights = buildGraph(numberOfAirports, airports);

  printGraph(flights);
  printf("\n------------------------------\n\n");

  // Find the shortest paths and print the result.  
  dijkstra(flights, argv[SRC]);
  printLabels(flights);

  printf("\n------------------------------\n\n");
  
  int destNum = -1;
  int srcNum = -1;
  // Get the index number of the destination and the source.
  i = 0;
  while(i < flights->V && srcNum == -1) {
    if( strncmp(argv[SRC], flights->array[i].label, MAXWIDTH) == 0) {
      srcNum = i;
    }
    i++;
  }

  i = 0;
  while(i < flights->V && destNum == -1) {
    if( strncmp(argv[DST], flights->array[i].label, MAXWIDTH) == 0) {
      destNum = i;
    }
    i++;
  }
  
  // Start at the destination, and going backwards to the source
  // find all of the members of the path from the source to the destination.
  // As I find each one, keep track of it in the path array.
  int path[numberOfAirports];

  printf("Getting the path from %d to %d. \n", srcNum, destNum);

  int j = 0;
  int pathFinder = destNum;
  while(pathFinder != srcNum) {
    path[j] = flights->array[pathFinder].pred;
    pathFinder = flights->array[pathFinder].pred;
    j++;
  } 

  printf("The path is %d flight(s) long: \n\n", j);
  
  // Print the path backwards.
  j--;
  while(j >= 0) {
    printf("%s -> ", flights->jump[path[j]]);
    j--;
  }
  
  // Print the final destination.
  printf("%s. \n", argv[DST]);
  
  // Print the total mileage.
  printf("%d miles.\n", flights->array[destNum].dValue); 
  printf("\n------------------------------\n");

  freeGraph(&flights);
  return EXIT_SUCCESS;
}


/*
 * buildThisGraph
 * construct edges from airport to airport
 */
Graph * buildGraph(int n, char ** cities) {

  // Initialize the graph data structure.
  Graph * g = initialize(n, cities);
  
  // Add edges between the cities.
  addEdge(g, "PDX", "SEA", 130);
  addEdge(g, "PDX", "SFO", 551);
  addEdge(g, "PDX", "LAX", 835);
  addEdge(g, "PDX", "DEN", 990);
  addEdge(g, "PDX", "ATL", 2168);
  addEdge(g, "PDX", "JFK", 2447);
  addEdge(g, "SEA", "MSP", 1395);
  addEdge(g, "SEA", "ORD", 1716);
  addEdge(g, "SEA", "DTW", 1922);
  addEdge(g, "SEA", "DFW", 1658);
  addEdge(g, "SEA", "SAN", 1051);
  addEdge(g, "LAX", "SAN", 109);
  addEdge(g, "LAX", "DEN", 860);
  addEdge(g, "LAX", "ATL", 1942);
  addEdge(g, "SAN", "JFK", 2440);
  addEdge(g, "SAN", "DFW", 1168);
  addEdge(g, "PVD", "JFK", 144);
  addEdge(g, "ANC", "SEA", 1445);
  addEdge(g, "PVD", "ORD", 847);
  addEdge(g, "ATL", "MCO", 404);
  addEdge(g, "PHL", "PHX", 2071);
  addEdge(g, "PHL", "JFK", 94);
  addEdge(g, "PHX", "SEA", 1107);
  addEdge(g, "IAD", "ORD", 587);
  addEdge(g, "IAD", "PVD", 372);
  addEdge(g, "JFK", "PHX", 2149);
  
  return g;
}  

/*
 * compare
 * Compare two strings.  That is, given two elements, extract the char
 * pointers from them and compare the strings using strncmp().
 */
int compare (const void * elem1, const void * elem2) {
  
  char * s1 = *(char **)elem1;
  char * s2 = *(char **)elem2;
  
  return  strncmp(s1, s2, MAXWIDTH); 
}


/* 
 * usage
 * Print the usage for this program and exit program.
 */
void usage(char * s) {
  printf("usage: %s <source city name> <dest. city name>\n", s);
  printf("  This program finds the shortest flight path from the given source city to destination.\n");
  exit(-1);
}

/* 
 * err
 * Print an error message for this program and exit proram.
 */
void err(char * s) {
  printf("%s is not in this set of airports.\n", s);
  exit(-1);
}
