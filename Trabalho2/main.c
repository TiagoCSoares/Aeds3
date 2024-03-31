#include "pilha.h"
#include "grafo.h"
#include "fila.h"
#include "labirinto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *nomeArquivo = "Labirintos/labirinto"; // Parte fixa do nome do arquivo
    char *extensao = ".txt"; // Extensão do arquivo
    No* nos[LINHAS][COLUNAS];
    
    // Alocar memória para o labirinto fora do loop
    char labirinto[LINHAS][COLUNAS];
    
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            //nos[i][j] = NULL;

            nos[i][j] = (No*)malloc(sizeof(No)); // Alocar memória para o nó
            nos[i][j]->percorrido = false; // Inicializar membros percorrido e visitado
            nos[i][j]->visitado = false;
        }
    }

    limparArquivo("Output/ProfundidadeOutput.txt");

    // Navegar pelos cinco labirintos
    for(int i = 1; i <= 5; i++) {
        // Converter o número inteiro para uma string
        char numero[10];
        sprintf(numero, "%d", i);

        // Determinar o tamanho necessário para o nome do arquivo completo
        size_t tamanhoNomeArquivoCompleto = strlen(nomeArquivo) + strlen(numero) + strlen(extensao) + 1;
        // Alocar memória para o nome do arquivo completo
        char *nomeArquivoCompleto = (char *)malloc(tamanhoNomeArquivoCompleto);

        // Construir o nome do arquivo completo
        strcpy(nomeArquivoCompleto, nomeArquivo);
        strcat(nomeArquivoCompleto, numero);
        strcat(nomeArquivoCompleto, extensao);

        // Ler o labirinto do arquivo
        lerLabirinto(nomeArquivoCompleto, labirinto);

        // Criar o grafo a partir do labirinto
        criarGrafo(labirinto, nos);

        No *entrada = NULL;
        No *saida = NULL;
        entradaSaida(&entrada, &saida, labirinto, nos);
        
        Pilha pilha;
        inicializarPilha(&pilha);
        empilhar(&pilha, entrada);
        entrada->visitado = false;

        buscaPorProfundidade(nos, entrada, saida, &pilha);
        escreverOutput("Output/ProfundidadeOutput.txt", pilha);

        // Liberar a memória alocada dinamicamente
        free(nomeArquivoCompleto);
    }





   limparArquivo("Output/LarguraOutput.txt");

    // Navegar pelos cinco labirintos
    for(int i = 1; i <= 5; i++) {

        
        char numero[10]; 
        sprintf(numero, "%d", i);

        // Determinar o tamanho necessário para o nome do arquivo completo
        size_t tamanhoNomeArquivoCompleto = strlen(nomeArquivo) + strlen(numero) + strlen(extensao) + 1;
        // Alocar memória para o nome do arquivo completo
        char *nomeArquivoCompleto = (char *)malloc(tamanhoNomeArquivoCompleto);

        // Construir o nome do arquivo completo
        strcpy(nomeArquivoCompleto, nomeArquivo);
        strcat(nomeArquivoCompleto, numero);
        strcat(nomeArquivoCompleto, extensao);

        // Ler o labirinto do arquivo
        lerLabirinto(nomeArquivoCompleto, labirinto);

        // Criar o grafo a partir do labirinto
        criarGrafo(labirinto, nos);

        No *entrada = NULL;
        No *saida = NULL;
        entradaSaida(&entrada, &saida, labirinto, nos);
        
        Fila fila;
        inicializarFila(&fila);
        enfileirar(&fila, entrada, NULL);
        entrada->visitado = true;

        No* paiSaida = buscaPorLargura(nos, *entrada, *saida, &fila, labirinto);
        if(paiSaida == NULL) {
            printf("NULL\n");
        }

        escreverOutputFila("Output/LarguraOutput.txt", &fila, paiSaida, *saida, *entrada);

        // Liberar a memória alocada dinamicamente
        free(nomeArquivoCompleto);
    }

    return 0;
}
