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



void buscaPorProfundidade(No* nos[LINHAS][COLUNAS], No* entrada, No* saida, Pilha* pilha) {

    if(topoDaPilha(pilha) == saida) {
        return;
    } else {
        No* atual = topoDaPilha(pilha);
        Aresta* listaAdjacencia = atual->listaAdjacencia;
        while(listaAdjacencia != NULL) {
            if(listaAdjacencia->destino->visitado == 0) {
                listaAdjacencia->destino->visitado = 1;
                empilhar(pilha, listaAdjacencia->destino);
                buscaPorProfundidade(nos, entrada, saida, pilha);
            }
            listaAdjacencia = listaAdjacencia->proximaAresta;
        }
        if(topoDaPilha(pilha) != saida) {
            desempilhar(pilha);
        }
    }
}



No* buscaPorLargura(No* nos[LINHAS][COLUNAS], No entrada, No saida, Fila* fila, char labirinto[LINHAS][COLUNAS]) {
    while (!filaVazia(fila)) {
        No* atual = desenfileirar(fila); // Obtemos o próximo nó da fila

        // Verifica se o nó atual é a saída
        if (atual->linha == saida.linha && atual->coluna == saida.coluna) {
            return atual; // Achou o nó de saída
        }

        // Marca o nó atual como visitado
        atual->visitado = true;

        // Itera sobre os nós adjacentes
        Aresta* listaAdjacencia = atual->listaAdjacencia;
        while (listaAdjacencia != NULL) {
            No* adjacente = listaAdjacencia->destino;
            // Verifica se o nó adjacente não foi visitado e não é uma parede
            if (!adjacente->visitado && labirinto[adjacente->linha][adjacente->coluna] != PAREDE) {
                // Marca o nó adjacente como visitado
                adjacente->visitado = true;
                // Enfileira o nó adjacente e seu nó pai
                enfileirar(fila, adjacente, atual);
            }
            listaAdjacencia = listaAdjacencia->proximaAresta;
        }
    }
    return NULL; // Não encontrou o caminho até a saída
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


void escreverOutputFila(char *caminhoDoArquivo, Fila* fila, No* PaiSaida, No saida, No entrada) {
    FILE *arquivo;
    arquivo = fopen(caminhoDoArquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    fprintf(arquivo, "%d,%d\n", saida.linha, saida.coluna);

    No* atual = PaiSaida;
    while (atual != NULL) {
        // Escreve as coordenadas do nó no arquivo
        fprintf(arquivo, "%d,%d\n", atual->linha, atual->coluna);

        // Se o nó atual for a entrada, saímos do loop
        if (atual->linha == entrada.linha && atual->coluna == entrada.coluna) {
            break;
        }

        // Encontra o nó pai na fila
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

    // Adiciona uma quebra de linha ao final de cada linha
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

void limparArquivo(char *caminhoDoArquivo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "w");
    fclose(arquivo);
}