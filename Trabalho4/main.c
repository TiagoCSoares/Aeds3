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
#include "Grafo/barabasiAlbert.h"
#include "ManipularArquivos/alterarArquivos.h"
#include "ManipularArquivos/operacoes.h"
#include "ManipularArquivos/lerCol.h"

#include "Heuristicas/algoritmoConstrutivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*
void liberarNos(No* nos[LINHAS][COLUNAS]) {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            free(nos[i][j]);
        }
    }
}*/


int main() {  
    srand(time(NULL));

    criarPastaSeNaoExistir("Output");
    //criarPastaSeNaoExistir("Output/grafos3color");
    //criarPastaSeNaoExistir("Output/grafos4color");
    criarPastaSeNaoExistir("Output/instances");
    criarPastaSeNaoExistir("Output/colors");

    limparArquivosNoDiretorio("Output/instances");
    limparArquivosNoDiretorio("Output/colors");

    const char *directory_path = "arquivos/instances";
    process_directory(directory_path);


    /*for(int i = 0; i < 5; i++){
        char nome[100];
        sprintf(nome, "grafos3color");
        limparArquivo(nome);
        char nomeArquivoGrafo[256];
        snprintf(nomeArquivoGrafo, sizeof(nomeArquivoGrafo), "Output/%s/ba%d.txt", nome, i);
        limparArquivo(nomeArquivoGrafo);
    }

    for(int i = 0; i < 5; i++){
        char nome[100];
        sprintf(nome, "grafos4color");
        limparArquivo(nome);
        char nomeArquivoGrafo[256];
        snprintf(nomeArquivoGrafo, sizeof(nomeArquivoGrafo), "Output/%s/ba%d.txt", nome, i);
        limparArquivo(nomeArquivoGrafo);
    }




    for(int i = 0; i < 5; i++){
        int numVertices = rand() % 50 + 25;
        int numVerticesIniciais = rand() % 5 + 9;
        char nome[100];
        sprintf(nome, "grafos3color");
        No** grafo = barabasiAlbert(numVertices, numVerticesIniciais, 6, nome, i);
        heuristicaConstrutivaColoracao(grafo, numVertices, 3);
    }

    for(int i = 0; i < 5; i++){
        int numVertices = rand() % 50 + 25;
        int numVerticesIniciais = rand() % 5 + 9;
        char nome[100];
        sprintf(nome, "grafos4color");
        No** grafo = barabasiAlbert(numVertices, numVerticesIniciais, 8, nome, i);
        heuristicaConstrutivaColoracao(grafo, numVertices, 4);
    }*/

    return 0;
}
