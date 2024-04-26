#ifndef WATTS_H
#define WATTS_H

#include <stdlib.h>
#include <stdio.h>

#include "../ManipularArquivos/alterarArquivos.h"
#include "dijkstra.h"
#include "grafo.h"

void wattsStrogatz(int numVertices, int ligacoesIniciais, float p);

#endif
