#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#include "grafo.h"


int minDistance(int dist[], int sptSet[], int numVertices);
void dijkstra(No** grafo, int numVertices, int raiz);
void printSolution(int dist[], int numVertices);

#endif