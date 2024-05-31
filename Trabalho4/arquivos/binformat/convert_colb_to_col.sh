#!/bin/bash

# Caminho para a pasta contendo os arquivos .col.b
folder="../instances/"

# Loop pelos arquivos .col.b na pasta
for file in "$folder"/*.col.b; do
    # Verifica se o arquivo existe
    if [ -f "$file" ]; then
        # Remove a extensão .col.b do nome do arquivo
        filename=$(basename "$file" .col.b)
        # Converte o arquivo para o formato .col
        ./bin2asc "$file" "$folder/$filename.col"
    fi
done

echo "Conversão concluída."
