/* 
 * CS 305 HW 6
 * Author: Tammy VanDeGrift, based on prior CS 303 HW by Tanya Crenshaw
 * main.h
 * contains constants and function prototypes
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "graph.h"

// Define constants for main
#define REQ_PARAM 3
#define SRC 1
#define DST 2

// Define the function prototypes for the functions implemented in main.c
Graph * buildGraph(int n, char ** cities);
int compare (const void * elem1, const void * elem2);
void err(char * s);
void usage(char * s);

// These functions are what students implement in dijkstra.c
void dijkstra(Graph * g, char * source);  
int isEmpty(Graph * g);
int getMin(Graph * g);

#endif
