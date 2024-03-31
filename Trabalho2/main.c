#include "pilha.h"
#include "grafo.h"
#include "fila.h"
#include "labirinto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


void lerLabirintoEConstruirGrafo(char *nomeArquivo, char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]) {
    lerLabirinto(nomeArquivo, labirinto);
    criarGrafo(labirinto, nos);
}

void liberarNos(No* nos[LINHAS][COLUNAS]) {
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            free(nos[i][j]);
        }
    }
}

char *construirNomeArquivoCompleto(char *nomeArquivo, char *extensao, int numero) {
    char numeroStr[10];
    sprintf(numeroStr, "%d", numero);
    size_t tamanho = strlen(nomeArquivo) + strlen(extensao) + strlen(numeroStr) + 1;
    char *nomeCompleto = (char *)malloc(tamanho);
    sprintf(nomeCompleto, "%s%s%s", nomeArquivo, numeroStr, extensao);
    return nomeCompleto;
}

void buscarEmProfundidade(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS], char *extensao, char *nomeArquivo) {
    limparArquivo("Output/ProfundidadeOutput.txt");
    for(int i = 1; i <= 5; i++) {
        char *nomeArquivoCompleto = construirNomeArquivoCompleto(nomeArquivo, extensao, i);
        lerLabirintoEConstruirGrafo(nomeArquivoCompleto, labirinto, nos);

        No *entrada = NULL;
        No *saida = NULL;
        entradaSaida(&entrada, &saida, labirinto, nos);
        
        Pilha pilha;
        inicializarPilha(&pilha);
        empilhar(&pilha, entrada);
        entrada->visitado = false;

        buscaPorProfundidade(nos, entrada, saida, &pilha);
        escreverOutput("Output/ProfundidadeOutput.txt", pilha);

        free(nomeArquivoCompleto);
    }
}

void buscarEmLargura(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS], char *extensao, char *nomeArquivo) {
    limparArquivo("Output/LarguraOutput.txt");
    for(int i = 1; i <= 5; i++) {
        char *nomeArquivoCompleto = construirNomeArquivoCompleto(nomeArquivo, extensao, i);
        lerLabirintoEConstruirGrafo(nomeArquivoCompleto, labirinto, nos);

        No *entrada = NULL;
        No *saida = NULL;
        entradaSaida(&entrada, &saida, labirinto, nos);
        
        Fila fila;
        inicializarFila(&fila);
        enfileirar(&fila, entrada, NULL);
        entrada->visitado = true;

        No* paiSaida = buscaPorLargura(nos, *entrada, *saida, &fila, labirinto);
        escreverOutputFila("Output/LarguraOutput.txt", &fila, paiSaida, *saida, *entrada);

        free(nomeArquivoCompleto);
    }
}

void criarPastaSeNaoExistir(const char *nomePasta) {
    struct dirent *dir;
    DIR *diretorio = opendir(nomePasta);
    
    if (!diretorio) {
        mkdir(nomePasta, 0700); // Permissões: 0700 (permissões rwx para o proprietário)
    } else {
        closedir(diretorio);
    }
}




int main() {
    char *nomeArquivo = "Labirintos/labirinto";
    char *extensao = ".txt";
    No* nos[LINHAS][COLUNAS];
    char labirinto[LINHAS][COLUNAS];


    //const char *nomePasta = "Output"; // Nome da pasta a ser criada
    criarPastaSeNaoExistir("Output");
       
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            nos[i][j] = (No*)malloc(sizeof(No));
            nos[i][j]->percorrido = false;
            nos[i][j]->visitado = false;
        }
    }

    buscarEmProfundidade(labirinto, nos, extensao, nomeArquivo);
    buscarEmLargura(labirinto, nos, extensao, nomeArquivo);

    liberarNos(nos);

    return 0;
}
