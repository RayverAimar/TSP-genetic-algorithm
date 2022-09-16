import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt
from math import sqrt

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

def euclideanDistance(one, two):
    """
    Args:
        one, two -> tuple (x, y)
    Returns:
        float: Distance between those two coordinates
    """

    result = 0.0
    result += (((one[0] - two[0]) * (one[0] - two[0])) + ((one[1] - two[1]) * (one[1] - two[1])))
    return sqrt(result)


def export_distances(pos):
    """
    Args:
        pos -> dict -> tuple (x, y)
    Returns:
        None
    """
    distances = {}

    for i in range(N_NODES):
        row = []
        for j in range(N_NODES):
            distance = euclideanDistance(pos[vertices[i]], pos[vertices[j]])
            row.append(distance)
        distances[vertices[i]] = row
    df = pd.DataFrame(data=distances)
    df.to_csv('../datasets/distances.csv', index = False, header=False)


def main():
    graph = nx.Graph()
    pos = get_pos()
    edges = get_edges()
    graph.add_nodes_from(vertices)
    nx.set_node_attributes(graph, pos, "pos")
    graph.add_edges_from(edges)
    export_distances(pos=pos)

    nx.draw(graph, pos=pos, node_color = "#add8e6", with_labels = True)
    plt.show()

if __name__ == '__main__':
    main()
