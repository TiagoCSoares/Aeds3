#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "Estruturas/pilha.h" // Adicione esta linha para usar a definição de Pilha
#include "Estruturas/fila.h"

#define PAREDE 'X'
#define CAMINHO '0'
#define ENTRADA 'E'
#define SAIDA 'S'

void lerLabirinto(char *nomeArquivo, char labirinto[LINHAS][COLUNAS]);
void entradaSaida(No** entrada, No** saida, char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]);
void escreverOutput(char *caminhoDoArquivo, Pilha pilha);
void escreverOutputFila(char *caminhoDoArquivo, Fila* fila, No* PaiSaida);
void limparArquivo(char *caminhoDoArquivo);

#endif
