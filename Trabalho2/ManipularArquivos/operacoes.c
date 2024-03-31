#include <stdio.h>
#include <string.h>
#include "operacoes.h"

char *construirNomeArquivoCompleto(char *nomeArquivo, char *extensao, int numero) {
    char numeroStr[10];
    sprintf(numeroStr, "%d", numero);
    size_t tamanho = strlen(nomeArquivo) + strlen(extensao) + strlen(numeroStr) + 1;
    char *nomeCompleto = (char *)malloc(tamanho);
    sprintf(nomeCompleto, "%s%s%s", nomeArquivo, numeroStr, extensao);
    return nomeCompleto;
}

void criarPastaSeNaoExistir(const char *nomePasta) {
    struct dirent *dir;
    DIR *diretorio;
    diretorio = opendir(nomePasta);
    
    if (!diretorio) {
        mkdir(nomePasta, 0700); // Permissões: 0700 (permissões rwx para o proprietário)
    } else {
        closedir(diretorio);
    }
}