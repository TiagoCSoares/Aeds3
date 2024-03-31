#ifndef NO_H
#define NO_H

#include <stdbool.h>

#define LINHAS 10
#define COLUNAS 10

typedef struct No {
    int linha;
    int coluna;
    bool visitado;
    struct Aresta* listaAdjacencia;
} No;

typedef struct Aresta {
    No* destino;
    struct Aresta* proximaAresta;
} Aresta;

#endif