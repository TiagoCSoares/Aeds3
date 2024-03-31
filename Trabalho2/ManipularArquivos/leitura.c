#include "../LabirintoOperacoes/labirinto.h"
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