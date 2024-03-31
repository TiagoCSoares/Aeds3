#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>



void lerLabirinto(char *nomeArquivo, char labirinto[LINHAS][COLUNAS]) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char c = fgetc(arquivo);
            labirinto[i][j] = c;
        }
        // Descartar o caractere de nova linha
        fgetc(arquivo);
    }

    fclose(arquivo);
}


void entradaSaida(No** entrada, 
            No** saida, 
            char labirinto[LINHAS][COLUNAS], 
            No* nos[LINHAS][COLUNAS]) {

    for(int i = 0; i < LINHAS; i++) {
            for(int j = 0; j < COLUNAS; j++) {
                if(labirinto[i][j] == ENTRADA) {
                    *entrada = nos[i][j];
                } else if(labirinto[i][j] == SAIDA) {
                    *saida = nos[i][j];
                }
            }
        }

        if (*entrada == NULL || *saida == NULL) {
            printf("Entrada ou saída não encontrada no labirinto.\n");
        return;
        }
}


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
            if (fila->items[i].filho == atual) {
                pai = fila->items[i].pai;
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