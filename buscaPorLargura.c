#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINHAS 10
#define COLUNAS 10
#define PAREDE 'X'
#define CAMINHO '0'
#define ENTRADA 'E'
#define SAIDA 'S'



typedef struct No {
    int linha;
    int coluna;
    int visistado;
    struct Aresta* listaAdjacencia;

} No;

typedef struct Aresta {
    No* destino;
    struct Aresta* proximaAresta;
} Aresta;


typedef struct Pilha {
    No* items[LINHAS * COLUNAS];
    int topo;
} Pilha;

void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

void empilhar(Pilha* pilha, No* item) {
    pilha->items[++pilha->topo] = item;
}

No* desempilhar(Pilha* pilha) {
    if(pilhaVazia(pilha)) {
        return NULL;
    }
    return pilha->items[pilha->topo--];
}

No* topoDaPilha(Pilha* pilha) {
    if(pilhaVazia(pilha)) {
        return NULL;
    }
    return pilha->items[pilha->topo];
}




// Função para adicionar uma aresta ao grafo
void adicionarAresta(Aresta** listaAdjacencia, No* destino) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->proximaAresta = *listaAdjacencia;
    *listaAdjacencia = novaAresta;
}

// Função para criar o grafo a partir do labirinto
void criarGrafo(char labirinto[LINHAS][COLUNAS], No* nos[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (labirinto[i][j] != PAREDE) {
                No* atual = (No*)malloc(sizeof(No));
                atual->linha = i;
                atual->coluna = j;
                atual->visistado = 0;
                //atual->proximo = NULL;
                atual->listaAdjacencia = NULL;
                nos[i][j] = atual;

                // Verificar células adjacentes
                if (i > 0 && labirinto[i - 1][j] != PAREDE) {
                    if (nos[i - 1][j] != NULL) {
                        adicionarAresta(&(atual->listaAdjacencia), nos[i - 1][j]);
                        adicionarAresta(&(nos[i - 1][j]->listaAdjacencia), atual);
                    }
                }
                if (i < LINHAS - 1 && labirinto[i + 1][j] != PAREDE) {
                    if (nos[i + 1][j] != NULL) {
                        adicionarAresta(&(atual->listaAdjacencia), nos[i + 1][j]);
                        adicionarAresta(&(nos[i + 1][j]->listaAdjacencia), atual);
                    }
                }
                if (j > 0 && labirinto[i][j - 1] != PAREDE) {
                    if (nos[i][j - 1] != NULL) {
                        adicionarAresta(&(atual->listaAdjacencia), nos[i][j - 1]);
                        adicionarAresta(&(nos[i][j - 1]->listaAdjacencia), atual);
                    }
                }
                if (j < COLUNAS - 1 && labirinto[i][j + 1] != PAREDE) {
                    if (nos[i][j + 1] != NULL) {
                        adicionarAresta(&(atual->listaAdjacencia), nos[i][j + 1]);
                        adicionarAresta(&(nos[i][j + 1]->listaAdjacencia), atual);
                    }
                }
            } else {
                nos[i][j] = NULL; // Marcar células de parede como nulas
            }
        }
    }
}

// Função para imprimir o grafo
//void imprimirGrafo(No* nos[LINHAS][COLUNAS]) {
//    for (int i = 0; i < LINHAS; i++) {
//        for (int j = 0; j < COLUNAS; j++) {
//            No* atual = nos[i][j];
//            if (atual != NULL) {
//                printf("(%d,%d) -> ", atual->linha, atual->coluna);
//                Aresta* listaAdjacencia = atual->listaAdjacencia;
//                while (listaAdjacencia != NULL) {
//                    printf("(%d,%d) ", listaAdjacencia->destino->linha, listaAdjacencia->destino->coluna);
//                    listaAdjacencia = listaAdjacencia->proximaAresta;
//                }
//                printf("\n");
//            }
//        }
//    }
//}

void lerLabirinto(char *nomeArquivo, char labirinto[LINHAS][COLUNAS]) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char c = fgetc(arquivo);
            labirinto[i][j] = c;
        }
        // Descartar o caractere de nova linha
        fgetc(arquivo);
    }

    fclose(arquivo);
}



void buscaPorProfundidade(No* nos[LINHAS][COLUNAS], No* entrada, No* saida, Pilha* pilha) {

    if(topoDaPilha(pilha) == saida) {
        return;
    } else {
        No* atual = topoDaPilha(pilha);
        Aresta* listaAdjacencia = atual->listaAdjacencia;
        while(listaAdjacencia != NULL) {
            if(listaAdjacencia->destino->visistado == 0) {
                listaAdjacencia->destino->visistado = 1;
                empilhar(pilha, listaAdjacencia->destino);
                buscaPorProfundidade(nos, entrada, saida, pilha);
            }
            listaAdjacencia = listaAdjacencia->proximaAresta;
        }
        if(topoDaPilha(pilha) != saida) {
            desempilhar(pilha);
        }
    }
}



void entradaSaida(No** entrada, 
            No** saida, 
            char labirinto[LINHAS][COLUNAS], 
            No* nos[LINHAS][COLUNAS]) {

    for(int i = 0; i < LINHAS; i++) {
            for(int j = 0; j < COLUNAS; j++) {
                if(labirinto[i][j] == ENTRADA) {
                    *entrada = nos[i][j];
                } else if(labirinto[i][j] == SAIDA) {
                    *saida = nos[i][j];
                }
            }
        }

        if (*entrada == NULL || *saida == NULL) {
            printf("Entrada ou saída não encontrada no labirinto.\n");
        return;
        }
}


void escreverOutput(char *caminhoDoArquivo, Pilha pilha) {
    FILE *arquivo = fopen(caminhoDoArquivo, "a");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.");
        return;
    }

    Pilha pilhaInversa;
        inicializarPilha(&pilhaInversa);

        while(!pilhaVazia(&pilha)) {
            empilhar(&pilhaInversa, desempilhar(&pilha));
        }

        while(!pilhaVazia(&pilhaInversa)) {
            No* atual = desempilhar(&pilhaInversa);
           fprintf(arquivo, "%d,%d\n", atual->linha, atual->coluna);
        }
        fprintf(arquivo, "\n");

        fclose(arquivo);
}

void limparArquivo(char *caminhoDoArquivo) {
    FILE *arquivo = fopen(caminhoDoArquivo, "w");
    fclose(arquivo);
}



int main() {

    char *nomeArquivo = "Labirintos/labirinto"; // Parte fixa do nome do arquivo
    char *extensao = ".txt"; // Extensão do arquivo
    No* nos[LINHAS][COLUNAS];
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            nos[i][j] = NULL;
        }
    }

    limparArquivo("Output/ProfundidadeOutput.txt");


    // Navegar pelos cinco labirintos
    for(int i = 1; i <= 5; i++) {
        // Converter o número inteiro para uma string
        char numero[20]; // Suponha que 20 seja um tamanho seguro para armazenar um número inteiro
        sprintf(numero, "%d", i);

        // Determinar o tamanho necessário para o nome do arquivo completo
        size_t tamanhoNomeArquivoCompleto = strlen(nomeArquivo) + strlen(numero) + strlen(extensao) + 1;
        // Alocar memória para o nome do arquivo completo
        char *nomeArquivoCompleto = (char *)malloc(tamanhoNomeArquivoCompleto);

        // Construir o nome do arquivo completo
        strcpy(nomeArquivoCompleto, nomeArquivo);
        strcat(nomeArquivoCompleto, numero);
        strcat(nomeArquivoCompleto, extensao);

        // Alocar memória para o labirinto
        char labirinto[LINHAS][COLUNAS];

        // Ler o labirinto do arquivo
        lerLabirinto(nomeArquivoCompleto, labirinto);

        // Criar o grafo a partir do labirinto
        criarGrafo(labirinto, nos);

        No *entrada = NULL;
        No *saida = NULL;
        entradaSaida(&entrada, &saida, labirinto, nos);
        
        Pilha pilha;
        inicializarPilha(&pilha);
        empilhar(&pilha, entrada);
        entrada->visistado = 1;

        buscaPorProfundidade(nos, entrada, saida, &pilha);
        escreverOutput("Output/ProfundidadeOutput.txt", pilha);

        // Liberar a memória alocada dinamicamente
        free(nomeArquivoCompleto);
        //free(numero); // Liberar a memória alocada para o número convertido
    }

    return 0;
}
