#ifndef OPERACOES_H
#define OPERACOES_H

#include <dirent.h>

char *construirNomeArquivoCompleto(char *nomeArquivo, char *extensao, int numero);
void criarPastaSeNaoExistir(const char *nomePasta);

#endif
