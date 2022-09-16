#ifndef __UTILS_H__
#define __UTILS_H__


#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

#define DISTANCES_PATH                      "../datasets/distances.csv"
#define N_NODES                             26
#define MAX_ITERATIONS                      500
#define INITIAL_POPULATION                  32
#define MUTATION_RATE                       0.0625
#define MAX_RANDOM_VALUE                    33554432

typedef std::vector<std::vector<float>>     FLOAT_MATRIX;
typedef std::vector<float>                  FLOAT_VECTOR;

FLOAT_MATRIX get_distances_matrix()
{
    
    FLOAT_MATRIX distances;
    
    std::ifstream file(DISTANCES_PATH);
    std::string line;

    while(std::getline(file, line))
    {
        FLOAT_VECTOR row;
        char* ptr = strtok((char*) line.c_str(), ",");
        while (ptr != NULL)  
        {  
            float number = atof(ptr);
            row.push_back(number);
            ptr = strtok (NULL, ",");
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


#endif //__UTILS_H__