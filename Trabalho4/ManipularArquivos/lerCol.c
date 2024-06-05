#include "lerCol.h"

// Função para processar um arquivo .col
void iterarArquivo(const char *filepath) {

    clock_t inicio, fim;
    double tempoTotal;

    // Verificar a extensão do arquivo
    const char *extension = ".col";
    size_t len_extension = strlen(extension);
    size_t len_filepath = strlen(filepath);
    if (len_filepath < len_extension || strcmp(filepath + len_filepath - len_extension, extension) != 0) {
        // Se a extensão não for ".col", retornar sem processar
        return;
    }

    // Extrair apenas o nome do arquivo
    const char *last_slash = strrchr(filepath, '/');
    const char *nome_com_path = (last_slash != NULL) ? last_slash + 1 : filepath;

    char nome[56];
    strncpy(nome, nome_com_path, sizeof(nome));
    nome[sizeof(nome) - 1] = '\0'; // Garantir terminação nula

    // Encontrar o ponto final na extensão
    char *dot = strrchr(nome, '.');
    if (dot != NULL) {
        *dot = '\0';  // Remover a extensão
    }

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filepath);
        return;
    }

    char line[MAX_LINE_LENGTH];  // Buffer para armazenar cada linha lida
    int numVertices = -1;
    int numArestas = -1;
    int numCores = -1;
    int found_edge_line = 0;

    // Verificar a linha que começa com "p edge"
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "p edge", 6) == 0) {
            if (sscanf(line, "p edge %d %d", &numVertices, &numArestas) == 1) {
                found_edge_line = 1;
            }
            break;
        }
    }

    // Verificar a linha que começa com b
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "b", 1) == 0) {
            if (sscanf(line, "b %d", &numCores) == 1) {
                found_edge_line = 1;
            }
            break;
        }
    }

    
    // Se não encontrou a linha "p edge", retornar sem processar mais
    if (!found_edge_line) {
        fclose(file);
        return;
    }

    No** grafo = criarGrafo(numVertices);

    // Agora processar as linhas que começam com "e "
    rewind(file);  // Voltar ao início do arquivo para processar novamente
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'e' && line[1] == ' ') {
            int num1, num2;
            if (sscanf(line, "e %d %d", &num1, &num2) == 2) {
                adicionarAresta(&(grafo[num1-1]->listaAdjacencia), grafo[num2-1]);
                adicionarAresta(&(grafo[num2-1]->listaAdjacencia), grafo[num1-1]);
            }
        }
    }

    char nomeArquivoGrafo[256];
    snprintf(nomeArquivoGrafo, sizeof(nomeArquivoGrafo), "Output/colors/%s.txt", nome);

    escreverCabecalho(nomeArquivoGrafo, nome, numVertices, numArestas, numCores);


    inicio = clock();
    int maxBuscaLocal = ILSColoracao(grafo, numVertices);
    fim = clock();
    tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    escreverOutputColors(nomeArquivoGrafo, "Busca Local", maxBuscaLocal, tempoTotal);

    inicio = clock();
    int maxEvolutiva = algoritmoGenetico(grafo, numVertices);
    fim = clock();
    tempoTotal = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    escreverOutputColors(nomeArquivoGrafo, "Evolutiva", maxEvolutiva, tempoTotal);

    snprintf(nomeArquivoGrafo, sizeof(nomeArquivoGrafo), "Output/instances/%s.txt", nome);

    // Escreve o grafo no arquivo
    escreverOutputGrafos(nomeArquivoGrafo, grafo, numVertices);

    fclose(file);
}








// Função para iterar sobre todos os arquivos .col na pasta instances
void executarHeuristicas(const char *dirpath) {
    DIR *dir = opendir(dirpath);

    if (dir == NULL) {
        fprintf(stderr, "Erro ao abrir o diretório %s\n", dirpath);
        return;
    }

    struct dirent *entry;
    char filepath[512];

    while ((entry = readdir(dir)) != NULL) {
        // Verificar se o arquivo tem extensão .col
        if (strstr(entry->d_name, ".col") != NULL) {
            snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);
            iterarArquivo(filepath);
        }
    }

    closedir(dir);
}