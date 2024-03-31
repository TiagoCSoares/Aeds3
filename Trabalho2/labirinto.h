#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "pilha.h" // Adicione esta linha para usar a definição de Pilha
#include "fila.h"

#define PAREDE 'X'
#define CAMINHO '0'
#define ENTRADA 'E'
#define SAIDA 'S'

void lerLabirinto(char *nomeArquivo, char labirinto[LINHAS][COLUNAS]);
void entradaSaida(No** entrada, No** saida, char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]);
void buscaPorProfundidade(No* nos[LINHAS][COLUNAS], No* entrada, No* saida, Pilha* pilha);
No* buscaPorLargura(No* nos[LINHAS][COLUNAS], No entrada, No saida, Fila* fila, char labirinto[LINHAS][COLUNAS]);
void escreverOutput(char *caminhoDoArquivo, Pilha pilha);
void escreverOutputFila(char *caminhoDoArquivo, Fila* fila, No* PaiSaida, No saida, No entrada);
void limparArquivo(char *caminhoDoArquivo);


#endif
