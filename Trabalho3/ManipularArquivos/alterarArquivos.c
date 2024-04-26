#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "alterarArquivos.h"


void escreverOutputGrafos(char *caminhoDoArquivo, No** grafo, int numVertices) {

    FILE *arquivo = fopen(caminhoDoArquivo, "a");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.");
        return;
    }

    for(int i = 0; i < numVertices; i++) {
        fprintf(arquivo, "%d ", grafo[i]->posicao);
        Aresta* adj = grafo[i]->listaAdjacencia;
        while(adj != NULL) {
            fprintf(arquivo, "%d ", adj->destino->posicao);
            //fprintf(arquivo, "%d ", adj->peso);
            adj = adj->proximaAresta;
        }
        fprintf(arquivo, "\n");
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);
}

void escreverOutputCloseness(char *caminhoDoArquivo, float* closeness, int numVertices) {
    
        FILE *arquivo = fopen(caminhoDoArquivo, "a");
    
        if(arquivo == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo.");
            return;
        }
    
        for(int i = 0; i < numVertices; i++) {
            fprintf(arquivo, "%d %.4f\n", i, closeness[i]);
        }
    
        fprintf(arquivo, "\n");
        fclose(arquivo);
    
}



void limparArquivo(char *caminhoDoArquivo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "w");
    fclose(arquivo);
}
