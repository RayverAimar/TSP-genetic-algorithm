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

def plot_best_path(graph, pos):
    visited_edges = []
    df = pd.read_csv("../datasets/edges_best_path.csv", index_col = None)
    for i in df.index:
        visited_edges.append((df["from"][i], df["to"][i]))
 
    nx.draw_networkx(G = graph, pos = pos, with_labels = True, edgelist = visited_edges, edge_color = "red", node_size = 400, width =3, style = "dashed")

    plt.axis("off")
    plt.title("Best Path")
    plt.show()

def plot_graphs_mins_BFV():
    means_y = []
    df_means = pd.read_csv("../datasets/means.txt", index_col = None)

    for i in df_means.index:
        means_y.append(df_means["label"][i])

    best_fitness_values_y = []
    df_best_fitness_values = pd.read_csv("../datasets/best_fitness_values.txt", index_col = None)

    for i in df_best_fitness_values.index:
        best_fitness_values_y.append(df_best_fitness_values["label"][i])

    plt.title ("Graphics TSP Genetic Algorithm")
    plt.xlabel("Iterations")
    plt.ylabel("Lengths")

    plt.plot(means_y, c = "dodgerblue", label = "Means", marker = "o")
    plt.plot(best_fitness_values_y, c = "midnightblue", label = "BFV", marker = "o")

    plt.legend(title = "Legend")

    plt.show()

def main():
    graph = nx.Graph()
    pos = get_pos()
    edges = get_edges()
    graph.add_nodes_from(vertices)
    nx.set_node_attributes(graph, pos, "pos")
    graph.add_edges_from(edges)
    #export_distances(pos=pos)
    nx.draw(graph, pos=pos, node_color = "#add8e6", with_labels = True)
    plt.title("Current Graph")
    plt.show()
    plot_best_path(graph, pos)

if __name__ == '__main__':
    main()
