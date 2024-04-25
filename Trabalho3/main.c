/*
*   AEDS III - Trabalho Prático 2 - Busca Em Grafos Sem Pesos
*
*   Matrícula                               RA
*   LUCAS DOGO DE SOUZA PEZZUTO             2020.1.08.026
*   MARIA EDUARDA FABIANO PIRES             2020.1.08.019
*   MATHEUS MALVÃO BARBOSA                  2020.1.08.025
*   RYAN RODRIGUES                          2021.1.08.032
*   TIAGO COSTA SOARES                      2020.1.08.017
*
*/


#include "Estruturas/pilha.h"
#include "Estruturas/fila.h"
#include "Grafo/grafo.h"
#include "Grafo/watts_strogatz.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void liberarNos(No* nos[LINHAS][COLUNAS]) {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            free(nos[i][j]);
        }
    }
}


int main() {
    
    /*int numVertices = (rand() % 50)+25;
    No** grafo = (No**)malloc(numVertices * sizeof(No*));

    No* nos[LINHAS];*/
       
    int n = 75;  // Número de nós
    int k = 4;   // Cada nó é inicialmente conectado a k vizinhos próximos
    float p = 0.1;  // Probabilidade de reconexão

    watts_strogatz(n, k, p);

    return 0;
}
