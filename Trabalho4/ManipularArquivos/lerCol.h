#ifndef LERCOL_H
#define LERCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../Grafo/grafo.h"
#include "alterarArquivos.h"
#include "../Heuristicas/algoritmoConstrutivo.h"
#include "../Heuristicas/buscaLocal.h"
#include "../Heuristicas/evolutiva.h"

#define MAX_LINE_LENGTH 256


void process_file(const char *filename);

void process_directory(const char *dirpath);

#endif