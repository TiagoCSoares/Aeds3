#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "../Estruturas/pilha.h" // Adicione esta linha para usar a definição de Pilha
#include "../Estruturas/fila.h"

typedef enum {
    PROFUNDIDADE,
    LARGURA
} TipoBusca;


#define PAREDE 'X'
#define CAMINHO '0'
#define ENTRADA 'E'
#define SAIDA 'S'

void entradaSaida(No** entrada, No** saida, char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]);
void lerLabirintoEConstruirGrafo(char *nomeArquivo, char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]);
void buscarLabirinto(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS], char *extensao, char *nomeArquivo, TipoBusca tipo);


#endif
