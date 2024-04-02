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
#include "LabirintoOperacoes/labirinto.h"
#include "ManipularArquivos/alterarArquivos.h"
#include "ManipularArquivos/operacoes.h"

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
    char *nomeArquivo = "Labirintos/labirinto";
    char *extensao = ".txt";
    No* nos[LINHAS][COLUNAS];
    char labirinto[LINHAS][COLUNAS];

    criarPastaSeNaoExistir("Output");
       
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            nos[i][j] = (No*)malloc(sizeof(No));
            nos[i][j]->visitado = false;
        }
    }

    buscarLabirinto(labirinto, nos, extensao, nomeArquivo, PROFUNDIDADE);
    buscarLabirinto(labirinto, nos, extensao, nomeArquivo, LARGURA);

    liberarNos(nos);

    return 0;
}
