#include "alterarArquivos.h"


void escreverOutputGrafos(char *caminhoDoArquivo, No** grafo, int numVertices) {

    FILE *arquivo = fopen(caminhoDoArquivo, "a");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.");
        return;
    }

    for(int i = 0; i < numVertices; i++) {
        fprintf(arquivo, "%d ", grafo[i]->posicao);
        Aresta* adj = grafo[i]->listaAdjacencia;
        while(adj != NULL) {
            fprintf(arquivo, "%d ", adj->destino->posicao);
            //fprintf(arquivo, "%d ", adj->peso);
            adj = adj->proximaAresta;
        }
        fprintf(arquivo, "\n");
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);
}

void escreverOutputColors(char *caminhoDoArquivo, char* metodo, int numCores) {
    
        FILE *arquivo = fopen(caminhoDoArquivo, "a");
    
        if(arquivo == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo.");
            return;
        }
    
        fprintf(arquivo, "%s: %d\n", metodo, numCores);
    
        fprintf(arquivo, "\n");
        fclose(arquivo);
    
}



void limparArquivo(char *caminhoDoArquivo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "w");
    fclose(arquivo);
}


// Função para limpar todos os arquivos em um diretório
void limparArquivosNoDiretorio(const char *diretorio) {
    DIR *dir = opendir(diretorio);
    if (dir == NULL) {
        fprintf(stderr, "Erro ao abrir o diretório %s\n", diretorio);
        return;
    }

    struct dirent *entry;
    char caminhoDoArquivo[512];

    while ((entry = readdir(dir)) != NULL) {
        snprintf(caminhoDoArquivo, sizeof(caminhoDoArquivo), "%s/%s", diretorio, entry->d_name);
        
        // Verificar se é um arquivo usando stat
        struct stat info;
        if (stat(caminhoDoArquivo, &info) == 0 && S_ISREG(info.st_mode)) {
            limparArquivo(caminhoDoArquivo);
        }
    }

    closedir(dir);
}

