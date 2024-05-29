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
#include "Grafo/wattsStrogatz.h"
#include "Grafo/barabasiAlbert.h"
#include "Grafo/dijkstra.h"
#include "Grafo/closeness.h"
#include "ManipularArquivos/alterarArquivos.h"
#include "ManipularArquivos/operacoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void liberarNos(No* nos[LINHAS][COLUNAS]) {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            free(nos[i][j]);
        }
    }
}


int main() {  
    //srand(time(NULL));
    criarPastaSeNaoExistir("Output");
    limparArquivo("Output/grafos.txt");
    limparArquivo("Output/closeness.txt");

    for(int i = 0; i < 5; i++){
        int numVertices = rand() % 50 + 25;
        int numVerticesIniciais = rand() % 5 + 9;
        barabasiAlbert(numVertices, numVerticesIniciais);
    }

    for(int i = 0; i < 5; i++){
        int numVertices = rand() % 50 + 25;
        int numLigacoesIniciais = rand() % 3 + 4;
        float p = (float)rand() / RAND_MAX * 0.6 + 0.1;
        printf("p: %f\n", p);
        wattsStrogatz(numVertices, numLigacoesIniciais, p);
    }
    
    // Comando para executar o arquivo Python
    char comando[100];
    sprintf(comando, "python3 main.py");
    
    // Executar o comando
    int status = system(comando);
    
    // Verificar se a execução foi bem sucedida
    if (status != 0) 
        printf("Ocorreu um erro durante a execução do script Python.\n");


    return 0;
}
