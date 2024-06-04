/*
*   AEDS III - Trabalho Prático 2 - Busca Em Grafos Sem Pesos
*
*   Matrícula                               RA
*   LUCAS DOGO DE SOUZA PEZZUTO             2020.1.08.026
*   MARIA EDUARDA FABIANO PIRES             2020.1.08.019
*   MATHEUS MALVÃO BARBOSA                  2020.1.08.025
*   RYAN RODRIGUES                          2021.1.08.032
*   TIAGO COSTA SOARES                      2020.1.08.017
*
*/


#include "Estruturas/pilha.h"
#include "Estruturas/fila.h"
#include "Grafo/grafo.h"
#include "Grafo/barabasiAlbert.h"
#include "ManipularArquivos/alterarArquivos.h"
#include "ManipularArquivos/operacoes.h"
#include "ManipularArquivos/lerCol.h"

#include "Heuristicas/algoritmoConstrutivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main() {  
    srand(time(NULL));

    criarPastaSeNaoExistir("Output");
    //criarPastaSeNaoExistir("Output/grafos3color");
    //criarPastaSeNaoExistir("Output/grafos4color");
    criarPastaSeNaoExistir("Output/instances");
    criarPastaSeNaoExistir("Output/colors");

    limparArquivosNoDiretorio("Output/instances");
    limparArquivosNoDiretorio("Output/colors");

    const char *directory_path = "arquivos/instances";
    process_directory(directory_path);

    return 0;
}
