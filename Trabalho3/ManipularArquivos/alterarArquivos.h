#ifndef ALTERAR_ARQUIVOS_H
#define ALTERAR_ARQUIVOS_H

#include "../Estruturas/no.h"
#include "../Grafo/grafo.h"

void escreverOutput(char *caminhoDoArquivo, No** grafo, int numVertices);
void limparArquivo(char *caminhoDoArquivo);

#endif
