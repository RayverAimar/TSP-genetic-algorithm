#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <string>

#define DISTANCES_PATH "../datasets/distances.csv"
#define N_NODES 26
#define MAX_ITERATIONS 500
#define INITIAL_POPULATION 32
#define MUTATION_RATE 0.0625
#define MAX_RANDOM_VALUE 33554432

typedef std::vector<std::vector<float>> FLOAT_MATRIX;
typedef std::vector<float> FLOAT_VECTOR;
typedef std::string GENOME;
typedef std::vector<GENOME> POPULATION;

FLOAT_MATRIX get_distances_matrix()
{

    FLOAT_MATRIX distances;

    std::ifstream file(DISTANCES_PATH);
    GENOME line;

    while (std::getline(file, line))
    {
        FLOAT_VECTOR row;
        char *ptr = strtok((char *)line.c_str(), ",");
        while (ptr != NULL)
        {
            float number = atof(ptr);
            row.push_back(number);
            ptr = strtok(NULL, ",");
        }
        distances.push_back(row);
    }
    return distances;
}

char get_node_name(int id)
{
    return char(id + 65);
}

int get_node_id(char name)
{
    return int(name) - 65;
}

void export_best_path(GENOME genome)
{
    std::string name_best_path = "../datasets/nodes_best_path.csv";
    std::string name_edges = "../datasets/edges_best_path.csv";
    std::ofstream path(name_best_path);
    std::ofstream edges(name_edges);

    path << "label\n";
    edges << "from,to\n";

    for (int i = 0; i < genome.size(); i++)
    {
        path << genome[i] << "\n";
    }

    for (int i = 0; i < genome.size() - 1; i++)
    {
        edges << genome[i] << "," << genome[i + 1] << "\n";
    }

    path.close();
    edges.close();
}

void export_float_vector(FLOAT_VECTOR float_vector, std::string name)
{
    std::string path = "../datasets/" + name + ".txt";

    std::ofstream out_file(path, std::ios::out);

    out_file << "label" << '\n';
    for (int idx = 0; idx < float_vector.size(); ++idx)
    {
        out_file << float_vector[idx];

        if (idx + 1 < float_vector.size())
            out_file << '\n';
    }
}

#endif //__UTILS_H__
