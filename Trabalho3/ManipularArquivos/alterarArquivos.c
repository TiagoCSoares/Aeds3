#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "alterarArquivos.h"
#include "../Estruturas/no.h"
#include "../Grafo/grafo.h"


void escreverOutput(char *caminhoDoArquivo, No** grafo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "a");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.");
        return;
    }
    
    int tamanho = tamanhoGrafo(grafo);
    for(int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d ", grafo[i]->posicao);
        Aresta* adj = grafo[i]->listaAdjacencia;
        while(adj != NULL) {
            fprintf(arquivo, "%d ", adj->destino->posicao);
            adj = adj->proximaAresta;
        }
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);
}



void limparArquivo(char *caminhoDoArquivo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "w");
    fclose(arquivo);
}
