#ifndef ALTERAR_ARQUIVOS_H
#define ALTERAR_ARQUIVOS_H

#include "../Estruturas/pilha.h" 
#include "../Estruturas/fila.h"

void escreverOutput(char *caminhoDoArquivo, Pilha pilha);
void escreverOutputFila(char *caminhoDoArquivo, Fila* fila, No* PaiSaida);
void limparArquivo(char *caminhoDoArquivo);

#endif
