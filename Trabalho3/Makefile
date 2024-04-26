# Nome do executável
TARGET = main

# Lista de arquivos fonte
SRCS = main.c Estruturas/fila.c Estruturas/pilha.c Grafo/grafo.c Grafo/wattsStrogatz.c Grafo/barabasiAlbert.c ManipularArquivos/alterarArquivos.c ManipularArquivos/operacoes.c

# Comando de compilação
CC = gcc

# Flags de compilação
CFLAGS = -g

# Regra padrão para compilar tudo
all: $(TARGET)

# Comando para compilar o executável
$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) -o $@ $^

# Regra para limpar os arquivos gerados
clean:
	@rm -f $(TARGET)
