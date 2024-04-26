import os
import networkx as nx
import matplotlib.pyplot as plt

def ler_arquivo(caminho_arquivo):
    dados = []
    with open(caminho_arquivo, 'r') as arquivo:
        linhas_valores = []
        for linha in arquivo:
            valores = [float(val) for val in linha.strip().split()]
            if not valores:  # Verifica se a linha está vazia
                if linhas_valores:  # Verifica se há valores na lista atual
                    dados.append(linhas_valores)
                    linhas_valores = []  # Reinicia a lista para a próxima iteração
            else:
                linhas_valores.append(valores)
        if linhas_valores:  # Adiciona a lista final, caso ainda haja valores não adicionados
            dados.append(linhas_valores)
    return dados

# Ler dados dos arquivos
dados_closeness = ler_arquivo('Output/closeness.txt')
dados_grafos = ler_arquivo('Output/grafos.txt')

# Iterar sobre os dados para gerar e salvar as imagens dos grafos
for idx in range(10):
    # Criar o grafo
    G = nx.Graph()
    for entrada_grafo in dados_grafos[idx]:
        no = entrada_grafo[0]
        for no_adjacente in entrada_grafo[1:]:
            G.add_edge(no, no_adjacente, weight=1)

    # Extrair valores de centralidade de proximidade
    valores_closeness = {entrada[0]: entrada[1] for entrada in dados_closeness[idx]}

    # Normalizar os valores de centralidade de proximidade
    max_closeness = max(valores_closeness.values())
    min_closeness = min(valores_closeness.values())
    closeness_normalizado = {no: (valor - min_closeness) / (max_closeness - min_closeness) for no, valor in valores_closeness.items()}

    # Gerar layout
    pos = nx.kamada_kawai_layout(G)

    # Gerar cores dos nós com base na centralidade de proximidade
    cores_nos = [plt.cm.jet(1 - closeness_normalizado.get(no, 0)) for no in G.nodes()]

    # Desenhar o grafo
    plt.figure()
    nx.draw(G, pos, node_color=cores_nos, node_size=300, edge_color='black', width=2)
    plt.title(f'Grafo {idx+1}')
    
    # Salvar a imagem
    if not os.path.exists('Imagens'):
        os.makedirs('Imagens')
    plt.savefig(f'Imagens/grafo{idx}.png')
    plt.close()  # Fechar a figura para liberar memória