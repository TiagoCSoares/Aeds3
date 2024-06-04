#ifndef OPERACOES_H
#define OPERACOES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>

char *construirNomeArquivoCompleto(char *nomeArquivo, char *extensao, int numero);
int criarPastaSeNaoExistir(const char *nomePasta);

#endif
