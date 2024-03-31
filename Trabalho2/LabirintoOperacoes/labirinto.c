
#include "../ManipularArquivos/alterarArquivos.c"
#include "../ManipularArquivos/leitura.c"
#include "../ManipularArquivos/operacoes.c"
#include "../Buscas/buscaPorLargura.c"
#include "../Buscas/buscaPorProfundidade.c"
#include "../Grafo/grafo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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



void lerLabirintoEConstruirGrafo(char *nomeArquivo, char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]) {
    lerLabirinto(nomeArquivo, labirinto);
    criarGrafo(labirinto, nos);
}


void buscarLabirinto(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS], char *extensao, char *nomeArquivo, TipoBusca tipo) {
    char outputFileName[50];
    switch(tipo) {
        case PROFUNDIDADE:
            strcpy(outputFileName, "Output/ProfundidadeOutput.txt");
            break;
        case LARGURA:
            strcpy(outputFileName, "Output/LarguraOutput.txt");
            break;
        default:
            printf("Tipo de busca inválido.\n");
            return;
    }
    
    limparArquivo(outputFileName);
    
    for(int i = 1; i <= 5; i++) {
        char *nomeArquivoCompleto = construirNomeArquivoCompleto(nomeArquivo, extensao, i);
        lerLabirintoEConstruirGrafo(nomeArquivoCompleto, labirinto, nos);

        No *entrada = NULL;
        No *saida = NULL;
        entradaSaida(&entrada, &saida, labirinto, nos);
        
        if (tipo == PROFUNDIDADE) {
            Pilha pilha;
            inicializarPilha(&pilha);
            empilhar(&pilha, entrada);
            entrada->visitado = false;

            buscaPorProfundidade(nos, entrada, saida, &pilha);
            escreverOutput(outputFileName, pilha);
        } else if (tipo == LARGURA) {
            Fila fila;
            inicializarFila(&fila);
            enfileirar(&fila, entrada, NULL);
            entrada->visitado = true;

            No* paiSaida = buscaPorLargura(nos, *entrada, *saida, &fila);
            escreverOutputFila(outputFileName, &fila, paiSaida);
        }

        free(nomeArquivoCompleto);
    }
}