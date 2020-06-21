/*
 * CS 305 HW 6
 * Author: Jonathan Liao, based on prior CS 303 HW by Tanya Crenshaw
 * dijkstra.c
 * Graph function implementations, based on adjacency list
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h" 
#include "main.h"
#include <math.h>

void dijkstra(Graph * g, char * source) {
//find current node index. We are given it's string name, but need to find the index number in Graph g
int i;

  for(i=0; i<g->V; i++) {
    if(strcmp(g->array[i].label, source) == 0) { //found the index place
      g->array[i].dValue = 0; //found the source. Set its distance to 0 and leave loop
      break;
    } 
  }
  while(isEmpty(g) == 0) {//while all the nodes are still white
    int U = getMin(g);
    while(g->array[U].head != NULL) {//while the list of U's neighbors hasn't been exhausted
      int neighbor = g->array[U].head->dest; //store the neighbor's node value here
      if(g->array[neighbor].dValue > (g->array[U].dValue + g->array[U].head->cost) ) {
	g->array[neighbor].dValue = g->array[U].dValue + g->array[U].head->cost;
	g->array[neighbor].pred = U;
      }
      g->array[U].head = g->array[U].head->next; //go on to next neighbor
    }
  g->array[U].color = BLACK;
  }
}


int isEmpty(Graph * g) {
  if(g == NULL) {
    return 1; //this graph is empty
  }
  int i;
  for(i=0; i<g->V; i++) {
    if(g->array[i].color == WHITE) { //found at least one white node
      return 0;
    } 
  }
  return 1; //loop unsucesfully found a white node if it made it here
}

int getMin(Graph * g) {
  if(g == NULL) {
    return -1; //this graph is empty
  }
  if(isEmpty(g) == 1) {
    return -1; //there are no white nodes
  }
  int i;
  int min = INF; //initialize as first dValue 
  for(i=0; i<g->V; i++) {
    if(g->array[i].color == WHITE && g->array[i].dValue < min ) { //found white node and with node smaller than min
	min = i; //index of this node is saved
    } 
  }
  return min;
}
