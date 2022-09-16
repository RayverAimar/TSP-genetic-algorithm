#include <iostream>
#include <vector>

#include "./include/utils.h"
#include "./include/genetic.h"


FLOAT_MATRIX distances = get_distances_matrix();

int main()
{
    std::vector<string> population;
    
    for (int i = 0; i < INITIAL_POPULATION; ++i)
        population.push_back(get_individual('A'));
    
    cout << "Size: " << population.size() << '\n';
    return 0;
}