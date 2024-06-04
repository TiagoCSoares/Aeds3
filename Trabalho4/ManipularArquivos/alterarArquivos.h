#ifndef ALTERAR_ARQUIVOS_H
#define ALTERAR_ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "../Estruturas/no.h"
#include "../Grafo/grafo.h"

void escreverOutputGrafos(char *caminhoDoArquivo, No** grafo, int numVertices);
void escreverCabecalho(char *caminhoDoArquivo, char* metodo, int numVertices, int numArestas, int numCores);
void escreverOutputColors(char *caminhoDoArquivo, char* metodo, int numCores, double tempo);
void limparArquivo(char *caminhoDoArquivo);
void limparArquivosNoDiretorio(const char *diretorio);

#endif
