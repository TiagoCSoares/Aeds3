#include "../LabirintoOperacoes/labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "alterarArquivos.h"


void escreverOutput(char *caminhoDoArquivo, Pilha pilha) {
    FILE *arquivo = fopen(caminhoDoArquivo, "a");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.");
        return;
    }

    Pilha pilhaInversa;
    inicializarPilha(&pilhaInversa);
    while(!pilhaVazia(&pilha)) {
        empilhar(&pilhaInversa, desempilhar(&pilha));
    }
    while(!pilhaVazia(&pilhaInversa)) {
        No* atual = desempilhar(&pilhaInversa);
        fprintf(arquivo, "%d,%d\n", atual->linha, atual->coluna);
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
}




void escreverOutputFila(char *caminhoDoArquivo, Fila* fila, No* PaiSaida) {
    FILE *arquivo = fopen(caminhoDoArquivo, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    Pilha pilha;
    inicializarPilha(&pilha);

    No* atual = PaiSaida;
    while(atual != NULL) {
        empilhar(&pilha, atual);
        No* pai = NULL;
        for (int i = 0; i <= fila->fim; i++) {
            if (fila->itens[i].filho == atual) {
                pai = fila->itens[i].pai;
                break;
            }
        }
        // Define o próximo nó como o nó pai
        atual = pai;
    }

    while(!pilhaVazia(&pilha)) {
        No* atual = desempilhar(&pilha);
        fprintf(arquivo, "%d,%d\n", atual->linha, atual->coluna);
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);
}



void limparArquivo(char *caminhoDoArquivo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "w");
    fclose(arquivo);
}
