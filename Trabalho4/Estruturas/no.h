#ifndef NO_H
#define NO_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10

typedef struct No {
    int posicao;
    int grau;
    int cor;
    struct Aresta* listaAdjacencia;
} No;

typedef struct Aresta {
    No* destino;
    struct Aresta* proximaAresta;
} Aresta;


No* criarNo(int posicao);

#endif