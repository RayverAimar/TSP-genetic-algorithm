import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt

N_NODES = 26
INF = 1e7

vertices = [chr(e + 65) for e in range(N_NODES)]

def get_pos():

    df = pd.read_csv("../datasets/coords.csv", index_col = None)

    coords = []
    cur_letter = 65
    for i in df.index:
        coords.append([chr(cur_letter), (df["x"][i], df["y"][i])])
        cur_letter = cur_letter + 1
    pos = dict(coords)

    return pos

def get_adj_matrix():

    df = pd.read_csv("../datasets/adj_matrix.csv", index_col = None)
    
    adj_matrix = []

    for i in df.index:
        row = []
        for j in df.columns:
            row.append(df[j][i])
        adj_matrix.append(row)

    return adj_matrix

def get_edges():
    
    adj_matrix = get_adj_matrix()

    edges = []

    for i in range(0, len(adj_matrix)):
        for j in range(0, len(adj_matrix[i])):
            if(adj_matrix[i][j] == 1):
                cur_edge = (vertices[i], vertices[j])
                if(not cur_edge[::-1]  in edges):
                    edges.append(cur_edge)
    return edges

if __name__ == '__main__':
    graph = nx.Graph()
    pos = get_pos()
    edges = get_edges()
    graph.add_nodes_from(vertices)
    nx.set_node_attributes(graph, pos, "pos")
    graph.add_edges_from(edges)

    nx.draw(graph, pos = pos, node_color = "#add8e6", with_labels = True)
    plt.show()