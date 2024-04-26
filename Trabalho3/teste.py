import networkx as nx
import matplotlib.pyplot as plt

# Exemplo de criação de um grafo
G = nx.Graph()
# Adicione vértices e arestas conforme a estrutura do seu grafo
G.add_edge('A', 'B', weight=1)
G.add_edge('B', 'C', weight=1)
G.add_edge('C', 'A', weight=1)
G.add_node('D')  # Um nó isolado

# Suponha que estes sejam os valores de centralidade normalizados
closeness = {'A': 1.0, 'B': 0.8, 'C': 0.8, 'D': 0.0}

# Mapeando os valores de centralidade para uma escala de cores
colors = [plt.cm.Blues(value) for value in closeness.values()]

# Desenhando o grafo
nx.draw(G, with_labels=True, node_color=colors, node_size=700)
plt.show()