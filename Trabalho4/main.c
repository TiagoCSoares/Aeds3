/*
*   AEDS III - Trabalho Prático 4 - Heurísticas para o Problema de Coloração de Grafos
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
    criarPastaSeNaoExistir("Output/instances");
    criarPastaSeNaoExistir("Output/colors");

    limparArquivosNoDiretorio("Output/instances");
    limparArquivosNoDiretorio("Output/colors");

    const char *directory_path = "arquivos/instances";
    executarHeuristicas(directory_path);

    return 0;
}
