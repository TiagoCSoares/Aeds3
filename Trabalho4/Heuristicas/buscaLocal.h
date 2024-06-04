#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "../Estruturas/no.h"
#include "algoritmoConstrutivo.h"


void atribuir_cores_aleatorias(No** grafo, int numVertices);
int calcular_conflitos(No** grafo, int numVertices);
int busca_local(No** grafo, int numVertices);

#endif