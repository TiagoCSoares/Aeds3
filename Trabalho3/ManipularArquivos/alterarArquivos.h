#ifndef ALTERAR_ARQUIVOS_H
#define ALTERAR_ARQUIVOS_H

#include "../Estruturas/no.h"
#include "../Grafo/grafo.h"

void escreverOutputGrafos(char *caminhoDoArquivo, No** grafo, int numVertices);
void limparArquivo(char *caminhoDoArquivo);

#endif
