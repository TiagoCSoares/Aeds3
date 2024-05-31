#ifndef CLOSENESS_H
#define CLOSENESS_H

#include <stdlib.h>
#include <stdio.h>

#include "../ManipularArquivos/alterarArquivos.h"
#include "grafo.h"
#include "dijkstra.h"

void closeness(No** grafo, int numVertices);

#endif