#!/bin/bash

# Caminho para a pasta contendo os arquivos .col
folder="../instances/"

# Loop pelos arquivos .col na pasta./convert_col_to_colb.sh
for file in $folder/*.col; do
    # Verifica se o arquivo existe
    if [ -f "$file" ]; then
        # Remove a extensão .col do nome do arquivo
        filename=$(basename "$file" .col)
        # Converte o arquivo para o formato .col.b
        ./asc2bin "$file" "$folder/$filename.col.b"
    fi
done

echo "Conversão concluída."
